#include "myFSinfoFunctions.hpp"
#include <fstream>
#include <sstream>

using namespace std;

myFSinfoFunctions::myFSinfoFunctions() {
	regFiles = 0;
	direc = 0;
	block = 0;
	character = 0;
	fifo = 0;
	symLink = 0;
	socket = 0;
}

myFSinfoFunctions::~myFSinfoFunctions() {
}

pidStat myFSinfoFunctions::readPidStat(string processStatPath) {
	ifstream file(processStatPath.c_str()); 	//	/proc/[pid]/stat
	string line;
	getline(file, line);
	istringstream ss(line);
	pidStat pidstat;
	//	read all the info from /proc/[pid]/stat
	ss >> pidstat.pid >> pidstat.comm >> pidstat.state >> pidstat.ppid
			>> pidstat.pgrp >> pidstat.session >> pidstat.tty_nr
			>> pidstat.tpgid >> pidstat.flags >> pidstat.minflt
			>> pidstat.cminflt >> pidstat.majflt >> pidstat.cmajflt
			>> pidstat.utime >> pidstat.stime >> pidstat.cutime
			>> pidstat.cstime >> pidstat.priority >> pidstat.nice
			>> pidstat.num_threads >> pidstat.itrealvalue >> pidstat.starttime
			>> pidstat.vsize >> pidstat.rss >> pidstat.rsslim
			>> pidstat.startcode >> pidstat.endcode >> pidstat.startstack
			>> pidstat.kstkesp >> pidstat.kstkeip >> pidstat.signal
			>> pidstat.blocked >> pidstat.sigignore >> pidstat.sigcatch
			>> pidstat.wchan >> pidstat.nswap >> pidstat.cnswap
			>> pidstat.exit_signal >> pidstat.processor >> pidstat.rt_priority
			>> pidstat.policy >> pidstat.delayacct_blkio_ticks
			>> pidstat.guest_time >> pidstat.cguest_time >> pidstat.start_data
			>> pidstat.end_data >> pidstat.start_brk >> pidstat.arg_start
			>> pidstat.arg_end >> pidstat.env_start >> pidstat.env_end
			>> pidstat.exit_code;
	file.close();
	return pidstat;
}

bool myFSinfoFunctions::isChildOfPPID(string processStatPath, pid_t ttyPID) {
	pidStat pidstat = readPidStat(processStatPath); // /proc/[pid]/stat
	if (pidstat.ppid == ttyPID) {
		return true;
	} else if (pidstat.ppid == 1 || pidstat.ppid == 0) {
		return false;
	} else {	//	search for the current process father's father, recursively backwards
		ostringstream ssprocessPPid;
		ssprocessPPid << pidstat.ppid;
		string sprocessPPid = ssprocessPPid.str().c_str();
		string parentProcessStatusPath = "/proc/" + sprocessPPid + "/status";
		return isChildOfPPID(parentProcessStatusPath, ttyPID);
	}
	return false;
}

