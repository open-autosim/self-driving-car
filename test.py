import socket
import json
import select

class CarClient:
    def __init__(self, host='127.0.0.1', port=8080):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.host = host
        self.port = port
        self.client_socket.connect((host, port))

    def send_data(self, data):
        data_size = str(len(data))  # Get the size of the data as a string
        self.client_socket.sendall(data_size.encode())  # Send the size first
        self.client_socket.sendall(data.encode())  # Send the data

    def receive_data(self):
        ready = select.select([self.client_socket], [], [], 5)  # Wait for up to 5 seconds
        if ready[0]:
            data_size = int(self.client_socket.recv(1024).decode())  # Receive the size
            data = self.client_socket.recv(data_size).decode()  # Receive the data
            return data
        else:
            return "No data received within the timeout."

    def close_connection(self):
        self.client_socket.close()

# Example usage
client = CarClient()

# response = client.receive_data()
# print("Received from server:", response)

# Create JSON data with field controls and inner fields [forward, reverse, left, right]
data = {
    "controls": {
        "forward": "true",
        "reverse": "false",
        "left": "false",
        "right": "false"
    }
}

# Convert the data to JSON string
json_data = json.dumps(data)
client.send_data(json_data)

client.close_connection()
