#ifndef MYFSINFOFUNCTIONS_HPP_
#define MYFSINFOFUNCTIONS_HPP_

#define HZ 100	//	clock ticks

#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <cstring>
#include "../infoIoList/infoIoList.hpp"

struct fileTimes {	//	q2 getAccessTimeInfo struct
	bool type;
	std::string typeNames;
	std::string timeType;
	std::string time;
	std::string dir;
};

struct pidStat {	// used for proc functions. saves all info from /proc/[pid]/stat
	int pid;
	std::string comm;
	char state;
	int ppid;
	int pgrp;
	int session;
	int tty_nr;
	int tpgid;
	unsigned int flags;
	unsigned long minflt;
	unsigned long cminflt;
	unsigned long majflt;
	unsigned long cmajflt;
	unsigned long utime;
	unsigned long stime;
	unsigned int cutime;
	unsigned int cstime;
	unsigned int priority;
	unsigned int nice;
	unsigned int num_threads;
	unsigned int itrealvalue;
	unsigned long long starttime;
	unsigned long vsize;
	unsigned int rss;
	unsigned long rsslim;
	unsigned long startcode;
	unsigned long endcode;
	unsigned long startstack;
	unsigned long kstkesp;
	unsigned long kstkeip;
	unsigned long signal;
	unsigned long blocked;
	unsigned long sigignore;
	unsigned long sigcatch;
	unsigned long wchan;
	unsigned long nswap;
	unsigned long cnswap;
	int exit_signal;
	int processor;
	unsigned int rt_priority;
	unsigned int policy;
	unsigned long long delayacct_blkio_ticks;
	unsigned long guest_time;
	unsigned int cguest_time;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_brk;
	unsigned long arg_start;
	unsigned long arg_end;
	unsigned long env_start;
	unsigned long env_end;
	int exit_code;
};

class myFSinfoFunctions {
private:
	int regFiles;
	int direc;
	int block;
	int character;
	int fifo;
	int symLink;
	int socket;
public:
	myFSinfoFunctions();
	~myFSinfoFunctions();

	int cnt(std::string); // Find statistics for given directory
	void printCnt();	// Print statistics for given directory

	int getAccessTimeInfo(fileTimes);// Get files accessed or modified at given time

	int ps();	//	info about resource usage from user's processes running in current tty
	std::string getCmdLine(std::string);	//	returns cmdline from /proc/[pid]/cmdline
	double getProcUpTime();	//	returns system uptime from /proc/uptime

	int ft();	//	info about file usage from user's processes running in current tty
	std::string getLinkTargetPath(std::string);	//	returns an absolute path from a given symbolic link

	int iostat(int, std::string);	//	info about i/o usage from user's processes running in current tty
	pidIo readPidIo(std::string);	// returns a pidIo (@infoIoList) from /proc/[pid]/io

	pidStat readPidStat(std::string);	//	returns a pidStat from /proc/[pid]/stat
	bool isChildOfPPID(std::string, pid_t);	// returns if a process is a descendant  of tty

};
#endif /* MYFSINFOFUNCTIONS_HPP_ */
