#include <iostream>
#include<sstream>
#include<iomanip>
#include<string>
#include <algorithm> //used for string functions like .insert()
#include <set>
#include "proj07_functions.h"
#include<fstream> //used to read the file
#include <stdio.h> //used for to lower() or toupper() functions
#include <ctype.h> // used for tolower() or toupper() functions
using std::ifstream;
using std::string; using std::getline; using std::to_string;
using std::setprecision; using std::cout; using std::cin; using std::endl; 

//const std::string letters = "abcdefghijklmnopqrstuvwxyz";

void deletes(const std::string &word, std::set<std::string> &result) {
//creates all the single letter deletes possible from the argument word and places them in the argument result.
//void return (meaning no return value.) All deletes are inserted into the set<string>&result.

	for (int count = 0; count < word.size(); count++) { //iterates through every letter in the word
		string the_word = word;
		the_word.erase(count, 1); // finds the specific delete position, length being 1 character deleted  
		result.insert(the_word);
	}
}

void inserts(const std::string &word, std::set<std::string> &result) {
/*creates all the single letter inserstions possible from the argument word and places them in the argument result.
void return (meaning no return value.) All inserstions are placed in the set<string>&result.*/
	for (int count = 0; count < word.size() + 1; count++) { //iterate through every letter in the word
		for (int j = 0; j < letters.size(); j++) { //iterates through all the letters in the alphabet string
			string the_word = word;
			the_word.insert(count, 1, letters[j]); //the 1 represents how many characters you're inserting
				result.insert(the_word);
		}	
	}
}

string swapChars(string& str, int i){ // this function finds the two characters that are swapped
	char index_char;
	index_char = str[i]; //character 1
	str[i] = str[i + 1]; //character 2
	str[i + 1] = index_char;
	return str;
}

void transposes(const std::string &word, std::set<std::string> &result) {
/*creates all the single letter transpositions possible from the argument word and places them in the argument result.
void return (meaning no return value.) All transpositions are placed in the set<string>&result.*/

	for (int count = 0; count < word.size() - 1; count++){ //iterates through every letter in the word
		string transpose_word = word; 
		swapChars(transpose_word, count); //calls the swap characters function 
		result.insert(transpose_word); // swap them back to original positions
		}
}

void replaces(const std::string &word, std::set<std::string> &result) {
	/*creates all the single letter replaces possible from the argument word and places them in the argument result.
	We allow the original letters to occur in the replacement set, making it potentially + 1 against the size of just the replacement set.
	void return (meaning no return value.) All replacements are placed in the set<string>&result.
	*/

	char original_char; 
	for (int count = 0; count < word.size() + 1; count++) { //iterates through every letter in the word
		string replace_word = word;
		original_char = replace_word[count]; //take the specific replaced word letter
		for (int j = 0; j < letters.size(); j++) { //iterates through every letter in the alphabet string
			string replace_word = word;
			replace_word[count] = letters[j]; //takes the specific replaced word letter and is set to the correct letter  
			result.insert(replace_word);
		}
	}
}

void read_words(std::string fname, std::set<std::string> &result) {
/*reads a file, the file name indicated by fname, into set<string> result. We provide a
file named words.txt with about 112,000 words, each word on a separate line. Write the
function to read files with multiple words on the same line.
Each word is converted to lower case before it is added to the set.
non-alphabetic character are deleted: Two4Me  twome
void return (meaning no return value.) All insertions are placed in the set<string>&result.*/
	ifstream words_text(fname);
	string input_word; // whatever word is given by user
	string lower_word; 

	if (words_text.is_open()) { //we want to loop over the string and convert chars in strings 
		while (getline(words_text, input_word)) { //reads each line in the file as a string
			string lower_word; // stores new lowercase words
			for (auto range : input_word) { //a range for loop 
				if (isalpha(range)) { //checks to see if characters are alphabets and not weird digits
					range = tolower(range); //makes all letters lowercase
					lower_word.push_back(range); //pushes back the new lower characterds into empty string
				}
			}
			result.insert(lower_word);
		}
	}
}

void find_completions(const std::string &word, const std::set<std::string> &word_list,std::set<std::string> &result) {
/*takes in a word ‘w’ as a string, and a set of valid words.
void return. All the words in word_list that have ‘w’ as a prefix are added to result.
*/
	string selected_word;
	for (auto each_word : word_list) { //goes through each word in the word list
		selected_word = each_word.substr(0, word.size());// finds part of the word that contains the same first letter as the rest of the words
			if (selected_word == word){ //compare the length of the word iterated to the given word 
				result.insert(each_word);
			}
	}
}

void find_corrections(const std::string &word, std::set<std::string> &result) {
/*takes in a word as a string, and calculates the deletes, inserts, transposes, and replaces sets for the word.
void return. All the dels, reps, trans and ins for each word are added to result. 
*/
	deletes(word, result); //call all four functions doing the corrections to do them at once in this one function
	replaces(word, result);
	transposes(word, result);
	inserts(word, result);
}

void find_2step_corrections(const std::string &word, std::set<std::string> &result) {
/*
-takes in a word as a string, and calculates 2 levels of the deletes, inserts, transposes, and
replaces sets for the word. i.e. for each word in 4 sets, all corrections are applied again.
-void return. All the dels, reps, trans and ins for each word are added to result. 
*/

	std::set<string> empty_set; //create an empty set 
	
	find_corrections(word, empty_set); //call each function from the find_corrections
	for (auto element : empty_set) { //iterate through each function again 
		find_corrections(element, result); //obtain the new corrections for the second time where results is the new set of corrections
	}
}

void find_reasonable_corrections(const std::set<std::string> &possibles, const std::set<std::string> 
								&word_list, std::set<std::string> &result) {
/*for every word in possibles, check if that word exists in the word_list. If it does, it is
added to result
void return
*/

	 for (auto word : possibles) { // iterating through every word in possibles
		 string some_string = word; // set iterated element to a variable 
		 std::set<std::string>::iterator iterate = word_list.find(some_string); // use the string algorithm to find specific iterated word in the word list

		 if (iterate != word_list.cend()) { //check if the word exists in the word list
			 result.insert(some_string); //if the word exists, it is added to the result
		 }
	 }
}



