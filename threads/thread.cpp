#include <thread>
#include <iostream>
#include <cstdlib>

void foo(int ID, int argNum) 
{
	int num = rand()%10000;
	while (num != argNum)
	{
		num = rand()%10000;
	}
	std::cout << "Thread " << ID << " completed." << std::endl; 
}

int main(int argc, char *argv[]) 
{

	std::thread myThreads[10];

	for (int i = 0; i < 10; i++)
	{
		myThreads[i] = std::thread(foo, i, std::stoi(argv[1]));
	}

	for (int i = 0; i < 10; i++)
	{
		myThreads[i].join();
	}
	
	std::cout << "All threads have finished finding numbers." << std::endl;

	return 0;
}
