#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

class Server {
public:
    Server(int port);
    ~Server();

    void initServer();
    void waitForConnection();
    void sendData(const char* data);
    char* receiveData();
    void closeServer();

private:
    int port;
    int server_fd;
    int new_socket;
};

#endif // SERVER_H
