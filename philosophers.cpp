#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
using fork = std::shared_ptr<std::mutex>;

class philosopher
{
	std::string name;
	fork 		left;
	fork 		right;
	/*	
	eating_process(fork f)
	{
		std::cout << "Philosopher " << name_ << " dining." << std::endl;
		std::this_thread::sleep_for(100ms);
		f->unlock();
		return;
	}
	*/
public:
	philosopher(std::string &name_, fork l, fork r) : 
		name(name_),
		left(l),
		right(r)
{}
	void eat()
	{
		std::lock(*left, *right);
		std::lock_guard<std::mutex>(*left, std::adopt_lock);
		std::lock_guard<std::mutex>(*right, std::adopt_lock);
		std::cout << "Philosopher " << name << " dining." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		/*
		if(left->try_lock())
		{
			std::cout << "Philosopher " << name << " dining." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			left->unlock();
			return;
		}
		else if(right->try_lock())
		{
			std::cout << "Philosopher " << name << " dining." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			right->unlock();
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		eat();
		*/
	}
};

int main()
{
	std::vector<std::string> names = {"John", "Anna", "William", "Maria", "Lilith"};
	std::vector<fork> forks;
	for(int i = 0; i < 5; i++)
		forks.push_back(fork(new std::mutex()));
	std::vector<philosopher> philosophers;
	for(int i = 0; i < 4; i++)
		philosophers.push_back(philosopher(names[i], forks[i], forks[i + 1]));
	philosophers.push_back(philosopher(names[4], forks[4], forks[0]));
	std::vector<std::thread> threads;
	for(int i = 0; i < 5; i++)
		threads.push_back(std::thread([&philosophers, i]() { philosophers[i].eat(); }));
	for(int i = 0; i < 5; i++)
		threads[i].join();
	return 0;
}
