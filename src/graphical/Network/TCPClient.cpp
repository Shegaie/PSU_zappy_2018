/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/

#include <zconf.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include "TCPClient.hpp"

TCPClient::TCPClient()
{
    fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
    fdPtr = fdopen(fd, "r");
}

TCPClient::~TCPClient()
{
    close(fd);
}

int TCPClient::connectTo(std::string serverIp, int port)
{
    struct sockaddr_in client_addr {};

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr = (struct in_addr){inet_addr(serverIp.c_str())};
    if (connect(fd, (const struct sockaddr*)&client_addr, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        exit(84);
    }
    return 0;
}

int TCPClient::sendMessage(std::string message)
{
    if(send(fd, message.c_str(), message.size(), 0) == -1) {
        perror("send");
        exit(84);
    }
    return 0;
}

std::string TCPClient::getMessage()
{
    char *buffer = nullptr;
    size_t i = 0;
    std::string message;

    getline(&buffer, &i, fdPtr);
    message = std::string(buffer);
    return message;
}

FILE *TCPClient::getFdPtr() const
{
    return fdPtr;
}

