#include "philosopher.hpp"

namespace {
void takeLeft(Chopsticks& chop);
void takeRight(Chopsticks& chop);
void putLeft(Chopsticks& chop);
void putRight(Chopsticks& chop);
}  // namespace

void Philosopher::eat(Chopsticks& left_chop, Chopsticks& right_chop) const {
	printSignature();
	::takeLeft(left_chop);
	printSignature();
	::takeRight(right_chop);
	printSignature();
	std::cout << "eating" << std::endl;
	printSignature();
	::putLeft(left_chop);
	printSignature();
	::putRight(right_chop);
}

void Philosopher::think() const {
	printSignature();
	std::cout << "thinking" << std::endl;
}

void Philosopher::printSignature() const {
	// todo: add timer
	std::cout << "-Phi " << ID << "-";
}

namespace {
void takeLeft(Chopsticks& chop) {
	chop.lock();
	std::cout << "taking left chopstick" << std::endl;
}

void takeRight(Chopsticks& chop) {
	chop.lock();
	std::cout << "taking right chopstick" << std::endl;
}

void putLeft(Chopsticks& chop) {
	chop.unlock();
	std::cout << "putting left chopstick" << std::endl;
}

void putRight(Chopsticks& chop) {
	chop.unlock();
	std::cout << "putting right chopstick" << std::endl;
}
}  // namespace
