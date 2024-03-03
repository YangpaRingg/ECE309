#ifndef ECE309_SPR23_STREETMAP_GRAPH_H
#define ECE309_SPR23_STREETMAP_GRAPH_H

#include <cstddef> // for size_t
#include <list>
#include <queue>
#include <set>
#include "HashTable.h"
using std::list;

// TEMPLATE CLASS for Graph, and TEMPLATE FUNCTIONS for BFS and DFS
// All definitions must go here. Do not create Graph.cpp.
// Additional private functions (for the class) or template functions (to help with BFS/DFS) may be added.
// DO NOT change the public member functions.

// TEMPLATE CLASS: Graph<K,W> -- the W type defaults to unsigned int
// This is a weighted graph, but weight on each edge defaults to 1.
// (So if you want unweighted, just leave off the weight parameters.)

// K is a key used to find a vertex in the graph -- K should be lightweight, passed by value.
// W is the type used for an edge weight (default is unsigned int).
// W must be a numeric type (int, double, etc.).
// Each vertex has a list of edges, which connect to adjacent vertices.

template <typename K, typename W = unsigned>
class Graph {
private:
    class Edge {
    public:
        K src;
        K dst;
        W weight;
        Edge(const K &from, const K &to, W wt = 1) : src{from}, dst{to}, weight{wt} {}
    };

    class Vertex {
    public:
        K key;
        Vertex(K id) : key{id} {}
        // add member variable(s) to store edges
        std::vector<Edge*> edgesOut;
        std::vector<Edge*> edgesIn;
        // (hint: graph may be directed or undirected -- directed will require separate incoming and outgoing edges)
    };
    // add a data structure (hint: hash table!) to store vertices
    HashTable<K, Vertex*> vertices;
    size_t n_edges {0};
    const bool is_directed;
public:
    Graph(bool directed = false) : is_directed{directed} {}
    bool isDirected() const { return is_directed; }
    bool addVertex(K key);
    bool addEdge(K a, K b, W weight = 1);
    bool removeVertex(K key);
    bool removeEdge(K a, K b);
    bool updateEdge(K a, K b, W newWeight);
    size_t numVertices() const { return vertices.size(); }
    size_t numEdges() const { return n_edges; }
    void clear();

    bool findVertex(K a) const;
    bool isAdjacent(K a, K b) const;
    bool isAdjacent(K a, K b, W& wt) const;  // returns weight if edge is found
    list<K> getAdjacencyList(K a);           // list of vertices to which there is an edge from a
    bool confirmPath(const list<K>& vertexList) const;
    W pathWeight(const list<K>& vertexList) const;  // returns 0 if path is not legit
    list<K> shortestPath(K from, K to, W& length);
};


//----- IMPLEMENTATION -----
// put Graph<K,W> member functions here
// (if the function is trivial, you can add it to the declaration above)
// because this is a template, definitions must go here, in the .h file  -- DO NOT create a Graph.cpp file

template<typename K, typename W>
bool Graph<K, W>::addVertex(K key) {
    Vertex* vertex {new Vertex(key)};
    Vertex* dummy;
    if (vertices.find(key, dummy)) {return false;}
    if (vertices.insert(key, vertex)) {return true;}
    else {return false;}
}

template<typename K, typename W>
bool Graph<K, W>::addEdge(K a, K b, W weight) {
    Vertex* vertA;
    Vertex* vertB;
    if (!vertices.find(a, vertA)) {return false;}
    if (!vertices.find(b, vertB)) {return false;}
    if (!is_directed) {
        for (auto& i : vertA->edgesOut) {
            if (i->src == a && i->dst == b) {return false;}
        }
        Edge* edgeAB {new Edge(a, b, weight)};
        vertA->edgesOut.push_back(edgeAB);
        Edge* edgeBA {new Edge(b, a, weight)};
        vertB->edgesOut.push_back(edgeBA);
        ++n_edges;
        return true;
    }
    else {
        for (auto& i : vertA->edgesOut) {
            if (i->src == a && i->dst == b) {return false;}
        }
        Edge* edgeAB {new Edge(a, b, weight)};
        vertA->edgesOut.push_back(edgeAB);
        vertB->edgesIn.push_back(edgeAB);
        ++n_edges;
        return true;
    }
}

