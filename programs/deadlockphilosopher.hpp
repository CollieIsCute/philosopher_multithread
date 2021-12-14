#ifndef __DEADLOCKPHILOSOPHER_HPP__
#define __DEADLOCKPHILOSOPHER_HPP__

#include "philosopher.hpp"
#include <atomic>
#include <stdexcept>

/* Because method 1 might encounter deadlock problems, so I add deadlock detection to it. */
class DeadlockPhilosopher : public Philosopher {
	bool hasChop;
	static std::atomic_int numberOwnChop;
	void takeChop(const std::string& phi_info, std::vector<Chopsticks>& chop, const int ID,
				  const bool leftFirst);
	void putChop(const std::string& phi_info, std::vector<Chopsticks>& chop, const int ID,
				 const bool leftFirst);

public:
	DeadlockPhilosopher() = delete;
	DeadlockPhilosopher(int ID) : Philosopher{ ID } {}
	void eat(std::vector<Chopsticks>& chop, const bool leftFirst = rand() % 2);
};

#endif