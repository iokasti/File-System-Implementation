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

int myFSinfoFunctions::ft() {
	pid_t ttyPID = getppid();
	string directory = "/proc";

	int totalOpenFiles = 0;

	DIR* dirPtr;
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
		if (isdigit(direntp->d_name[0])) {
			// first letter of d_name is digit so it's a process directory
			string d_name = direntp->d_name;
			string processStatPath = "/proc/" + d_name + "/stat";
			if (isChildOfPPID(processStatPath, ttyPID) == true) {
				// process is a descendant of the ttyPID
				string processFdPath = "/proc/" + d_name + "/fd";
				DIR* fdDirPtr;
				struct dirent *fdDirentp;
				fdDirPtr = opendir(processFdPath.c_str());
				if (fdDirPtr == NULL) {
					perror(processFdPath.c_str());
					return -1;
				}
				linkPathsList *linkPaths = new linkPathsList();
				while ((fdDirentp = readdir(fdDirPtr)) != NULL) {
					string link = processFdPath + "/" + fdDirentp->d_name; 	// /proc/[pid]/fd/x
					string linkTargetPath = getLinkTargetPath(link); //	receive where the link x points to
					if (linkTargetPath != "") {
						linkPaths->insert(linkTargetPath);	//	push to list
					}
				}
				if (linkPaths->getSize() != 0) {	//	found a link, so process uses at least one file
					cout << "PID\t" << d_name << endl;
				}
				while (linkPaths->getSize() != 0) {
					totalOpenFiles++;
					string linkPath = linkPaths->popFront();
					struct stat info;
					stat(linkPath.c_str(), &info);
					// print whatever is necessary
					cout << ((S_ISDIR(info.st_mode)) ? "d" : "-")
							<< ((info.st_mode & S_IRUSR) ? "r" : "-")
							<< ((info.st_mode & S_IWUSR) ? "w" : "-")
							<< ((info.st_mode & S_IXUSR) ? "x" : "-")
							<< ((info.st_mode & S_IRGRP) ? "r" : "-")
							<< ((info.st_mode & S_IWGRP) ? "w" : "-")
							<< ((info.st_mode & S_IXGRP) ? "x" : "-")
							<< ((info.st_mode & S_IROTH) ? "r" : "-")
							<< ((info.st_mode & S_IWOTH) ? "w" : "-")
							<< ((info.st_mode & S_IXOTH) ? "x" : "-") << " "
							<< info.st_nlink << " "
							<< getpwuid(info.st_uid)->pw_name << " "  // uid and returns username
							<< getgrgid(info.st_gid)->gr_name << " "	// gid and returns groupname
							<< info.st_size << " " << linkPath << endl;
				}
				cout << endl;
				delete linkPaths;
			}
		}
	}
	cout << "----------------------------------------------------" << endl;
	cout << "Total open files:\t" << totalOpenFiles << endl;
	return 0;
}

string myFSinfoFunctions::getLinkTargetPath(string link) {
	char cpath[PATH_MAX];
	ssize_t len = ::readlink(link.c_str(), cpath, sizeof(cpath) - 1);
	string path = "";
	if (len != -1) {
		cpath[len] = '\0';
		path = cpath;
	}
	return path;
}

