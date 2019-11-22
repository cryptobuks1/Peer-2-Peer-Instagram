//
// Created by Mazen on 16.11.19.
//

#ifndef DISTRIBUTEDC_COMMUNICATION_H
#define DISTRIBUTEDC_COMMUNICATION_H

#include <netinet/in.h>
#include <printf.h>
#include <arpa/inet.h>
#include <cstring>
#include <zconf.h>
#include <cstdlib>
#include <cmath>
#include "Message.h"

class Communication {
private:

    struct Transaction{
        int server_fd;
        sockaddr_in address;
    };


    int sock;
    // Imaging using ReqReply
    int socketfd;
    struct sockaddr_in peerAddr;
    struct hostent * peer;
    long stat, read_size, total_size;
    char send_buffer[1024];

public:
    Communication();


    Transaction authTx;
    Transaction loginTx;

    void reset();
    Transaction init_socket(const char *LISTEN_IP, int LISTEN_PORT);
    int init_imaging_socket(std::string dest_ip);
    int listenTx(Communication::Transaction tx, char* req);

    char* sendMsg(const char * IP, int PORT, char* msg);

    Message buildImageMsg(int image_id, std::string owner_ip, std::string owner_name);
    int getImage(Message & m);
    int sendImage(Message &m);

    // Attempt
    int sendReply(Message & m, std::string destIp);
    int getReply(Message & m, const char *listenerIP) ;
};


#endif //DISTRIBUTEDC_COMMUNICATION_H
