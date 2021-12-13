#ifndef __DEADLOCKPHILOSOPHER_HPP__
#define __DEADLOCKPHILOSOPHER_HPP__

#include "philosopher.hpp"

/* Because method 1 might encounter deadlock problems, so I add deadlock detection to it. */
class DeadlockPhilosopher : public Philosopher {
	bool hasChop;
	static int numberOwnChop;

public:
	DeadlockPhilosopher() = delete;
	DeadlockPhilosopher(int ID) : Philosopher{ ID } {}
	void eat(std::vector<Chopsticks>& chop, const bool leftFirst = rand() % 2);
};

#endif