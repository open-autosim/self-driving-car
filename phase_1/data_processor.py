import torch

class DataProcessor:

    def process_sensor_data(self, sensors):
        processed_sensors = [float(sensor) if sensor is not None else 0.0 for sensor in sensors]
        return torch.tensor(processed_sensors, dtype=torch.float32)
    
    # def compute_network_output(self, car_id, network_inputs, network):

    #     return network(network_inputs)

    def compute_network_output(self, car_id, network_inputs, network):
        network_inputs = network_inputs.unsqueeze(0)  # Add a batch dimension
        network_outputs = network(network_inputs)
        thresholded_outputs = (network_outputs > 0.5).int()
        return thresholded_outputs.squeeze(0) 
    
    def determine_controls(self, network_outputs):

        return {
            "forward": int(network_outputs[0].item()),
            "left": int(network_outputs[1].item()),
            "right": int(network_outputs[2].item()),
            "reverse": int(network_outputs[3].item())
        }


    
