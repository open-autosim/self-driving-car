import socket
import struct
import json
import torch
import network as nn

class Client:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect(('127.0.0.1', 8080))
        self.networks = {}
        self.default_neuron_counts = [5, 6, 4]

    def send_data(self, message):
    # Encode the message to bytes, prepare header
        encoded_message = message.encode()
        message_length = len(encoded_message)
        header = struct.pack('I', message_length)

        # Send the header followed by the actual message
        self.client_socket.sendall(header)
        self.client_socket.sendall(encoded_message)

    def receive_data(self):
        # Receive the length of the data (4 bytes for uint32_t)
        data_length_bytes = self.client_socket.recv(4)
        if not data_length_bytes:
            return None
        data_length = struct.unpack('I', data_length_bytes)[0]

        # Now receive the actual data
        data = b''
        while len(data) < data_length:
            packet = self.client_socket.recv(data_length - len(data))
            if not packet:
                return None
            data += packet

        return data.decode()
    
    def get_or_create_network(self, car_id, neuron_counts=None):
        if car_id not in self.networks:
            if neuron_counts is None:
                neuron_counts = self.default_neuron_counts
            self.networks[car_id] = nn.NeuralNetwork(neuron_counts)
        return self.networks[car_id]

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
            response = self.receive_data()
            if response is None or response == 'exit':
                break

            response_dict = json.loads(response)
            car_id = response_dict["id"]  # Make sure to get the car_id correctly from the response
            sensors = response_dict["sensor_readings"]

            network_inputs = self.process_sensor_data(sensors)
            network_outputs = self.compute_network_output(car_id, network_inputs)  # Pass car_id along with network_inputs
            controls = self.determine_controls(network_outputs)

            json_controls = json.dumps({"id": car_id, "controls": controls})
            self.send_data(json_controls)


    def close(self):
        self.client_socket.close()