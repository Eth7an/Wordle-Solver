//
//  main.cpp
//  Wordle Guesser
//
//  Created by Ethan White on 3/21/22.
//

// ENTER YELLOW, GREEN, GREY Letters. YELLOW LETTERS LIKE GREEN WITH SPACES AND REMOVE IF MATCHING POSITION AFTER RUNINNG TO CHECK ALL LETTERS ARE IN ELEMENT
// option for yellow positioning factoring
// ANOTHER FILE FOR PRESORTED WORDS... AT BEGINNIGN OF PROGRAAM DO YOU WANT TO UPDATE WORD FILE Y/N

// Libraries
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

// Using standard namespace
using namespace std;

// Function declarations
string getKnownLetters(bool, int);
string getWrongLetters();
bool compareFrequency(string, string);
vector<string> sortByFrequency(vector<string>, vector<string>, int);
vector<string> importWords(string, bool);
vector<string> importUnigramWords(string, int);
void printVector(vector<string>);


int wordLength = 5;


/**
 This is the main method.
 @return the program exit code.
 */
int main() {
    
    // Select reference file names based on set word length
    string commonWordFileName;
    string allWordFileName;
    switch(wordLength) {
        case 5:
            allWordFileName = "FiveLetterWords.txt";
        default:
            allWordFileName = "FiveLetterWords.txt";
            
    }
    
    // Import all words of length wordLength in csv format with relative frequencies
    vector<string> wordFrequencies = importUnigramWords("unigram_freq.csv", wordLength);
    // Import all words of length wordLength which are not proper nouns
    vector<string> wordReference = importWords(allWordFileName, true);
    
        
    //
    char knownLetters[wordLength];
    char knownPositions[wordLength];
    char knownWrong[26];
    
    
    cout << "Ethan's Wordle Solver!" << endl << endl;
    
    cout << "Importing and sorting all words of length " << wordLength << " by relative frequency..." << endl << endl;
    wordReference = sortByFrequency(wordReference, wordFrequencies, wordLength);
    
    vector<string> possibleWords;
    
    while(true) {
         
          possibleWords = wordReference;

          string userInput;
         
          userInput = getKnownLetters(false, wordLength);
          for(int i = 0; i < wordLength; i++) {
               knownLetters[i] = userInput.at(i);
          }
         
          cout << endl << "Yellow letters: '";
          for(int i = 0; i < wordLength; i++) {
               cout << knownLetters[i] << "'";
          }
         
         // REMOVE WORDS WITHOUT KNOWN LETTERS
         
         for(int i = 0; i < possibleWords.size(); i++) {
             // for each possible word
             
             bool individualLetterMatch = false;
             bool allLetterMatch = true;
             
             for(int k = 0; k < wordLength; k++) {
                 // for each known letter
                 
                 if(knownLetters[k] != ' ') {
                     for(int z = 0; z < wordLength; z++) {
                         // for each letter in a word
                         if(possibleWords[i].at(z) == knownLetters[k]) {
                             individualLetterMatch = true;
                         }
                     }
                 } else {
                     individualLetterMatch = true;
                 }
                 
                 if(individualLetterMatch == false) {
                     allLetterMatch = false;
                     // break, one letter doesnt match
                 } else {
                     individualLetterMatch = false;
                 }

             }
         
             if(!allLetterMatch) {
                 possibleWords.erase(possibleWords.begin() + i);
                 i--;
             }
             
         }
          
          
          // REMVOE WORDS WITH YELLOW LETTERS IN THE YELLOW POSITIONS
          
          for(int i = 0; i < possibleWords.size(); i++) {
              // for each possible word
              
              bool individualPositionMatch = false;
              bool anyPositionMatch = false;
              
              for(int k = 0; k < wordLength; k++) {
                  // for each yellow letter
                  
                  if(knownLetters[k] != ' ') {
                      
                      if(possibleWords[i].at(k) == knownLetters[k]) {
                          individualPositionMatch = true;
                      }
                      
                  } else {
                      individualPositionMatch = false;
                  }
                  
                  if(individualPositionMatch == true) {
                       anyPositionMatch = true;
                       individualPositionMatch = false;
                      // break, one letter doesnt match
                  } else {
                      individualPositionMatch = false;
                  }

              }
          
              if(anyPositionMatch) {
                  possibleWords.erase(possibleWords.begin() + i);
                  i--;
              }
              
          }

         
         cout << endl;
          userInput = getKnownLetters(true, wordLength);
          for(int i = 0; i < wordLength; i++) {
               knownPositions[i] = userInput.at(i);
          }
         
          cout << endl << "Green letters: '";
          for(int i = 0; i < wordLength; i++) {
               cout << knownPositions[i] << "'";
          }
         
         // REMVOE WORDS WITH LETTERS IN THE WRONG POSITIONS
         
         for(int i = 0; i < possibleWords.size(); i++) {
             // for each possible word
             
             bool individualPositionMatch = false;
             bool allPositionMatch = true;
             
             for(int k = 0; k < wordLength; k++) {
                 // for each known position
                 
                 if(knownPositions[k] != ' ') {
                     
                     if(possibleWords[i].at(k) == knownPositions[k]) {
                         individualPositionMatch = true;
                     }
                     
                 } else {
                     individualPositionMatch = true;
                 }
                 
                 if(individualPositionMatch == false) {
                     allPositionMatch = false;
                     // break, one letter doesnt match
                 } else {
                     individualPositionMatch = false;
                 }

             }
         
             if(!allPositionMatch) {
                 possibleWords.erase(possibleWords.begin() + i);
                 i--;
             }
             
         }
         

         cout << endl;
          userInput = getWrongLetters();
          for(int i = 0; i < 26; i++) {
               knownWrong[i] = userInput.at(i);
          }

          cout << endl << "Grey letters: '";
          for(int i = 0; i < 26; i++) {
            if(knownWrong[i] == ' ')
                continue;
            cout << knownWrong[i] << "'";
          }
        
         // REMOVE WORDS WITH KNOWN WRONG LETTERS
         
         for(int i = 0; i < possibleWords.size(); i++) {
             // for each possible word
             
             bool anyLetterMatch = false;
             
             for(int k = 0; k < 26; k++) {
                 // for each known letter
                 
                 if(knownWrong[k] != ' ') {
                     for(int z = 0; z < wordLength; z++) {
                         // for each letter in a word
                         if(possibleWords[i].at(z) == knownWrong[k]) {
                             anyLetterMatch = true;
                         }
                     }
                 }

             }
         
             if(anyLetterMatch) {
                 possibleWords.erase(possibleWords.begin() + i);
                 i--;
                 anyLetterMatch = false;
             }
             
         }

         
        string continueProgram;
        getline(cin, continueProgram);
        
        
        // SORT VECTOR BY FREQUENCY
        vector<string> sortByFrequency(vector<string>, vector<string>, int);
        
        
        cout << endl << "Possible solutions (sorted by relative frequency low to high): " << endl;
        printVector(possibleWords);
        
        
        string endProgram;
        cout << endl << "Press enter to run again, or type stop to end the program.   ";
        getline(cin, endProgram);
                
        if(endProgram == "stop")
            break;
        
        
        cout << endl;
        
    }
    
    
    cout << endl << endl;
    return 0;
    
}



