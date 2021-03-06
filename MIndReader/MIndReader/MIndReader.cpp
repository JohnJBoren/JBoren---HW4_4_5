#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
#include "HashTable.h"

using namespace std;

// Variables
string answer;
string pastAnswer = "";
int playerScore = 0;
int compScore = 0;
string myGuess;
const int TABLE_SIZE = 10000;
HashTable<string> hashTable(TABLE_SIZE);

// function prototypes
void TakeGuess();
void flip();
void score();
void MakeGuess();

int main()
{
	cout << "\n\t\t- Heads or Tails Mind Reader -\n";
	
	// First guess
	TakeGuess();
	hashTable.InsertLinearProbe(answer, 0, "");
	flip();
	score();

	// The rest of them
	do {
		TakeGuess();
		hashTable.InsertLinearProbe(pastAnswer, 0, answer);
		MakeGuess();
		score();
	} while ((playerScore < 25) and (compScore < 25));
	
	if (playerScore > compScore)
	{
		cout << "\n\n\t\t- YOU WON!!! -";
	}
	else
	{
		cout << "\n\n\t\t- I WON!!!  YOU LOSE!!!";
	}
 
}

void TakeGuess()
{
	string h = "h";
	string t = "t";

	cout << "\nGuess heads or tails and I'll predict your guess.\n";
	cout << "What is your pick, [h/t] ?: ";
	cin >> answer;
	if (answer == h or answer == t)
	{
		pastAnswer.append(answer);
	}
	else {
		TakeGuess();
	}
}

void flip()
{
	int flip = rand() % 2 + 1;
	if (flip == 1)
	{
		myGuess = "h";
	}
	else {
		myGuess = "t";
	}

}

void score()
{
	cout << "\nYou entered: " << answer;
	if (myGuess == answer)
	{
		cout << "\nYes!  You lost, I too predicted: " << myGuess;
		++compScore;
	}
	else
	{  
		cout << "\nNo!  You won, I predicted: " << myGuess;
		++playerScore;
	}

	cout << "\nScore = Comp: " << compScore << " | Player: " << playerScore;
}

void MakeGuess()
{
	int guess;
	int end = pastAnswer.length();
	// Get the past 4 answers
	if (end = 1)
	{
		string pastAnswer2 = pastAnswer;
		guess = hashTable.Count(pastAnswer2);
	}
	if (end = 2)
	{
		string pastAnswer2 = pastAnswer;
		guess = hashTable.Count(pastAnswer2);
	}

	if (end = 3)
	{
		string pastAnswer2 = pastAnswer;
		guess = hashTable.Count(pastAnswer2);
	}
	
	if (end = 4)
	{
		string pastAnswer2 = pastAnswer;
		guess = hashTable.Count(pastAnswer2);
	}
	
	if (end > 4)
	{
		string pastAnswer2 = pastAnswer.substr((end - 4), end);
		guess = hashTable.Count(pastAnswer2);
		
	}
	if (guess == 1)
	{
		myGuess = "t";
	}
	else
	{
		myGuess = "h";
	}
	
	
}
