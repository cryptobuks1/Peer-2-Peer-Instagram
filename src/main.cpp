#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/DoS.h"
#include "../headers/Communication.h"
#include "../headers/Stego.h"

using namespace std;

#define NUM_THREADS 2
const char* hostname ;
const char* port ;

void *client_thread(void *threadid) {
    Client * c = new Client(hostname, port);
    c->executePrompt();
}

void *server_thread(void *threadid) {
    Server* s = new Server(hostname, port);
    s->serveRequest();
}


int main(int argc,char **argv){  
    int rc;
    
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
    else if(strcmp(argv[3], "server") == 0)
    {
        rc = pthread_create(&threads[1], NULL, server_thread, (void *) 1);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
        pthread_exit(NULL);
    }
    else {// DoS
        /*
         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
         */
        const char* auth_port = argv[1];
        const char* login_port = argv[2];
        const char* ip = argv[3];

        bool client_tst = true;
        if (client_tst) {
            auto com = new Communication();
            com->sendMsg(ip, stoi(auth_port), "Mazen/123");
            com->sendMsg(ip, stoi(login_port), "Mazen/123");
        }
        else {
            auto dos = new DoS(ip, stoi(auth_port), stoi(login_port));
            dos->runAuthThread();
            dos->runLoginThread();
            dos->join();
        }
    }
    return 0;
}

