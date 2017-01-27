all:: infoIoList.o linkPathsList.o myFSinfoFunctions.o cnt.o ft.o getAccessTimeInfo.o iostat.o ps.o main.o
	g++ -o myfsinfo infoIoList.o linkPathsList.o myFSinfoFunctions.o cnt.o ft.o getAccessTimeInfo.o iostat.o ps.o main.o 


infoIoList.o: infoIoList/infoIoList.cpp infoIoList/infoIoList.hpp
	g++ -c infoIoList/infoIoList.cpp


linkPathsList.o: linkPathsList/linkPathsList.cpp linkPathsList/linkPathsList.hpp
	g++ -c linkPathsList/linkPathsList.cpp


myFSinfoFunctions.o: myFSinfoFunctions/cnt.cpp myFSinfoFunctions/ft.cpp myFSinfoFunctions/getAccessTimeInfo.cpp myFSinfoFunctions/iostat.cpp myFSinfoFunctions/myFSinfoFunctions.cpp myFSinfoFunctions/myFSinfoFunctions.hpp myFSinfoFunctions/ps.cpp
	g++ -c myFSinfoFunctions/cnt.cpp myFSinfoFunctions/ft.cpp myFSinfoFunctions/getAccessTimeInfo.cpp myFSinfoFunctions/iostat.cpp myFSinfoFunctions/myFSinfoFunctions.cpp myFSinfoFunctions/ps.cpp


main.o: main.cpp
	g++ -c main.cpp


clean:
	rm -f *.o myfsinfo