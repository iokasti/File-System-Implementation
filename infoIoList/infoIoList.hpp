#ifndef INFOIOLIST_INFOIOLIST_HPP_
#define INFOIOLIST_INFOIOLIST_HPP_

#include <string>

struct pidIo {
	unsigned long rchar;
	unsigned long wchar;
	unsigned int syscr;
	unsigned int syscw;
	unsigned long read_bytes;
	unsigned long write_bytes;
	unsigned long cancelled_write_bytes;
};

struct infoIoListNode {
	pidIo io;
	std::string processPID;
	infoIoListNode* next;
};

class infoIoList {
private:
	infoIoListNode* head;
	int records;
	std::string fieldname;
	int size;
public:
	infoIoList(int, std::string);
	~infoIoList();

	void insert(pidIo, std::string );
	void print();

	void sortPID();
	void sortRCHAR();
	void sortWCHAR();
	void sortSYSR();
	void sortSYSW();
	void sortRFS();
	void sortWFS();

};

#endif /* INFOIOLIST_INFOIOLIST_HPP_ */
