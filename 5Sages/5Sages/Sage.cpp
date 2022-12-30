#include "Sage.h"

Sage::Sage(int numberSages, int eatingTimeNeeded, int minThinkingTime,
	int maxThinkingTime, int minEatingTime, int maxEatingTime, int id)
{
	state = State::THINKING;
	this->eatingTimeNeeded = eatingTimeNeeded;
	this->minThinkingTime = minThinkingTime;
	this->maxThinkingTime = maxThinkingTime;
	this->minEatingTime = minEatingTime;
	this->maxEatingTime = maxEatingTime;
	this->id = id;
	chopstick = nullptr;
	eatingTimeDone = 0;
}

void Sage::Think(int min, int max)
{
	state = State::THINKING;
	int timeThinking = rand() % max + min;
	std::this_thread::sleep_for(std::chrono::seconds(timeThinking));
	state = State::STARVING;
}

void Sage::Eat(std::mutex *chopstickBis, int min, int max)
{
		if (chopstick->try_lock())
		{
			if (chopstickBis->try_lock())
			{
				state = State::EATING;
				int timeEating = rand() % max + min;
				if (timeEating + eatingTimeDone > eatingTimeNeeded)
					timeEating = eatingTimeNeeded - eatingTimeDone;
				eatingTimeDone += timeEating;
				std::this_thread::sleep_for(std::chrono::seconds(timeEating));
				chopstick->unlock();
				chopstickBis->unlock();
			}
			else
				chopstick->unlock();

		}

}

void Sage::Update(std::vector<Sage>& sages)
{
	
	while (state != State::SLEEPING)
	{
			if (state == State::STARVING)
			{
				if (id + 1 < sages.size())
					Eat(sages.at(id + 1).chopstick, minEatingTime, maxEatingTime);
				else
					Eat(sages.at(0).chopstick, minEatingTime, maxEatingTime);
			}
			else
				Think(minThinkingTime, maxThinkingTime);

		if (eatingTimeDone >= eatingTimeNeeded)
			this->state = State::SLEEPING;
	}

	
}



