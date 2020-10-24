#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <thread>
#include "TCPSerCli.h"

using namespace std;


// Constructor
TCPClient::TCPClient(char *hostName, int port, char *nodeNumber, char *Neighbor) : hostName(hostName), port(port), myNodeNumber(nodeNumber), oneNeighbor(Neighbor){};

// ClientSetup
void TCPClient::clientSetup()

{
    //Initializing neighbors
    mylock.lock();
    string oneHop(oneNeighbor);
    if(neighbors.size() == 0){
        neighbors.push_back(oneHop); 
    }else{
        neighbors.at(0) +=",";
        neighbors.at(0) +=oneHop;
    }
    mylock.unlock();
    // wait for neighbors to be initialized !!!
    sleep(3);
    
    getIpByHost();

    connectfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);

    inet_pton(AF_INET, ipAddr, &servAddr.sin_addr);

    connect(connectfd, (sockaddr *)&servAddr, sizeof(servAddr));

    cliResponse(connectfd);

    exit(0);
}

// getIpByHost
void TCPClient::getIpByHost()
{
    struct hostent *hptr;

    hptr = gethostbyname(hostName);

    if (hptr == NULL)
    {
        printf("gethostbyname error for host: %s: %s\n", hostName, hstrerror(h_errno));
        return;
    }

    char **pptr;

    switch (hptr->h_addrtype)
    {
    case AF_INET:
        pptr = hptr->h_addr_list;
        inet_ntop(hptr->h_addrtype, hptr->h_addr, ipAddr, sizeof(ipAddr));
        break;

    default:
        printf("unknown address type\n");
        break;
    }

    return;
}

//CliResponse
void TCPClient::cliResponse(int connectfd)
{
    char sendMsg[MAXSIZE], recvMsg[MAXSIZE];

    while (true)
    {

        ssize_t n;
        memset(sendMsg, 0, MAXSIZE);
        memset(recvMsg, 0, MAXSIZE);


        // Send message to other node
        strcat(sendMsg, "Round: ");
        strcat(sendMsg, to_string(Round).c_str());
        strcat(sendMsg, " Node: ");
        strcat(sendMsg, myNodeNumber);
        strcat(sendMsg, " send message to neighbor ");
        strcat(sendMsg, oneNeighbor);
        strcat(sendMsg, ". My neighbors:");
        
        for(string neighbor: neighbors) {
            strcat(sendMsg, " ");
            strcat(sendMsg, neighbor.c_str());
        }
        cout << sendMsg << endl;
        write(connectfd, &sendMsg, sizeof(sendMsg));
        
        // Recv the response from other node
        if ((n = read(connectfd, &recvMsg, sizeof(recvMsg))) == 0)
            return; /* connection closed by other end */
        cout << recvMsg << endl;
        messageRecevied++;

        //thread wait
        unique_lock<mutex> m_lock(myMutex);
        mycon.wait(m_lock);
        sleep(2);
    }
}
