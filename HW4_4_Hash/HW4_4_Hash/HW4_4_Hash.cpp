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

// iterator declaration for hash table
typedef HashTable<string>::Iterator iterDec;

// hash table size
const int TABLE_SIZE = 60331;

// function prototypes
void PrintTableStats(HashTable<string>& hashTable);
string ToLowerCase(string word);

int main()
{
	// declare variables
	int result = 0;
	string userInput;
	string currWord;
	clock_t beg; // used to time the hashtable load
	clock_t end; // used to time the hashtable load
	char response;
	
	// Chaining with table size of 60331
	ifstream infile;
	HashTable<string> hashTable(TABLE_SIZE);

	// open the dictionary file
	infile.open("words.txt");

	// check if the file exists, EXIT if it doesnt
	if (infile.fail())
	{
		cout << "\n\n**ERROR - The dictionary file could not be found...\n";
		exit(1);
	}

	cerr << "\nLoading dictionary with chaining....";
	beg = clock(); // start the timer

	// get data from file and put into hashtable
	while (infile >> currWord)
	{
		// makes sure duplicate words arent inserted into table
		if (!hashTable.Count(currWord))
		{
			hashTable.Insert(currWord);
		}
	}
	end = clock() - beg; // end the timer
	infile.close();
	cout << "\nTotal number of collisions: " << hashTable.maxCollision << "\n\n";
	PrintTableStats(hashTable);

	cout << "\nDictionary loaded in " << (double)end / ((double)CLOCKS_PER_SEC) << " secs!";

	// creates a line separator
	cout << endl;
	cout.fill('-');
	cout << left << setw(50) << "" << endl;

	do { // get user input
		cout << "\n>> Please enter a word to check if it is in the dictionary:  ";
		cin >> userInput;
		cout << endl;

		int howMany = hashTable.Count(userInput);

		if (howMany == 0)
		{
			cout << "\n" << userInput << " is not in the dictionary.";
		}
		else if (howMany > 0) {
			cout << "\nYes, it is in the dictionary " << howMany << " times.\n";
		}
		
		// ask for more data
		cout << "\nDo you want to enter another word? Enter Y for YES or anything else for NO ";
		cin >> response;
	} while (toupper(response) == 'Y');

	// Chaining with table size 120721
	ifstream infile2;
	int TABLE_SIZE2 = 120721;
	HashTable<string> hashTable2(TABLE_SIZE2);

	// open the dictionary file
	infile2.open("words.txt");

	// check if the file exists, EXIT if it doesnt
	if (infile2.fail())
	{
		cout << "\n\n**ERROR - The dictionary file could not be found...\n";
		exit(1);
	}

	cerr << "\nLoading dictionary with chaining and twice the hash table size....";
	beg = clock(); // start the timer

	// get data from file and put into hashtable
	while (infile2 >> currWord)
	{
		// makes sure duplicate words arent inserted into table
		if (!hashTable2.Count(currWord))
		{
			hashTable2.Insert(currWord);
		}
	}
	end = clock() - beg; // end the timer
	infile2.close();
	cout << "\nTotal number of collisions: " << hashTable2.maxCollision << "\n\n";
	PrintTableStats(hashTable2);

	cout << "\nDictionary loaded in " << (double)end / ((double)CLOCKS_PER_SEC) << " secs!";

	// creates a line separator
	cout << endl;
	cout.fill('-');
	cout << left << setw(50) << "" << endl;

	do { // get user input
		cout << "\n>> Please enter a word to check if it is in the dictionary:  ";
		cin >> userInput;
		cout << endl;

		int howMany = hashTable2.Count(userInput);

		if (howMany == 0)
		{
			cout << "\n" << userInput << " is not in the dictionary.";
		}
		else if (howMany > 0) {
			cout << "\nYes, it is in the dictionary " << howMany << " times.\n";
		}

		// ask for more data
		cout << "\nDo you want to enter another word? Enter Y for YES or anything else for NO ";
		cin >> response;
	} while (toupper(response) == 'Y');
	
	// Linear Probing with 60331 table size
	ifstream infile3;
	int TABLE_SIZE3 = 60331;
	HashTable<string> hashTable3(TABLE_SIZE3);

	// open the dictionary file
	infile3.open("words.txt");

	// check if the file exists, EXIT if it doesnt
	if (infile3.fail())
	{
		cout << "\n\n**ERROR - The dictionary file could not be found...\n";
		exit(1);
	}

	cerr << "\nLoading dictionary with Linear Probing and a hash table size of: " << TABLE_SIZE3 << "...";
	beg = clock(); // start the timer

	// get data from file and put into hashtable
	while (infile3 >> currWord)
	{
		// makes sure duplicate words arent inserted into table
		if (!hashTable3.Count(currWord))
		{
			hashTable3.InsertLinearProbe(currWord, 0);
		}
	}
	end = clock() - beg; // end the timer
	infile3.close();
	cout << "\nTotal number of collisions: " << hashTable3.maxCollision << "\n\n";
	PrintTableStats(hashTable3);

	cout << "\nDictionary loaded in " << (double)end / ((double)CLOCKS_PER_SEC) << " secs!";
	cout << "\n\nLargest Collision Chain was: " << hashTable3.maxCollision;

	// creates a line separator
	cout << endl;
	cout.fill('-');
	cout << left << setw(50) << "" << endl;

	do { // get user input
		cout << "\n>> Please enter a word to check if it is in the dictionary:  ";
		cin >> userInput;
		cout << endl;

		int howMany = hashTable3.Count(userInput);

		if (howMany == 0)
		{
			cout << "\n" << userInput << " is not in the dictionary.";
		}
		else if (howMany > 0) {
			cout << "\nYes, it is in the dictionary " << howMany << " times.\n";
		}

		// ask for more data
		cout << "\nDo you want to enter another word? Enter Y for YES or anything else for NO ";
		cin >> response;
	} while (toupper(response) == 'Y');
	
	// Linear Probing with 120721 table size
	ifstream infile4;
	int TABLE_SIZE4 = 120721;
	HashTable<string> hashTable4(TABLE_SIZE4);

	// open the dictionary file
	infile4.open("words.txt");

	// check if the file exists, EXIT if it doesnt
	if (infile4.fail())
	{
		cout << "\n\n**ERROR - The dictionary file could not be found...\n";
		exit(1);
	}

	cerr << "\nLoading dictionary with Linear Probing and a hash table size of: " << TABLE_SIZE4 << ".....";
	beg = clock(); // start the timer

	// get data from file and put into hashtable
	while (infile4 >> currWord)
	{
		// makes sure duplicate words arent inserted into table
		if (!hashTable4.Count(currWord))
		{
			hashTable4.InsertLinearProbe(currWord, 0);
		}
	}
	end = clock() - beg; // end the timer
	infile4.close();
	cout << "\nTotal number of collisions: " << hashTable.maxCollision << "\n\n";
	PrintTableStats(hashTable4);

	cout << "\nDictionary loaded in " << (double)end / ((double)CLOCKS_PER_SEC) << " secs!";
	cout << "\n\nLargest Collision Chain was: " << hashTable4.maxCollision << " \n";

	// creates a line separator
	cout << endl;
	cout.fill('-');
	cout << left << setw(50) << "" << endl;

	do { // get user input
		cout << "\n>> Please enter a word to check if it is in the dictionary:  ";
		cin >> userInput;
		cout << endl;

		int howMany = hashTable4.Count(userInput);

		if (howMany == 0)
		{
			cout << "\n" << userInput << " is not in the dictionary.";
		}
		else if (howMany > 0) {
			cout << "\nYes, it is in the dictionary " << howMany << " times.\n";
		}

		// ask for more data
		cout << "\nDo you want to enter another word? Enter Y for YES or anything else for NO ";
		cin >> response;
	} while (toupper(response) == 'Y');

	cout << "\n\nPeace";

	return 0;
}// end of main

