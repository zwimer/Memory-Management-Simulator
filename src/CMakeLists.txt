cmake_minimum_required(VERSION 3.0)
project(Memory-Management-Simulator)

add_executable(Memory-Management-Simulator.out
	main.cpp
	Time.cpp
	Event.cpp
	HardDrive.cpp
	MemoryManager.cpp
	Virtual.cpp 
	NonContiguous.cpp
	NextFit.cpp BestFit.cpp WorstFit.cpp )
