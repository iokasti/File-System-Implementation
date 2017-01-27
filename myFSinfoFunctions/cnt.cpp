#include "myFSinfoFunctions.hpp"
#include <sys/stat.h>
#include <iostream>
#include <cstdio>

using namespace std;

int myFSinfoFunctions::cnt(string directory) {
	DIR* dirPtr;
	struct stat info;
	struct dirent *direntp;
	dirPtr = opendir(directory.c_str());
	if (dirPtr == NULL) {
		perror(directory.c_str());
		return -1;
	}
	while ((direntp = readdir(dirPtr)) != NULL) {
		if (strcmp(direntp->d_name, ".") == 0
				|| strcmp(direntp->d_name, "..") == 0) {
			// ignore . and ..
			continue;
		}

		// initialize stat info
		string path = directory + "/" + direntp->d_name;
		stat(path.c_str(), &info);

		//	Directories
		if ((info.st_mode & S_IFMT) == S_IFDIR) {
			direc++;
			cnt(path);
		}
		// Regular Files
		else if ((info.st_mode & S_IFMT) == S_IFREG) {
			regFiles++;
		}
		//	Block Device Files
		else if ((info.st_mode & S_IFMT) == S_IFBLK) {
			block++;
		}
		//	Char Devices
		else if ((info.st_mode & S_IFMT) == S_IFCHR) {
			character++;
		}
		//	Fifo
		else if ((info.st_mode & S_IFMT) == S_IFIFO) {
			fifo++;
		}
		//	Symbolic Link
		else if ((info.st_mode & S_IFMT) == S_IFLNK) {
			symLink++;
		}
		//	Socket
		else if ((info.st_mode & S_IFMT) == S_IFSOCK) {
			socket++;
		}
	}

	closedir(dirPtr);
	return 0;
}

void myFSinfoFunctions::printCnt() {
	int allCont = regFiles + direc + block + character + fifo + symLink
			+ socket;
	cout << "All files:\t\t" << allCont << "\t100%" << endl;
	cout << "Regular files:\t\t" << regFiles << "\t"
			<< ((allCont != 0) ? 100 * regFiles / (double) allCont : 0) << "%" 	// make sure we don't divide by zero, likewise below
			<< endl;
	cout << "Directories:\t\t" << direc << "\t"
			<< ((allCont != 0) ? 100 * direc / (double) allCont : 0) << "%"
			<< endl;
	cout << "Symbolic links:\t\t" << symLink << "\t"
			<< ((allCont != 0) ? 100 * symLink / (double) allCont : 0) << "%"
			<< endl;
	cout << "Named pipes:\t\t" << fifo << "\t"
			<< ((allCont != 0) ? 100 * fifo / (double) allCont : 0) << "%"
			<< endl;
	cout << "Char devices:\t\t" << character << "\t"
			<< ((allCont != 0) ? 100 * character / (double) allCont : 0) << "%"
			<< endl;
	cout << "Sockets:\t\t" << socket << "\t"
			<< ((allCont != 0) ? 100 * socket / (double) allCont : 0) << "%"
			<< endl;
	cout << "Block device files:\t" << block << "\t"
			<< ((allCont != 0) ? 100 * block / (double) allCont : 0) << "%"
			<< endl;
}


