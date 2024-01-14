import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.nn.init as init


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

        # Apply step function at the output
        x = torch.heaviside(x, values=torch.tensor([0.0]).to(x.device))
        return x


    def mutate(self, amount=1):
        with torch.no_grad():
            for layer in self.layers:
                layer.weight += amount * (torch.rand_like(layer.weight) * 2 - 1)
                layer.bias += amount * (torch.rand_like(layer.bias) * 2 - 1)



# class NeuralNetwork(nn.Module):
#     def __init__(self, neuronCounts, dropout_rate=0):
#         super(NeuralNetwork, self).__init__()
#         self.layers = nn.ModuleList()
#         for i in range(len(neuronCounts) - 1):
#             layer = nn.Linear(neuronCounts[i], neuronCounts[i+1])
#             init.kaiming_uniform_(layer.weight)  # He initialization
#             self.layers.append(layer)
#             if i < len(neuronCounts) - 2:  # No dropout for the output layer
#                 self.layers.append(nn.Dropout(dropout_rate))

#     def forward(self, x):
#         for layer in self.layers:
#             if isinstance(layer, nn.Linear):
#                 x = layer(x)
#                 x = F.relu(x)  # ReLU activation for linear layers
#             else:
#                 x = layer(x)  # Dropout layer
#         return torch.sigmoid(x)  
    

#     # def mutate(self, amount=1):
#     #     with torch.no_grad():
#     #         for layer in self.layers:
#     #             if hasattr(layer, 'weight') and hasattr(layer, 'bias'):
#     #                 layer.weight += amount * (torch.rand_like(layer.weight) * 2 - 1)
#     #                 layer.bias += amount * (torch.rand_like(layer.bias) * 2 - 1)

#     def mutate(self, std_dev=0.1):
#         with torch.no_grad():
#             for layer in self.layers:
#                 if hasattr(layer, 'weight'):
#                     noise = torch.randn_like(layer.weight) * std_dev
#                     layer.weight += noise
#                 if hasattr(layer, 'bias'):
#                     noise = torch.randn_like(layer.bias) * std_dev
#                     layer.bias += noise

#     # def mutate(self, std_dev=0.01, mutation_rate=0.1):
#     #     with torch.no_grad():
#     #         for layer in self.layers:
#     #             if hasattr(layer, 'weight'):
#     #                 mask = torch.rand_like(layer.weight) < mutation_rate
#     #                 noise = torch.randn_like(layer.weight) * std_dev
#     #                 layer.weight += mask * noise
#     #             if hasattr(layer, 'bias'):
#     #                 mask = torch.rand_like(layer.bias) < mutation_rate
#     #                 noise = torch.randn_like(layer.bias) * std_dev
#     #                 layer.bias += mask * noise


