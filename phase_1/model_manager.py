import os
import torch
import copy
import json
from typing import Dict, List, Optional
import network as nn  # Assuming NeuralNetwork is defined in 'network.py'

class ModelManager:
    def __init__(self, model_save_path="./saved_models", min_y_values_save_path="./min_y_values.json"):
        self.model_save_path = model_save_path
        self.min_y_values_save_path = min_y_values_save_path
        os.makedirs(self.model_save_path, exist_ok=True)
        self.networks = {}
        self.default_neuron_counts = [5, 6, 4]
        self.min_y_values = self._load_min_y_values()
        self.load_best_models()


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
            self.networks[car_id] = copy.deepcopy(best_model)

            if car_id != best_model_index:
                self.networks[car_id].mutate(0.1)

    def save_model(self, car_id, model, y_value):

        car_id_str = str(car_id)  # Convert car_id to string
        model_path = os.path.join(self.model_save_path, str(car_id_str))
        
        # Save the model
        try:
            torch.save(model, model_path)
        except Exception as e:
            print(f"Error saving model: {e}")
            return

        # Check if car_id_str is already in the min_y_values and update if necessary
        if car_id_str in self.min_y_values:
            # Update if the new y value is better
            if y_value < self.min_y_values[car_id_str]:
                self.min_y_values[car_id_str] = y_value
        else:
            # If car_id_str is not present, add it
            self.min_y_values[car_id_str] = y_value

    def get_or_create_network(self, car_id, neuron_counts=None):
        
        car_id_str = str(car_id)  # Convert car_id to string
        
        if car_id_str not in self.networks:
            self.networks[car_id_str] = nn.NeuralNetwork(neuron_counts or self.default_neuron_counts)

        return self.networks[car_id_str]