void PrintTableStats(HashTable<string>& hashTable)
{
	int largestBucket = -9999999;
	int largestIndex = 0;
	int smallestBucket = 9999999;
	int smallestIndex = 0;
	double numBuckestUsed = 0;

	for (int x = 0; x < hashTable.TableSize(); ++x)
	{
		// iterator is used to traverse each hashtable bucket
		iterDec it = hashTable.begin(x);
		if (!hashTable.IsEmpty(x))
		{
			if (smallestBucket > hashTable.BucketSize(x))
			{
				smallestBucket = hashTable.BucketSize(x);
				smallestIndex = x;
			}
			if (largestBucket < hashTable.BucketSize(x))
			{
				largestBucket = hashTable.BucketSize(x);
				largestIndex = x;
			}
			++numBuckestUsed;
		
		}
	}
	cout << "Complete!\n";

	// creates a line separator
	cout << endl;
	cout.fill('-');
	cout << left << setw(50) << "" << endl;

	cout << "Total dictionary words = " << hashTable.TotalElems() << endl
		<< "Hash table size = " << hashTable.TableSize() << endl
		<< "Largest bucket size = " << largestBucket << " items at index #" << largestIndex << endl
		<< "Smallest bucket size = " << smallestBucket << " items at index #" << smallestIndex << endl
		<< "Total buckets used = " << numBuckestUsed << endl
		<< "Total percent of hash table used aka 'the load' = " << (numBuckestUsed / hashTable.TableSize()) * 100 << "%" << endl
		<< "Average bucket size = " << (hashTable.TotalElems() / numBuckestUsed) << " items";
}// end of PrintTableStats


string ToLowerCase(string word)
{
	for (unsigned x = 0; x < word.length(); ++x)
	{
		word[x] = tolower(word[x]);
	}
	return word;
}
