all:
	g++ -std=c++14 -pthread ./*/*.h ./*/*.cpp ./*/*/*.h ./*/*/*.cpp ./main.cpp
