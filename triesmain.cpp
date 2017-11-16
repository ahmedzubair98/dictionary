#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include<conio.h>

#include "stacks.h"
#include "myconsole.h"
#include "mygraphics.h"
#include "tries.h"

using namespace std;
const int Y_OF_SUGGESTIONS = 20;

void resetString(char *str, int length)
{
	for (int i=0;i<length;++i)
		str[i] = 0;
}

//assuming that str is a substring of words in strArray
//WILL NOT WORK IF str is NOT a substring of words in strArray
void displaySuggestions(char strArray[][MAXWORDSIZE],char *str)
{
	int xcord=0,ycord=0;
	GetCursorPosition(xcord,ycord);		//save cursor position
	PlaceCursor(0,Y_OF_SUGGESTIONS);

	int arrIndex = 0;
	int strIndex = 0;
	while (strArray[arrIndex][strIndex] != '\0')
	{
		while(str[strIndex] != '\0')
		{
			
			cout << str[strIndex++];
			SetColor(BACKGROUND_RED);
		}
		while(strArray[arrIndex][strIndex] != '\0')
		{	
			cout << strArray[arrIndex][strIndex++];
			SetColor(BACKGROUND_BLUE);

		}

		cout << " ";
		arrIndex++;
		strIndex = 0;
	}

	PlaceCursor(xcord,ycord);	//place cursor right back where it was

}

void autoCorrect(trie &dictionary)
{
	//THIS ARRAY IS TO BE FILLED OUT BY THE TRIE METHOD getMatchingSuffixes
	char wordSuggestions[MAXWORDS][MAXWORDSIZE] = {"a","app","apple","apples"};  //should have '\0' in the zeroth index for the last string...will mark the end of array of strings
													//see displaySuggestions to understand

	char x=0;
	int strIndex = 0;
	bool done = false;
	char str[MAXWORDSIZE]={0};
	int xcord=0,ycord=0;

	while (!done)
	{
		x = 0;
		x = CheckKeyPressed();
		if (x>0)
		{
			cout << x;
			if (x>='A' && x <= 'Z')
				x = x -'A' +'a';  //lower case
			if (x>='a' && x<='z')
			{	str[strIndex++] = x;				
				//call the trie method to get word suggestions
				dictionary.getMatchingSuffixes(wordSuggestions,str);
			}
			else
			{	resetString(str,MAXWORDSIZE);
				strIndex = 0;
			}

		} 

		if (strIndex>0)
			displaySuggestions(wordSuggestions,str);
		if (x==ESCKEY)
			done = true;
	}

	
}




int main()
{
	trie dictionary;
	//call the menu here
	//autocorrect should be called from menu
	
	char buff[100];
	char x;
	cout << "1. Construct a trie\n";
	cout << "Enter file name to read from\n";
	cin >> buff;
	dictionary.read(buff);
	system("cls");
	while (1)
	{
		cout << "1. Insert a word\n";
		cout << "2. Delete a word\n";
		cout << "3. Delete whole trie\n";
		cout << "4. Word Suggestions\n";
		cout << "5. Print trie\n";
		cout << "6. Read words from file\n";
		cout << "7. Exit\n";

		x=getch();
		system("cls");
		if (x == '1')
		{
			cout << "Enter word\n";
			cin >> buff;
			dictionary.insertWord(buff);
		}
		if (x == '2')
		{
			cout << "Enter word\n";
			cin >> buff;
			dictionary.deleteWord(buff);
		}
		if (x == '3')
		{
			dictionary.~trie();
		}
		if (x == '4')
		{
			autoCorrect(dictionary);
		}
		if (x == '5')
		{
			dictionary.printTree();
			getch();
		}
		if (x == '6')
		{
			cout << "Enter file name to read from\n";
			cin >> buff;
			dictionary.read(buff);
		}
		if (x == '7')
		{
			return 0;
		}
		system("cls");
	}
}