template<typename K, typename W>
bool Graph<K, W>::removeVertex(K key) {
    Vertex* vert;
    if (vertices.find(key, vert)){
        if (!is_directed) {
            for (auto& i : vert->edgesOut) {
                Vertex* dstVert;
                vertices.find(i->dst, dstVert);
                auto& edgeList {dstVert->edgesOut};
                for (size_t j = 0; j < edgeList.size(); ++j) {
                    if (edgeList[j]->dst == key) {
                        delete edgeList[j];
                        edgeList.erase(edgeList.begin() + j);
                    }
                }
                delete i;
                --n_edges;
            }
            Vertex* dummy;
            vertices.erase(key, dummy);
            return true;
        }
        else if (is_directed) {
            for (auto& i : vert->edgesOut) {
                Vertex* dstVert;
                vertices.find(i->dst, dstVert);
                auto& edgeList {dstVert->edgesIn};
                for (size_t j = 0; j < edgeList.size(); ++j) {
                    if (edgeList[j]->src == key) {
                        edgeList.erase(edgeList.begin() + j);
                    }
                }
                delete i;
                --n_edges;
            }
            for (auto& i : vert->edgesIn) {
                Vertex* srcVert;
                vertices.find(i->src, srcVert);
                auto& edgeList {srcVert->edgesOut};
                for (size_t j = 0; j < edgeList.size(); ++j) {
                    if (edgeList[j]->dst == key) {
                        edgeList.erase(edgeList.begin() + j);
                    }
                }
                delete i;
                --n_edges;
            }
            delete vert;
            Vertex* dummy;
            vertices.erase(key, dummy);
            return true;
        }
    }
    else {
        return false;
    }
}

template<typename K, typename W>
bool Graph<K, W>::removeEdge(K a, K b) {
    bool removed {false};
    Vertex* vertA;
    Vertex* vertB;
    if (!is_directed) {
        if (vertices.find(a, vertA)) {
            std::vector<Edge*>& edgeList {vertA->edgesOut};
            for (size_t i = 0; i < edgeList.size(); ++i) {
                if (edgeList[i]->src == a && edgeList[i]->dst == b) {
                    delete edgeList[i];
                    edgeList.erase(edgeList.begin() + i);
                    removed = true;
                }
            }
        }
        if (vertices.find(b, vertB)) {
            std::vector<Edge*>& edgeList {vertB->edgesOut};
            for (size_t i = 0; i < edgeList.size(); ++i) {
                if (edgeList[i]->src == b && edgeList[i]->dst == a) {
                    delete edgeList[i];
                    edgeList.erase(edgeList.begin() + i);
                    removed = true;
                }
            }
        }
        if (removed) {
            --n_edges;
            return true;
        }
        else {
            return false;
        }
    }
    else if (is_directed) {
        if (vertices.find(a, vertA)) {
            std::vector<Edge*>& edgeList {vertA->edgesOut};
            for (size_t i {0}; i < edgeList.size(); ++i) {
                if (edgeList[i]->src == a && edgeList[i]->dst == b) {
                    delete edgeList[i];
                    edgeList.erase(edgeList.begin() + i);
                    removed = true;
                }
            }
        }
        if (vertices.find(b, vertB)) {
            std::vector<Edge*>& edgeList {vertB->edgesOut};
            for (size_t i {0}; i < edgeList.size(); ++i) {
                if (edgeList[i]->src == a && edgeList[i]->dst == b) {
                    delete edgeList[i];
                    edgeList.erase(edgeList.begin() + i);
                    removed = true;
                }
            }
        }
        if (removed) {
            --n_edges;
            return true;
        }
        else {return false;}
    }
}

template<typename K, typename W>
bool Graph<K, W>::updateEdge(K a, K b, W newWeight) {
    bool updated {false};
    if (!is_directed) {
        Vertex* vertA;
        Vertex* vertB;
        if (vertices.find(a, vertA)) {
            for (auto& i : vertA->edgesOut) {
                if (i->src == a && i->dst == b) {
                    i->weight = newWeight;
                    updated = true;
                }
            }
        }
        if (vertices.find(b, vertB)) {
            for (auto& i : vertB->edgesOut) {
                if (i->src == b && i->dst == a) {
                    i->weight = newWeight;
                    updated = true;
                }
            }
        }
        if (updated) {return true;}
        else {return false;}
    }
    else if (is_directed) {
        Vertex* vertA;
        if (vertices.find(a, vertA)) {
            for (auto& i : vertA->edgesOut) {
                if (i->src == a && i->dst == b) {
                    i->weight = newWeight;
                    updated = true;
                }
            }
        }
        if (updated) {return true;}
        else {return false;}
    }
}

