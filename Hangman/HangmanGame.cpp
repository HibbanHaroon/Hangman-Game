#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
void playerMode();					// Asks for number of players. 
void difficultyLevel(int&, int&, int&, int&); // Sets difficulty level for the game.
void gameMode();					// Sets mode for the game.
string getWord(int, int, int, int);	// Gets a word from the file according to the set difficulty level.
void printDashes(int);	            // Print blank dashes infront of unexposed letters.
void getGuess(int);		            // Takes guess letters as input.
bool checkGuess(int, bool);	// Checks if the entered guess is correct or not.
void correctGuess(int);        // what to do in case guess is correct.
void wrongGuess(int);		        // what to do in case guess is incorrect.
void hangman(int);					// Draws Hangman when a user guesses incorrectly.
void result(int);					// Displays result and asks if the user wants to play again. 
int validationForInteger();			// Input Validation for Integers. 
string hidden, word, totalGuesses;				// Global Variables
char guessLetter, check;      
int position[12], guessPosition, guess, expose, level, mode, player;
int main()
{
	guess = 8, expose = 0;
	int l1 = 0, l2 = 0, l3 = 0, l4 = 0;
	cout << "*********************************************";
	cout << endl << "\t THE \t HANGMAN\t GAME" << endl;
	cout << "*********************************************";
	playerMode();
	gameMode();
	if (player == 1)		// If user chooses single player then get word from the file.
	{
		difficultyLevel(l1, l2, l3, l4);
		word = getWord(l1, l2, l3, l4);
	}
	int size = word.length();
	if (mode == 3)			// If user chooses Shuffle Mode then scramble the word.
	{
		for (int i = 0; i < size; i++)
		{
			int index1 = rand() % size;
			int index2 = rand() % size;
			swap(word[index1], word[index2]);
		}
	}
	hidden = word;		
	for (int i = 0; i < size; i++)		
	{
		hidden[i] = '_';			// Hide the word with dashes.
		position[i] = i + 1;		// Store indices in an array. like 1 2 3 4 etc.
	}
	cout << endl << "Your word is: " << endl;
	while ((guess != 0) && (expose != size))		// If guesses equals 0 or expose equals the size of the word,
	{												// Exit the loop.
		printDashes(size);
		getGuess(size);
		bool correct = false;
		correct = checkGuess(size, correct);
		if (correct == true)                        // If correct equals true then correct guess entered. 
		{
			correctGuess(size);
		}
		else if (correct == false)        			// If correct false then wrong guess entered. 
		{
			wrongGuess(size);
			hangman(guess);
		}
	}
	result(size);
	system("pause");
	return 0;
}
void playerMode()
{
	cout << "\nHow would you like to play the game: \n1. Single Player \n2. Two Player";
	do
	{
		cout << "\nEnter Player Mode (1 or 2): ";
		player = validationForInteger();
	} while ((player != 1) && (player != 2));
	if (player == 2)			//If user chooses Two player then ask for the word.
	{
		cout << "Enter the word: ";
		cin >> word;
		for (int i = 0; i < word.length(); i++)
		{														//If the word has a character other than alphabets. 
			if (!((int(word[i]) >= 97) && (int(word[i]) <= 122)) || ((int(word[i]) >= 65) && (int(word[i]) <= 90)))
			{
				cout << "Invalid Word Entered. \nEnter word again: ";
				cin >> word;
				i = 0;
				continue;
			}
			if ((int(word[i]) >= 65) && (int(word[i]) <= 90)) //Making the word case-insensitive. 
			{										// If Uppercase are entered, they will be converted into lowercase.
				int j = int(word[i]) + 32;
				word[i] = char(j);
			}
		}
	}
}
void gameMode()
{
	cout << "\nMode: " << endl;
	cout << "1. Normal Mode: \n";
	cout << "The word is \"DOG\". \n";				// \" represents double quotation. 
	cout << "_ \t_ \t_ \n";
	cout << "\n2. Fixed Mode: \n";
	cout << "The word is \"DOG\". \n";
	cout << "_ \t_ \t_ \n";
	cout << "1. \t2. \t3. \n";
	cout << "\n3. Shuffled Mode: \n";
	cout << "The word is \"GDO\". \n";
	cout << "_ \t_ \t_ \n";
	cout << "1. \t2. \t3. \n";
	do
	{
		cout << "\nEnter Mode (1, 2, 3) : ";
		mode = validationForInteger();
	} while ((mode != 1) && (mode != 2) && (mode != 3));
}
void difficultyLevel(int& a, int& b, int& c, int& d)
{
	cout << "\nDifficulty Level: " << endl;
	cout << "1. Easy (3 to 5 letters) \t";
	cout << "2. Medium (6 to 8 letters) \t";
	cout << "3. Difficult (9 to 12 letters) \t";
	do
	{
		cout << "\nEnter Dificulty Level (1, 2, 3) : ";
		level = validationForInteger();
	} while ((level != 1) && (level != 2) && (level != 3));
	switch (level)
	{
	case 1:			//If difficulty level 1 is chosen
	{
		a = 3, b = 4, c = 5;
		break;
	}
	case 2:			//If difficulty level 2 is chosen
	{
		a = 6, b = 7, c = 8;
		break;
	}
	case 3:			//If difficulty level 3 is chosen
	{
		a = 9, b = 10, c = 11, d = 12;
		break;
	}
	default:
		break;
	}
}
string getWord(int a, int b, int c, int d)
{
	if (d == 0)			// If difficulty level is other than 3, then d will be 0.
	{
		d = a;			// Value of a is stored in d, so that it doesn't allow any blank space as a word.  
	}
	// Opening the File to store words according to the set diffuclty level in the sorted file.
	fstream wordFile;
	ofstream sortedFile;
	wordFile.open("words.txt");
	sortedFile.open("sorted.txt");
	for (int n = 0; getline(wordFile, word); n++)
	{
		int length = word.length();
		if ((length == a) || (length == b) || (length == c) || (length == d))
		{
			for (int i = 0; i < length; i++)
			{													   //If the word has a character other than alphabets.
				if (!((int(word[i]) >= 97) && (int(word[i]) <= 122)) || ((int(word[i]) >= 65) && (int(word[i]) <= 90)))
				{
					word = "";
					wordFile << word;				// Store a blank space in the place of that faulty word.
					break;
				}
				if ((int(word[i]) >= 65) && (int(word[i]) <= 90)) //Making the word case-insensitive. 
				{										
					int j = int(word[i]) + 32;
					word[i] = char(j);
				}
			}
			if (word == "")							// If there is a faulty word, look for another word.
			{
				continue;
			}
			sortedFile << word << "\n";				// Finally store the word in the sorted file.
		}
	}
	wordFile.close();
	sortedFile.close();
	// Opening the sorted file again to find the total number of words(size) in the File. 
	ifstream file;
	file.open("sorted.txt");
	int size = 0;
	while (getline(file, word))
	{
		size++;
	}
	file.close();
	// Opening the sorted file again to find a random word from the file.
	ifstream myFile;
	myFile.open("sorted.txt");
	srand((unsigned)time(0));
	int randomNum = rand() % size + 0; //"size" is no. of words in the file
	int i = 0;
	while ((i != randomNum) && (getline(myFile, word)))
	{
		i++;
	}
	myFile.close();
	return word;
}
void printDashes(int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << hidden[i] << "\t";		// Output the hidden word 
	}
	cout << endl;
	if ((mode == 2) || (mode == 3))
	{	
		for (int i = 0; i < size; i++)
		{
			cout << position[i] << ".\t";
		}
	}
	cout << "\n\nLetters Guessed : " << totalGuesses;
	cout << endl << endl << "Guesses Remaining: " << guess << endl;
	return;
}
void getGuess(int size)
{
	cout << "\nEnter a letter: ";
	cin >> guessLetter;
	if ((int(guessLetter) >= 65) && (int(guessLetter) <= 90)) //Making the letter case-insensitive. 
	{										
		int i = int(guessLetter) + 32;
		guessLetter = char(i);
	}
	if (!((int(guessLetter) >= 97) && (int(guessLetter) <= 122))) // Character Validation. 
	{															  // It checks if only letters are entered. 
		cout << "The letter you entered is invalid. \n";
		getGuess(size);
	}
	totalGuesses = totalGuesses + guessLetter + "-";
	if ((mode == 2) || (mode == 3))
	{
		do
		{
			cout << "Enter Position (1, 2, ...) : ";
			guessPosition = validationForInteger();
		} while (!(guessPosition > 0 && guessPosition <= size));
	}
}
bool checkGuess(int size, bool correct)
{
	for (int i = 0; i < size; i++)
	{
		if (guessLetter == hidden[i]) // Check If the guessLetter has already been entered before or not.
		{
			cout << "The letter has already been entered. \n";
			getGuess(size);			  // If yes ask for guess again.
		}
		else if (guessLetter == word[i]) // If guessLetter is in the word then correct guess entered. 
		{
			if ((mode == 2) || (mode == 3))
			{
				if (!(guessPosition == i + 1))		// Check if the position of the guess is accurate too.
				{
					break;			  // Break and return false if position is not same. 
				}
			}
			correct = true;
		}
	}
	return correct;
}
void correctGuess(int size)
{
	cout << endl << "The letter you entered is correct." << endl;
	for (int i = 0; i < size; i++)
	{
		if (guessLetter == word[i])
		{
			hidden[i] = word[i];			// Saving the guess on the correct index of the hidden word.
		}
	}
	++expose;
	return;
}
void wrongGuess(int size)
{
	cout << endl << "Wrong Letter Entered." << endl;
	--guess;
	return;
}
void result(int size)
{
	if (guess == 0)					//If no. of guesses remaining equals 0. 
	{
		cout << endl;
		cout << "\n\t\a   HANGED MAN \n";
		cout << "Guesses Remaining: 0 \n";
		cout << "\nYou've Lost The Game.  \n";				//Game Lost.
		cout << "\nThe word was " << word << endl;
		cout << "\nBetter Luck Next Time. \n \n";
	}
	else if (expose == size)		// If all letters are guessed.
	{
		cout << endl;
		cout << "You've Won The Game. \n";					//Game Won.
		cout << "\nThe word was " << word << endl;
		cout << "\nBravo. \n \n";
	}
	
	//Asking if the user wants to play again. 
	cout << "Do you want to play the Game again? (Y or N): ";
	cin >> check;
	if (check == 'Y' || check == 'y')
	{
		system("CLS");
		main();
	}
	else if (check == 'N' || check == 'n')
	{
		cout << endl << "\nBye come back again. \n \n";
		return;
	}
}
void hangman(int guess)
{
	if (guess < 8) // Nested if is used to stop the redundancy of lines of code. 
	{
		cout << "\t ---------------" << endl;
		cout << "\t|               |" << endl;
		cout << "\t ---------------" << endl;
		if (guess < 7)
		{
			cout << "\t        |" << endl;
			cout << "\t        |" << endl;
			if (guess < 6)
			{						
				cout << "\t       ( )" << endl;
				if (guess < 5)
				{
					switch (guess)
					{
						case 4:
						{
							cout << "\t        |" << endl;
							cout << "\t        |" << endl;
							cout << "\t        |" << endl;
							break;
						}
						case 3:
						{
							cout << "\t       /|" << endl;
							cout << "\t      / |" << endl;
							cout << "\t        |" << endl;
							break;
						}
					}
					if (guess < 3)
					{
						cout << "\t       /|\\" << endl; // "\\" this represents a single backslash.
						cout << "\t      / | \\" << endl;
						cout << "\t        |" << endl;
						switch (guess)
						{
							case 1:
							{					
								cout << "\t       /" << endl;
								break;
							}
							case 0:
							{                   
								cout << "\t       / \\" << endl;
								break;
							}
						}
					}
				}
			}
		}
	}
}
int validationForInteger()
{
	int validate;
	while (!(cin >> validate))			// Input validation of Integers. 
	{
		cin.clear();					// If a character is entered clear the stream and the buffer. 
		cin.ignore(100, '\n');
		cout << "Invalid Number Entered. \nEnter again: ";
	}
	return validate;
}