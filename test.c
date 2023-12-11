#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return 0;
    }

    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 15;
    aStates[6].electoralVotes = 12;
    aStates[7].electoralVotes = 8;
    aStates[8].electoralVotes = 14;
    aStates[9].electoralVotes = 13;
    
    printf(" Checking totalEVs() for 10 States:\n");
    res = totalEVs(aStates,10);
    if (res != 100) {
        printf("  expected total EVs = 100, actual total EVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_totalPVs() 
{
    
    State aStates[10];
    int res;
    
    aStates[0].popularVotes = 5000;
    aStates[1].popularVotes = 8540;
    aStates[2].popularVotes = 1201;
    aStates[3].popularVotes = 600;
    aStates[4].popularVotes = 7235;
    aStates[5].popularVotes = 0;

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    
    if (res != 22576) 
    {
        printf("  expected total PVs = 22576, actual total PVs = %d\n",res);
        return false;
    }

    aStates[0].popularVotes = 10000;
    aStates[1].popularVotes = 555000;
    aStates[2].popularVotes = 126700;
    aStates[3].popularVotes = 69000;
    aStates[4].popularVotes = 75688;
    aStates[5].popularVotes = 15000;
    aStates[6].popularVotes = 125000;
    aStates[7].popularVotes = 83000;
    aStates[8].popularVotes = 1421;
    aStates[9].popularVotes = 139899;
    
    printf(" Checking totalPVs() for 10 States:\n");
    res = totalPVs(aStates,10);
    
    if (res != 1200708) 
    {
        printf("  expected total PVs = 1191708, actual total PVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_setSettings() 
{
    int year;
    bool fastMode;
    bool quietMode;
    bool result;

    char* argv[6] = {"./app.exe", "-y", "2020", "-f", "-q"};
    int argc = 5;
    result = setSettings(argc, argv, &year, &fastMode, &quietMode);
    
    if (result != true || year != 2020 || fastMode != true || quietMode != true)
    {
        printf("failed the command line argument ./app.exe -y 2020 -f -q\n");
        return false;
    }
    
    char* argv1[6] = {"./app.exe", "-y", "1923"};
    int argc1 = 3;
    result = setSettings(argc1, argv1, &year, &fastMode, &quietMode);
    
    if (result != true || year != 0 || fastMode != false || quietMode != false)
    {
        printf("failed the command line argument ./app.exe -y 1923\n");
        return false;
    }

    char* argv2[6] = {"./app.exe", "-y", "100"};
    int argc2 = 2;
    result = setSettings(argc2, argv2, &year, &fastMode, &quietMode);
    
    if (result != true || year != 0 || fastMode != false || quietMode != false)
    {
        printf("failed the command line argument ./app.exe -y 100\n");
        return false;
    }

    char* argv3[6] = {"./app.exe", "-s", "-y", "1980"};
    int argc3 = 4;
    result = setSettings(argc3, argv3, &year, &fastMode, &quietMode);
    
    if (result == true)
    {
        printf("failed the command line argument ./app.exe -s -y 1980\n");
        return false;
    }

    char* argv4[6] = {"./app.exe", "-q"};
    int argc4 = 2;
    result = setSettings(argc4, argv4, &year, &fastMode, &quietMode);
    
    if (result != true || year != 0 || fastMode != false || quietMode != true)
    {
        printf("failed the command line argument ./app.exe -q\n");
        return false;
    }

    return true; 
}

bool test_inFilename() 
{
    char filename[20];
    int year = 2000;
    inFilename(filename, year);

    if (strcmp(filename, "data/2000.csv") != 0)
    {
        printf("test case failed when year = 2000 expected result = data/2000.csv and your result = %s\n", filename);
        return false;
    }

    char filename1[20];
    int year1 = 1980;
    inFilename(filename1, year1);
    
    if (strcmp(filename1, "data/1980.csv") != 0)
    {
        printf("test case failed when year = 1980 expected result = data/1980.csv and your result = %s\n", filename1);
        return false;
    }

    char filename2[20];
    int year2 = 1828;
    inFilename(filename2, year2);
    
    if (strcmp(filename2, "data/1828.csv") != 0)
    {
        printf("test case failed when year = 1828 expected result = data/1828.csv and your result = %s\n", filename2);
        return false;
    }

    char filename3[20];
    int year3 = -100;
    inFilename(filename3, year3);
    
    if (strcmp(filename3, "data/-100.csv") != 0)
    {
        printf("test case failed when year = -100 expected result = data/-100.csv and your result = %s\n", filename3);
        return false;
    }

    return true; 
}

bool test_outFilename() 
{
    
    char filename[20];
    int year = 2000;
    outFilename(filename, year);

    if (strcmp(filename, "toWin/2000_win.csv") != 0)
    {
        printf("test case failed when year = 2000 expected result = toWin/2000_win.csv and your result = %s\n", filename);
        return false;
    }

    char filename1[20];
    int year1 = 1980;
    outFilename(filename1, year1);
    
    if (strcmp(filename1, "toWin/1980_win.csv") != 0)
    {
        printf("test case failed when year = 1980 expected result = toWin/1980_win.csv and your result = %s\n", filename1);
        return false;
    }

    char filename2[20];
    int year2 = 1828;
    outFilename(filename2, year2);
    
    if (strcmp(filename2, "toWin/1828_win.csv") != 0)
    {
        printf("test case failed when year = 1828 expected result = toWin/1828_win.csv and your result = %s\n", filename2);
        return false;
    }

    char filename3[20];
    int year3 = -100;
    outFilename(filename3, year3);
    
    if (strcmp(filename3, "toWin/-100_win.csv") != 0)
    {
        printf("test case failed when year = -100 expected result = toWin/-100_win.csv and your result = %s\n", filename3);
        return false;
    }

    return true; 
}

bool test_parseLine() 
{
    State myState;
    int result;

    
    char line1[30] = "Delaware,DE,3,13944";
    result = parseLine(line1, &myState);
    
    if (strcmp(myState.name, "Delaware") != 0 || strcmp(myState.postalCode, "DE") != 0 || myState.electoralVotes != 3 || myState.popularVotes != 13944) 
    {
        printf("Test case failed with line: Delaware,DE,3,13944\n");
        return false;
    }

    
    char line2[30] = "NewYork,NY,5,25000";
    result = parseLine(line2, &myState);
    
    if (strcmp(myState.name, "NewYork") != 0 || strcmp(myState.postalCode, "NY") != 0 || myState.electoralVotes != 5 || myState.popularVotes != 25000) 
    {
        printf("Test case failed with line: NewYork,NY,5,25000\n");
        return false;
    }

    char line3[30] = "California,CA,5";
    if (parseLine(line3, &myState)) 
    {
        printf("Test case failed with line: California,CA,5\n");
        return false;
    }

    char line5[30] = "";
    if (parseLine(line5, &myState)) 
    {
        printf("Test case failed with an empty line\n");
        return false;
    }

    char line6[30] = "Ohio,OH,5,28000\n";
    result = parseLine(line6, &myState);
    if (strcmp(myState.name, "Ohio") != 0 || strcmp(myState.postalCode, "OH") != 0 || myState.electoralVotes != 5 || myState.popularVotes != 28000) 
    {
        printf("Test case failed with line: Ohio,OH,5,28000\n");
        return false;
    }

    char line7[30] = "5,28000,Ohio,OH";
    if (parseLine(line7, &myState)) 
    {
        printf("Test case failed with line: 5,28000,Ohio,OH\n");
        return false;
    }

    return true;
}

bool test_readElectionData() 
{

    State allStates[50];
    int nStates = 0;

    if (readElectionData("data/1828.csv", allStates, &nStates)) 
    {
        if (nStates != 24) 
        {
            printf("Test case 7 failed. Incorrect number of states read (1828.csv).\n");
            return false;
        }
        // Check specific data for a few states
        if (strcmp(allStates[0].name, "Alabama") != 0 || strcmp(allStates[0].postalCode, "AL") != 0 ||
                               allStates[0].electoralVotes != 5 || allStates[0].popularVotes != 18618) 
        {
            printf("Test case 7 failed. Incorrect state data (1828.csv).\n");
            return false;
        }
        
        if (strcmp(allStates[2].name, "Delaware") != 0 || strcmp(allStates[2].postalCode, "DE") != 0 ||
            allStates[2].electoralVotes != 3 || allStates[2].popularVotes != 13944) {
            printf("Test case 7 failed. Incorrect state data (1828.csv).\n");
            return false;
        }
        
        if (strcmp(allStates[5].name, "Indiana") != 0 || strcmp(allStates[5].postalCode, "IN") != 0 ||
            allStates[5].electoralVotes != 5 || allStates[5].popularVotes != 39210) {
            printf("Test case 7 failed. Incorrect state data (1828.csv).\n");
            return false;
        }
    } 
    
    else 
    {
        printf("Test case 7 failed. Failed to read data/1828.csv\n");
        return false;
    }

    if (readElectionData("data/1904.csv", allStates, &nStates)) 
    {
        if (nStates != 45) 
        {
            printf("Test case 8 failed. Incorrect number of states read (1904.csv).\n");
            return false;
        }
        
        if (strcmp(allStates[0].name, "Alabama") != 0 || strcmp(allStates[0].postalCode, "AL") != 0 ||
            allStates[0].electoralVotes != 11 || allStates[0].popularVotes != 108785) 
        
        {
            printf("Test case 8 failed. Incorrect state data (1904.csv).\n");
            return false;
        }
        
        if (strcmp(allStates[3].name, "Colorado") != 0 || strcmp(allStates[3].postalCode, "CO") != 0 ||
            allStates[3].electoralVotes != 5 || allStates[3].popularVotes != 243667) 
        
        {
            printf("Test case 8 failed. Incorrect state data (1904.csv).\n");
            return false;
        }
        
        if (strcmp(allStates[11].name, "Iowa") != 0 || strcmp(allStates[11].postalCode, "IA") != 0 ||
            allStates[11].electoralVotes != 13 || allStates[11].popularVotes != 486093) 
        
        {
            printf("Test case 8 failed. Incorrect state data (1904.csv).\n");
            return false;
        }
    } 
    
    else 
    {
        printf("Test case 8 failed. Failed to read data/1904.csv\n");
        return false;
    }

    if (readElectionData("non_existent.txt", allStates, &nStates)) 
    {
        printf("Test case 2 failed. Should have returned false for a non-existent file.\n");
        return false;
    }

    return true;
}

bool test_minPVsSlow() 
{
    State allStates[50];
    int nStates = 0;
    MinInfo minSet;

    int result1 = readElectionData("data/1828.csv", allStates, &nStates);
    minSet = minPopVoteToWin(allStates, nStates);

    if (minSet.subsetPVs != 196802) 
    {
        printf("Test 1 Failed: Total popular votes do not match.\n");
        return false;
    }

    if (minSet.someStates[0].electoralVotes != 24) 
    {
        printf("Test 2 Failed: Total electoral votes do not match.\n");
        return false;
    }

    if (strcmp(minSet.someStates[3].name, "Rhode Island") != 0) 
    {
        printf("Test 2 Failed: Total electoral votes do not match.\n");
        return false;
    }

    if (minSet.szSomeStates != 14) {
        printf("Test 3 Failed: Number of states in the subset do not match.\n");
        return false;
    }

    if (!minSet.sufficientEVs) {
        printf("Test 4 Failed: Subset does not have enough electoral votes to win.\n");
        return false;
    }

    return true;
}

bool test_minPVsFast() 
{
 
    State allStates1[51];
    int nStates1 = 0;
    MinInfo minSet1;

    int result2 = readElectionData("data/2020.csv", allStates1, &nStates1);
    minSet1 = minPopVoteToWinFast(allStates1, nStates1);

    if (minSet1.subsetPVs != 34142388) 
    {
        printf("Test 1 Failed: Total popular votes do not match.\n");
        return false;
    }

    if (minSet1.someStates[0].electoralVotes != 3) 
    {
        printf("Test 2 Failed: Total electoral votes do not match.\n");
        return false;
    }

    if (strcmp(minSet1.someStates[3].name, "Utah") != 0) 
    {
        printf("Test 2 Failed: Total electoral votes do not match.\n");
        return false;
    }

    if (minSet1.szSomeStates != 35) {
        printf("Test 3 Failed: Number of states in the subset do not match.\n");
        return false;
    }

    if (!minSet1.sufficientEVs) {
        printf("Test 4 Failed: Subset does not have enough electoral votes to win.\n");
        return false;
    }

    return true;
}


int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
