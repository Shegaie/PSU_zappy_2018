/*
** EPITECH PROJECT, 2022
** graphical
** File description:
** Created by lgregoire,
*/
#ifndef GRAPHICAL_TCPCLIENT_HPP
#define GRAPHICAL_TCPCLIENT_HPP

#include <string>
#include <memory>

class TCPClient
{
    public:
        TCPClient();
        ~TCPClient();

        int connectTo(std::string serverIp, int port);
        int sendMessage(std::string message);
        std::string getMessage();
    private:
        int fd;
        FILE *fdPtr;
    public:
    FILE *getFdPtr() const;
};


#endif //GRAPHICAL_TCPCLIENT_HPP
