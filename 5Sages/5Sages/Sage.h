#pragma once

#include <mutex>
#include <thread> 
#include <chrono> 
#include <random>
#include <iostream> 

enum class State
{
	THINKING,
	EATING,
	STARVING,
	SLEEPING
};

class Sage
{
public:
	std::mutex *chopstick;
	State state;
	int eatingTimeNeeded, eatingTimeDone, 
		minThinkingTime, maxThinkingTime,
		minEatingTime, maxEatingTime;
	unsigned int id;

	Sage(int numberSages, int eatingTimeNeeded, int minThinkingTime,
		int maxThinkingTime, int minEatingTime, int maxEatingTime, int id);
	void Eat(std::mutex* chopstickBis, int min, int max);
	void Think(int min, int max);
	void Update(std::vector<Sage>& sages);
};

