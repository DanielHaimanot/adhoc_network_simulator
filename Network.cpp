//
// Created by Daniel on 31/05/2016.
//
#include "Network.h"

using namespace std;

void Network::Step(){
    int time = 0;
    int stop_time = 50;
    while(time < stop_time /*&& pending > 0*/){ //pending is number of links queued up.
        for(const auto& node: setNodes) {
            node.Run(time); //Run the node actions
        }

        time += 1;
    }
}

void Network::Broadcast(pair<int,int> srcCoord,int calcRange, Packet &cPacket){

    for(const auto& destNode: setNodes) {
        pair<int,int> destCoord = destNode.location;
        int nodeArea = (int) (pow(destCoord.first - srcCoord.first,2.0)
                              + pow(destCoord.second - srcCoord.second,2.0));

        if(nodeArea <= calcRange && destCoord != srcCoord){
            //Send packet to all nodes in the same area.
            destNode.Recv(cPacket);
        }
    }
}

void Network::AddNodes(std::set<pair<int,int>> &coordinates){
    for(const auto& elem: coordinates){
        Node node;
        node.location = elem;
        node.NODE_TYPE = NORMAL;
        node.pNetwork = this;
        node.nodeId = "(" + to_string(elem.first) + "," + to_string(elem.second) + ")";
        setNodes.insert(node);
    }
}

void Network::AddSink(pair<int,int> coord){
    Node node;
    node.location = coord;
    node.NODE_TYPE = SINK;
    node.nodeHopCount = 0;
    node.pNetwork = this;
    node.nodeId = "(" + to_string(coord.first) + "," + to_string(coord.second) + ")";
    setNodes.insert(node);
}

void Network::PrintHops(){
    vector<vector<string>> table;
    int maxCount = 0;

    for(const auto& node: setNodes){
        if(node.nodeHopCount > maxCount) maxCount = node.nodeHopCount;
    }

    vector<string> t;
    for(int hops = 0; hops <= maxCount; hops++) {
        for (const auto &node: setNodes) {
            if(node.nodeHopCount == hops){
                t.push_back(node.nodeId);
            }
        }
        table.push_back(t);
        t.clear();
    }

    std::vector< std::vector<string> >::const_iterator row;
    std::vector<string>::const_iterator col;

    int i = 0;
    for (row = table.begin(); row != table.end(); ++row) {
        cout << "Hop : " << i << " :";
        for (col = row->begin(); col != row->end(); ++col) {
            std::cout << *col;
        }
        cout << endl;
        i++;
    }
}

void Network::PrintNodes(){
    cout << "Child   <->  Parent  Hop Count" << endl;
    for(const auto& node: setNodes){
        pair<int,int> cord;
        cord = node.location;
        cout << "("<< cord.first << "," << cord.second <<  ") ";
        cout << " <-> " << node.nodeParentId << " : " << node.nodeHopCount;
        cout << endl;
    }
    cout << endl;

    PrintHops();
}

Network::Network(){

}

Network::~Network(){

}
