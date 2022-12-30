#include "App.h"
#include <windows.h>
#include <wincon.h>

App::App()
{
	std::cout << "Use default setting ? (y/n) \n";
	std::cin >> setting;
	std::cout << "\n";
	if (setting != 'y')
	{
		std::cout << "Enter number of sages : ";
		std::cin >> numberSages;
		std::cout << "Enter duration of the reunion (days) : ";
		std::cin >> days;
		std::cout << "Enter minimum thinking time (seconds) : ";
		std::cin >> minThinkingTime; 
		std::cout << "Enter maximum thinking time (seconds) : ";
		std::cin >> maxThinkingTime;
		std::cout << "Enter minimum eating time (seconds) : ";
		std::cin >> minEatingTime;
		std::cout << "Enter maximum eating time (seconds) : ";
		std::cin >> maxEatingTime;
		std::cout << "Enter the eating time needed in total (seconds) : ";
		std::cin >> eatingTimeNeeded;
	}
	else
	{
		numberSages = 5;
		minThinkingTime = 1;
		maxThinkingTime = 2;
		minEatingTime = 1;
		maxEatingTime = 3;
		eatingTimeNeeded = 4;
		days = 7;
	}
	CreateSages();
	InitThreads();
}

App::~App()
{
}

void App::CreateSages()
{
	for (int i = 0; i < numberSages; i++)
	{
		sages.push_back(Sage(numberSages, eatingTimeNeeded, minThinkingTime, 
			maxThinkingTime, minEatingTime, maxEatingTime,  i));
		mutexes.push_back(new std::mutex);
		sages.at(i).chopstick = mutexes.at(i);
	}
}

void App::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	for (unsigned int i = 0; i < sages.size(); i++)
	{
		switch (sages.at(i).state)
		{
		case State::EATING:
			SetConsoleTextAttribute(console, 9);
			std::cout <<"| " <<sages.at(i).id << " E |";
			break;
		case State::THINKING:
			SetConsoleTextAttribute(console, 15);
			std::cout << "| " << sages.at(i).id << " T |";
			break;
		case State::SLEEPING:
			SetConsoleTextAttribute(console, 11);
			std::cout << "| " << sages.at(i).id << " S |";
			break;
		case State::STARVING:
			SetConsoleTextAttribute(console, 4);
			std::cout << "| " << sages.at(i).id << " H |";
			break;
		default:
			std::cout << "Status error \n";
			break;
		}

	}
	std::cout << "\t\r" << std::flush;
}

bool App::CheckState()
{
	for (unsigned int i = 0; i < sages.size(); i++)
	{
		if (sages.at(i).state != State::SLEEPING)
		{
			return false;
		}
	}
	return true;
}

void App::InitThreads()
{
	for (unsigned int i = 0; i < sages.size(); i++)
	{
		threads.push_back(std::thread());
	}
}

void App::Update()
{

	for (unsigned int i = 0; i <= days; i++)
	{
		for (unsigned int i = 0; i < threads.size(); i++)
		{
			threads.at(i) = std::thread(&Sage::Update, std::ref(sages.at(i)), std::ref(sages));
		}
		while (!CheckState())
		{
			Draw();
		}
		Draw();
		Reset();
		for (unsigned int i = 0; i < sages.size(); i++)
		{
			threads.at(i).join();
		}
	}
}

void App::Reset()
{
	for (unsigned int i = 0; i < sages.size(); i++)
	{
		sages.at(i).eatingTimeDone = 0;
		sages.at(i).state = State::THINKING;
	}

}

