#include <iostream>
#include "functions.h"
#include <fstream>
#include <string>
#include <sstream>

//For my files to open to read in I had to move Authors.csv and Books.csv into my cmake-build-debug folder
// My code runs correctly on my end. If for some reason it is not reading in the files on your end please let me know.
using namespace std;
int main() {
    // open ofstream file to output into results
    ofstream file("../Results.csv");

    //Declare an ifstream fileIn
    ifstream fileIn;

    //fileIn will read Authors.csv and perform readTable func on it
    fileIn.open("Authors.csv");// on my machine this is fileIn.open("C:\\CS1341\\program-3-riamuk101\\Authors.csv"); had I not moved the files to cmake
    //save the file read
    vector<vector<string>> rightTable = readTable(fileIn);
    //fileIn will read Books.csv and perform readTable func on it (it is closed at the end of the readTable function so no need to close again)
    fileIn.open("Books.csv");// on my machine this is fileIn.open("C:\\CS1341\\program-3-riamuk101\\Books.csv");had I not moved the files to cmake
    vector<vector<string>> leftTable = readTable(fileIn);

    //writeTable function writes 2d array into Results.csv that innerJoin creates
    writeTable(file, innerJoin(leftTable,rightTable));
    //close the ofstream and Results.csv file
    file.close();
    return 0;
}
