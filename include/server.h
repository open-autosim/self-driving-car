#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <zmq.hpp>

class Server {
public:
    Server(int port);
    ~Server();

    void initServer();
    void sendData(const std::string& data);
    std::string receiveData();
    void closeServer();
    char* receiveData2();

private:
    int port;
    zmq::context_t context;
    zmq::socket_t socket;
};

#endif // SERVER_H