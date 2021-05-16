#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

using namespace std;

void bubbleSort(int* array, int n)
{	
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (array[j] < array[j-1])
			{
				temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
			}
		}
	}

}

int main(int argc, char *argv[]) 
{
        pid_t p;
        int pipe1[2];
        int pipe2[2];
        int pipe3[2];
	int pipe4[2];

	pipe(pipe1);
	pipe(pipe2);
	pipe(pipe3);
	pipe(pipe4);
	int nums[5];
	
	//cout << "Main" << endl;
	for (int i = 1; i < 6; i++) 
	{
		nums[i-1] = atoi(argv[i]);
		//cout << nums[i-1] << endl;
	}

	p = fork();
	if(p < 0) 
	{
		return 1; 
		//error
	}
	else if(p > 0) //parent process
	{	
		//cout << "Parent 1" << endl;
		int buf1;
		close(pipe1[0]);
		for (int i = 0; i < 5; i++)
		{
			buf1 = nums[i];
			write(pipe1[1], &buf1, sizeof(int));
		}
		p = fork();
		if(p < 0)
		{
			return 1;
			//error
		}
		else if (p > 0) // parent process
		{
			//cout << "parent 2" << endl;
			int median;
			int bufParent;
			int numsParent[5];

			close(pipe2[1]);
			for (int i = 0; i < 5; i++)
			{
	      			read(pipe2[0], &bufParent, sizeof(int));
			 	numsParent[i] = bufParent;
			}
			for (int i = 0; i < 5; i++)
			{
				if (i < 4)
				{
					cout << numsParent[i] << ", ";
				}
				else
				{
					cout << numsParent[i] << endl;
				}
			}

			close(pipe4[1]);
			read(pipe4[0], &median, sizeof(int));
			cout << "Median: " << median << endl;
		}
		else //second child
		{
			//cout << "child 2" << endl;
			int numsChild2[5];
			int bufChild2;
			close(pipe3[1]);
	    		for (int i = 0; i < 5; i++)
			{
	      			read(pipe3[0], &bufChild2, sizeof(int));
				numsChild2[i] = bufChild2; 
			}

			close(pipe4[0]);
			bufChild2 = numsChild2[2];
			write(pipe4[1], &bufChild2, sizeof(int));
			
			exit(0);
		}
	}
	else //first (sorting child) process
	{
		//cout << "child 1" << endl;
		int numsChild[5];
		int bufChild1;

		close(pipe1[1]);
	    	for (int i = 0; i < 5; i++)
		{
	      		read(pipe1[0], &bufChild1, sizeof(int));
			numsChild[i] = bufChild1; 
		}

		//SORTING ------------------------
		bubbleSort(numsChild, 5);
		// -------------------------------
		close(pipe2[0]);
		close(pipe3[0]);

		for (int i = 0; i < 5; i++)
		{
			bufChild1 = numsChild[i];
			write(pipe2[1], &bufChild1, sizeof(int)); 
			write(pipe3[1], &bufChild1, sizeof(int));
		}

		exit(0);
	}

	return 0;
}
