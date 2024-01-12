import socket
import struct
import json
import network as nn
import torch


network = nn.NeuralNetwork([5, 6, 4])


def send_data(sock, message):
    # Encode the message to bytes, prepare header
    encoded_message = message.encode()
    message_length = len(encoded_message)
    header = struct.pack('I', message_length)

    # Send the header followed by the actual message
    sock.sendall(header)
    sock.sendall(encoded_message)

def receive_data(sock):
    # Receive the length of the data (4 bytes for uint32_t)
    data_length_bytes = sock.recv(4)
    if not data_length_bytes:
        return None
    data_length = struct.unpack('I', data_length_bytes)[0]

    # Now receive the actual data
    data = b''
    while len(data) < data_length:
        packet = sock.recv(data_length - len(data))
        if not packet:
            return None
        data += packet

    return data.decode()

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
client_socket.connect(('127.0.0.1', 8080))

while True:

    # Receive a response from the server and process it
    response = receive_data(client_socket)
    # if response:
    #     print("Received:", response)

    response_dict = json.loads(response)
    id = response_dict["id"]
    sensors = response_dict["sensor_readings"]

    for i in range(len(sensors)):
        if sensors[i] is not None:
            sensors[i] = float(sensors[i])
        else:
            sensors[i] = 0.0  

    network_inputs = torch.tensor(sensors, dtype=torch.float32)
    network_outputs = network(network_inputs)


    print(network_outputs)

    controls = {
        "forward": int(network_outputs[0].item() > -0.5),
        "left": int(network_outputs[1].item() > 0.5),
        "right": int(network_outputs[2].item() > 0.5),  # Assuming index 2 for 'right'
        "reverse": int(network_outputs[3].item() > 0.5)  # Assuming index 3 for 'reverse'
    }

    # Convert the id and controls to a JSON string
    json_controls = json.dumps({
        "id": id,
        "controls": controls
    })

    # Send the JSON string to the server
    send_data(client_socket, json_controls)

    # Add any necessary conditions to break the loop
    # For example, if a specific message is received, break the loop
    if response == 'exit':
        break

# Close the connection
client_socket.close()

