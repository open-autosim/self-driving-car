import socket   
import struct
import json


class NetworkClient:
    
    def __init__(self, server_address='127.0.0.1', port=8080):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((server_address, port))

    def send_data(self, message):
        try:
            encoded_message = message.encode()
            message_length = len(encoded_message)
            header = struct.pack('I', message_length)

            # Send the header followed by the actual message
            self.client_socket.sendall(header)
            self.client_socket.sendall(encoded_message)
        except Exception as e:
            print(f"Error sending data: {e}")
            self.close()
            return

    def receive_data(self):
        try:
            data_length_bytes = self.client_socket.recv(4)
            if not data_length_bytes:
                return None
            data_length = struct.unpack('I', data_length_bytes)[0]

            data = b''
            while len(data) < data_length:
                packet = self.client_socket.recv(data_length - len(data))
                if not packet:
                    return None
                data += packet

            # print(f"Received data: {data}")

            return data.decode()
        except Exception as e:
            print(f"Error receiving data: {e}")
            self.close()
            return None
        
        
    def close(self, min_y_values_save_path, min_y_values):
        print("Closing client socket")
        if self.client_socket:
            self.client_socket.close()
            self.client_socket = None

        # Save the min_y_values to the JSON file upon closing
        try:
            with open(min_y_values_save_path, "w") as min_y_values_json:
                json.dump(min_y_values, min_y_values_json, indent=4)
            print(f"min_y_values saved to {min_y_values_save_path}")
            print(f'new minimum value set for car { min(min_y_values, key=min_y_values.get) }')
        except IOError as e:
            print(f"Error writing min y values to file: {e}")

    