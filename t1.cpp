#include <iostream>	//for output
#include <algorithm>	//for shuffle
#include <stdlib.h>	//for rand()
 
using namespace std;
 
int* setDrawers() {
	int drawers[100];
	for (int i = 0; i < 100; i++) {
		drawers[i] = i;
	}
	random_shuffle(&drawers[0], &drawers[99]);
	return drawers;
}
 
bool playRandom()
{
	int* drawers = setDrawers();
	bool openedDrawers[100] = { 0 };
	for (int prisonerNum = 0; prisonerNum < 100; prisonerNum++) {	//loops through prisoners numbered 0 through 99
		bool prisonerSuccess = false;
		for (int i = 0; i < 50; i++) {	//loops through 50 draws for each prisoner 
			int drawerNum;
			while (true) {
				drawerNum = rand() % 100;
				if (!openedDrawers[drawerNum]) {
					openedDrawers[drawerNum] = true;
					cout << endl;
					break;
				}
			}
			if (*(drawers + drawerNum) == prisonerNum) {
				prisonerSuccess = true;
				break;
			}
		}
		if (!prisonerSuccess)
			return false;
	}
	return true;
}
 
bool playOptimal()
{
	int* drawers = setDrawers();
	for (int prisonerNum = 0; prisonerNum < 100; prisonerNum++) {
		bool prisonerSuccess = false;
		int checkDrawerNum = prisonerNum;
		for (int i = 0; i < 50; i++) {
			if (*(drawers + checkDrawerNum) == prisonerNum) {
				prisonerSuccess = true;
				break;
			}
			else
				checkDrawerNum = *(drawers + checkDrawerNum);
		}
		if (!prisonerSuccess)
			return false;
	}
	return true;
}
 
double simulate(string strategy)
{
	int numberOfSuccesses = 0;
	for (int i = 0; i <= 10000; i++) {
		if ((strategy == "random" && playRandom()) || (strategy == "optimal" && playOptimal())) //will run playRandom or playOptimal but not both becuase of short-circuit evaluation
			numberOfSuccesses++;
	}
	return numberOfSuccesses / 100.0;
}
 
int main()
{
	cout << "Random Strategy: " << simulate("random") << "%" << endl;
	cout << "Optimal Strategy: " << simulate("optimal") << "%" << endl;
	system("PAUSE");
	return 0;
}