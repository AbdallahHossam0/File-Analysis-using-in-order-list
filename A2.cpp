//============================================================================
// Name        : A21.cpp
// Author      : Abdallah Hossam Eldin Hosny
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "inorderlist.h"

using namespace std;

int countLineWords(string);
int isSubstring(string, string);
void wordCount(const int);
void distWords(const int);
void charCount(const int);
void frequentWord(InOrderList&);
void countWord(InOrderList&, const string);
void starting(InOrderList&, const string);
void containing(InOrderList&, const string);
void search(InOrderList&, const string);
bool checkCommon(const string);
void strToLower(char*);





int main(int argc, char** argv){
	InOrderList wordList, distinictWordList, mostrepeatedWord;
	ifstream comm1, comm2;
	ifstream test1, test2;
	string line, currentWord, receivedWord, command, lastStoredWord;
	char word[250] = "";
	int lineNumber = 0, wordCounter = 0, receivedLine = 0, counter = 0;
	int distinctNumberWords = 0, wordRepeatedCounter = 0;
	long letterCounter = 0;

	if(argc != 3){
		cout << "Incorrect number of arguments"<< endl;
		exit(0);
	}
	test1.open(argv[1]);
	test2.open(argv[1]);
	comm1.open(argv[2]);
	comm2.open(argv[2]);
	if(!(comm1.is_open() && comm2.is_open() && test1.is_open())){
		cout<< "File not found";
		exit(0);
	}

	while(!test1.eof()){
		getline(test1, line);
		letterCounter++;
		for(auto character : line){
			(void)character;
			letterCounter++;
		}
	}
	letterCounter--;
	test1.clear();
	test1.seekg(0, ios::beg);
	for(lineNumber = 0; !test1.eof(); lineNumber++){
		getline(test1, line);
		counter = countLineWords(line);
		for(; counter > 0; counter--){
			test2 >> word;
			strToLower(word);
			for(unsigned int counter1 = 0; counter1 < strlen(word); counter1++){
				if(word[counter1] == '"' || word[counter1] == ',' || word[counter1] == ';' || word[counter1] == ':' ||
						word[counter1] == '\'' || word[counter1] == '`' || word[counter1] == '&' || word[counter1] == '.' ||
						word[counter1] == '[' || word[counter1] == ']' || word[counter1] == '{' || word[counter1] == '}' ||
						word[counter1] == '/'){
					word[counter1] = ' ';
				}
			}
			char *word1 = strtok(word, " ");
			while(word1 != NULL){
				wordCounter++;
				if(!wordList.sortedInsert(word1, lineNumber)){
					cout << "Unable to store the word" << endl;
				}
				word1 = strtok(NULL, " ");
			}
		}
	}

	counter = 0;
	test1.close();
	test2.close();

	if(wordList.readFirst(receivedWord, receivedLine)){
		currentWord = receivedWord;
		counter++;
		while(wordList.readNext(receivedWord, receivedLine)){
			if(receivedWord == currentWord){
				counter++;
			}
			else{
				distinctNumberWords++;
				lastStoredWord = currentWord;
				distinictWordList.sortedInsert(currentWord, counter);
				currentWord = receivedWord;
				counter = 1;
			}
		}
	}
	if(lastStoredWord == currentWord){
		counter++;
	}
	else{
		distinctNumberWords++;
	}
	distinictWordList.sortedInsert(currentWord, counter);

	counter = 0;


	if(distinictWordList.readFirst(receivedWord, wordRepeatedCounter)){
		if(checkCommon(receivedWord)){
			mostrepeatedWord.sortedInsert(receivedWord, wordRepeatedCounter);
			counter = wordRepeatedCounter;
		}
		while(distinictWordList.readNext(receivedWord, wordRepeatedCounter)){
			if(counter == wordRepeatedCounter && checkCommon(receivedWord)){
				mostrepeatedWord.sortedInsert(receivedWord, wordRepeatedCounter);
			}
			else if(wordRepeatedCounter > counter && checkCommon(receivedWord)){
				mostrepeatedWord.deleteWholeList();
				mostrepeatedWord.sortedInsert(receivedWord, wordRepeatedCounter);
				counter = wordRepeatedCounter;
			}
		}
	}

	counter = 0;
	for(lineNumber = 0; !comm1.eof(); lineNumber++){
		getline(comm1, line);
		counter = countLineWords(line);
		if(counter == 0)
			continue;
		if(counter == 1){
			comm2 >> command;
			if(command == "wordCount")
				wordCount(wordCounter);
			else if(command == "distWords")
				distWords(distinctNumberWords);
			else if(command == "charCount")
				charCount(letterCounter);
			else if(command == "frequentWord")
				frequentWord(mostrepeatedWord);
			else
				if(command == "countWord" || command == "search" || command == "containing" || command == "starting")
					cout << "Incorrect number of arguments" << endl;
				else
					cout << "Undefined command" << endl;
		}
		else if(counter == 2){
			comm2 >> command;
			comm2 >> word;
			strToLower(word);
			if(command == "starting")
				starting(distinictWordList, word);
			else if(command == "containing")
				containing(distinictWordList, word);
			else if(command == "search")
				search(wordList, word);
			else if(command == "countWord")
				countWord(distinictWordList, word);
			else
				if(command == "wordCount" || command == "distWords" || command == "charCount" || command == "frequentWord")
					cout << "Incorrect number of arguments" << endl;
				else
					cout << "Undefined command" << endl;
		}
		else{
			comm2 >> command;
			counter --;
			if(command == "wordCount" || command == "distWords" || command == "charCount" || command == "frequentWord"
					|| command == "countWord" || command == "search" || command == "containing" || command == "starting"){
				cout << "Incorrect number of arguments" << endl;
			}
			else
				cout << "Undefined command" << endl;
			for(; counter > 0; counter--){
				comm2 >> command;
			}
		}
	}


	comm1.close();
	comm2.close();
	mostrepeatedWord.deleteWholeList();
	distinictWordList.deleteWholeList();
	wordList.deleteWholeList();
	return 0;
}


