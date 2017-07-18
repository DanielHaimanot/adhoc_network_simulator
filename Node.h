//
// Created by Daniel on 31/05/2016.
//
#ifndef SIM_NODE_H
#define SIM_NODE_H

#include <iostream>
#include <random>
#include <chrono>
#include <utility>
#include <set>
#include <math.h>
#include <string>

using namespace std;

enum nodeType {NORMAL, SINK};

class Network;//Forward declaration
class Packet;

class Node {
public:
    mutable int nodeHopCount = 65536; //infinity for NORMAL and 0 for SINK
    mutable vector<Packet> pRecvBuffer;
    mutable vector<Packet> pSendBuffer;
    mutable vector<int> pDataStore;

    int nodeRange = 6;
    string nodeId = "";
    mutable string nodeParentId = "";

    nodeType NODE_TYPE;
    pair<int,int> location;
    Network *pNetwork;
    
    int Run(int time) const;
    void Recv(Packet) const;
    void Send(Packet) const;
    friend bool operator<(const Node &left, const Node &right);
};


#endif //SIM_NODE_H
