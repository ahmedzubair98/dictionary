#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>


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
	dictionary.read("aa.txt");
	dictionary.printTree();
	autoCorrect(dictionary);
}