int countLineWords(string str){
	int NWords = str.empty() || str.back() == ' ' ? 0 : 1;
	for (size_t s = str.size(); s > 0; --s)
		if (str[s] == ' ' && str[s-1] != ' ') ++NWords;
	return NWords;
}

int isSubstring(string str1, string str2)
{
	int M = str1.length();
	int N = str2.length();
	int j;
	for (int i = 0; i <= N - M; i++) {
		for (j = 0; j < M; j++)
			if (str2[i + j] != str1[j])
				break;
		if (j == M)
			return true;
	}
	return false;
}

void wordCount(const int number){
	cout << number << " words" << endl;
}

void distWords(const int number){
	cout << number << " distinct words" << endl;
}

void charCount(const int number){
	cout << number << " characters"<< endl;
}

void frequentWord(InOrderList& list){
	string word;
	int i;
	if(list.readFirst(word, i)){
		cout << "Most frequent word is: " << word;
		while(list.readNext(word, i)){
			cout << " " << word;
		}
		cout << endl;
	}
}

void countWord(InOrderList& list, const string str){
	string word;
	int i;
	if(list.readFirst(word, i)){
		if(word == str){
			cout << word << " is repeated " << i << " times" << endl;
			return;
		}
		while(list.readNext(word, i)){
			if(word == str){
				cout << word << " is repeated " << i << " times" << endl;
				return;
			}
		}
	}
	cout << str << " is repeated 0 times" << endl;
}

void starting(InOrderList& list, const string str){
	string word;
	int number;
	bool found;
	if(list.readFirst(word, number) && !word.substr(0, str.length()).compare(str)){
		cout << word <<": " << number << "\t";
		found = true;
	}
	while(list.readNext(word, number)){
		if(!word.substr(0, str.length()).compare(str)){
			cout << word <<": " << number << "\t";
			found = true;
		}
	}
	if(!found)
		cout << "Word not found";
	cout << endl;
}

void containing(InOrderList& list, const string str){
	string word;
	int i;
	bool found = false;
	if(list.readFirst(word, i)){
		if(isSubstring(str, word)){
			cout << word << ": "<< i << "\t";
			found = true;
		}
		while(list.readNext(word, i)){
			if(isSubstring(str, word)){
				cout << word << ": "<< i << "\t";
				found = true;
			}
		}
	}
	if(!found){
		cout << "Word not found";
	}
	cout << endl;
}

void search(InOrderList& list, const string str){
	string word, prev;
	int i, prevline;
	bool found = false;
	if(list.readFirst(word, i)){
		if(isSubstring(str, word) == 1){
			cout << word << ":\tlines\t" << i + 1;
			prevline = i;
			found = true;
			prev = word;
		}
		while(list.readNext(word, i)){
			if(isSubstring(str, word)){
				if(word == prev){
					if(i != prevline)
						cout << "\t" << i + 1;
				}
				else{
					cout << endl;
					cout << word << ": lines\t" << i + 1;
					found = true;
				}
			}
			prev = word;
			prevline = i;
		}
	}
	if(!found)
		cout << "Word not found";
	cout << endl;
}

bool checkCommon(const string word){
	if (word == "a" || word == "an" || word == "the" || word == "of" || word == "in" || word == "on" || word == "and" ||word == "is" || word == "are"){
		return false;
	}
	else
		return true;
}

void strToLower(char* str){
	for(unsigned int counter = 0; counter < strlen(str); counter++){
		if(str[counter] > 64 && str[counter] < 91)
			str[counter] |= 0x20;
	}
}
