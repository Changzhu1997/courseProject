#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <sstream>
#include "TCPSerCli.h"

using namespace std;

// Constructor
TCPServer::TCPServer(int port, char *nodeNum) : myNodeNum(nodeNum), port(port){};

// serverSetup
int TCPServer::serverSetup()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servAddr.sin_port = htons(port);

    if ((bind(listenfd, (struct sockaddr *)&servAddr, sizeof(servAddr))) < 0)
    {
        cerr << "Bind error" << endl;
        return -1;
    }

    if (listen(listenfd, listenQN) < 0)
    {
        cerr << "Listen Error" << endl;
        return -1;
    }

    while (true)
    {
        cliLength = sizeof(cliAddr);
        connectfd = accept(listenfd, (struct sockaddr *)&cliAddr, &cliLength);

        if (connectfd < 0)
        {
            if (errno == EINTR)
                // back to while()
                continue;
            else
                continue;
            //cerr << "Accept error" << endl;
        }

        int tempLFD = listenfd;
        int tempCFD = connectfd;

        thread childServer([this, tempLFD, tempCFD]() {
            // close(tempLFD);
            // process the request
            // wait for neighbors to be initialized !!!
            sleep(3);
            serverResponse(tempCFD);
        });

        childServer.detach();

        //close(connectfd);
        //    int childpid;
        // if ( (childpid = fork()) == 0) {
        //      close(tempLFD);
        //     // process the request
        //     serverResponse(tempCFD);
        //     exit(0);
        // }
    }

    // int childpid;
    // if ( (childpid = fork()) == 0) {
    //      close(tempLFD);
    //     // process the request
    //     serverResponse(tempCFD);
    //     exit(0);
    // }

    return 0;
}

//serverResponse
void TCPServer::serverResponse(int connectfd)
{
    char sendMsg[MAXSIZE], recvMsg[MAXSIZE];

    while (true)
    {

        ssize_t n;
        memset(sendMsg, 0, MAXSIZE);
        memset(recvMsg, 0, MAXSIZE);

        if ((n = read(connectfd, &recvMsg, sizeof(recvMsg))) == 0)
            return; /* connection closed by other end */

        //here write the cotrol logic
        //cout << recvMsg << endl;
        //string recvMsg =str(recvMsg);
        istringstream in(recvMsg);
        vector<string> message;

        string temp;
        while (in >> temp)
        {
            message.push_back(temp);
        }

        //check for round
        while (true)
        {
            if (stoi(message.at(1)) <= Round)
            {
                break;
            }
            sleep(2);
        }

        // Send response message
        string response = "Round: " + message.at(1) + " Node: " + myNodeNum + " received one message from: " + message.at(3);

        strcpy(sendMsg, response.c_str());
        write(connectfd, &sendMsg, sizeof(sendMsg));

        // add new neighbor to neighbor vector
        if (neighbors.size() == 0)
            continue;

        for (int i = 11; i < message.size(); i++)
        {

            vector<string> results = split(message.at(i), ",");

            for (string oneNode : results)
            {
                if (strcmp(oneNode.c_str(), myNodeNum) == 0)
                    continue;

                else if (Check(oneNode, neighbors))
                    continue;
                else
                {
                    mylock.lock();
                    if (neighbors.size() < (i - 9))
                    {
                        neighbors.push_back(oneNode);
                    }
                    else
                    {
                        neighbors.at(i - 10) += ",";
                        neighbors.at(i - 10) += oneNode;
                    }
                    mylock.unlock();
                }
            }
        }
    }
    close(connectfd);
}

bool TCPServer::Check(string nextHop, vector<string> neighbors)
{

    for (string neighbor : neighbors)
    {
        vector<string> results = split(neighbor, ",");
        for (string temp : results)
        {
            if (temp == nextHop)
                return true;
        }
    }
    return false;
}

vector<string> TCPServer::split(const string &str, const string &delim)
{
    vector<string> res;
    if ("" == str)
        return res;
    char *strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p)
    {
        string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
    }

    return res;
}