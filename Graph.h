#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include <list>
#include <string>

/** Graph to be used for CatvDog problem.
 *  This is a header file, method definitions
 *  can be found in main cpp file.
 *  @author: Gabe Villasana
 *  @email: villagab4@gmail.com
 *  @date: May 27, 2017
 */

class Graph {

public:

    Graph(int numV) : numVertices(numV) {}

	Node* addVertex(Node* v);

	void addEdge(Node* from, Node* to);

	void removeVertex(Node* v);

	void removeEdge(Node* from, Node* to);

	int numVertices;

	std::list<Node*> vertices;

};

#endif