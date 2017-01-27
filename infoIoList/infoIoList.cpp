#include "infoIoList.hpp"
#include <iostream>

using namespace std;

infoIoList::infoIoList(int records, string fieldname) {
	this->records = records;
	this->fieldname = fieldname;
	size = 0;
	head = NULL;
}
infoIoList::~infoIoList() {
	infoIoListNode *temp = head;
	if (head != NULL) {
		while (head->next != NULL) {
			temp = head->next;
			delete head;
			head = temp;
		}
		delete head;
	}
}
// normal insert
void infoIoList::insert(pidIo io, string processPID) {
	// search the list for path
	if (head == NULL) {
		head = new infoIoListNode();
		head->io = io;
		head->processPID = processPID;
		head->next = NULL;
	} else {
		infoIoListNode *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new infoIoListNode();
		temp->next->io = io;
		head->next->processPID = processPID;
		temp->next->next = NULL;
	}
	size++;
}

// sort the list by PID
void infoIoList::sortPID() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->processPID > tmpPtr->processPID) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// sort the list by RCHAR
void infoIoList::sortRCHAR() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->io.rchar > tmpPtr->io.rchar) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// sort the list by WCHAR
void infoIoList::sortWCHAR() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->io.wchar > tmpPtr->io.wchar) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// sort the list by SYSR
void infoIoList::sortSYSR() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->io.syscr > tmpPtr->io.syscr) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// sort the list by SYSW
void infoIoList::sortSYSW() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->io.syscw > tmpPtr->io.syscw) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// sort the list by RFS
void infoIoList::sortRFS() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->io.read_bytes > tmpPtr->io.read_bytes) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// sort the list by WFS
void infoIoList::sortWFS() {
	infoIoListNode *tmpPtr = head;
	infoIoListNode *tmpNxt = head->next;
	string tmpPID;
	pidIo tempIO;
	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (tmpNxt->io.write_bytes > tmpPtr->io.write_bytes) {
				tmpPID = tmpPtr->processPID;
				tempIO = tmpPtr->io;
				tmpPtr->processPID = tmpNxt->processPID;
				tmpPtr->io = tmpNxt->io;
				tmpNxt->processPID = tmpPID;
				tmpNxt->io = tempIO;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNxt = tmpNxt->next;
	}
}

// print sorted list according to requested fieldname
void infoIoList::print() {
	if (fieldname == "PID") {
		sortPID();
	} else if (fieldname == "RCHAR") {
		sortRCHAR();
	} else if (fieldname == "WCHAR") {
		sortWCHAR();
	} else if (fieldname == "SYSR") {
		sortSYSR();
	} else if (fieldname == "SYSW") {
		sortSYSW();
	} else if (fieldname == "RFS") {
		sortRFS();
	} else if (fieldname == "WFS") {
		sortWFS();
	}
	infoIoListNode *temp = head;
	int i=0;
	while (temp != NULL) {
		if(i==records){
			break;
		}
		cout << temp->processPID << "\t\t" << temp->io.rchar << "\t"
				<< temp->io.wchar << "\t\t" << temp->io.syscr << "\t"
				<< temp->io.syscw << "\t\t" << temp->io.read_bytes << "\t\t"
				<< temp->io.write_bytes << endl;
		temp = temp->next;
		i++;
	}

}
