#ifndef NODE_H
#define NODE_H
#include <string>

/** Node class which will contain voter. */

class Node {

	public:

		Node(std::string yes, std::string no) : keep(yes), kick(no) {}
		std::string getKeep() {return keep;}
		std::string getKick() {return kick;}

	private:

		std::string keep;
		std::string kick;

};

#endif