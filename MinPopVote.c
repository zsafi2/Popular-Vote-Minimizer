/*-------------------------------------------
Program 1: Vote Minimizer Application
Course: CS 211, Fall 2023, UIC
System: Visual Studio Code
Author: Zaheer Safi
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

// this function take the command line arguments and sets settings according to them and 
// and returns true/false according to the valid and invlaid entry of command line
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    
    // default setting values
    *fastMode = false;
    *quietMode = false;
    *year = 0;
    
    int tempYear = 0; // to hold the value fo year
    bool check_commandline = true; // check if the command line entry is correct
    
    // go through each command line argument
    for (int i = 1; i < argc; i++)
    {
        tempYear = atoi(argv[i]); // store the argument of year in temp year
        
        // if you see a -y flag
        if (strcmp(argv[i], "-y") == 0)
        {
            tempYear = atoi(argv[i+1]); // go to the next argumetn
            
            // if the year is according to statment update the year 
            if (tempYear >= 1828 && tempYear <= 2020 && tempYear % 4 == 0)
            {
                *year = tempYear;
                
            }
            i++; // pass through the next command becuase it is the year
        }
        
        // update the remainging commands according to the flags
        else if (strcmp(argv[i], "-q") == 0)
        {
            *quietMode = true;
        }
        
        else if (strcmp(argv[i], "-f") == 0)
        {
            *fastMode = true;
        }

        // if a command is none of the above make commandLIne equal to fasle
        else
        {
            check_commandline = false;
        }
    }
   
    return check_commandline; // return the command line
}

// this function takes the filename and year as an argument and update the file name according to the file of input
void inFilename(char* filename, int year) 
{
    
    char str_year[10]; // temp veriable to store the year as a string
    sprintf(str_year, "%d", year); // change the integer year to string
    strcpy(filename,"data/"); // copy the given string
    strcat(filename, str_year); // now copy the string year
    strcat(filename, ".csv"); // and then copy the .csv to filename
    return;
}

// it is a similar function as above it updates the filename for the output file
void outFilename(char* filename, int year) 
{
    // do similar things as the inFilename funciton
    char str_year[10];
    sprintf(str_year, "%d", year);
    strcpy(filename,"toWin/");
    strcat(filename, str_year);
    strcat(filename, "_win.csv");
    return;
}

// this function takes a string line and the takes out the words seprated by comma and updates the myState struct with the data accordingly
// return true if the given line has the correct format or fasle if the format is incorrect
bool parseLine(char* line, State* myState) 
{
    char *token; // define a token counter
    int count = 0;

    // Use strtok to split the string by commas and store the words in variables.
    token = strtok(line, ",");

    // go through each word 
    while (token != NULL && count < 4) 
    {
        // store each word in the apporpiate veriable in the myState struct
        if (count == 0) 
        {
            strcpy(myState->name, token); // store the name
        } 
        
        else if (count == 1) 
        {
            if (strlen(token) == 2) 
            {
                strcpy(myState->postalCode, token); // store the postal ID
            } 
            // if the postal ID has letters more then 2 return false
            else 
            {
                return false;
            }
        } 
        
        else if (count == 2) 
        {
            myState->electoralVotes = atoi(token); // store the electoral votes
        } 
        
        else if (count == 3) 
        {
            myState->popularVotes = atoi(token); // store the popular votes
        }

        token = strtok(NULL, ",");
        count++;
    }

    // check if there are only 4 words
    if (count != 4) 
    {
        return false;
    }

    return true;
}

// this function reads the data from the given file name and stores it the allState struct array
// return true/false according if the file has been opened or fialed to open
bool readElectionData(char* filename, State* allStates, int* nStates) 
{
    // open the file
    FILE *input;
    input = fopen(filename, "r");
    
    // if the file was not opened return false
    if (input == NULL)
    {
        return false;
    }

    char line[200]; // veriable to store each line
    *nStates = 0; // number of states

    while(fgets(line, 200, input))
    {
        parseLine(line, &allStates[*nStates]); // call the parselline to seprate each word and store it accordingly 
        (*nStates)++;
    }
    fclose(input);

    return true; 
}

// this function calculates the toal number of EVs in the states array and returns the sum
int totalEVs(State* states, int szStates) 
{
    int sum = 0;
    // go through each sturct and update the sum of electoral votes
    for (int i = 0; i < szStates; i++)
    {
        sum += states[i].electoralVotes;
    }
    return sum;
}

// this function does similar thing by counting the total PVs and returning the sum
int totalPVs(State* states, int szStates) 
{
    int sum = 0;
    // go through each sturct and update the sum of popular votes
    for (int i = 0; i < szStates; i++)
    {
        sum += states[i].popularVotes;
    }
    return sum; 
}

// this fuction creates a power set of the states array of structs and checks the sets which fulfills the requirement of required EVs 
// and the find the minimum popular votes from those sturcts and updates th MinInfo struct and return it
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) 
{
    // base case if start reached the end of states return an empty sturct MinInfo
    if (start == szStates) 
    {
        MinInfo result;
        result.sufficientEVs = (EVs <= 0);
        result.subsetPVs = 0;
        result.szSomeStates = 0;
        return result;
    }

    // Exclude the current state
    MinInfo excluded = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    // Include the current state
    MinInfo included = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    
    // update the someStates arry of state structs and the size of the array veriable
    included.subsetPVs += states[start].popularVotes/2 + 1;
    included.someStates[included.szSomeStates] = states[start];
    included.szSomeStates++;

    // Determine which subset has the minimum popular votes
    if (excluded.sufficientEVs && included.sufficientEVs) 
    {
        // If both subsets are sufficient, choose the one with the fewer popular votes
        if (excluded.subsetPVs < included.subsetPVs) 
        {
            return excluded;
        } 
        else 
        {
            return included;
        }
    } 
    
    else if (excluded.sufficientEVs) 
    {
        // If only the excluded subset is sufficient, return it
        return excluded;
    } 
    
    else if (included.sufficientEVs) 
    {
        // If only the included subset is sufficient, return it
        return included;
    }
    
    else 
    {
        // If neither subset is sufficient, return the one with fewer popular votes
        return (excluded.subsetPVs < included.subsetPVs) ? excluded : included;
    }
}

// function to call the minPopVotesAtLeast
MinInfo minPopVoteToWin(State* states, int szStates) 
{
    int totEVs = totalEVs(states, szStates); // find the total EVs
    int reqEVs = totEVs / 2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}  

// this function is the same as the minPopVoteAtLeast the only thign differnt is it uses memeoization to make the process faster
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) 
{
    // base case
    if (start == szStates) 
    {
        MinInfo result;
        result.sufficientEVs = (EVs <= 0);
        result.subsetPVs = 0;
        result.szSomeStates = 0;
        return result;
    }

    // Check if the result for this parameter pair is already in memo
    if (memo[start][EVs].subsetPVs != -1) 
    {
        return memo[start][EVs];
    }

    // Exclude the current state
    MinInfo excluded = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);

    // Include the current state
    MinInfo included = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);
    included.subsetPVs += states[start].popularVotes/2 + 1;
    included.someStates[included.szSomeStates] = states[start];
    included.szSomeStates++;

    // Determine which subset has the minimum popular votes
    if (excluded.sufficientEVs && included.sufficientEVs) 
    {
        // If both subsets are sufficient, choose the one with the fewer popular votes
        if (excluded.subsetPVs < included.subsetPVs) 
        {
            memo[start][EVs] = excluded;
            return excluded;
        } 
        else 
        {
            memo[start][EVs] = included;
            return included;
        }
    } 
    
    // update the memo array to reduce repetation
    else if (excluded.sufficientEVs) 
    {
        memo[start][EVs] = excluded;
        return excluded;
    } 
    
    else if (included.sufficientEVs) 
    {
        memo[start][EVs] = included;
        return included;
    } 
    
    else 
    {
        memo[start][EVs] = (excluded.subsetPVs < included.subsetPVs) ? excluded : included;
        return (excluded.subsetPVs < included.subsetPVs) ? excluded : included;
    }
}

// similar to minPopVoteToWin but calls the faster version
MinInfo minPopVoteToWinFast(State* states, int szStates) 
{
    int totEVs = totalEVs(states, szStates);
    int reqEVs = totEVs / 2 + 1; 

    // Create and initialize the memoization table
    MinInfo** memo = (MinInfo**)malloc((szStates + 1) * sizeof(MinInfo*));
    for (int i = 0; i < szStates + 1; ++i) 
    {
        memo[i] = (MinInfo*)malloc((reqEVs + 1) * sizeof(MinInfo));
        for (int j = 0; j < reqEVs + 1; ++j) 
        {
            memo[i][j].subsetPVs = -1;
        }
    }

    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo); // call the funciton

    // Free up the heap-allocated memory for the memoization table
    for (int i = 0; i < szStates + 1; ++i) 
    {
        free(memo[i]);
    }
    free(memo);

    return res;
}

// function to write the data to a file and return true and false if the file opend or not
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) 
{
    FILE* file = fopen(filenameW, "w");
    
    if (file == NULL) 
    {
        return false; // Failed to open the file
    }

    // Write the statistical summary
    fprintf(file, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);

    // Write the individual State details for the subset in reverse order
    for (int i = toWin.szSomeStates - 1; i >= 0; i--) 
    {
        // Calculate the minimum popular votes to win the state's electoral votes
        fprintf(file, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, 
                toWin.someStates[i].electoralVotes, toWin.someStates[i].popularVotes/2 + 1);
    }

    fclose(file);
    return true;
}