/**
 Get user input for a string of known characters, ensuring it isn't greater than length wordLength.
 If greater than length wordLength, inform user and ask again.
 If less than length wordLength, append string with ' 's until the return string is of length wordLength.
 @param positionKnown will determine if the function asks for letters with or without a known position.
 @return a string of known characters of length wordLength.
 */
string getKnownLetters(bool positionKnown, int length) {
    
    string userInput;
    bool validInput = false;
    
    while(!validInput) {
        
        if(positionKnown) {
            cout << "Input green letters (in known positions): ";
        } else {
            cout << "Input yellow letters (in known positions): ";
        }
        
        getline(cin, userInput);
        
        if(userInput.length() > length) {
            cerr << "ERROR: User input contains more characters than the puzzle solution." << endl;
        } else if(userInput.length() < length) {
            int numSpaces = length - (int)userInput.length();
            for(int i = 0; i < numSpaces; i++) {
                userInput.push_back(' ');
            }
            validInput = true;
        } else {
            validInput = true;
        }
        
    }
    
    for(int i = 0; i < userInput.length(); i++) {
        userInput[i] = toupper(userInput[i]);
    }
        
    return userInput;
    
}


/**
 Get user input for a string of characters which are known to not be in the solution word.
 If greater than length of the alphabet, inform user and ask again.
 If less than length of the alphabet, append string with ' 's until the return string is of length of the alphabet.
 @return a string of known characters of length 26.
 */
