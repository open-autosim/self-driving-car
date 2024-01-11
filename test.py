import socket
import json

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
        data_size = int(self.client_socket.recv(1024).decode())  # Receive the size
        data = self.client_socket.recv(data_size).decode()  # Receive the data
        return data

    def close_connection(self):
        self.client_socket.close()

# Example usage
client = CarClient()
client.send_data("Hello from Python!")
response = client.receive_data()
print("Received from server:", response)





# Example usage

client.send_data(json_data)
response = client.receive_data()
print("Received from server:", response)
client.close_connection()



