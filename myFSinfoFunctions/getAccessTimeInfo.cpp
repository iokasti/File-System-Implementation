#include "myFSinfoFunctions.hpp"
#include <sys/stat.h>
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

int myFSinfoFunctions::getAccessTimeInfo(fileTimes times) {
	DIR* dirPtr;
	struct stat info;
	struct dirent *direntp;

	dirPtr = opendir((times.dir).c_str());
	if (dirPtr == NULL) {
		perror(times.dir.c_str());
		return -1;
	}

	time_t now;
	time(&now);

	char timeType;
	int timeGiven;
	unsigned long long secondsGiven; //	we need it big enough
	istringstream ss(times.time);
	ss >> timeGiven >> timeType;
	if (timeType == 'd') {
		secondsGiven = timeGiven * 86400;
	} else if (timeType == 'h') {
		secondsGiven = timeGiven * 3600;
	} else if (timeType == 'm') {
		secondsGiven = timeGiven * 60;
	} else if (timeType == 's') {
		secondsGiven = timeGiven;
	}

	//	if no specific type requested
	if (times.type == false) {
		if (strcmp(times.timeType.c_str(), "-lw") == 0) { // needs modification time
			while ((direntp = readdir(dirPtr)) != NULL) {
				if (strcmp(direntp->d_name, ".") == 0
						|| strcmp(direntp->d_name, "..") == 0) {
					// ignore . and ..
					continue;
				}

				// initialize stat info
				string path = times.dir + "/" + direntp->d_name;
				stat(path.c_str(), &info);

				if ((unsigned) (now - info.st_mtim.tv_sec) <= secondsGiven) {	//	compare filetime with current time
					//	convert seconds to date
					struct tm *timeinfo = localtime(&info.st_mtim.tv_sec);
					char *date = asctime(timeinfo);
					date[strcspn(date, "\n")] = '\0'; // removes new line from date
					cout << date << "\t" << times.dir + "/" + direntp->d_name
							<< endl;
				}

				if ((info.st_mode & S_IFMT) == S_IFDIR) {
					// if it's a directory recurse with the new directory path
					//	new struct because we still need the first one for the next files in current folder
					fileTimes newTimes;
					newTimes.dir = times.dir + "/" + direntp->d_name;
					newTimes.time = times.time;
					newTimes.timeType = times.timeType;
					newTimes.type = times.type;
					newTimes.typeNames = times.typeNames;
					getAccessTimeInfo(newTimes);
				}
			}
		} else if (strcmp(times.timeType.c_str(), "-lr") == 0) { // needs access time
			while ((direntp = readdir(dirPtr)) != NULL) {
				if (strcmp(direntp->d_name, ".") == 0
						|| strcmp(direntp->d_name, "..") == 0) {
					// ignore . and ..
					continue;
				}

				// initialize stat info
				string path = times.dir + "/" + direntp->d_name;
				stat(path.c_str(), &info);

				if ((unsigned) (now - info.st_mtim.tv_sec) <= secondsGiven) {
					struct tm *timeinfo = localtime(&info.st_atim.tv_sec);
					char *date = asctime(timeinfo);
					date[strcspn(date, "\n")] = '\0'; // removes new line from date
					cout << date << "\t" << times.dir + "/" + direntp->d_name
							<< endl;
				}

				if ((info.st_mode & S_IFMT) == S_IFDIR) {
					// if it's a directory recurse with the new directory path
					fileTimes newTimes;
					newTimes.dir = times.dir + "/" + direntp->d_name;
					newTimes.time = times.time;
					newTimes.timeType = times.timeType;
					newTimes.type = times.type;
					newTimes.typeNames = times.typeNames;
					getAccessTimeInfo(newTimes);
				}
			}
		} else {
			cout << "Error!Check time arguments." << endl;
			return -1;
		}
	} else {	// if specific file types are requested
		if (strcmp(times.timeType.c_str(), "-lw") == 0) { // needs modification time
			while ((direntp = readdir(dirPtr)) != NULL) {
				if (strcmp(direntp->d_name, ".") == 0
						|| strcmp(direntp->d_name, "..") == 0) {
					// ignore . and ..
					continue;
				}

				// initialize stat info
				string path = times.dir + "/" + direntp->d_name;
				stat(path.c_str(), &info);

				//	Directories
				//	if it is a directory and there is NO d in specific types requested
				if ((info.st_mode & S_IFMT) == S_IFDIR
						&& (times.typeNames.find_first_of('d') == string::npos)) {
					// if it's a directory recurse with the new directory path and then continue
					fileTimes newTimes;
					newTimes.dir = times.dir + "/" + direntp->d_name;
					newTimes.time = times.time;
					newTimes.timeType = times.timeType;
					newTimes.type = times.type;
					newTimes.typeNames = times.typeNames;
					getAccessTimeInfo(newTimes);
					continue;
				}
				// likewise below

				// Regular Files
				else if ((info.st_mode & S_IFMT) == S_IFREG
						&& (times.typeNames.find_first_of('f') == string::npos)) {
					continue;
				}
				//	Block Device Files
				else if ((info.st_mode & S_IFMT) == S_IFBLK
						&& (times.typeNames.find_first_of('b') == string::npos)) {
					continue;
				}
				//	Char Devices
				else if ((info.st_mode & S_IFMT) == S_IFCHR
						&& (times.typeNames.find_first_of('c') == string::npos)) {
					continue;
				}
				//	Fifo
				else if ((info.st_mode & S_IFMT) == S_IFIFO
						&& (times.typeNames.find_first_of('p') == string::npos)) {
					continue;
				}
				//	Symbolic Link
				else if ((info.st_mode & S_IFMT) == S_IFLNK
						&& (times.typeNames.find_first_of('l') == string::npos)) {
					continue;
				}
				//	Socket
				else if ((info.st_mode & S_IFMT) == S_IFSOCK
						&& (times.typeNames.find_first_of('s') == string::npos)) {
					continue;
				}

				//	if one of the above specific types is requested
				if ((unsigned) (now - info.st_mtim.tv_sec) <= secondsGiven) {
					struct tm *timeinfo = localtime(&info.st_mtim.tv_sec);
					char *date = asctime(timeinfo);
					date[strcspn(date, "\n")] = '\0'; // removes new line from date
					cout << date << "\t" << times.dir + "/" + direntp->d_name
							<< endl;
				}
				//	it is a directory and THERE IS a d in specific type requested
				if ((info.st_mode & S_IFMT) == S_IFDIR) {
					// if it's a directory recurse with the new directory path
					fileTimes newTimes;
					newTimes.dir = times.dir + "/" + direntp->d_name;
					newTimes.time = times.time;
					newTimes.timeType = times.timeType;
					newTimes.type = times.type;
					newTimes.typeNames = times.typeNames;
					getAccessTimeInfo(newTimes);
				}
			}
		} else if (strcmp(times.timeType.c_str(), "-lr") == 0) { // needs access time
			while ((direntp = readdir(dirPtr)) != NULL) {
				if (strcmp(direntp->d_name, ".") == 0
						|| strcmp(direntp->d_name, "..") == 0) {
					// ignore . and ..
					continue;
				}

				// initialize stat info
				string path = times.dir + "/" + direntp->d_name;
				stat(path.c_str(), &info);

				//	Directories
				if ((info.st_mode & S_IFMT) == S_IFDIR
						&& (times.typeNames.find_first_of('d') == string::npos)) {
					// if it's a directory recurse with the new directory path and then continue
					fileTimes newTimes;
					newTimes.dir = times.dir + "/" + direntp->d_name;
					newTimes.time = times.time;
					newTimes.timeType = times.timeType;
					newTimes.type = times.type;
					newTimes.typeNames = times.typeNames;
					getAccessTimeInfo(newTimes);
					continue;
				}
				// Regular Files
				else if ((info.st_mode & S_IFMT) == S_IFREG
						&& (times.typeNames.find_first_of('f') == string::npos)) {
					continue;
				}
				//	Block Device Files
				else if ((info.st_mode & S_IFMT) == S_IFBLK
						&& (times.typeNames.find_first_of('b') == string::npos)) {
					continue;
				}
				//	Char Devices
				else if ((info.st_mode & S_IFMT) == S_IFCHR
						&& (times.typeNames.find_first_of('c') == string::npos)) {
					continue;
				}
				//	Fifo
				else if ((info.st_mode & S_IFMT) == S_IFIFO
						&& (times.typeNames.find_first_of('p') == string::npos)) {
					continue;
				}
				//	Symbolic Link
				else if ((info.st_mode & S_IFMT) == S_IFLNK
						&& (times.typeNames.find_first_of('l') == string::npos)) {
					continue;
				}
				//	Socket
				else if ((info.st_mode & S_IFMT) == S_IFSOCK
						&& (times.typeNames.find_first_of('s') == string::npos)) {
					continue;
				}

				if ((unsigned) (now - info.st_atim.tv_sec) <= secondsGiven) {
					struct tm *timeinfo = localtime(&info.st_atim.tv_sec);
					char *date = asctime(timeinfo);
					date[strcspn(date, "\n")] = '\0'; // removes new line from date
					cout << date << "\t" << times.dir + "/" + direntp->d_name
							<< endl;
				}

				if ((info.st_mode & S_IFMT) == S_IFDIR) {
					// if it's a directory recurse with the new directory path
					fileTimes newTimes;
					newTimes.dir = times.dir + "/" + direntp->d_name;
					newTimes.time = times.time;
					newTimes.timeType = times.timeType;
					newTimes.type = times.type;
					newTimes.typeNames = times.typeNames;
					getAccessTimeInfo(newTimes);
				}
			}
		} else {
			cout << "Error!Check time arguments." << endl;
			return -1;
		}

	}

	closedir(dirPtr);
	return 0;
}

