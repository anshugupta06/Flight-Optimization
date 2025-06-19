#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility> // for std::pair

class Backend {
public:
    Backend();

    bool loadConnections(const std::string& filename);
    std::pair<std::vector<std::string>, int> dijkstra(const std::string& start, const std::string& end);
    std::pair<std::vector<std::string>, int> aStar(const std::string& start, const std::string& end);

    const std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& getGraph() const;
    const std::unordered_map<std::string, std::string>& getAirportNames() const;

    bool isDataLoaded() const;

    int heuristic(const std::string& a, const std::string& b) const;

private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
    std::unordered_map<std::string, std::string> airportNames;
    bool dataLoadedSuccessfully = false;
};

#endif // BACKEND_H
