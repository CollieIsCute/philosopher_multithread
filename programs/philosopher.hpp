#ifndef __PHYLOSOPHER_HPP__
#define __PHYLOSOPHER_HPP__

#include "chopsticks.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

class Philosopher {
	int ID;
	int mealCnt;
	std::string getSignature() const;

public:
	Philosopher() = delete;
	Philosopher(int ID) : ID{ ID }, mealCnt{ 0 } {}
	//定義第 ID 根筷子為 left_chop, ID+1 為 right_chop, 若 ID+1 overflow, 則第 0 為 right_chop
	void eat(std::vector<Chopsticks>& chop, const bool leftFirst = rand() % 2) const;
	void think() const;
};

#endif