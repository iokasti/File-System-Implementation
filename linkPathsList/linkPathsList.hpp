#ifndef LINKPATHSLIST_LINKPATHSLIST_HPP_
#define LINKPATHSLIST_LINKPATHSLIST_HPP_

#include <string>

struct linkPathsListNode {
	std::string linkPath;
	linkPathsListNode* next;
};

class linkPathsList {
private:
	linkPathsListNode* head;
	int size;
public:
	linkPathsList();
	~linkPathsList();

	void insert(std::string);
	std::string popFront();
	int getSize();
};

#endif /* LINKPATHSLIST_LINKPATHSLIST_HPP_ */
