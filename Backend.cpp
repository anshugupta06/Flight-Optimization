#include "Backend.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <climits>
#include <algorithm>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug> // Include for debugging output

using namespace std;

Backend::Backend() : dataLoadedSuccessfully(false) {
    loadConnections(QCoreApplication::applicationDirPath().toStdString() + "/airport_connections.csv");
}

bool Backend::loadConnections(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file: " << filename << endl;
        dataLoadedSuccessfully = false;
        return false;
    }

    string line;
    getline(file, line); // Skip header: "Source,Destination,Distance_km"
    qDebug() << "Skipped Header:" << QString::fromStdString(line);

    set<string> seenEdges;
    int lineNumber = 1;
    while (getline(file, line)) {
        lineNumber++;
        stringstream ss(line);
        string src, dest, distStr;
        string dummy; // To consume the name fields if they exist (or are empty)

        getline(ss, src, ',');
        getline(ss, dest, ',');
        getline(ss, distStr, ','); // Distance is the third column

        qDebug() << "Line " << lineNumber << ": Read - Src:'" << QString::fromStdString(src) << "'"
                 << ", Dest:'" << QString::fromStdString(dest) << "'"
                 << ", DistStr:'" << QString::fromStdString(distStr) << "'";

        if (src.empty() || dest.empty() || distStr.empty()) {
            qDebug() << "Line " << lineNumber << ": Skipping due to empty fields.";
            continue;
        }

        int distance;
        try {
            distance = stoi(distStr);
            qDebug() << "Line " << lineNumber << ": Distance converted:" << distance;
        } catch (const std::invalid_argument& e) {
            qDebug() << "Line " << lineNumber << ": Error converting distance to integer: '" << QString::fromStdString(distStr) << "' - " << e.what();
            continue;
        } catch (const std::out_of_range& e) {
            qDebug() << "Line " << lineNumber << ": Distance out of range: '" << QString::fromStdString(distStr) << "' - " << e.what();
            continue;
        }

        string edgeKey1 = src + "-" + dest;
        string edgeKey2 = dest + "-" + src;

        if (seenEdges.count(edgeKey1) == 0 && seenEdges.count(edgeKey2) == 0) {
            graph[src].push_back(make_pair(dest, distance));
            graph[dest].push_back(make_pair(src, distance)); // undirected
            seenEdges.insert(edgeKey1);
            seenEdges.insert(edgeKey2);
        }
        // We don't have separate name columns in your provided CSV structure
        airportNames[src] = src; // Use the code as the name for now
        airportNames[dest] = dest;
    }
    qDebug() << "Size of graph:" << graph.size();
    qDebug() << "Size of airportNames:" << airportNames.size();
    dataLoadedSuccessfully = true;
    return true;
}

pair<vector<string>, int> Backend::dijkstra(const string& start, const string& goal) {
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;

    for (const auto& pair : graph) {
        dist[pair.first] = INT_MAX;
    }

    dist[start] = 0;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        string current = pq.top().second;
        pq.pop();

        if (current == goal) break;
        if (currentDist > dist[current]) continue; // Optimization

        for (const auto& neighborPair : graph[current]) {
            string neighbor = neighborPair.first;
            int weight = neighborPair.second;
            int newDist = currentDist + weight;

            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = current;
                pq.push({newDist, neighbor});
            }
        }
    }

    vector<string> path;
    if (dist[goal] != INT_MAX) {
        for (string at = goal; !at.empty(); at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
    }
    return {path, (dist[goal] == INT_MAX ? -1 : dist[goal])}; // -1 indicates no path
}

int Backend::heuristic(const std::string& a, const std::string& b) const {
    return 0; // Dummy heuristic
}

pair<vector<string>, int> Backend::aStar(const string& start, const string& goal) {
    unordered_map<string, int> gScore;
    unordered_map<string, int> fScore;
    unordered_map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> openSet;

    for (const auto& pair : graph) {
        gScore[pair.first] = INT_MAX;
        fScore[pair.first] = INT_MAX;
    }

    gScore[start] = 0;
    fScore[start] = heuristic(start, goal);
    openSet.push({fScore[start], start});

    while (!openSet.empty()) {
        string current = openSet.top().second;
        if (current == goal) break;
        openSet.pop();

        for (const auto& neighborPair : graph[current]) {
            string neighbor = neighborPair.first;
            int weight = neighborPair.second;
            int tentativeG = gScore[current] + weight;
            if (tentativeG < gScore[neighbor]) {
                prev[neighbor] = current;
                gScore[neighbor] = tentativeG;
                fScore[neighbor] = tentativeG + heuristic(neighbor, goal);
                openSet.push({fScore[neighbor], neighbor});
            }
        }
    }

    vector<string> path;
    if (gScore[goal] != INT_MAX) {
        for (string at = goal; !at.empty(); at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
    }
    return {path, (gScore[goal] == INT_MAX ? -1 : gScore[goal])}; // -1 indicates no path
}

const unordered_map<string, vector<pair<string, int>>>& Backend::getGraph() const {
    return graph;
}

const unordered_map<string, string>& Backend::getAirportNames() const {
    return airportNames;
}

bool Backend::isDataLoaded() const {
    return dataLoadedSuccessfully;
}
