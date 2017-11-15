#include <iostream>
#include <math.h>
#include <fstream>
#include"stacks.h"
#include"mygraphics.h"

#include <Windows.h>
#include "tries.h"

using namespace std;
//implement the trie class here



void trie::printTree()
{
	myRect(0, 0, 800, 500, RGB(255, 255, 255), RGB(255, 255, 255));
	print(root, 0, 600, 0, 1);

}

//will print in preorder
void trie::print(trieNode *n, int minx, int maxx, int y, int ht)
{
	if (!n) return;
	int width = 30;
	int down = 25;
	COLORREF red = RGB(255, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	COLORREF black = RGB(0, 0, 0);
	COLORREF yellow = RGB(0, 255, 255);
	int x = (minx + maxx) / 2;

	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		if (n->child[i])
		{
			for (int j = 0; j < ALPHABETSIZE; j++)
			{
				if (n->child[i]->child[j])
					myLine(x + 15 * i + 5, y + 15, x + 15 * j + 5 , y + 3 * down, yellow);
			}
		}


		char str[2];
		str[0] = i + 'a';
		str[1] = 0;
		COLORREF colour = black;

		if (n->child[i] )
			myDrawText(x + 15*i, y, 20, str, colour, white);

		//recursive
		print(n->child[i], minx, maxx, y + 3*down, ht + 1);
	}
}





bool trieNode::isLeaf()
{
	bool flag = true;
	for (int i = 0; i < ALPHABETSIZE && flag; i++)
	{
		if (child[i] != NULL)
			flag = false;
	}
	return flag;
}

trie::trie()
{
	root = new trieNode;
}

void trie::insertWord(char *word)
{
	for (int i = 0; word[i] != 0; i++)
	{
		word[i] = tolower(word[i]);
		if (!(word[i] >= 'a' && word[i] <= 'z'))
		{
			for (int j = i; word[j] != 0; j++)
			{
				word[j] = word[j + 1];
			}
		}
	}
	trieNode *curr = root;
	for (int i = 0; word[i] != 0; i++)
	{
		int index = word[i] - 'a';
		if (curr->child[index] == NULL)
		{
			curr->child[index] = new trieNode;
			curr = curr->child[index];
		}
		else
		{
			curr = curr->child[index];
		}
	}
	curr->isWordEnd = true;
}

bool trie::deleteWord(char *word)
{
	for (int i = 0; word[i] != 0; i++)
	{
		word[i] = tolower(word[i]);
		if (!(word[i] >= 'a' && word[i] <= 'z'))
		{
			for (int j = i; word[j] != 0; j++)
			{
				word[j] = word[j + 1];
			}
		}
	}
	trieNode *curr = root;
	bool flag = true;
	int index;
	stack<trieNode *> nodeStack;
	stack<int> indexStack;
	for (int i = 0; word[i] != 0 && flag; i++)
	{
		index = word[i] - 'a';
		if (curr->child[index] == NULL)
		{
			flag = false;
		}
		else
		{
			nodeStack.push(curr);
			indexStack.push(index);
			curr = curr->child[index];
		}
	}
	if (!curr->isWordEnd)
		flag = false;
	else
		curr->isWordEnd = false;
	if (flag)
	{
		while (!nodeStack.empty())
		{
			nodeStack.pop(curr);
			indexStack.pop(index);
			if (curr->child[index]->isLeaf() && !curr->child[index]->isWordEnd)
			{
				delete curr->child[index];
				curr->child[index] = NULL;
			}
		}
	}
	return flag;
}

void trie::del(trieNode *n,trieNode *p, int i)
{
	if (n->isLeaf() && p)
	{
		delete [] n->child;
		p->child[i] = NULL;
		return;
	}
	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		if (n->child[i])
		{
			del(n->child[i],n, i);
		}
	}
}

void trie::getWords(char strArray[][MAXWORDSIZE], trieNode *curr, char arr[MAXWORDSIZE], int i, int &n)
{
	if (n == 29)
		return;
	if (curr->isWordEnd)
	{
		arr[i] = 0;
		strcpy(strArray[n], arr);
		n++;
	}
	if (curr->isLeaf())
	{
		i = 0;
		return;
	}
	for (int j = 0; j < ALPHABETSIZE; j++)
	{
		if (curr->child[j])
		{
			arr[i] = char(j + 'a');
			getWords(strArray, curr->child[j], arr, i + 1, n);
		}
	}
}


void trie::getMatchingSuffixes(char strArray[][MAXWORDSIZE], char *word)
{
	int n = 0;
	char buff[MAXWORDSIZE];
	for (int i = 0; word[i] != 0; i++)
	{
		word[i] = tolower(word[i]);
		if (!(word[i] >= 'a' && word[i] <= 'z'))
		{
			for (int j = i; word[j] != 0; j++)
			{
				word[j] = word[j + 1];
			}
		}
	}
	trieNode *curr = root;
	for (int i = 0; word[i] != 0; i++)
	{
		int index = word[i] - 'a';
		if (curr->child[index] == NULL)
		{
			return;
		}
		else
		{
			curr = curr->child[index];
		}
	}
	strcpy(buff, word);
	getWords(strArray, curr, buff, strlen(buff), n);
	buff[0] = 0;
	strcpy(strArray[n], buff);
}


void trie::read(char *str)
{
	char buff[MAXWORDSIZE];
	ifstream fin;
	fin.open(str);
	while(!fin.eof())
	{
		fin >> buff;
		insertWord(buff);
	}

}
