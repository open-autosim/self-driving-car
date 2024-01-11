import socket
import struct
import json


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

# Send and receive messages in a loop
while True:
    # Send a message to the server
    controls = {
        "forward": True,
        "left": True,
        "right": False,
        "reverse": False
    }

    # Convert the controls to a JSON string
    json_controls = json.dumps(controls)

    # Send the JSON string to the server
    send_data(client_socket, json_controls)

    # Receive a response from the server and process it
    response = receive_data(client_socket)
    if response:
        print("Received:", response)

    # Add any necessary conditions to break the loop
    # For example, if a specific message is received, break the loop
    if response == 'exit':
        break

# Close the connection
client_socket.close()

