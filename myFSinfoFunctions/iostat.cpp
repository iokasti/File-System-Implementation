#include "myFSinfoFunctions.hpp"
#include "../linkPathsList/linkPathsList.hpp"
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <fstream>
#include <grp.h>
#include <pwd.h>
#include <sstream>
#include <unistd.h>
#include <limits.h>

using namespace std;

int myFSinfoFunctions::iostat(int records, string fieldname) {
	pid_t ttyPID = getppid();
	string directory = "/proc";

	DIR* dirPtr;
	struct dirent *direntp;
	dirPtr = opendir(directory.c_str());
	if (dirPtr == NULL) {
		perror(directory.c_str());
		return -1;
	}

	cout << "PID\t\tRCHAR\t\tWCHAR\t\tSYSR\t\tSYSW\t\tRFS\t\t\tWFS" << endl;
	infoIoList *ioList = new infoIoList(records, fieldname);
	while ((direntp = readdir(dirPtr)) != NULL) {
		if (strcmp(direntp->d_name, ".") == 0
				|| strcmp(direntp->d_name, "..") == 0) {
			// ignore . and ..
			continue;
		}
		if (isdigit(direntp->d_name[0])) {
			// first letter of d_name is digit so it's a process directory
			string d_name = direntp->d_name;
			string processStatPath = "/proc/" + d_name + "/stat";
			if (isChildOfPPID(processStatPath, ttyPID) == true) {
				// process is a descendant of the ttyPID
				string processIoPath = "/proc/" + d_name + "/io";
				pidIo io = readPidIo(processIoPath);
				ioList->insert(io, d_name);
			}
		}
	}
	ioList->print();
	cout << "----------------------------------------------------" << endl;
	delete ioList;
	return 0;
}

pidIo myFSinfoFunctions::readPidIo(string pidIoPath) {
	pidIo io;
	ifstream infile(pidIoPath.c_str());
	string line;
	while (getline(infile, line)) {
		istringstream iss(line);
		string name;
		iss >> name;
		if (name == "rchar") {
			iss >> io.rchar;
		} else if (name == "wchar") {
			iss >> io.wchar;
		} else if (name == "syscr") {
			iss >> io.syscr;
		} else if (name == "syscw") {
			iss >> io.syscw;
		} else if (name == "read_bytes") {
			iss >> io.read_bytes;
		} else if (name == "write_bytes") {
			iss >> io.write_bytes;
		} else if (name == "cancelled_write_bytes") {
			iss >> io.cancelled_write_bytes;
		}

	}
	return io;
}
