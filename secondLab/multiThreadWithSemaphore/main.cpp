#include <semaphore.h>
#include <ostream>
#include <cstdio>
#include <fstream>
#include <iostream>

void* WriteToFile(int);
void* ReadFromFile(int);
int errno;
sem_t psem;
std::fstream read_n_write;
char filename[] = "./rezult.txt";

int main(int argc, char **argv) {
	pthread_t tidA,tidB, tidC, tidD;

	read_n_write.open(&filename[0]);
	read_n_write<<pthread_self()<<"START"<<std::endl;
	read_n_write<<fflush;
	sem_init(&psem,0,3);
	sem_post(&psem);
	pthread_create(&tidA, nullptr, reinterpret_cast<void *(*)(void *)>(&WriteToFile), (void*)10);
	pthread_create(&tidC, nullptr, reinterpret_cast<void *(*)(void *)>(&ReadFromFile), (void*)10);
	pthread_create(&tidB, nullptr, reinterpret_cast<void *(*)(void *)>(&WriteToFile), (void*)10);
	pthread_create(&tidD, nullptr, reinterpret_cast<void *(*)(void *)>(&ReadFromFile), (void*)10);
	pthread_join(tidA,nullptr);
	pthread_join(tidB,nullptr);
	pthread_join(tidC,nullptr);
	pthread_join(tidD,nullptr);
	sem_destroy(&psem);
	read_n_write.close();
}
void* WriteToFile(int f){
	int max = (int)f;
	for (int i=0; i<=max; i++) {
			sem_wait(&psem);
			read_n_write<<pthread_self()<<" count i="<<i<<std::endl;
			read_n_write<<fflush;
			sem_post(&psem);
		}
	return nullptr;
}

void* ReadFromFile(int f) {
	int max = (int)f;
	std::streampos size;
	for (int i=0; i<=max; i++) {
		sem_wait(&psem);
		size = 300;
		char* readed = new char[size];
		if (read_n_write.read(readed, 1)) {
			std::cout << "Файл прочитан" << std::endl;
		} else {
			std::cout << "Не удалось прочитать файла" << std::endl;
		}
		read_n_write.clear();
		sem_post(&psem);
	}
	return nullptr;
}