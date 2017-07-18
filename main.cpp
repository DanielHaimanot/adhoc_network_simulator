#include <iostream>
#include <random>
#include <chrono>
#include <utility>
#include <set>
#include <math.h>
#include "Network.h"

using namespace std;

void GenerateRandomNodes(std::set<pair<int,int>> &coordinates, int nodeCount, int areaSize){
    //Generate Random numbers
    unsigned int seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    std::uniform_int_distribution<>dist(1,areaSize);

    for(int i = 0; i<nodeCount;i++)// number of nodes
    {
        std::pair<int,int> location;

        do {
            location = std::make_pair(dist(gen), dist(gen));
        }while(coordinates.count(location) == 1);

        coordinates.insert(location);
    }

    cout << "Set Size: " << coordinates.size() << endl;

    for(const auto& elem: coordinates){
        cout << "("<< elem.first << ":" << elem.second <<  ")";
    }
    cout << endl << endl;
}

void GenerateFromString(string input, set< pair <int,int> > &pNetList)
{
    string A, B;
    size_t found = 0, start = 0, end = 0;

    do
    {
        found = input.find(":",found);

        if(found != string::npos)
        {
            A = input.substr(start, found - start);

            end = input.find(",",found);
            size_t len = end - found;

            if(end != string::npos){
                B = input.substr(found+1, len-1);
            }

            found = end + 1;
            start = end + 1;

            pNetList.insert(make_pair(stoi(A), stoi(B)));
        }
    }
    while(found != string::npos);
}

int main()
{
    //This is a good test network:
  //  string test_coord = "1:6,1:12,2:4,3:8,5:14,6:2,6:15,7:1,7:11,9:3,9:11,9:13,10:4,10:6,10:14,11:4,11:9,13:14,16:5,16:8,";
    string test_coord = "1:12,3:8,5:14,6:15,7:11,9:3,9:11,10:6,";

    std::set<pair<int,int>> coordinates;

    //    GenerateRandomNodes(coordinates, 20,16); -- Generate 20 random nodes in a 16x16 area
    GenerateFromString(test_coord,coordinates);
    Network simNet;
    simNet.AddNodes(coordinates);
    simNet.AddSink(make_pair(8,0));
    simNet.Step();
    simNet.PrintNodes();
/*
    std::set<pair<int,int>> tempList;
    std::set<pair<int,int>> parentList;

    parentList.insert(std::make_pair(8,0));
    int range = (int) pow(6,2.0);
    int solved = 0;

    for(int levels = 1; levels < 16; levels++)
    {
        cout << "Hop  " << levels << " : " << std::flush;
        for(const auto& child: coordinates) {
            for(const auto& parent: parentList){
                int nodeArea = (int) (pow(child.first - parent.first,2.0)
                                      + pow(child.second - parent.second,2.0));

                if(nodeArea <= range){
                    cout << "("<< child.first << "," << child.second <<  ") , ";

                    solved++;
                    tempList.insert(std::make_pair(child.first,child.second));
                    break;
                }
            }
        }

        if(tempList.empty() == true){
     //       cout << "Can't find level!" << endl;
            break;
        }

        for(const auto& temp: tempList){
            coordinates.erase(temp);
        }

        parentList = tempList;
        tempList.clear();
        cout << endl;

        if(coordinates.empty() == true) break;
    }

    cout << "Total Connected = " << solved;
*/
    return 0;
}