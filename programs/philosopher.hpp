#ifndef __PHYLOSOPHER_HPP__
#define __PHYLOSOPHER_HPP__

#include "chopsticks.hpp"
#include <iostream>

class Philosopher {
	int ID;
	int mealCnt;
	void printSignature() const;

public:
	Philosopher() = default;
	Philosopher(int ID) : ID{ ID }, mealCnt{ 0 } {}
	void eat(Chopsticks& left_chop, Chopsticks& right_chop) const;
	void think() const;
};

#endif