#include <fstream>
#include <algorithm>
#include "SpellChecker.h";
#include "timer.h"

using namespace std;

Dictionary<string> dictionary;

string cleanWord(string temp) {

	// Remove non-letters from the word, keeping only the apostrophe and numbers
	temp.erase(remove_if(temp.begin(), temp.end(), [](char character)
	{
		return !isalpha(character) && character != '\'' && !isdigit(character);
	}),
		temp.end()
		);

	//convert to lower case
	for (int i = 0; i < temp.size(); i++)
		temp[i] = tolower(temp[i]);

	return temp;
}

int main()
{
	ifstream dictionaryFile("dict.txt", ios::in);

	int correctWords = 0, misspelledWords = 0, compares = 0, uncheckedWords = 0;
	string word;

	while (dictionaryFile)
	{
		dictionaryFile >> word;
		dictionary.insert(word);
	}

	cout << "dictionary Size " << dictionary.getSize() << endl;
	Timer time;

	time.Start();

	ifstream bookFile("book.txt", ios::in);
	while (bookFile)
	{
		string temp;
		bookFile >> temp;

		word = cleanWord(temp);

		if (word.length() == 0)
			continue;

		if (!isalpha(word[0]))
		{
			uncheckedWords++;
			continue;
		}

		if (dictionary.compare(word) == 1)
		{
			correctWords++;
			cout << "Correct: " << word << endl;
		}

		else
		{
			misspelledWords++;
			cout << "Misspelled: " << word << endl;
		}

	}

	time.Stop();


	cout << "done checking and these are the results\n";
	cout << "Finished in time " << time.Time() << endl;
	cout << "There are " << correctWords << " words found in the dictionary.\n";
	cout << "\t" << Dictionary<string>::compareCorrect << " compares. Average " << Dictionary<string>::compareCorrect / correctWords << endl;
	cout << "There are " << misspelledWords << " words NOT found in the dictionary.\n";
	cout << "\t" << Dictionary<string>::compareMisspelled << " compares. Average " << Dictionary<string>::compareMisspelled / misspelledWords << endl;

}