// Server side C/C++ program to demonstrate Socket programming

/* TO DO
 * otwieranie wielu portw dla wielu polaczen - done
 * przesyanie wiadomo.sci midzy kliebtami
 * polaczenie z baza danych
 * weryfikacja uzytkownikow
 * zapisywanie wiadomosci
 * tworzenie pokoi
 */

#include "Klasy/ReceiveAndResend.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "pthread.h"

#define PORT 2137
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100
#define MAXSOCK 70000

void *connection_handler(void *);

int main()
{
    int sockfd; //to create socket
    int socket_desc, new_socket, *new_sock;
    struct sockaddr_in serverAddress; //client will connect on this

    char msg1[MAXSZ];
    char msg2[MAXSZ];
    int NoOfClients = MAXSOCK;
    memset(msg2,0,100);
    void *ret;

    json test;
    test["id"] = 3;
    test["authorId"] = 1;
    test["groupId"] = 2;

    ReceiveAndResend testClass = ReceiveAndResend(test.dump());

    json result = testClass.getResult();

    string wyniki =  result.dump();



    struct sockaddr_in server =
            {
                    .sin_family = AF_INET,
                    .sin_port = htons( PORT )
            };
    if(inet_pton( AF_INET, SERVER_IP, & server.sin_addr ) <= 0 )
    {
        perror( "inet_pton() ERROR" );
        exit( 1 );
    }

    const int socket_ = socket( AF_INET, SOCK_STREAM, 0 );
    if( socket_ < 0 )
    {
        perror( "socket() ERROR" );
        exit( 2 );
    }

    socklen_t len = sizeof( server );
    if(bind(socket_, ( struct sockaddr * ) & server, len ) < 0 )
    {
        perror( "bind() ERROR" );
        exit( 3 );
    }

    if( listen( socket_, MAXSOCK ) < 0 )
    {
        perror( "listen() ERROR" );
        exit( 4 );
    }

    for(int i =0; i < MAXSOCK; i++)
    {
        printf( "Waiting for connection...\n" );

        struct sockaddr_in client = { };

        const int clientSocket = accept( socket_,( struct sockaddr * ) & client, & len );
        if( clientSocket < 0 )
        {
            perror( "accept() ERROR" );
            continue;
        }
            //new_socket = connect(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

            printf("new socket connected= %d", new_socket);

            pthread_t sniffer_thread[MAXSOCK];
            new_sock = (int *) malloc(sizeof(int));
            *new_sock = clientSocket;
            int p = -1;
            p = pthread_create(&sniffer_thread[i], NULL, connection_handler, (void *) new_sock);
            if (p < 0) {
                perror("could not create thread");
                return 1;
            }
            p = pthread_join(sniffer_thread[i], &ret);
            if (p < 0) {
                std::cout << "Unable to join" << std::endl;

            }
        }

    return 0;
}
/*
 * This will handle connection for each client
 * */


std::string clearMessage(char *message){
    bool end = false;
    for(int i = 0; i < strlen(message); i++)
    {
        if(end){
            message[i] = '\0';
        }
        if(message[i] == '}'){
            end = true;
        }
    }
    std::string mess = message;
    return mess;
}

void *connection_handler(void *socket_desc) {
    //Get the socket descriptor
    int sock = *(int *) socket_desc;
    char message[1024];
    int read_size;
    json messageJson;

    int userID;

    printf("we are in connection handler");

    if (read(sock, message, 1024) > 0) {//TO DO sprawdzenie odebrania;
        std::string mess = clearMessage(message);
        mess.resize(mess.size(), 5);
        ReceiveAndResend receive = ReceiveAndResend(mess);
        messageJson = receive.getResult();
        write(sock, messageJson.dump().c_str(), strlen(messageJson.dump().c_str()));
    } else {
        //Free the socket pointer
        close(sock);
        free(socket_desc);

        return 0;
    }
}