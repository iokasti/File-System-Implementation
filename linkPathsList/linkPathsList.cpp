#include "linkPathsList.hpp"

using namespace std;

linkPathsList::linkPathsList() {
	size = 0;
	head = NULL;
}
linkPathsList::~linkPathsList() {
	linkPathsListNode *temp = head;
	if (head != NULL) {
		while (head->next != NULL) {
			temp = head->next;
			delete head;
			head = temp;
		}
		delete head;
	}
}
//	normal insert but if the path already exists we skip it
void linkPathsList::insert(string path) {
	// search the list for path
	linkPathsListNode *temp = head;
	while (temp != NULL) {
		if (temp->linkPath == path) {
			// if found return and don't add it again
			return;
		}
		temp = temp->next;
	}
	// not found add it
	if (head == NULL) {
		head = new linkPathsListNode();
		head->linkPath = path;
		head->next = NULL;
	} else {
		temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new linkPathsListNode();
		temp->next->linkPath = path;
		temp->next->next = NULL;
	}
	size++;
}

string linkPathsList::popFront() {
	string linkPath = "";
	if (head != NULL) {
		linkPathsListNode *temp = head->next;
		linkPath = head->linkPath;
		delete head;
		head = temp;
	}
	size--;
	return linkPath;
}

int linkPathsList::getSize() {
	return size;
}
