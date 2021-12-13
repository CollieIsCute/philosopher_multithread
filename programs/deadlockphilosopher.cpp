#include "deadlockphilosopher.hpp"

namespace {
void takeLeft(const std::string& phi_info, Chopsticks& chop);
void takeRight(const std::string& phi_info, Chopsticks& chop);
void putLeft(const std::string& phi_info, Chopsticks& chop);
void putRight(const std::string& phi_info, Chopsticks& chop);
}  // namespace

int DeadlockPhilosopher::numberOwnChop = 0;

void DeadlockPhilosopher::eat(std::vector<Chopsticks>& chop, const bool leftFirst) {
	takeChop(getSignature(), chop, ID, leftFirst);

	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });
	std::string line(getSignature());
	line += "eating\n";
	std::cout << line;
	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });

	putChop(getSignature(), chop, ID, leftFirst);
}

void DeadlockPhilosopher::takeChop(const std::string& phi_info, std::vector<Chopsticks>& chop,
								   const int ID, const bool leftFirst) {
	const int left_chop = ID, right_chop = ((unsigned long)ID < chop.size() - 1) ? ID + 1 : 0;

	if(leftFirst) {
		::takeLeft(phi_info, chop.at(left_chop));
		if(hasChop == false)
			numberOwnChop++;
		hasChop = true;
		// deadlock detection
		if(chop.size() == (unsigned long)numberOwnChop) {
			std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });
			throw std::runtime_error("Deadlock happened!\n");
		}
		::takeRight(phi_info, chop.at(right_chop));
	}
	else {
		::takeRight(phi_info, chop.at(right_chop));
		if(hasChop == false)
			numberOwnChop++;
		hasChop = true;
		// deadlock detection
		if(chop.size() == (unsigned long)numberOwnChop) {
			std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });
			throw std::runtime_error("Deadlock happened!\n");
		}
		::takeLeft(phi_info, chop.at(left_chop));
	}
}

void DeadlockPhilosopher::putChop(const std::string& phi_info, std::vector<Chopsticks>& chop,
								  const int ID, const bool leftFirst) {
	const int left_chop = ID, right_chop = ((unsigned long)ID < chop.size() - 1) ? ID + 1 : 0;

	if(leftFirst) {
		::putLeft(phi_info, chop.at(left_chop));
		::putRight(phi_info, chop.at(right_chop));
	}
	else {
		::putRight(phi_info, chop.at(right_chop));
		::putLeft(phi_info, chop.at(left_chop));
	}
	if(hasChop)
		numberOwnChop--;
	hasChop = false;
}

namespace {
void takeLeft(const std::string& phi_info, Chopsticks& chop) {
	chop.lock();
	std::string line(phi_info);
	line += "taking left chopstick\n";
	std::cout << line;
}

void takeRight(const std::string& phi_info, Chopsticks& chop) {
	chop.lock();
	std::string line(phi_info);
	line += "taking right chopstick\n";
	std::cout << line;
}

void putLeft(const std::string& phi_info, Chopsticks& chop) {
	chop.unlock();
	std::string line(phi_info);
	line += "putting left chopstick\n";
	std::cout << line;
}

void putRight(const std::string& phi_info, Chopsticks& chop) {
	chop.unlock();
	std::string line(phi_info);
	line += "putting right chopstick\n";
	std::cout << line;
}
}  // namespace