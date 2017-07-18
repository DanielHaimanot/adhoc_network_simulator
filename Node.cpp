//
// Created by Daniel on 31/05/2016.
//
#include "Node.h"
#include "Network.h"

//We have node doing stuff, but not done with other stuff.
int Node::Run(int time) const {
    //Check if anything received.
    if(pRecvBuffer.size() > 0){
        Packet recvPacket;
        recvPacket = pRecvBuffer.front();

        //A sink node can't receive broadcast packages
        if(recvPacket.TYPE == BEACON && NODE_TYPE != SINK){
            //If we found a better route, prepare a broadcast package
            if( nodeHopCount > recvPacket.beaconHopCount + 1){
                nodeHopCount = recvPacket.beaconHopCount + 1;
                nodeParentId = recvPacket.beaconSender;

                Packet sendPacket;
                sendPacket.beaconSender = nodeId;
                sendPacket.beaconHopCount = recvPacket.beaconHopCount + 1;
                sendPacket.TYPE = BEACON;

                pSendBuffer.push_back(sendPacket);
            }
        }else if(recvPacket.TYPE == DATA){
            //Recv a DATA packet
            Packet sendPacket;
            sendPacket.beaconSender = nodeId;
            sendPacket.TYPE = DATA;
            pSendBuffer.push_back(sendPacket);
        }
    }

    //Do a beacon broadcast at time == 0
    if(NODE_TYPE == SINK && (time == 0)){
        Packet aPacket;
        aPacket.beaconHopCount = 0; //Sink Node
        aPacket.beaconSender = nodeId;
        aPacket.TYPE = BEACON;

        pSendBuffer.push_back(aPacket);
    }

    //Check if there is anything to be send
    if(pSendBuffer.size() > 0){
        Packet tmpPacket =  pSendBuffer.front();
        if(tmpPacket.TYPE == BEACON){
            int calcRange = (int) pow(nodeRange,2.0); //Get the nodes radio range
            pNetwork->Broadcast(location,calcRange,tmpPacket);
        }
        /*else if(tmpPacket.TYPE == DATA){
        }*/
    }
}

//Add packet to the receive buffer
void Node::Recv(Packet pPacket) const{
    pRecvBuffer.push_back(pPacket);
}

void Node::Send(Packet pPacket) const{
    pSendBuffer.push_back(pPacket);
}

//Node operator
bool operator<(const Node &left, const Node &right){
    return left.location < right.location;
}