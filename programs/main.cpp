#include "chopsticks.hpp"
#include "philosopher.hpp"
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <functional>

void method_1(const int N, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop);
void phi_routine_1(const int phiID, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop);
void method_2(const int N, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop);
void method_3(const int N, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop);

int main(int argc, char* argv[]) {
	const int M = std::stoi(argv[1]), N = std::stoi(argv[2]);
	std::vector<Philosopher> phi;
	std::vector<Chopsticks> chop;
	for(int i = 0; i < N; i++) {
		phi.push_back(Philosopher(i));
		chop.emplace_back(Chopsticks());
	}

	switch(M) {
		case 1:
			method_1(N, phi, chop);
			break;
		case 2:
			method_2(N, phi, chop);
			break;
		case 3:
			method_3(N, phi, chop);
			break;
	}
}

void method_1(const int N, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop) {
	std::thread t_arr[N];
	for(int phi_ID = 0; phi_ID < N; phi_ID++)
		t_arr[phi_ID] = std::thread(phi_routine_1, phi_ID, std::ref(phi), std::ref(chop));
	for(int phi_ID = 0; phi_ID < N; phi_ID++)
		t_arr[phi_ID].join();
}

void phi_routine_1(const int phiID, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop) {
	const int MEAL_CNT = 10;
	for(int i = 0; i < MEAL_CNT; i++) {
		// todo: boundry condition at chop's index
		phi.at(phiID).eat(chop.at(phiID), chop.at(phiID + 1));
		phi.at(phiID).think();
	}
}

void method_2(const int N, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop) {
	//TODO
}

void method_3(const int N, std::vector<Philosopher>& phi, std::vector<Chopsticks>& chop) {
	//TODO
}