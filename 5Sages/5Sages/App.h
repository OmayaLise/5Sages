#pragma once
#include "Sage.h"

class App
{
public:
	std::vector< std::mutex*> mutexes;
	std::vector<Sage> sages;
	std::vector<std::thread> threads;

	int numberSages, minEatingTime, 
		maxEatingTime, minThinkingTime, 
		maxThinkingTime, eatingTimeNeeded,
		days;

	char setting;

	App();
	~App();
	void CreateSages();
	void Draw();
	bool CheckState();
	void InitThreads();
	void Update();
	void Reset();
};
