import torch
import torch.nn as nn
import torch.nn.functional as F

class NeuralNetwork(nn.Module):
    def __init__(self, neuronCounts):
        super(NeuralNetwork, self).__init__()
        self.layers = nn.ModuleList()
        for i in range(len(neuronCounts) - 1):
            self.layers.append(nn.Linear(neuronCounts[i], neuronCounts[i+1]))

    def forward(self, x):
        for i, layer in enumerate(self.layers):
            x = layer(x)
            if i < len(self.layers) - 1:
                x = F.relu(x)  # using ReLU activation for hidden layers
        return x

    def mutate(self, amount=1):
        with torch.no_grad():
            for layer in self.layers:
                layer.weight += amount * (torch.rand_like(layer.weight) * 2 - 1)
                layer.bias += amount * (torch.rand_like(layer.bias) * 2 - 1)

# Example usage
# neuronCounts = [5, 6, 4]  # Define your network structure
# network = NeuralNetwork(neuronCounts)

# # Example forward pass with random inputs
# inputs = torch.rand(10)  # Random input tensor
# outputs = network(inputs)

# # Mutate the network
# network.mutate(amount=0.1)