template<typename K, typename W>
void Graph<K, W>::clear() {
    vertices.clear();
    n_edges = 0;
}

template<typename K, typename W>
bool Graph<K, W>::findVertex(K a) const {
    Vertex* dummy;
    return vertices.find(a, dummy);
}

template<typename K, typename W>
bool Graph<K, W>::isAdjacent(K a, K b) const {
    Vertex* vertA;
    if (vertices.find(a, vertA)) {
        for (auto& i : vertA->edgesOut) {
            if (i->src == a && i->dst == b) {
                return true;
            }
        }
    }
    return false;
}

template<typename K, typename W>
bool Graph<K, W>::isAdjacent(K a, K b, W& wt) const {
    Vertex* vertA;
    if (vertices.find(a, vertA)) {
        for (auto& i : vertA->edgesOut) {
            if (i->src == a && i->dst == b) {
                wt = i->weight;
                return true;
            }
        }
    }
    return false;
}

template<typename K, typename W>
list<K> Graph<K, W>::getAdjacencyList(K a) {
    Vertex* source;
    list<K> adjList;
    if (!is_directed) {
        if (vertices.find(a, source)) {
            for (auto &i : source->edgesOut) {
                adjList.push_back(i->dst);
            }
        }
        return adjList;
    }
    if (is_directed) {
        if (vertices.find(a, source)) {
            for (auto &i : source->edgesIn) {
                adjList.push_back(i->src);
            }
        }
        return adjList;
    }
}

template<typename K, typename W>
bool Graph<K, W>::confirmPath(const list<K>& vertexList) const {
    auto iter {vertexList.begin()};
    while (iter != --vertexList.end()) {
        Vertex* vert;
        vertices.find(*iter, vert);
        bool adjFound {false};
        for (auto &j: vert->edgesOut) {
            if (*std::next(iter, 1) == j->dst) {
                adjFound = true;
                break;
            }
        }
        if (!adjFound) {return false;}
        ++iter;
    }
    return true;
}

template<typename K, typename W>
W Graph<K, W>::pathWeight(const list<K>& vertexList) const {
    if (!confirmPath(vertexList)) {return 0;}
    W totWeight {0};
    auto iter {vertexList.begin()};
    while (iter != vertexList.end()) {
        Vertex* vert;
        vertices.find(*iter, vert);
        for (auto& j : vert->edgesOut) {
            if (*std::next(iter, 1) == j->dst) {
                totWeight += j->weight;
                break;
            }
        }
        ++iter;
    }
    return totWeight;
}

