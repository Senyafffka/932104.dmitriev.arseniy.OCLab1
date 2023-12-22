#include <iostream>      
#include <thread>           
#include <semaphore>
#include <chrono>

using namespace std;
binary_semaphore first_semaphore(0);
binary_semaphore second_semaphore(0);

void thread_provider() {
	while (true) {
		this_thread::sleep_for(chrono::seconds(1));
		cout << "Событие отправлено" << endl;
		second_semaphore.release();
		first_semaphore.acquire();
	}
}

void thread_consumer() {
	while (true) {
		second_semaphore.acquire();
		cout << "Событие обработано" << endl;
		first_semaphore.release();
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	thread thread_first(thread_provider);
	thread thread_second(thread_consumer);
	thread_first.join();
	thread_second.join();
}