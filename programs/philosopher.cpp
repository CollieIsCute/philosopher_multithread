#include "philosopher.hpp"

namespace {
void takeLeft(const std::string& phi_info, Chopsticks& chop);
void takeRight(const std::string& phi_info, Chopsticks& chop);
void putLeft(const std::string& phi_info, Chopsticks& chop);
void putRight(const std::string& phi_info, Chopsticks& chop);
}  // namespace

void Philosopher::eat(std::vector<Chopsticks>& chop, const bool leftFirst) {
	takeChop(getSignature(), chop, ID, leftFirst);

	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });
	std::string line(getSignature());
	line += "eating\n";
	std::cout << line;
	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });

	putChop(getSignature(), chop, ID, leftFirst);
}

void Philosopher::takeChop(const std::string& phi_info, std::vector<Chopsticks>& chop, const int ID,
						   const bool leftFirst) {
	const int left_chop = ID, right_chop = ((unsigned long)ID < chop.size() - 1) ? ID + 1 : 0;

	if(leftFirst) {
		::takeLeft(phi_info, chop.at(left_chop));
		::takeRight(phi_info, chop.at(right_chop));
	}
	else {
		::takeRight(phi_info, chop.at(right_chop));
		::takeLeft(phi_info, chop.at(left_chop));
	}
}

void Philosopher::putChop(const std::string& phi_info, std::vector<Chopsticks>& chop, const int ID,
						  const bool leftFirst) {
	const int left_chop = ID, right_chop = ((unsigned long)ID < chop.size() - 1) ? ID + 1 : 0;
	if(leftFirst) {
		::putLeft(phi_info, chop.at(left_chop));
		::putRight(phi_info, chop.at(right_chop));
	}
	else {
		::putRight(phi_info, chop.at(right_chop));
		::putLeft(phi_info, chop.at(left_chop));
	}
}

void Philosopher::immediately_eat(std::vector<Chopsticks>& chop) {
	const int left_chop = ID, right_chop = ((unsigned long)ID < chop.size() - 1) ? ID + 1 : 0;
	int L_err, R_err;
	do {  // get both chopsticks at the same time
		L_err = chop.at(left_chop).trylock();
		if(L_err == EBUSY)
			continue;
		else {
			R_err = chop.at(right_chop).trylock();
			if(R_err == EBUSY) {
				chop.at(left_chop).unlock();
				continue;
			}
		}
	} while(L_err == EBUSY || R_err == EBUSY);

	std::string line(getSignature());
	line += "taking both left and right chopsticks\n";
	std::cout << line;

	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });
	line = std::string(getSignature());
	line += "eating\n";
	std::cout << line;
	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });

	chop.at(left_chop).unlock();
	chop.at(right_chop).unlock();
	line = std::string(getSignature());
	line += "putting both left and right chopsticks\n";
	std::cout << line;
}

void Philosopher::think() const {
	std::string line(getSignature());
	line += "thinking\n";
	std::cout << line;
	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 5 + 5 });
}

std::string Philosopher::getSignature() const {
	auto time = std::time(nullptr);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&time), "%T") << "-Phi " << ID << "-";
	return ss.str();
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