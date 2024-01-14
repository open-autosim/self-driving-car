from client import Client

if __name__ == "__main__":
    
    client = Client()
    try:
        client.run()
    finally:
        client.close()