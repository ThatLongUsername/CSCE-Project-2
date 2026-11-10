//Author: Ahmed Amin
//Purpose: Implement campus graph, building connection, graph statistics, and BFS
#include "CampusGraph.h"
#include <iostream>
#include <queue>
#include <cctype>

CampusGraph::CampusGraph(){
    totalConnections = 0;
}
string CampusGraph::lowerName(string word)const{
    for(char& x : word)
        x = static_cast<char>(
            tolower(static_cast<unsigned char>(x))
            );
    return word;
}
int CampusGraph::locateBuilding(const string& buildingName) const{
    for(int i= 0; i <buildings.size(); i++){
        if(lowerName(buildings[i]) ==lowerName( buildingName)){return i;}
    }
    return -1;
}
bool CampusGraph::addingBuildings(const string& buildingName){
    if(locateBuilding(buildingName)!= -1){return false;}
    buildings.push_back(buildingName);
    neighbors.push_back(vector<int>());
    return true;
}
bool CampusGraph::connectingBuilding(const string& building1, const string& building2){
    int one = locateBuilding(building1);
    int two = locateBuilding(building2);
    if (one== -1|| two == -1){return false;}
    if (one==two){return false;}
    for(int x: neighbors[one]){
        if(x==two){return false;}
    }
    neighbors[one].push_back(two);
    neighbors[two].push_back(one);
    totalConnections++;
    return true;
}
bool CampusGraph::buildingExists(const string& buildingName) const{
    return locateBuilding(buildingName) != -1;
}
void CampusGraph::showGraph() const{
    if(buildings.empty()){
        cout << "No buildings available." << endl;
        cout << "Total number of buildings: 0"<< endl;
        cout<< "Total connections: 0" << endl;
        return;}
    for(int i=0; i< buildings.size(); i++){
        cout << buildings[i] <<": ";
        if(neighbors[i].empty()){cout<<"(no connections)";}
        else{
            for(int x:neighbors[i]){
                cout << buildings[x]<< " ";
            }
        }
        cout<<endl;
    }    
}
void CampusGraph::showGraphStats()const{
    cout << "Total number of buildings: " << buildings.size() <<endl;
    cout << "Total connections: " << totalConnections << endl;
    for(int i=0; i< buildings.size(); i++){
        cout<< buildings[i]  <<": degree " << neighbors[i].size() << endl;
    }
}
void CampusGraph::tryBFS(const string& source) const{
    int initiate = locateBuilding(source);
    if(initiate ==-1)cout<< "Unknown building: "<< source<< endl;
    return;}

    vector<bool> alreadyVisited(buildings.size(),false);
    vector<int> spacing(buildings.size(),-1);
    queue<int> q;
    alreadyVisited[initiate] =true;
    spacing[initiate] = 0;
    q.push(initiate);
    int reach=0;

    while(!q.empty()){
        int present = q.front();
        q.pop();
        cout<<buildings[present]<<" (distance "<< spacing[present]
        <<")" << endl;
        reach++;
        for(int next : neighbors[present]){
            if(!alreadyVisited[next]){
                alreadyVisited[next] = true;
                spacing[next] = spacing[present]+1;
                q.push(next);
            }
        }
    }
    cout << "Reachable: "<<reach<< " of "<< buildings.size()<<" buildings"<<endl;
}
