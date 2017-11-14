#ifndef TRIE_H
#define TRIE_H


const int MAXSTACKSIZE = 500;
const int ALPHABETSIZE = 26;
const int MAXWORDSIZE = 30;
const int MAXWORDS = 100;

class trieNode;
class trie;

class trieNode
{
	//methods
	//implement constructor and destructor
	trieNode() { for (int i = 0; i < ALPHABETSIZE; i++) child[i] = NULL; isWordEnd = false; };
	~trieNode() { };
	// check if a node is leaf
	bool isLeaf();	
	//data members
	trieNode *child[ALPHABETSIZE];
	bool isWordEnd;

	friend class trie;
};

class trie
{
public:
	//constructor
	trie();
	void printTree();				//print the whole trie as was done in avl trees
	bool deleteWord(char *word);
	void insertWord(char *word);
	void getMatchingSuffixes(char strArray[][MAXWORDSIZE],char *str);
	void read(char *str);
 
	//destructor...you must implement the destructor also
	~trie() { del(root, NULL, 0); delete root; };

private:
	void del(trieNode *n, trieNode *p, int i);
	void getWords(char strArray[][MAXWORDSIZE], trieNode *curr, char arr[MAXWORDSIZE], int i, int &n);
	void print(trieNode *n, int minx, int maxx, int y, int ht);

	trieNode *root;
};


#endif