#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>

//100 Prisoners
//100 boxes
//100 slips
std::vector<int> prisoners(100);
std::vector<int> box(100);
std::vector<int> slip(100);
std::vector<bool> prisonedOutcome(100);

int TotalEscapeCount = 0;

std::vector<int> Rand50()
{
	std::vector<int> temp100(100);
	for (int i = 0; i < 100; i++)
	{
		temp100[i] = i + 1;
	}
	std::random_device rd2;
	std::mt19937 g2(rd2());
	std::shuffle(temp100.begin(), temp100.end(), g2);

	std::vector<int> ret50(50);
	for (int i = 0; i < 50; i++)
	{
		ret50[i] = temp100[i];
	}

	return ret50;
}

void Method1()
{
	//METHOD 1
	//loop - Picking Random
	for (int i = 0; i < 100; i++)
	{
		//std::cout << "Prisoner " << i + 1 << " \n";
		std::vector<int> PickedBox = Rand50();
		bool FoundNum = false;
		for (int j = 0; j < 50; j++)
		{
			if (box[PickedBox[j]-1] == prisoners[i])
			{
				FoundNum = true;
				
			}
		}
		//std::cout << "Result: " << FoundNum << "\n\n";
		prisonedOutcome[i] = FoundNum;
	}
	
	//Count Number of Pass/fail
	int PassCount = 0;
	int FailCount = 0;
	for (int i = 0; i < 100; i++)
	{
		if (prisonedOutcome[i] == true)
		{
			PassCount++;
		}
		else
		{
			FailCount++;
		}
	}
	std::cout << "\nTotal Pass: " << PassCount;
	std::cout << "\nTotal Fail: " << FailCount<<"\n";

	if (PassCount == 100)
	{
		++TotalEscapeCount;
	}
}

void Method2()
{
	//METHOD 2
	//implement the loop picking method
	int PassCount = 0;
	int FailCount = 0;
	for (int i = 0; i < 100; i++)
	{
		int boxOpened = 0;
		bool numFound = false;
		int lastBoxVal = prisoners[i] - 1;
		//Prisoner 1- 100

		if (box[lastBoxVal] == prisoners[i])
		{
			boxOpened++;
			numFound = true;
		}
		else
		{
			boxOpened++;
			lastBoxVal = box[lastBoxVal] - 1;
			while (boxOpened < 50)
			{
				if (box[lastBoxVal] == prisoners[i])
				{
					boxOpened++;
					numFound = true;
					break;
				}
				else
				{
					lastBoxVal = box[lastBoxVal] - 1;
					boxOpened++;
				}

			}

		}
		prisonedOutcome[i] = numFound;

	}

	for (int i = 0; i < 100; i++)
	{
		if (prisonedOutcome[i] == true)
		{
			PassCount++;
		}
		else
		{
			FailCount++;
		}
	}	
	std::cout << "\nTotal Pass: " << PassCount;
	std::cout << "\nTotal Fail: " << FailCount << "\n";

	if (PassCount == 100)
	{
		++TotalEscapeCount;
	}
}

void InitializeRoom()
{
	//Initialize prisoners, boxes, and slips
	for (int i = 0; i < 100; i++)
	{
		prisoners[i] = i + 1;
	}

	for (int i = 0; i < 100; i++)
	{
		slip[i] = i + 1;
	}

	//shuffle slips
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(slip.begin(), slip.end(), g);

	//place slips in box
	for (int i = 0; i < 100; i++)
	{
		box[i] = slip[i];
	}
}

int main()
{	
	
	//InitializeRoom();

	int MethodChoice;
	std::cout << "1 - Method 1: Random\n2 - Method 2: Loop\n\nEnter 1 or 2: ";
	std::cin >> MethodChoice;

	int NoOfLoops = 1;
	std::cout << "\nEnter the number of simulations: ";
	std::cin >> NoOfLoops;

	switch (MethodChoice)
	{
		case 1:
			std::cout << "\n\nMethod 1 - Random\n";
			
			for (int a = 0; a < NoOfLoops; a++)
			{
				std::cout << "\nSimulation "<<a+1<<":";
				InitializeRoom();
				Method1();
			}
			break;
		case 2:
			std::cout << "\n\nMethod 2 - Loops\n";
			
			for (int a = 0; a < NoOfLoops; a++)
			{
				std::cout << "\nSimulation " << a + 1<<":";
				InitializeRoom();
				Method2();
			}
			break;
	}

	float percent = (static_cast<float>(TotalEscapeCount) / NoOfLoops) * 100;
	std::cout << "\nSucceeded percentage: " << percent << " %\n\n";

	system("pause");
	return 0;
}


