#include <iostream>
#include <fstream>
#include <list>
#include <unordered_set>
#include <vector>
#include <random>
#include <string>

using std::list;
using std::unordered_set;

// DO NOT MODIFY GRAPH NODE DEFINITION
class GraphNode {
  // This class represents a single node
  
public:
    std::string name;     // name of the node

    list<GraphNode*> adjList; // adjacency list for the node -- list of other nodes
    // constructor requires a name, so that we can print out the
    // nodes by name.
    GraphNode(std::string n, list<GraphNode*> adj={}):name(n),adjList(adj) {}

    // Add an edge to adjacency list; add to both nodes
    void addEdge(GraphNode *g)
    {
        adjList.push_back(g);
        g->adjList.push_back(this);
    }
};

// DO NOT MODIFY FUNCTION ARGUMENTS OR RETURN TYPE
// dfs_search:
//    GraphNode *g          : a pointer to the node where you should begin DFS
//    list<GraphNode*> &dfs : list of visited nodes; append to this list
//                           as you traverse.  Use push_back() member function.
//    unordered_set<GraphNode*> &visited:
//                          this is a hash table provided by the std library.
//                          Use insert(g) member function to add to it. Use find()
//                          member function to search if a node has been visited.
//
//    You must implement this as a recursive function.
void dfs_search(GraphNode *g, std::list<GraphNode*> &dfs, std::unordered_set<GraphNode*> &visited)
{
    if (visited.find(g) == visited.end()) {
        dfs.push_back(g);
        visited.insert(g);
    }
    for (auto& i : g->adjList) {
        if (visited.find(i) == visited.end()) {
            dfs.push_back(i);
            visited.insert(i);
            dfs_search(i, dfs, visited);
        }
    }
    return;
}

// DO NOT MODIFY FUNCTIONS AFTER THIS POINT
std::ostream& operator << (std::ostream& out, const std::list<GraphNode*> &dfs)
{
  out << "DFS order: \n";
  for(auto i = dfs.cbegin(); i!=dfs.cend(); i++)
    {
      if (i!=dfs.cbegin())
	out << ", ";
      out << (*i)->name;
    }
  out << std::endl;
  return out;
}

GraphNode *random_graph(int nodes)
{
  std::vector<GraphNode*> graph;
  for(auto i = 0;  i<nodes; i++)
    {
      graph.push_back( new GraphNode( std::to_string(i) ) );
    }

  std::cout << graph.size() << std::endl;
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist(0,nodes-1);

  for(auto i = 0; i<nodes; i++)
    {
      auto r = dist(generator);
      graph[i]->addEdge( graph[r] );
      if (i>0)
	      graph[i]->addEdge( graph[i-1] );
    }

  return graph[0];
}

int main()
{
  {
    GraphNode *a = new GraphNode("a");
    GraphNode *b = new GraphNode("b");
    GraphNode *c = new GraphNode("c");
    GraphNode *d = new GraphNode("d");
    GraphNode *e = new GraphNode("e");
    
    a->addEdge(b);
    a->addEdge(c);
    a->addEdge(d);
    d->addEdge(e);
    
    std::list<GraphNode*> dfs;
    std::unordered_set<GraphNode*> visited;
    
    dfs_search(a,dfs,visited);
    
    std::cout << dfs;
  }
    
  return 0;
}