string getWrongLetters() {
    
    string userInput;
    bool validInput = false;
    
    while(!validInput) {
        
        cout << "Input grey letters: ";
        
        getline(cin, userInput);
        
        if(userInput.length() > 26) {
            cerr << "ERROR: User input contains more characters than are in the alphabet." << endl;
        } else if(userInput.length() < 26) {
            int numSpaces = 26 - (int)userInput.length();
            for(int i = 0; i < numSpaces; i++) {
                userInput.push_back(' ');
            }
            validInput = true;
        } else {
            validInput = true;
        }
        
    }
    
    for(int i = 0; i < userInput.length(); i++) {
        userInput[i] = toupper(userInput[i]);
    }
        
    return userInput;
    
}


/**
 
 */
bool compareFrequency(string s1, string s2) {
    
    if(s1.find(',') == string::npos)
        return true;
    if(s2.find(',') == string::npos)
        return false;
    
    return stol(s1.substr(wordLength + 1, s1.length() - wordLength - 1)) < stol(s2.substr(wordLength + 1, s2.length() - wordLength - 1));
    
}

/**
 Sorts...........
 */
vector<string> sortByFrequency(vector<string> possibleWords, vector<string> unigramWords, int length) {
    
    string unigramWord;
    
    for(int i = 0; i < possibleWords.size(); i++) {
        
        for(int k = 0; k < unigramWords.size(); k++) {
                        
            if(unigramWords[k].substr(0, length) == possibleWords[i]) {
                possibleWords[i] = unigramWords[k];
                break;
            }
            
        }
        
    }

    sort(possibleWords.begin(), possibleWords.end(), compareFrequency);
    
    for(int i = 0; i < possibleWords.size(); i++) {
        if(possibleWords[i].find(',') != string::npos) {
            
            possibleWords[i] = possibleWords[i].erase(possibleWords[i].find(','), possibleWords[i].length() - wordLength);
            
        }
    }
    
    return possibleWords;
    
}


/**
 Takes in a filename and puts each line of this file into a vector element.
 @param fileName is the name of the file to be vectorized.
 @return a vector with each line of the file as an element.
 */
vector<string> importWords(string fileName, bool header) {
    
    ifstream possibileWords;
    possibileWords.open(fileName);
    
    if (!possibileWords) {
        cerr << "Unable to open word database";
        exit(1);   // call system to stop
    }
    
    bool onHeader = true;
    string readFile;
    vector<string> wordVector;
    
    while(getline(possibileWords, readFile)) {
        for(int i = 0; i < readFile.length(); i++) {
            readFile[i] = toupper(readFile[i]);
        }
        if(!onHeader || !header) {
            wordVector.push_back(readFile);
        } else {
            onHeader = false;
        }
    }

    possibileWords.close();
    
    return wordVector;
    
}


/**
 Takes in a filename and word length puts each line of this file which contains an appropriately long word into a vector element along with word frequency.
 @param fileName is the name of the file to be vectorized.
 @param length is the length of words to import
 @return a vector with each line of the file containing the correct length word as an element, then a comma and word frequency.
 */
vector<string> importUnigramWords(string fileName, int length) {
    
    ifstream possibileWords;
    possibileWords.open(fileName);
    
    if (!possibileWords) {
        cerr << "Unable to open word database";
        exit(1);   // call system to stop
    }
    
    bool desiredLength = false;
    string readFile;
    vector<string> wordVector;
    
    while(getline(possibileWords, readFile)) {
        
        
        for(int i = 0; i < readFile.length(); i++) {
            readFile[i] = toupper(readFile[i]);
            if(readFile.at(i) == ',' && i == length) {
                desiredLength = true;
            }
        }
        
        if(desiredLength) {
            wordVector.push_back(readFile);
            desiredLength = false;
        }
        
    }

    possibileWords.close();
    
    return wordVector;
    
}


/**
 Prints the contents of a string vector with each element on a new line.
 @param vec is the string vector to be printed.
 */
void printVector(vector<string> vec) {
    
    for(int i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << endl;
    }
    
}
