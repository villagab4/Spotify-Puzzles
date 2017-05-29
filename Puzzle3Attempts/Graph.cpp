/** Graph to be used for CatvDog problem.
 *  This is a header file, method definitions
 *  can be found in main file.
 *  @author: Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date: May 27, 2017
 */

#include "Graph.h"
#include "Node.h"
#include <algorithm>
#include <iostream> // Remove after

struct NodeMatch {

 	NodeMatch(Node* n): compare(n) {}

 	bool operator()(const Node* element) const {
 		return element == compare; // Compare references
 	}

 	private:

 	Node* compare;

 };

Node* Graph::addVertex(Node* v) {

	// Add vertex to list of vertices
	this->vertices.emplace_back(v);
	return v;

}

void Graph::addEdge(Node* from, Node* to) {

	// Check that not creating self loop
	if (from != to) {
		
		// Check that node exists in vertices list
		if ( (std::find(this->vertices.begin(), this->vertices.end(), from) != this->vertices.end() ) &&
		std::find(this->vertices.begin(), this->vertices.end(), to) != this->vertices.end() ) {
			

			// Add 'to' vertex to 'from' adjacency list, except
			// when 'to' is already present in the adjacency list
			if ( std::find(from->edges.begin(), from->edges.end(), to) == from->edges.end() ) from->edges.push_back(to);

			// Add 'from' vertex to 'to' adjacency list, except
			// when 'from' is already present in the adjacency list
			if ( std::find(to->edges.begin(), to->edges.end(), from) == to->edges.end() ) to->edges.push_back(from);

		}	
	}

}

void Graph::removeVertex(Node* v) {

	// Iterate through this vertex's edge list, 
	// go to each vertex and eliminate this vertex
	// from their edge list.
	for (Node* n : v->edges) {
		n->edges.remove_if(NodeMatch(v));
	}

	// Delete vertex from list of vertices.
	this->vertices.remove_if(NodeMatch(v));

}

void Graph::removeEdge(Node* from, Node* to) {

	// Remove edge from 'from' edge list
	from->edges.remove_if(NodeMatch(to));

	// Remove edge from 'to' edge list
	to->edges.remove_if(NodeMatch(from));

}
