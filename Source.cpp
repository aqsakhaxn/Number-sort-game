#include<iostream>
#include<queue>
#include<stack>
#include<fstream>
#include<string>
#include <stdlib.h>
using namespace std;

string levelFlask[2][5] = {
	{ "L1F1", "L1F2", "L1F3", "L1F4", "L1F5" },
	{ "L2F1", "L2F2", "L2F3", "L2F4", "L2F5" }
};


int tempFlask[5][4];
stack<int> flask[5];

void ClearScreen()
{
	if (system("CLS"))
	{
		system("clear");
	}
}

void UpdateStack(){

	// POPING STACK IN ARRAY

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (flask[i].empty())
			{
				tempFlask[i][j] = 0;
			}
			else
			{
				tempFlask[i][j] = flask[i].top();
				flask[i].pop();
			}
		}

	}

	// STORING IN STACK AGAIN

	for (int i = 0; i < 5; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (tempFlask[i][j] != 0)
			{
				flask[i].push(tempFlask[i][j]);
			}
		}
	}

}

bool CheckAction(int input1,int input2){

	ClearScreen();
	if (flask[input1-1].empty())
	{
		cout << ">>>>>>>  WRONG MOVE!  <<<<<<<\n\n";
		return false;
	}
	else if (flask[input2-1].size()==4)
	{
		cout << ">>>>>>> WRONG MOVE! <<<<<<<\n\n";
		return false;
	}
	else if (flask[input2 - 1].size()<4 && flask[input2 - 1].size()>0)
	{
		if (flask[input1 - 1].top() != flask[input2 - 1].top())
		{
			cout << ">>>>>>>  WRONG MOVE!  <<<<<<<\n\n";
			return false;
		}
		else
		{
			cout << ">>>>>>>  RIGHT MOVE <<<<<<<\n\n";
			flask[input2 - 1].push(flask[input1 - 1].top());
			flask[input1 - 1].pop();
			UpdateStack();
			return true;
		}
	}
	else
	{
		cout << ">>>>>>>  RIGHT MOVE  <<<<<<<\n\n";
		flask[input2 - 1].push(flask[input1 - 1].top());
		flask[input1 - 1].pop();
		UpdateStack();
		return true;
	}
	//cout << "\nfirst\n";
}


void PrintStacks(int levelNumber){

	int input1,input2;
	cout << "------------------- LEVEL " << levelNumber << " -------------------\n\n";

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << "\t" << tempFlask[j][i];
		}
		cout << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << "\t" << "STACK" << i + 1;
	}
	cout << "\n\n" << "Select poping stack: ";
	cin >> input1;
	cout << "Select pushing stack: ";
	cin >> input2;
	CheckAction(input1, input2);

}

bool Loss(){

	bool checkFlask[5] = { false };
	bool isFlaskFull[5] = { false };
	//bool allFlaskFull = false;
	int counter1 = 0, counter2, counter3 = 0;
	int num;

	for (int i = 0; i < 5; i++)
	{
		if (flask[i].size()==4)
		{
			isFlaskFull[i] = true;
			counter1++;
		}
	}
	if (counter1==3)
	{
		for (int i = 0; i < 5; i++)
		{
			if (tempFlask[i][0]>0)
			{
				num = tempFlask[i][0];
				counter2 = 0;
				for (int j = 0; j < 4; j++)
				{
					if (tempFlask[i][j]!=num)
					{
						checkFlask[i] = false;
					}
					else
					{
						counter2++;
					}
				}
				if (counter2==4)
				{
					checkFlask[i] = true;
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (checkFlask[i])
			{
				counter3++;
			}
		}
		if (counter3==3)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

void RunLevel(int levelNumber){

	string line;
	ifstream readFlask[5];

	// STORING IN STACK FROM FILE

	for (int i = 0; i < 5; i++)
	{
		readFlask[i].open(levelFlask[levelNumber][i] + ".txt");
		while (getline(readFlask[i], line))
		{
			flask[i].push(stoi(line));
		}
		readFlask[i].close();
	}

	UpdateStack();
	ClearScreen();
	cout << ">>>>>>>  PERFORM ACTION  <<<<<<<\n\n";

	while (Loss())
	{
		PrintStacks(levelNumber+1);
	}
	if (!Loss())
	{
		cout << endl;
		cout << "----------------------------------\n";
		cout << "----------------------------------\n";
		cout << "--------  CONGRATULATIONS  -------\n";
		cout << "------------  WINNER  ------------\n";
		cout << "--------------  :D  --------------\n";
		cout << "----------------------------------\n";
		cout << "----------------------------------\n";
		cout << endl;
	}
}

int main(){

	int level=-1;
	while (level!=0)
	{
		cout << "*********** NUMBER SORT GAME ***********\n";

		cout << "Enter level: ";
		cin >> level;
		RunLevel(level-1);

	}


	system("pause");
}
