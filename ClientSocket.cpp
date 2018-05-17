#include "ClientSocket.hpp"
#include "Constants.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <strings.h>
#include <cstring>
#include <cerrno>
#include <cstdio>

#include <endian.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

void ClientSocket::terminateProgram(std::string msg) {
    std::cout << "Error: " << msg << std::endl;
    perror("");
    exit(EXIT_FAILURE);
}

ClientSocket::ClientSocket(const char *addr, int port) {

    _addr_info = new struct sockaddr_in();

    _addr_info->sin_family = AF_INET;
    _addr_info->sin_port = htons(port);

    if (inet_addr(addr) == -1) {
        struct hostent *he;
        struct in_addr **addr_list;

        if ((he = gethostbyname(addr)) == NULL) { terminateProgram("Failed to resolve hostname"); }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **)he->h_addr_list;

        for (int i = 0; addr_list[i] != NULL; i++) {
            _addr_info->sin_addr = *addr_list[i];
            std::cout << addr << " resolved to " << inet_ntoa(*addr_list[i]) << std::endl;
            break;
        }
    } else {
        _addr_info->sin_addr.s_addr = inet_addr(addr);
    }
}

void ClientSocket::connectToServer(){

    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd < 0) { terminateProgram("Socket not created"); }

    if (connect(_fd, (struct sockaddr *)_addr_info, sizeof(struct sockaddr_in)) < 0) {
        terminateProgram("connect failed");
    }

    std::cout << "Connected\n";
}

uint64_t ClientSocket::receiveChallenge() const {
    char buffer[12];

    if( recv(_fd , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("recv failed");
    }

    int16_t* s = new int16_t;
    memcpy(s, buffer, 2);
    uint16_t size_data = ntohs(*s);
    if(size_data != 12) terminateProgram("Lose primljena poruka");

    memcpy(s, buffer + 2, 2);
    uint16_t enroll_data = ntohs(*s);
    if(enroll_data != ENROLL_INIT) terminateProgram("Lose primljena poruka");
    delete s;

    uint64_t a;
    memcpy(&a, buffer + 4, 8);

    return a;
}

// big endian is network byte order
bool ClientSocket::sendEnrollRegistration(uint64_t challenge, uint64_t nonce) const {

    uint16_t buffer_size =  24 + INFO.size(); // 2 + 2 + 8 + 2 + 2 + 8 + INFO.length();
    uint8_t buffer[buffer_size];

    uint16_t tmp16 = htons(buffer_size);
    memcpy(buffer, &tmp16, 2);

    tmp16 = htons(ENROLL_REGISTER);
    memcpy(buffer + 2, &tmp16, 2);

    memcpy(buffer + 4, &challenge, 8);

    memcpy(buffer + 12, &TEAM_RANDOM, 2);
    memcpy(buffer + 14, &PROJECT, 2);

    memcpy(buffer + 16, &nonce, 8);

    memcpy(buffer + 24, INFO_C, strlen(INFO_C));

    if( send(_fd , buffer , buffer_size , 0) <= 0)
    {
        std::cout << "Send failed" << std::endl;
        return false;
    }

    std::cout <<"Data send\n" << std::endl;
    return true;
}

bool ClientSocket::receiveAnswer() const{

    char buffer[48];
    std::string reply;

    uint8_t d;
    if( (d = recv(_fd , buffer , sizeof(buffer) , 0)) < 0)
    {
        puts("recv failed");
    }

    if (d == 0){
        std::cout << "Connection closed" << std::endl;
        return false;
    }

    int16_t * s = new int16_t;

    memcpy(s, buffer, 2);
    uint16_t size_data = ntohs(*s);

    memcpy(s, buffer + 2, 2);
    uint16_t enroll_data = ntohs(*s);

    memcpy(s, buffer + 4, 2);
    uint16_t reserved = ntohs(*s);

    memcpy(s, buffer + 6, 2);
    uint16_t team_or_error = ntohs(*s);

    delete s;

    std::cout << "reserved: " << reserved << std::endl;
    if (enroll_data == ENROLL_FAILURE){

        char por[size_data - 8];
        memcpy(por, buffer + 8, size_data - 8);
        std::cout << "Kod: " << team_or_error << " Greska: " <<  por <<std::endl;

        return false;
    } else if (enroll_data == ENROLL_SUCCESS){
        std::cout << "Registrovan, team number: " << team_or_error << std::endl;
        return true;
    }
}

ClientSocket::~ClientSocket() {
    delete _addr_info;
}