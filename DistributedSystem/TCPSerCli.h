//TCPSerCli.h
#ifndef TCPSerCli
#define TCPSerCli 

#define MAXSIZE 100
#include <atomic>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
//define it in main
extern std::atomic<int> Round;
extern std::atomic<int> messageRecevied;
extern std::condition_variable mycon;
extern std::mutex myMutex,mylock;
extern std::vector<std::string> neighbors;
extern int Counter;

vector<string> setUp();

class TCPServer
{
public:
    struct sockaddr_in servAddr, cliAddr;
    socklen_t cliLength;
    pid_t childPid;
    int listenfd, connectfd, port;
    int listenQN = 45;
    char* myNodeNum;
    

public:
    TCPServer(int port, char *nodeNum);

    int serverSetup();
    
    void serverResponse(int connectfd);

    bool Check(std::string nextHop, std::vector<std::string> neighbors);

    std::vector<std::string> split(const std::string& str, const std::string& delim);

};

class TCPClient
{

public:
    int connectfd, port;
    struct sockaddr_in servAddr;
    char *myNodeNumber, *oneNeighbor, *hostName;
    char ipAddr[INET_ADDRSTRLEN];

public:
    TCPClient(char *ipAddr, int port, char *nodeNumber, char *Neighbor);

    void clientSetup();

    void clientSetup(int port);

    void getIpByHost();

    void cliResponse(int connectfd);
};
#endif