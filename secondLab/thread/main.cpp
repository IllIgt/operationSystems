#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <ctime>

int i = 0;
struct timespec tw = {1,125000000};
struct timespec tr;

void* thread_func(void *arg) {
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
		for (i=0; i < 4; i++) {
		printf("I'm still running!\n");
		nanosleep(&tw, &tr);
	}
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
	pthread_testcancel();
	printf("YOU WILL NOT STOP ME!!!\n");
	return nullptr;
}

int main(int argc, char * argv[]) { pthread_t thread;
	pthread_create(&thread, nullptr, thread_func, nullptr); while (i < 1) nanosleep(&tw, &tr);;
	pthread_cancel(thread); printf("Requested to cancel the thread\n");
	pthread_join(thread, nullptr); printf("The thread is stopped.\n");
	return EXIT_SUCCESS;
}

