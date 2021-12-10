#include "chopsticks.hpp"

Chopsticks::Chopsticks() {
	pthread_mutex_init(&this->mutex, nullptr);
}

Chopsticks::~Chopsticks() {
	pthread_mutex_destroy(&mutex);
}

void Chopsticks::lock() {
	pthread_mutex_lock(&mutex);
}

void Chopsticks::unlock() {
	pthread_mutex_unlock(&mutex);
}