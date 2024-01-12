import socket
import struct
import json
import torch
import network as nn
import os
import logging
from typing import Dict, List, Optional
import signal
import sys


class Client:
    def __init__(self, server_address: str = '127.0.0.1', port: int = 8080):
        self.model_save_path = "./saved_models"
        self.min_y_values_save_path = "./min_y_values.json"
        os.makedirs(self.model_save_path, exist_ok=True)

        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((server_address, port))
        self.networks: Dict[str, nn.NeuralNetwork] = {}
        self.default_neuron_counts = [5, 6, 4]
        self.min_y_values = self._load_min_y_values()

        self.load_best_models()

        signal.signal(signal.SIGINT, self.signal_handler)


    def _load_min_y_values(self) -> Dict[str, float]:
        try:
            with open(self.min_y_values_save_path, "r") as file:
                return json.load(file)
        except FileNotFoundError:
            return {}

    def load_best_models(self):
        
        if not self.min_y_values:
            print("No min y values available to determine the best model.")
            return
        
        best_model_index = min(self.min_y_values, key=self.min_y_values.get)
        print(f"Loading best model {best_model_index} for all cars.")

        best_model = torch.load(os.path.join(self.model_save_path, best_model_index))

        for car_id in self.min_y_values.keys():
            self.networks[car_id] = best_model

    def save_model(self, car_id, model, y_value):

        car_id_str = str(car_id)  # Convert car_id to string
        model_path = os.path.join(self.model_save_path, str(car_id_str))
        
        # Save the model
        try:
            torch.save(model, model_path)
        except Exception as e:
            logging.error(f"Error saving model for car {car_id_str}: {e}")
            return

        # Check if car_id_str is already in the min_y_values and update if necessary
        if car_id_str in self.min_y_values:
            # Update if the new y value is better
            if y_value < self.min_y_values[car_id_str]:
                self.min_y_values[car_id_str] = y_value
        else:
            # If car_id_str is not present, add it
            self.min_y_values[car_id_str] = y_value


    def send_data(self, message):
        try:
            encoded_message = message.encode()
            message_length = len(encoded_message)
            header = struct.pack('I', message_length)

            # Send the header followed by the actual message
            self.client_socket.sendall(header)
            self.client_socket.sendall(encoded_message)
        except Exception as e:
            print(f"Error sending data: {e}")
            self.close()
            return

    def receive_data(self):
        try:
            data_length_bytes = self.client_socket.recv(4)
            if not data_length_bytes:
                return None
            data_length = struct.unpack('I', data_length_bytes)[0]

            data = b''
            while len(data) < data_length:
                packet = self.client_socket.recv(data_length - len(data))
                if not packet:
                    return None
                data += packet

            return data.decode()
        except Exception as e:
            print(f"Error receiving data: {e}")
            self.close()
            return None

    def close(self):
        print("Closing client socket")
        if self.client_socket:
            self.client_socket.close()
            self.client_socket = None

        # Save the min_y_values to the JSON file upon closing
        try:
            with open(self.min_y_values_save_path, "w") as min_y_values_json:
                json.dump(self.min_y_values, min_y_values_json, indent=4)
            print(f"min_y_values saved to {self.min_y_values_save_path}")
        except IOError as e:
            logging.error(f"Error writing min y values to file: {e}")
    
    def get_or_create_network(self, car_id, neuron_counts=None):
        
        car_id_str = str(car_id)  # Convert car_id to string
        
        if car_id_str not in self.networks:
            self.networks[car_id_str] = nn.NeuralNetwork(neuron_counts or self.default_neuron_counts)
            print(f"Created new network for car {car_id_str} with neuron counts {neuron_counts or self.default_neuron_counts}")

        return self.networks[car_id_str]

    def compute_network_output(self, car_id, network_inputs):

        network = self.get_or_create_network(car_id)
        return network(network_inputs)
    
    def process_sensor_data(self, sensors):

        processed_sensors = [float(sensor) if sensor is not None else 0.0 for sensor in sensors]
        return torch.tensor(processed_sensors, dtype=torch.float32)


    def determine_controls(self, network_outputs):

        return {
            "forward": int(network_outputs[0].item()),
            "left": int(network_outputs[1].item()),
            "right": int(network_outputs[2].item()),
            "reverse": int(network_outputs[3].item())
        }


    def run(self):
        while True:
            try:
                response = self.receive_data()
                if response is None or response == 'exit':
                    logging.info("Exiting the main loop.")
                    break

                response_dict = json.loads(response)
                car_id = int(response_dict.get("id"))
                sensors = response_dict.get("sensor_readings")
                y_value = float(response_dict.get("position", [0, 0])[1])

                # Ensure a network is created for this car_id
                self.get_or_create_network(car_id)

                # Process sensor data and compute network output
                network_inputs = self.process_sensor_data(sensors)
                network_outputs = self.compute_network_output(car_id, network_inputs)
                controls = self.determine_controls(network_outputs)

                # Update and save the model if necessary
                # Now the save_model method itself will decide whether to save or not
                if y_value < self.min_y_values.get(str(car_id), float('inf')):
                    self.save_model(car_id, self.networks[str(car_id)], y_value)

                # Send controls back
                json_controls = json.dumps({"id": car_id, "controls": controls})
                self.send_data(json_controls)
            
            except json.JSONDecodeError as e:
                logging.error(f"JSON decoding error: {e}")
            except Exception as e:
                logging.error(f"Unexpected error: {e}")
                break  # or continue based on desired behavior on exception



    def signal_handler(self, sig, frame):
        print('You pressed Ctrl+C! Cleaning up...')
        sys.exit(0)