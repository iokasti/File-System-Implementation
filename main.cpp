#include <iostream>
#include <cstring>
#include <cstdlib>
#include "myFSinfoFunctions/myFSinfoFunctions.hpp"

using namespace std;

int main(int argc, char** argv) {

	/****************	READ COMMAND LINE ARGUMENTS	*********************************************/
	if ((argc != 2) && (argc != 3) && (argc != 4) && (argc != 6)) {
		cout << "Wrong number of given arguments!" << endl;
		return 1;
	}
	string dirName;
	myFSinfoFunctions *fsInfo = new myFSinfoFunctions();
	if (argc == 2) {
		if (strcmp(argv[1], "-ps") == 0) {
			int psStatus = fsInfo->ps();
			delete fsInfo;
			return psStatus;
		} else if (strcmp(argv[1], "-ft") == 0) {
			int ftStatus = fsInfo->ft();
			delete fsInfo;
			return ftStatus;
		} else {
			cout << "Wrong type of argument given!" << endl;
			delete fsInfo;
			return 1;
		}
	} else if (argc == 3) {
		if (strcmp(argv[1], "-cnt") == 0) {
			dirName = argv[2];
			cout << "Printing directories statistics for directory: " << dirName
					<< endl;
			int cntReturn = fsInfo->cnt(dirName);
			if (cntReturn == 0) {
				fsInfo->printCnt();
			}
			delete fsInfo;
			return cntReturn;
		} else {
			cout << "Wrong type of argument given!" << endl;
			delete fsInfo;
			return 1;
		}
	} else if (argc == 6) {
		if (strcmp(argv[1], "-type") == 0) {
			fileTimes Times;
			Times.type = true;
			Times.typeNames = argv[2];
			Times.timeType = argv[3];
			Times.time = argv[4];
			Times.time = Times.time.substr(1);
			Times.dir = argv[5];
			cout << "Printing files of types: " << Times.typeNames << " with "
					<< ((strcmp(Times.timeType.c_str(), "-lr") == 0) ?
							"access" : "modification") << " time " << Times.time
					<< " for directory: " << Times.dir << endl;
			int accessTimeInfoStatus = fsInfo->getAccessTimeInfo(Times);
			delete fsInfo;
			return accessTimeInfoStatus;
		} else if (strcmp(argv[1], "-iostat") == 0) {
			int records = 0;
			string fieldname = "";
			if (strcmp(argv[2], "-k") == 0) {
				records = atoi(argv[3]);
			} else if (strcmp(argv[2], "-f") == 0) {
				fieldname = argv[3];
			}
			if (strcmp(argv[4], "-k") == 0) {
				records = atoi(argv[5]);
			} else if (strcmp(argv[4], "-f") == 0) {
				fieldname = argv[5];
			}
			int iostatStatus = fsInfo->iostat(records, fieldname);
			delete fsInfo;
			return iostatStatus;
		} else {
			cout << "Wrong type of argument given!" << endl;
			delete fsInfo;
			return 1;
		}
	} else if (argc == 4) {
		if ((strcmp(argv[1], "-lw") == 0) || (strcmp(argv[1], "-lr") == 0)) {
			fileTimes Times;
			Times.type = false;
			Times.typeNames = "";
			Times.timeType = argv[1];
			Times.time = argv[2];
			Times.time = Times.time.substr(1);
			Times.dir = argv[3];
			cout << "Printing files with "
					<< ((strcmp(Times.timeType.c_str(), "-lr") == 0) ?
							"access" : "modification") << " time " << Times.time
					<< " for directory: " << Times.dir << endl;
			int accessTimeInfoStatus = fsInfo->getAccessTimeInfo(Times);
			delete fsInfo;
			return accessTimeInfoStatus;
		} else {
			cout << "Wrong type of argument given!" << endl;
			delete fsInfo;
			return 1;
		}
	}
	delete fsInfo;
	return 0;
}

