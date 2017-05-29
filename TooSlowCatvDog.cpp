#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include "Graph.h"
#include "Node.h"

/** This is a solution to the Spotify Cat vs Dog puzzle.
 *  Each voter is added to a graph as a node object. After storing all
 *  voters in a graph, I use the Bron Kerbosch algorithm to determine 
 *  the maximal clique within the graph which represents the maximum
 *  number of satisfied customers. Note, finding the maximal clique
 *  in a graph is an NP-complete problem. 
 *  @author Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date:  May 26, 2017 
 */

// Update during BronKerbosch Algorithm
unsigned int maximalCliqueSize = 0;

/** This method constructs a simple unweighted graph with each 
 *  voter as a vertex. Two vertices are connected if their
 *  votes are not conflicting. That is: (a,b) in E(G) st
 *  a->keep != b->kick && a->kick != b->keep.
 */

void buildGraph(int numVoters, Graph &voters) {

	//Initialize variables.
	std::string keep = "";
	std::string kick = "";

	for (int i = 0; i < numVoters; i++) {

		// Get voter information and store as string
		std::cin >> keep >> kick;

		Node* curr = new Node(keep, kick);

		// Add current vertex to graph
		curr = voters.addVertex(curr);

		for (Node *v : voters.vertices) {

			// As long as views do not conflict, connect with edge.
			if (curr->keep.compare(v->kick) && curr->kick.compare(v->keep)) {
				voters.addEdge(curr, v);
				voters.addEdge(v, curr);
			}

		}

	}

}

/** This method returns the maximum number of satisfied customers.
 *  Using the Bron-Kerbosch algorithm, the program discovers the size 
 *  of the largest maximal clique in the graph. Each clique represents a
 *  subset of voters with non-conflicting views. Thus, the largest clique
 *  represents the largest possible group of satisfied voters.
 */

void BornKerbosch(std::list<Node*> R, std::list<Node*> P, std::list<Node*> X) {

	if ( (P.empty()) && (X.empty()) ) {

		if (R.size() > maximalCliqueSize) maximalCliqueSize = R.size();
		
	} else {

		std::map<Node*, int> intersectFind;

		// Determine pivot as elemnet in P U X with
		// most neighbors.

		// std::list<Node*> mUnion (P);

		// Add each P entry to a map
		for (auto uIter = P.begin(); uIter != P.end(); uIter++) {
			intersectFind[*uIter]++;
		}

		Node *pivot;
		if (!P.empty()) pivot = P.front();
		else 			pivot = X.front();

		// Create list of P \ N(pivot)
		std::list<Node*> Pprime (P);

		// Since intersectFind map was not cleared, still has 
		// entries from P. Can just iterate through to find overlap
		for (auto iter3 = pivot->edges.begin(); iter3 != pivot->edges.end(); iter3++) {

			if (intersectFind[*iter3] != 0) Pprime.remove(*iter3);

		}

		for (auto iter4 = Pprime.begin(); iter4 != Pprime.end(); /* Intentionally blank. */) {

			Node *temp = *iter4;
			std::list<Node*> Rprime (R);
			std::list<Node*> Xprime;
			std::list<Node*> Pdoubleprime;

			// Union R and iter4
			if (std::find(R.begin(), R.end(), temp) == R.end()) Rprime.push_back(temp);

			// Intersect P and N(*iter4). Since intersectFind
			// still contains P elements, only need 1 iteration
			for (auto edgeIt = temp->edges.begin(); edgeIt != temp->edges.end(); edgeIt++) {
				if (intersectFind[*edgeIt] > 0) Pdoubleprime.push_back(*edgeIt);
			}

			// Reset map since done using P entries
			intersectFind.clear();

			// Intersect X and N(*iter4)
			for (auto itX = X.begin(); itX != X.end(); itX++) {
				intersectFind[*itX]++;
			}
			for (auto edgeIt2 = temp->edges.begin(); edgeIt2 != temp->edges.end(); edgeIt2++) {
				if (intersectFind[*edgeIt2] > 0) Xprime.push_back(*edgeIt2);
			}
			
			BornKerbosch(Rprime, Pdoubleprime, Xprime);

			// Remove iter4 from P
			P.remove(*iter4++);

			// Union X and iter4
			if (std::find(X.begin(), X.end(), temp) == X.end()) X.push_back(temp);

			// Clear for next iteration
			intersectFind.clear();

		}
	}
}

int main() {

	// Initialize variables.
	int numCats, numDogs, numVoters, numTrials;
	std::cin >> numTrials;
	int y = 0;

	while (y < numTrials) {

		std::cin >> numCats >> numDogs >> numVoters;

		// This graph will hold all the voters and their
		// votes.
		Graph voters = Graph(numVoters);

		// Populate the map properly based on voter input.
		buildGraph(numVoters, voters);

		/**
		for (Node *vert : voters.vertices) {
			std::cout << "Keep is: " << vert->keep << " | Kick is: " << vert->kick << std::endl;
			int size = vert->edges.size();
			std::cout << "Connected to " << size << " vertices" << std::endl;
			std::cout << "List of Edges: ";
			for (Node *n : vert->edges) {
				std::cout << n->keep << " " << n->kick << "\t";
			}
			std::cout << std::endl;
		} */

		// Determine maximal clique
		std::list<Node*> R;
		std::list<Node*> X;

		BornKerbosch(R, voters.vertices, X);

		// Print maximum clique size
		std::cout << maximalCliqueSize << std::endl;

		// Free dynamically allocated memory
		for (Node* n: voters.vertices) {delete(n);}

		// Reset maximalCliqueSize
		maximalCliqueSize = 0;

		// Move on to next trial (if such trial exists).
		y++;

	}

}