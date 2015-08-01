#pragma once


#include <ctime>


// simple timer class. Starts as soon as it's instanced. (todo: move to own header later)
class Timer {

private:
	double start;

public:
	//constructor
	Timer()
		: start(std::clock())
	{}

	//returns elapsed time since timer object was instantiated
	double elapsed()
	{
		return (std::clock() - start) / CLOCKS_PER_SEC;
	}

	//resets the timer
	void reset()
	{
		start = std::clock();
	}

};
