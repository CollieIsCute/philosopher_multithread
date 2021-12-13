#ifndef __CHOPSTICKS_HPP__
#define __CHOPSTICKS_HPP__

#include <cassert>
#include <cerrno>
#include <pthread.h>

class Chopsticks {
	pthread_mutex_t mutex;

public:
	Chopsticks();
	~Chopsticks();
	void lock();
	int trylock();
	void unlock();
};

#endif