template<typename K, typename W>
list<K> Graph<K, W>::shortestPath(K from, K to, W& length) {
    list<K> Path;
    HashTable<K, Vertex*> unvisitedQueue {vertices};

    std::vector<std::pair<K, W>> weights; // array of weights from start to vertex
    weights.push_back({from, 0}); // insert initial weights as 0 start node

    std::vector<std::pair<K, list<K>>> paths; // vector of paths for each vertex that correspond to the weights vector
    paths.push_back({from, {from}});

    Vertex* curVert; // current vertex
    vertices.find(from, curVert); // initialize curVert to from

    W altPathDistance;
    W curPathDistance;
    list<K> altPath;
    list<K> curPath;
    while (!unvisitedQueue.empty()) {
        // Find current path distance
        for (auto& i : weights) {
            if (i.first == curVert->key) {
                curPathDistance = i.second;
                break;
            }
        }
        // Find current path
        for (auto& i : paths) {
            if (i.first == curVert->key) {
                curPath = i.second;
                break;
            }
        }

        // Calculate neighbor path distance and update weights and paths as necessary
        Vertex* dstVert;
        for (auto& i : curVert->edgesOut) {
            K dstVertKey {i->dst};
            unvisitedQueue.find(dstVertKey, dstVert);
            altPathDistance = curPathDistance + (i->weight);
            altPath = curPath;
            altPath.push_back(i->dst);
            bool found {false}; // boolean value if key is found in weights, so if no entry is present for a vertex, it can be initialized in the array.
            bool updated {false}; // boolean value if key is found in weights and weight is less that current weight, then must update paths.
            for (auto& j : weights) {
                if (dstVertKey == j.first) {
                    found = true;
                    if (altPathDistance < j.second) {
                        updated = true;
                        j.second = altPathDistance;
                    }
                    break;
                }
            }
            if (!found) { weights.push_back({dstVertKey, altPathDistance}); }
            // Update path
            for (auto& j : paths) {
                if ((dstVertKey == j.first) && (updated == true)) {
                    j.second = altPath;
                }
            }
            if (!found) { paths.push_back({dstVertKey, altPath}); }
        }
        Vertex* dummy; // used to hold useless values from HashTable::find() or HashTable::erase()
        unvisitedQueue.erase(curVert->key, dummy);

        // determine next vertex to go to
        W min;
        Vertex* minVert;
        // initialize min value to first vertex that is unvisited.
        for (auto& i : weights) {
            if ((unvisitedQueue.find(i.first, minVert))) {
                min = i.second;
            }
        }
        for (auto& i : weights) {
            if ((unvisitedQueue.find(i.first, dummy)) && (i.second < min)) {
                min = i.second;
                unvisitedQueue.find(i.first, minVert);
            }
        }
        curVert = minVert;
    }

    for (auto& i : weights) {
        if (i.first == to) {
            length = i.second;
            break;
        }
    }

    for (auto& i : paths) {
        if (i.first == to) {
            Path = i.second;
        }
    }
    return Path;
}

//---------------------------

// function templates for BFS and DFS

// G is graph class  -- for this assignment, you can assume it will be
// some instance of Graph<K,W>

// K is key type, used to locate the starting vertex (must be the same as Graph's K)

// V is function class that performs "visit" operation -- return true to stop traversal/search
// V must provide function call operator that takes a K parameter and returns a bool

template <class G, class K, class V>
void BFS(G& graph, K start, V& visit) {
    std::set<K> discoveredSet;
    std::queue<K> frontierQueue;
    discoveredSet.insert(start);
    frontierQueue.push(start);
    while (!frontierQueue.empty()) {
        K n {frontierQueue.front()};
        frontierQueue.pop();
        if (visit(n)) {return;}
        for (auto& j : graph.getAdjacencyList(n)) {
            if (discoveredSet.find(j) == discoveredSet.end()) {
                frontierQueue.push(j);
                discoveredSet.insert(j);
            }
        }
    }
}

template <class G, class K, class V>
void DFS(G& graph, K start, V& visit) {
    K vert {start};
    list<K> adjList {graph.getAdjacencyList(start)};
    if (visit(vert)) {return;}
    std::set<K> visitedSet;
    std::vector<K> history;
    while (visitedSet.size() != graph.numVertices()) {
        visitedSet.insert(vert);
        history.push_back(vert);
        if (adjList.empty()) {
            vert = history.back();
                history.pop_back();
                adjList = graph.getAdjacencyList(vert);
            }
            else {
                auto iter = adjList.begin();
                bool jumpFound {false};
                for (iter; iter != adjList.end(); ++iter) {
                if ((adjList.size() == 1) && ((visitedSet.find(*iter) != visitedSet.end()) || (*iter == *(history.end() - 2)))) {
                    vert = *(history.end() - 2);
                    history.pop_back();
                    history.pop_back();
                    adjList = graph.getAdjacencyList(vert);
                    jumpFound = true;
                    break;
                }
                if (visitedSet.find(*iter) == visitedSet.end()) {
                    vert = *iter;
                    if (visit(vert)) {return;}
                    adjList = graph.getAdjacencyList(vert);
                    jumpFound = true;
                    break;
                }
            }
            if (!jumpFound) {
                vert = *(history.end() - 2);
                history.pop_back();
                history.pop_back();
                adjList = graph.getAdjacencyList(vert);
            }
        }
    }
}

// Other template functions can be added as needed.
// Do not create a Graph.cpp file.


#endif //ECE309_SPR23_STREETMAP_GRAPH_H