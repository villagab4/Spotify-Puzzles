#ifndef NODE_H
#define NODE_H
#include <string>
#include <list>

/** Node class which will contain voter. */

class Node {

	public:

		Node(std::string yes, std::string no) : keep(yes), kick(no) {}

		void addEdge(Node* neighbor) {
			edges.push_back(neighbor);
		}

		std::string keep;
		std::string kick;
		std::list<Node*> edges;

};

#endif