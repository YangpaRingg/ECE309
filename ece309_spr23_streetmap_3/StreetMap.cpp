// Functions related to StreetMap

#include "StreetMap.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::string, std::getline;
#include <memory>
using std::shared_ptr, std::make_shared;

string extractTag(const string& xmlString);
string extractAttr(const string& xmlString, const char * name);
Node createNode(const string&);
Way createWay(const string&);

// open an OSM file and read the data
// returns true if successful, false if failed (e.g., cannot open file)
// This implementation assumes that OSM file is properly formatted.
bool StreetMap::readOSM(std::string_view filename) {
    if (!nodes.empty()) nodes.clear();
    if (!ways.empty()) ways.clear();

    ifstream osm { filename.data() };
    if (!osm.is_open()) return false;

    string inbuf;   // used to read lines from the file
    // ignore first three lines of the file
    getline(osm, inbuf);  // xml prolog
    getline(osm, inbuf);  // osm root
    getline(osm, inbuf);  // boundary

    bool inWay { false };
    string tag;
    WayPtr wp {nullptr};

    while (true) {
        getline(osm, inbuf);
        if (osm.eof()) break;

        tag = extractTag(inbuf);
        if (tag == "node") {
            auto np = make_shared<Node>(createNode(inbuf));
            nodes.insert(np->getID(), np);
        }
        //else if (tag == "/node") inNode = false;
        else if (tag == "tag" && inWay) {
            string key = extractAttr(inbuf, "k");
            string value = extractAttr(inbuf, "v");
            wp->addTag({key, value});
        }
        else if (tag == "way") {
            wp = make_shared<Way>(createWay(inbuf));
            if (inbuf.find("/>") == std::string::npos) inWay = true;
            else {
                ways.push_back(wp);  // should never happen: Way must have nodes
                wp = nullptr;
            }
        }
        else if (tag == "/way") {
            inWay = false;
            ways.push_back(wp);
            wp = nullptr;
        }
        else if (tag == "nd" && inWay) {
            long long id = std::stoll(extractAttr(inbuf, "ref"));
            auto np = lookupNode(id);
            wp->addNode(np);
            np->addWay(wp);
        }
        else if (tag == "relation") break;  // exit when ways are done
    }
    for (auto& i : ways) {
        if (i->isPath()) {
            for (auto& j : i->intersections()) {
                routeGraph.addVertex(j->getID());
            }
            if (i->intersections().size() > 0) {
                for (size_t j {0}; j < (i->intersections().size() - 1); ++j) {
                    NodePtr currNode {i->intersections().at(j)};
                    NodePtr nextNode {i->intersections().at(j+1)};
                    routeGraph.addEdge(currNode->getID(), nextNode->getID(), currNode->distance(*nextNode));
                }
            }
        }
    }
    return true;
}

// helper function -- get OSM tag (e.g., node, way...) from line
string extractTag(const string& str) {
    size_t pos = str.find('<') + 1;
    size_t p = pos+1;
    while ((str.at(p) != ' ') && (str.at(p) != '>')) p++;
    string tag = str.substr(pos, (p-pos));
    //std::cout << "tag = " << tag << std::endl;
    return tag;
}

// helper function -- get key/value from line
string extractAttr(const string& str, const char * name) {
    string ns{name};
    ns += "=";
    size_t pos = str.find(ns);
    pos = str.find('\"', pos) + 1;
    size_t end = str.find('\"', pos + 1);
    return str.substr(pos, end-pos);
}

// get Node information from string and create Node object
Node createNode(const string& inbuf) {
    long long id = std::stoll(extractAttr(inbuf, "id"));
    double lat = std::stod(extractAttr(inbuf, "lat"));
    double lon = std::stod(extractAttr(inbuf, "lon"));
    return {id, lat, lon};
}

// get Way ID from string and create Way object
Way createWay(const string& inbuf) {
    long long id = std::stoll(extractAttr(inbuf, "id"));
    return Way(id);
}

// given node ID, return pointer to Node object
NodePtr StreetMap::lookupNode(long long id) const {
    NodePtr found {nullptr};
    nodes.find(id, found);
    return found;
}

// given way ID, return pointer to Way object
WayPtr StreetMap::lookupWay(long long id) const {
    for (auto iter {ways.cbegin()}; iter != ways.cend(); ++iter) {
        if ((*iter)->getID() == id) return *iter;
    }
    return nullptr;
}

// look through Way list and return all buildings
WayList StreetMap::getBuildings() const {
    WayList b;
    for (auto iter {ways.cbegin()}; iter != ways.cend(); ++iter) {
        if ((*iter)->isBuilding()) b.push_back(*iter);
    }
    return b;
}

// look through Way list and return all paths
WayList StreetMap::getPaths() const {
    WayList p;
    for (auto iter {ways.cbegin()}; iter != ways.cend(); ++iter) {
        if ((*iter)->isPath()) p.push_back(*iter);
    }
    return p;
}

double StreetMap::shortestRoute(long long start, long long end) {
    double distance;
    routeGraph.addVertex(start);
    routeGraph.addVertex(end);
    routeGraph.shortestPath(start, end, distance);
    return distance;
}

double StreetMap::shortestRoute(long long start, long long end, Route& r) {
    double distance;
    routeGraph.addVertex(start);
    routeGraph.addVertex(end);
    list<long long> path {routeGraph.shortestPath(start, end, distance)};
    auto iter1 = path.begin();
    auto iter2 = path.begin();
    ++iter2;
    for (; iter2 != path.end(); ++iter2) {
        RoutePart* rp {new RoutePart};
        routeGraph.isAdjacent(*iter1, *iter2, rp->distance);
        rp->toNode = lookupNode(*iter2);
        for (auto& i : ways) {
            if (i->lookupNode(*iter1) != nullptr) {
                for (auto& j : i->intersections()) {
                    if (j->getID() == *iter2) {
                        rp->way = i;
                    }
                }
            }
        }
        r.push_back(*rp);
        ++iter1;
    }
    return distance;
}