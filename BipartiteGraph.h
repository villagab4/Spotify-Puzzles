#ifndef BIPARTITEGRAPH_H
#define BIPARTITEGRAPH_H
#include "Node.h"
#include <list>
#include <map>

/** Bipartite Graph to be used for CatvDog problem.
 *  This is a header file, method definitions
 *  can be found in main cpp file.
 *  @author: Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date: May 29, 2017
 */

class BipartiteGraph {

public:

	// Constructor
    BipartiteGraph(int numC, int numD);

    // Add edge to graph
	void addEdge(Node* from, Node* to);

	// Returns true if augmented path exists
	bool bfs();

	// Adds augmented path if there is one beginning with v
	bool dfs(Node* v);

	// Returns size of maximum matching... same
	// as minimum vertex cover.
	int HopcroftKarp();

	// Add cat lover to set of cats
	void addCats(Node *cat);

	// Add dog lover to set of dogs
	void addDogs(Node *dog);

private:

	// Represents cardinality of each set
	// in the biparitite sets of graph
	int numCats, numDogs;

	// adj[C] stores adjacents of cat voter C.
	// 0 is used for dummy vertex since range is 
	// from 1 to numCats. Same for dogs. 
	std::map<Node*, std::list<Node*>> adj;

	// Stores the set of cats and dogs lovers
	std::list<Node*> cats, dogs;

	// Necessary for Hopcroft-Karp algorithm
	std::map<Node*, int> dist;
	std::map<Node*, Node*> pairC, pairD;

};

#endif