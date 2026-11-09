//Author: Ahmed Amin
//Purpose: Declare CampusGraph class
#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include <string>
#include <vector>
using namespace std;

class CampusGraph{
    private:
    vector<string> buildings;
    vector<vector<int>> neighbors;
    int totalConnections;
    string lowerName(string word) const;
    int locateBuilding(const string& buildingName) const;

    public:
    CampusGraph();
    bool addingBuildings(const string& buildingName);
    bool connectingBuilding(const string& building1, const string& building2);
    void showGraph() const;
    void showGraphStats() const;
    void tryBFS(const string& source) const;

};
#endif
