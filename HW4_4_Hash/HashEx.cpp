#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
#define _GLIBCXX_USE_CXX11_ABI 0/1

using namespace std;

// hash table size
const int TABLE_SIZE = 60331;

// function prototypes
string ToLowerCase(string word);
unsigned int APHash(const string& str);

int main()
{
	int result = 0;
	string userInput;
	string currWord;
	clock_t begin;
	clock_t end;
	ifstream infile;

	// open the file
	infile.open("words.txt");

	// make sure it exists
	if (infile.fail())
	{
		cout << "\n\nWHOOPS - the word file does not exist\n";
		exit(1);
	}

	cerr << "\nLoading word file...\n";
	begin = clock();

	// get the words and output the hash
	while (infile >> currWord)
	{
		unsigned int hashedIt;
		hashedIt = APHash(currWord);
		std::cout << hashedIt << "\n";
	}

	end = clock();

	cout << "\nElasped Time = " << (end - begin);


	return 0;
}


unsigned int APHash(const string& str)
{
	unsigned int hash = 0xAAAAAAAA;

	for (int i = 0; i < str.length(); i++)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ str[i] * (hash >> 3)) :
			(~((hash << 11) + (str[i] ^ (hash >> 5))));
	}

	return hash;
}
