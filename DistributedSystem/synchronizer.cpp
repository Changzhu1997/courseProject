#include "TCPSerCli.h"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <string.h>
#include <sstream>
#include <sys/utsname.h>
#include <fstream>
#include <signal.h>
using namespace std;

atomic<int> Round;
atomic<int> messageRecevied;

vector<string> neighbors;

// Counter-hop neighbors for this node
int Counter;

condition_variable mycon;
mutex myMutex, mylock;
string node;
void server_Thread(TCPServer &server)
{
    server.serverSetup();
}

void client_Thread(TCPClient &client)
{
    client.clientSetup();
}

void setUp(vector<string> &args)
{
    string serverNodeName;
    struct utsname buf; //Sets struct to get info
    // get the node name for this machine
    if (uname(&buf) == 0)
        serverNodeName = buf.nodename;

    string dcNum = serverNodeName.substr(0, 4);

    // parse configuration file
    vector<string> configuration;
    vector<string> allServerNodes;
    ifstream afile;
    afile.open("configuration.txt", ios::in);

    string oneLine;
    while (getline(afile, oneLine))
    {
        configuration.push_back(oneLine);

        if (oneLine.size() < 11)
            continue;

        if (oneLine.find("dc") != string::npos)
            allServerNodes.push_back(oneLine);
    }

    // 1.parse server information
    for (string information : configuration)
    {
        if (information.find(dcNum) != string::npos)
        {
            istringstream in1(information);
            vector<string> serverSetup;

            string temp;
            while (in1 >> temp)
            {
                serverSetup.push_back(temp);
            }

            // server port number
            args.push_back(serverSetup.at(2));
            //server node number
            args.push_back(serverSetup.at(0));
            break;
        }
    }

    //2.parse neighbor information
    for (string information : configuration)
    {
        string nodeNum = "node " + args[1];
        if (information.find(nodeNum) != string::npos)
        {
            istringstream in2(information);
            string oneNeighbor;

            while (in2 >> oneNeighbor)
            {
                if (oneNeighbor == "#")
                    break;

                for (string infor : allServerNodes)
                {
                    istringstream in3(infor);
                    vector<string> infor2;

                    string temp;
                    while (in3 >> temp)
                    {
                        infor2.push_back(temp);
                    }

                    if (infor2.at(0) == oneNeighbor)
                    {
                        // hostname, port number, my neighborNum

                        string domainName = infor2.at(1) + ".utdallas.edu";
                        args.push_back(domainName); // hostname

                        args.push_back(infor2.at(2)); //port number;

                        args.push_back(oneNeighbor);
                    }
                }
            }
        }
    }
}

void interrupt(int signum)
{
    cout << "My nodeNum: " << node << endl;
    for (int i = 0; i < neighbors.size(); i++)
    {
        cout << (i + 1) << "-hop: " << neighbors.at(i) << endl;
    }
    cout << "Eccentricity:" << neighbors.size() << endl;
    exit(signum);
}

int main()
{
    // to receive key interrupt
    signal(SIGINT, interrupt);

    vector<string> args;
    Counter = 1;
    Round = 1;
    int numberOfNeighbor = 0;

    setUp(args);
    // Server initialization
    //port and mynodeNum

    char *myNode = new char[args.at(1).length() + 1];
    node = args.at(1);
    strcpy(myNode, args.at(1).c_str());

    TCPServer ts(stoi(args.at(0)), myNode);
    thread st(server_Thread, ref(ts));
    st.detach();
    cout << "Server Initialized !" << endl;
    sleep(10);

    // Client initialization
    // hostname, port number, mynodeNum, my neighborNum
    cout << "Round: " << Round << endl;

    vector<TCPClient> clientVector;
    vector<thread> thread_vec;
    for (int i = 2; i < args.size(); i += 3)
    {
        //char *hostName, int port, char *nodeNumber, char *Neighbor
        char *hostName = new char[args.at(i).length() + 1];
        char *neighbor = new char[args.at(i + 2).length() + 1];

        strcpy(hostName, args.at(i).c_str());
        strcpy(neighbor, args.at(i + 2).c_str());
        TCPClient tc(hostName, stoi(args.at(i + 1)), myNode, neighbor);
        clientVector.push_back(tc);
        numberOfNeighbor++;
    }

    for (int j = 0; j < numberOfNeighbor; j++)
    {
        thread_vec.emplace_back(thread(client_Thread, ref(clientVector.at(j))));
    }

    for (thread &t : thread_vec)
    {
        t.detach();
    }

    while (true)
    {
        if (messageRecevied / numberOfNeighbor >= Round)
        {
            Round++;
            cout << endl;
            sleep(2);
            cout << "Round: " << Round << endl;
            mycon.notify_all();
        }
        sleep(1);

        // outfile
        ofstream outfile;
        string filename = node + "-result.txt";
        outfile.open(filename, ios::out | ios::trunc);
        outfile << "My nodeNum: " << node << endl;
        for (int i = 0; i < neighbors.size(); i++)
        {
            outfile << (i + 1) << "-hop: " << neighbors.at(i) << endl;
        }
        outfile << "Eccentricity:" << neighbors.size() << endl;

        outfile.close();
    }
}
