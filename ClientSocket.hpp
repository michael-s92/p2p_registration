#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include <string>

class ClientSocket {
    private:
    int _fd;
    struct sockaddr_in* _addr_info = 0;

    static void terminateProgram(std::string msg);

    public:
    ClientSocket(const char* addr, int port);
    void connectToServer();
    uint64_t receiveChallenge() const;
    bool sendEnrollRegistration(uint64_t ch, uint64_t nonce) const;
    bool receiveAnswer() const;
    ~ClientSocket();

};

#endif