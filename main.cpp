#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <ctime>


char guess();
std::vector<char> string_to_char(std::string word);
void printWord(std::vector<char> word);
std::vector<std::string> getWords();
std::vector<int> changeWord(char character, std::vector<char> w_copy);
int findIndex(char guess_char, std::vector<char> word);

int main() {
    std::vector<std::string> words_list = getWords();  // Obtains a vector containing 200 random words
    srand((unsigned) time(0));  // Allows the rand function to be random each time when executed
    int rand_num = std::rand() % 201;  // Gets a random number in the range 0 to 200
    int guess_num = 0;
    std::string w_copy_str = words_list[rand_num];  // A string copy of the randomised word
    std::vector<char> w_copy = string_to_char(w_copy_str);  // A vector containing the characters of the randomised word
    std::string word_str;
    for(int i = 0; i < w_copy_str.length(); i++){  // Initialises the '___ ...' string based on the length of the word
        word_str += "_";
    }
    std::vector<char> word = string_to_char(word_str);  // Creates a vector containing the characters of the '___ ...' word above
    int max_guess = w_copy_str.length() * 2;  // The maximum allowed guesses of the user based on the length of the word
    std::vector<char> guess_list;  // A vector containing the wrong characters the user guessed
    printWord(word);
    while(guess_num < max_guess && word != w_copy){  // While loop runs until the user exceeds the maximum guesses or if they guess the word correctly
        char guess_char = guess();  // Obtains guess from user
        std::cout << guess_char << std::endl;
        if(!(std::count(w_copy.begin(), w_copy.end(), guess_char))){  // If the character they guessed is not in the word
            std::cout << "Wrong guess, please try again!" << std::endl;
            guess_list.push_back(guess_char);
            guess_num += 1;
        }
        else{
            std::vector<int> index = changeWord(guess_char, w_copy);  // Obtains a vector containing the index(es) of the character in the word
            for(int & i : index){  // Loops through the vector obtained above, changing the '___ ...' vector to the guessed character at the complementary index(es)
                word[i] = guess_char;
            }
        }
        printWord(word);
        std::cout << std::endl;
        std::cout << "Wrong guesses so far: ";
        printWord(guess_list);
        std::cout << std::endl;
    }
    if(word == w_copy){
        std::cout << "You've Won!\nThe word was: " << w_copy_str;
    }
    else{
        std::cout << "Sorry, you've lost, please try again!\nThe word was: " << w_copy_str;
    }
    return 0;
}

/*
 * Obtains guess from the user
 * Returns a character of their guess
 */
char guess(){
    char guess_letter;
    std::cout << "Please input your guess character:";
    std::cin >> guess_letter;

    if(isdigit(guess_letter)){  // Checks if they input a number instead of a character
        std::cout << "Invalid input!\nPlease try again!" << std::endl;
        guess();
    }
    return guess_letter;
}

/*
 * Gets a vector of 200 words from a text file by reading each line
 * Returns a vector containing the 200 words
 */
std::vector<std::string> getWords(){
    std::vector<std::string> words_list;
    std::ifstream in("words.txt");
    if(!in){  // If the file doesn't open properly, error is printed
        std::cout << "ERROR: Couldn't open file!";
    }
    for(std::string line; std::getline(in, line);){
        words_list.push_back(line);
    }

    return words_list;
}

/*
 * Prints a vector of characters as a string
 */
void printWord(std::vector<char> word){
    for (char & i : word) {
        std::cout << i;
    }
    std::cout << std::endl;
}

/*
 * Converts a string object into a vector containing its characters
 * Returns a vector of characters
 */
std::vector<char> string_to_char(std::string word){
    std::vector<char> str_array;
    for(char & i : word) {
        str_array.push_back(i);
    }
    return str_array;
}

/*
 * Changes the '___' string based on the guesses of the user
 * Returns a vector of the indexes of the letter in the word
 */
std::vector<int> changeWord(char character, std::vector<char> w_copy){
    std::vector<char> w_copy_2 = w_copy;  // Creates a copy of the vector containing the characters of the word
    std::vector<int> index;
    while(std::count(w_copy_2.begin(), w_copy_2.end(), character) > 0){  // Loops until all the occurrences of the character guessed are looped through
        int ind = findIndex(character, w_copy_2);  // Finds the index of each of the character's occurrence in the word
        index.push_back(ind);
        w_copy_2[ind] = 0;  // Deletes the characters already looped through in the word copy vector
    }
    return index;
}

/*
 * Finds the index of a specified character in a vector of characters
 * Returns an integer specifying the index of the character
 */
int findIndex(char guess_char, std::vector<char> word){
    auto it = std::find(word.begin(), word.end(), guess_char);
    int index = it - word.begin();
    return index;
}

