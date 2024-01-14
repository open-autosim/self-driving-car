#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
    Server(int port);
    ~Server();

    void initServer();
    void waitForConnection();
    void sendData(const std::string& data);
    char* receiveData();
    void closeServer();

private:
    int server_fd, new_socket;
    int port;
};

#endif // SERVER_H