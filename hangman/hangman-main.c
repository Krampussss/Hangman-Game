#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#define TRIES 6

int tries = 0;
char word[20];  
char dispWord[20];  
char guessedLetters[26] = {' '};    

void startGame();
void displayHangman();
void displayGameStatus();
int makeGuess();
int main()
{
    printf("\n\nWELCOME TO HANGMAN\n\nPLEASE AVOID GUESSING 'WHOLE WORDS'\n\n");
    sleep(1);
    printf("GAME IS NOW STARTING....\n\n");
    sleep(3);

    srand(time(NULL));
    
    startGame();
    while(tries < TRIES)
    {   

        system("clear");

        displayGameStatus();
        displayHangman();

        if(strcmp(word,dispWord) == 0)
        {
            printf("You have guessed the word!!!\nThe word was: %s\n",word);
            return 0;
        }

        printf("\nMake your Guess: ");
        int guess = makeGuess();

        if(guess == -1)
        {
            printf("You have already guessed that letter! Try again\n");
            sleep(1);
        }

        else if(guess == 0)
        {
            printf("Incorrect Guess!\n");
            tries++;
            sleep(1);
        }

        else
        {
            printf("Correct Guess!\n");
            sleep(1);
        }
    }

    if(tries == TRIES)
    {
        printf("The man has been hung. The correct word was: %s\n",word);
    }
}

void startGame()
{
    int i;
    char wordList[][20] = {"hangman","college","computer","programming","examination"};
    strcpy(word,wordList[rand() % sizeof(wordList) / sizeof(wordList[0])]);
    
    int wordLength = strlen(word);

    for(i = 0;i < wordLength;i++)
    {
        dispWord[i] = '_';
    }
}

void displayGameStatus()
{
    int i;
    printf("Word: %s\n",dispWord);
    printf("Tries Left: %d\n",TRIES - tries);
    printf("Guessed Letters: ");

    for (i = 0;i < 26;i++)
    {
        if(isalpha(guessedLetters[i]))
        {
            printf("%c ",guessedLetters[i]);
        }
    }
    printf("\n");
}


void displayHangman()
{
    const char hangmanParts[][40] = 
    {
        "  -----\n  |   |\n      |\n      |",
        "  -----\n  |   |\n  O   |\n      |",
        "  -----\n  |   |\n  O   |\n  |   |",
        "  -----\n  |   |\n  O   |\n /|   |",
        "  -----\n  |   |\n  O   |\n /|\\  |",
        "  -----\n  |   |\n  O   |\n /|\\  |\n /    |",
        "  -----\n  |   |\n  O   |\n /|\\  |\n / \\  |"
    };

    printf("\n%s\n", hangmanParts[tries]);
}

int makeGuess()
{
    int i;
    char guess;
    scanf(" %c",&guess);
    guess = tolower(guess);

    if ( strchr(guessedLetters , guess) != 0 )
    {
        return -1;
    }

    guessedLetters[strlen(guessedLetters)] = guess;
    int flag = 0;

    for(i = 0;i < strlen(word);i++)
    {
        if(word[i] == guess)
        {
            dispWord[i] = guess;
            flag = 1;
        }
    }
    return flag;
}
