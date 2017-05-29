/** This is the final solution to the Spotify Cat vs Dog puzzle.
 *  Each voter is added to a graph as a node object. After storing all
 *  voters in a graph, I use the Hopcroft-Karp algorithm to determine 
 *  the number of edges in a maximum matching of the graph. This also determines
 *  the number of vertices in the minimum vertex cover of the graph, which can 
 *  be used to solve for the maximum of satisfied voters.
 *  @author Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date:  May 29, 2017 
 */

#include <iostream>
#include <vector>
#include <string>
#include "BipartiteGraph.h"
#include "Node.h"


void buildGraph(int numVoters, BipartiteGraph *voters, std::vector<Node*> &listOfVertices) {

	//Initialize variables.
	std::string keep = "";
	std::string kick = "";
	bool catLover;

	for (int i = 0; i < numVoters; i++) {

		// Get voter information and store as string
		std::cin >> keep >> kick;

		Node *curr;

		if (keep.at(0) == 'C') {
			catLover = true;
			curr = new Node(keep, kick);
			voters->addCats(curr);
		} else {
			catLover = false;
			curr = new Node(keep, kick);
			voters->addDogs(curr);
		}

		listOfVertices.push_back(curr);

		for (Node *v : listOfVertices) {

			// As long as views CONFLICT, connect with edge. De Morgan's
			// law says this is valid method of checking.
			if (!(curr->getKeep().compare(v->getKick()) && curr->getKick().compare(v->getKeep()))) {

				// Determine proper ordering of edges
				// In addEdge method, cat must go first.
				if (catLover) voters->addEdge(curr, v);
				else		  voters->addEdge(v, curr);

			}

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

		std::vector<Node*> listOfVertices;

		// This graph will hold all the voters and their
		// respective votes.
		BipartiteGraph *voters = new BipartiteGraph(numCats, numDogs);

		// Populate the map properly based on voter input.
		buildGraph(numVoters, voters, listOfVertices);

		// Print maximum satisfied voters.
		std::cout << (numVoters - voters->HopcroftKarp()) << std::endl;

		// Free dynamically allocated memory
		for (Node* n: listOfVertices) {delete(n);}

		delete(voters);

		// Move on to next trial (if such trial exists).
		y++;

	}

}