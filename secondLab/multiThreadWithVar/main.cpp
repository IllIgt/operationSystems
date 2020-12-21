#include <pthread.h>
#include <cstdio>
#include <ctime>

pthread_mutex_t mutex;
pthread_cond_t cond;

int buffer[100];

int loops = 10;
int length = 0;

struct timespec tw = {1,125000000};
struct timespec tw_slower = {2,125000000};
struct timespec tr;

void *producer(void *arg) {
	int i;
	for (i = 0; i < loops; i++) {
		pthread_mutex_lock(&mutex);
		buffer[length++] = i;
		printf("producer length %d\n", length);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		nanosleep(&tw_slower, &tr);
	}
	return nullptr;
}

void *consumer(void *arg) {
	int i;
	for (i = 0; i < loops; i++) {
		pthread_mutex_lock(&mutex);
		while(length == 0) {
			printf(" consumer waiting...\n");
			pthread_cond_wait(&cond, &mutex);
		}
		int item = buffer[--length];
		printf("Consumer %d\n", item);
		pthread_mutex_unlock(&mutex);
		nanosleep(&tw, &tr);
	}
	return nullptr;
}

int main(int argc, char *argv[])
{

	pthread_mutex_init(&mutex, nullptr);
	pthread_cond_init(&cond, nullptr);

	pthread_t pThread, cThread;
	pthread_create(&pThread, nullptr, producer, nullptr);
	pthread_create(&cThread, nullptr, consumer, nullptr);
	pthread_join(pThread, nullptr);
	pthread_join(cThread, nullptr);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}