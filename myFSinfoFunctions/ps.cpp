#include "myFSinfoFunctions.hpp"
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

int myFSinfoFunctions::ps() {
	pid_t ttyPID = getppid();
	string directory = "/proc";

	DIR* dirPtr;
	struct dirent *direntp;
	dirPtr = opendir(directory.c_str());
	if (dirPtr == NULL) {
		perror(directory.c_str());
		return -1;
	}

	long double totalMemoryUsageKb = 0;
	double totalCpuTime = 0;

	cout << "PID\tPPID\tCPU\tSTATE\tSTART\tVSZ\tRSS\tPRIORITY\tCMDLINE" << endl;

	while ((direntp = readdir(dirPtr)) != NULL) {
		if (strcmp(direntp->d_name, ".") == 0
				|| strcmp(direntp->d_name, "..") == 0) {
			// ignore . and ..
			continue;
		}
		if (isdigit(direntp->d_name[0])) {
			// first letter of d_name is digit so it's a process directory
			string d_name = direntp->d_name;	// is a pid so we use it for the path below line 39
			string processStatPath = "/proc/" + d_name + "/stat";
			if (isChildOfPPID(processStatPath, ttyPID) == true) {
				// process is a descendant of the ttyPID
				pidStat pidstat = readPidStat(processStatPath);
				double cpuTime = (pidstat.utime + pidstat.stime + pidstat.cutime
						+ pidstat.cstime) / (double) HZ;
				int startTimeSeconds = getProcUpTime()
						- (pidstat.starttime / (double) HZ);
				int startTimeHour = startTimeSeconds / 3600;
				int statTimeSecond = startTimeSeconds % 3600;
				int startTimeMinute = statTimeSecond / 60;
				statTimeSecond = statTimeSecond % 60;
				long double vsizeKB = pidstat.vsize / (double) 1024;
				long pagesize = sysconf(_SC_PAGESIZE);
				long double rssKB = (pidstat.rss * pagesize) / (double) 1024;
				string processCmdLinePath = "/proc/" + d_name + "/cmdline";
				string cmdline = getCmdLine(processCmdLinePath);
				totalMemoryUsageKb += vsizeKB;
				totalCpuTime += cpuTime;
				cout << pidstat.pid << "\t" << pidstat.ppid << "\t" << cpuTime
						<< "s\t" << pidstat.state << "\t" << startTimeHour
						<< ":" << startTimeMinute << "\t" << vsizeKB << "\t"
						<< rssKB << "\t" << pidstat.priority << "\t\t"
						<< cmdline << endl;
			}
		}
	}
	cout << "----------------------------------------------------" << endl;
	cout << "Total memory usage Kb:\t" << totalMemoryUsageKb << endl;
	cout << "Total cpu time sec's:\t" << totalCpuTime << endl;
	return 0;
}

double myFSinfoFunctions::getProcUpTime() {
	double uptime;
	string procUptimePath = "/proc/uptime";
	ifstream file(procUptimePath.c_str());
	string line;
	getline(file, line);
	istringstream ss(line);
	ss >> uptime;
	file.close();
	return uptime;
}

string myFSinfoFunctions::getCmdLine(string processCmdLinePath) {
	ifstream file(processCmdLinePath.c_str());
	string cmdLine;
	getline(file, cmdLine);
	return cmdLine;
}

