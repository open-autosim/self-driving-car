import json
from network_client import NetworkClient
from model_manager import ModelManager
from data_processor import DataProcessor


class Client:
    def __init__(self):
        self.network_client = NetworkClient('127.0.0.1', 8080)
        self.model_manager = ModelManager()
        self.data_processor = DataProcessor()


    def run(self):

        while True:
            try:
                response = self.network_client.receive_data()
                if response is None or response == 'exit':
                    break

                response_dict = json.loads(response)
                car_id = int(response_dict.get("id"))
                sensors = response_dict.get("sensor_readings")
                y_value = float(response_dict.get("position", [0, 0])[1])

                # Ensure a network is created for this car_id
                network = self.model_manager.get_or_create_network(car_id)

                # Process sensor data and compute network output
                network_inputs = self.data_processor.process_sensor_data(sensors)
                network_outputs = self.data_processor.compute_network_output(car_id, network_inputs, network)
                controls = self.data_processor.determine_controls(network_outputs)

                # Update and save the model if necessary
                # Now the save_model method itself will decide whether to save or not
            
                if y_value < self.model_manager.min_y_values.get(str(car_id), float('inf')):
                    self.model_manager.save_model(car_id, self.model_manager.networks[str(car_id)], y_value)

                # Send controls back
                json_controls = json.dumps({"id": car_id, "controls": controls})
                self.network_client.send_data(json_controls)
            
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON: {e}")
            except Exception as e:
                print(f"Error: {e}")
                break  # or continue based on desired behavior on exception


if __name__ == "__main__":
    
    client = Client()
    try:
        client.run()
    finally:
        # client.network_client.close(client.model_manager.min_y_values_save_path, client.model_manager.min_y_values)
        client.network_client.close(client.model_manager.min_y_values_save_path, client.model_manager.min_y_values)