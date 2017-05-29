/** Bipartite Graph to be used for CatvDog problem.
 *  Definitions of methods.
 *  @author: Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date: May 29, 2017
 */

#include "BipartiteGraph.h"
#include "Node.h"
#include <queue>

#define INF (1<<28) // ~Infinity
#define NIL (NULL) // Dummy variable

// Constructor
BipartiteGraph::BipartiteGraph(int numC, int numD) : numCats(numC), numDogs(numD) {}

// Add edges
void BipartiteGraph::addEdge(Node* cat, Node* dog) {

	// Add member to respective adj list
	adj[cat].push_back(dog);
	adj[dog].push_back(cat);

}

// Returns true if augmenting path
bool BipartiteGraph::bfs() {

	// Queue for processing
	std::queue<Node*> Q;

	// Iterate through all cats
	for (auto it = cats.begin(); it != cats.end(); ++it) {

		// If free vertex, add to Queue
		if (pairC[*it] == 0) {

			dist[*it] = 0;
			Q.push(*it);

		} else dist[*it] = INF;

	}

	dist[NIL] = INF;

	// Process Queue
	while(!Q.empty()) {

		// Deque voter
		Node* voter = Q.front();
		Q.pop();

		// If node is not 0, and can provide shorter path to 0
		if (dist[voter] < dist[NIL]) {

			// Get all neighbors of voter
			for (auto it = adj[voter].begin(); it!= adj[voter].end(); ++it) {

				Node* d = *it;

				// If pair of neighbor is not considered so far, 
				// havent explored its edges.
				if (dist[pairD[d]] == INF) {

					// Consider pair and add to queue
					dist[pairD[d]] = dist[voter] + 1;	
					Q.push(pairD[d]);

				}

			}

		}

	}

	return dist[NIL] != INF;

}

// Returns true if there exists an augmenting path
// beginning with free vertex v
bool BipartiteGraph::dfs(Node *c) {

	if (c != NIL) {

		for (auto it = adj[c].begin(); it != adj[c].end(); ++it) {

			Node* d = *it;

			if (dist[pairD[d]] == (dist[c] + 1) ) {

				// If dfs for pair of d also returns true
				if (dfs(pairD[d])) {
					pairD[d] = c;
					pairC[c] = d;
					return true;
				}

			}

		}

		// If no augmenting path beginning with c
		dist[c] = INF;
		return false;

	}

	return true;

}

// Perform Hopcroft Karp algorithm for maximum matching
int BipartiteGraph::HopcroftKarp() {
	int maximumMatching = 0;
	
	// Keep updating if augmented path exists
	while(bfs()) {

		// Find free vertex. Free vertex is vertex 
		// not connected to matching edge.
		for (auto it = cats.begin(); it != cats.end(); ++it) {

			// If curr vertex is free and has augmenting
			// path, increase matching size
			if (pairC[*it]==0 && dfs(*it)) maximumMatching++;

		}

	}

	return maximumMatching;

}

// Add cat lover to cat set
void BipartiteGraph::addCats(Node* cat) {
	cats.push_back(cat);
}

// Add dog lover to dog set
void BipartiteGraph::addDogs(Node* dog) {
	dogs.push_back(dog);
}