//
// Created by Daniel on 31/05/2016.
//
#ifndef SIM_NETWORK_H
#define SIM_NETWORK_H

#include <iostream>
#include <random>
#include <chrono>
#include <utility>
#include <set>
#include <math.h>
#include <string>
#include <vector>

#include "Node.h"

using namespace std;

enum packetType {BEACON, DATA};

class Packet{
public:
    int beaconHopCount = 0;
    string beaconSender = "";
    packetType TYPE;
};

class Link {

};

class Network{
public:
    void Broadcast(pair<int,int> srcCoord,int calcRange, Packet &cPacket);
    void AddNodes(std::set<pair<int,int>> &coordinates); //Complete
    void AddSink(pair<int,int> coord);
    void PrintNodes();
    void PrintHops();

    void Step();
    Network();
    ~Network();

    std::set<Node> setNodes;
};


#endif //SIM_NETWORK_H
