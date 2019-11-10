#include "../headers/Server.h"



Server::Server(const char * hostname, const char * port){
    this->port = port ;
    this->hostname = hostname ;
    std::string serverIp = hostname_to_ip((char *)hostname);
    reqReply = new RequestReply(port, serverIp.c_str(), false, 1024);
}
void Server::setBufferSize(int size){
    /*delete buffer;
    buffer = new char [buff_size];
    reqReply->setBuffSize(buff_size);*/
}

void Server::serveRequest(){

//    printf("Enter Image Path:");
//    scanf("%s", buffer );
//
//  reqReply->doOperation(buffer);

    reqReply->getReq(reqNum);
    printf("Request Number: %i\n", reqNum);

    switch (reqNum)
    {
        case 0:{ //Samples
            for (int i=1 ;i<4 ;i++) {
                string s= "/Users/owner/CLionProjects/Distributed-Server/imag"+ to_string(i) + ".jpg" ;
                reqReply->doOperation(s);
            }


            break;
        }

    }
}

Server::~Server(){
    reqReply->shutDownFD();

}