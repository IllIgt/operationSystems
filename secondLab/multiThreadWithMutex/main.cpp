#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <ctime>

struct timespec tw = {1,125000000};
struct timespec tr;
static int counter = 0;
static int max_iterations=3;
typedef struct use_mutex_tag {
	pthread_mutex_t mutex;
} use_mutex_t;

void* minus(void *args) {
	auto *arg = (use_mutex_t*) args;
//	pthread_mutex_lock(&(arg->mutex));
	for (int i=0; i<=max_iterations; i++) {
		printf("thread %lu min %d\n", pthread_self(), counter);
		counter -= 1;
		nanosleep(&tw, &tr);

	}
//	pthread_mutex_unlock(&(arg->mutex));
	return nullptr;
}

void* plus(void *args) {
	auto *arg = (use_mutex_t*) args;
//	pthread_mutex_lock(&(arg->mutex));
	for (int i=0; i<=max_iterations; i++) {
		printf("thread %lu pls %d\n", pthread_self(), counter);
		counter += 1;
		nanosleep(&tw, &tr);
	}
//	pthread_mutex_unlock(&(arg->mutex));
	return nullptr;
}

int main() {
	pthread_t tidA, tidB, tidC, tidD;

	size_t i;
	use_mutex_t param;

	printf("counter = %d\n", counter);
	pthread_mutex_init(&(param.mutex), nullptr);

	pthread_create(&tidA, nullptr, minus, &param);
	pthread_create(&tidB, nullptr, plus, &param);
	pthread_create(&tidC, nullptr, minus, &param);
	pthread_create(&tidD, nullptr, plus, &param);
	pthread_join(tidA, nullptr);
	pthread_join(tidB, nullptr);
	pthread_join(tidC, nullptr);
	pthread_join(tidD, nullptr);
	printf("counter = %d\n", counter);
	pthread_mutex_destroy(&(param.mutex));
	getpt();
	return 0;
}