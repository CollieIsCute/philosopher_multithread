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

int Chopsticks::trylock() {
	int ret = pthread_mutex_trylock(&mutex);
	assert(errno != EAGAIN);
	assert(errno != EINVAL);
	return ret;
}

void Chopsticks::unlock() {
	pthread_mutex_unlock(&mutex);
}