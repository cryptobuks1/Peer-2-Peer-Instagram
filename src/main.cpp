#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"

using namespace std;


int main(int argc,char **argv){  
      
    if(strcmp(argv[3], "client") == 0){ // equal doesn't work
        Client * c = new Client(argv[2], argv[1]);
        /*if (argc > 4){
           // client load <num_reqs>
           int num_req = atoi(argv[5]);
           varyLoad(c,num_req);
        }
        else*/
          c->executePrompt();

    }
    else if(strcmp(argv[3], "server") == 0){
        Server* s = new Server(argv[2], argv[1]);
        /*if(argc > 4){
           // server buffer <buff_size>
           int buff_size = atoi(argv[5]);
           varyBuffSize(s,buff_size); 
        }*/
        s->serveRequest();
    }
    else {;
    }
    return 0;
}

