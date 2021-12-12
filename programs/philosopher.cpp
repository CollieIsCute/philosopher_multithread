#include "philosopher.hpp"

namespace {
void takeLeft(const std::string& phi_info, Chopsticks& chop);
void takeRight(const std::string& phi_info, Chopsticks& chop);
void putLeft(const std::string& phi_info, Chopsticks& chop);
void putRight(const std::string& phi_info, Chopsticks& chop);
}  // namespace

void Philosopher::eat(std::vector<Chopsticks>& chop, const bool leftFirst) const {
	const int left_chop = ID, right_chop = ((unsigned long)ID < chop.size() - 1) ? ID + 1 : 0;
	if(leftFirst) {
		::takeLeft(getSignature(), chop.at(left_chop));
		::takeRight(getSignature(), chop.at(right_chop));
	}
	else {
		::takeRight(getSignature(), chop.at(left_chop));
		::takeLeft(getSignature(), chop.at(right_chop));
	}

	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });
	std::string line(getSignature());
	line += "eating\n";
	std::cout << line;
	std::this_thread::sleep_for(std::chrono::seconds{ rand() % 4 + 1 });

	if(leftFirst) {
		::putLeft(getSignature(), chop.at(left_chop));
		::putRight(getSignature(), chop.at(right_chop));
	}
	else {
		::putRight(getSignature(), chop.at(right_chop));
		::putLeft(getSignature(), chop.at(left_chop));
	}
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
