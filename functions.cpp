//Ria Mukherji
//LAB 3
//CS1342 Kenneth Howard
// 3/4/23

#include "functions.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/** This function uses the file stream object, file,
   and creates a 2D vector with the data that is read from the file.
   You will use this function twice, one for Authors, one for Books.
   **/
vector<vector<string>> readTable(ifstream &file) {
// declare string token to hold what is read in
string token;

//declare a 2D vector values
vector<vector<string>> values;

//print error message if the file open fails
if (!file.is_open()){
        cout << "Error: file not opened";
    }// end checking if file opened

    //if the file opens
    //create a string that will hold each individual line
    string lineOfFile;

    //while there are still lines to read in the file (replacement for eof.file)
    //this allows for the function to read as many or as few columns exist as long as same format
    while(getline(file,lineOfFile))
    {
        //create a vector for each row
        vector<string> row;

        //create an istring
        // this will be able to analyze a line that has already been read in
        //istring reads in lineOfFile to analyze
        istringstream line(lineOfFile);

        // create a string to hold the separated tokens in lineOfFile
        string separateTokenInLine;

        //while each lineOfFile still has stuff/tokens in it add token to the row vector
        //tokens separated by ,
        while(getline(line,separateTokenInLine, ',')) {
        row.push_back(separateTokenInLine);
        }//end while
        //2d vector values adds a column of one whole row vector
        values.push_back(row);
    }//end while

    //close file
    file.close();

    //return values the 2d vector
    return values;
}// end readTable

/** This function writes the contents of any
 * 2D vector to a file object, file, in csv format
 **/
void writeTable(ofstream &file, const vector<vector<string>> &table) {
    //outer vector
    for (int i = 0; i < table.size(); i++) {
        //inner vector with the []
        for (int j = 0; j < table[i].size(); j++){
            //index through the entire inner for each outer and then for all except last add a ,
            file << table[i][j];
            if( j < table[i].size()-1){
                file << ",";
            }
        }
        file << endl;
    }
}

/** This function creates a new 2D vector that is a "join" of leftTable and rightTable.
 *  You will join the data based on the AUTHOR_ID
 **/
vector<vector<string>> innerJoin(vector<vector<string>> &leftTable, vector<vector<string>> &rightTable) {
    //leftTable is meant to be books
    //rightTable is meant to be authors


    //these semi constants are for the books table inner array - not necessary but more readable code
    //they come from the index format of the files Books and authors
    //for example leftTable[index1][2] will return the title of the book
    //this is because the title is always formatted at the second index
    //to be used with leftTable
    const int bookID = 0;
    const int bookAUTHOR_ID = 1;
    const int TITLE = 2;
    const  int GENRE = 3;
    const int PUBLISHER = 4;
    //these semi-constants are for author table inner array - not necessary but more readable code
    //to be used with rightTable
    const int ID = 0;
    const int NAME = 1;
    const int YEAR_OF_BIRTH = 2;
    const int COUNTRY = 3;
    const int FIRSTROW = 0;

     //result vector first row is a constant due to the known format of the csv files
     vector<vector<string>> joinResult =  { {leftTable[FIRSTROW][TITLE],leftTable[FIRSTROW][GENRE],leftTable[FIRSTROW][PUBLISHER],rightTable[FIRSTROW][NAME],rightTable[FIRSTROW][YEAR_OF_BIRTH],rightTable[FIRSTROW][COUNTRY]}};

     //string a is the Author ID from the books table
     string a;
     //string b is the ID from the Authors table
     string b;
     //count will be the list number at the beginning incremented
     int count = 0;
     //index1 will be where the match is found in the leftTable
     int index1;
     //index2 will be where the match is found in the rightTable
     int index2;

     //the outer loop of the left table - needed to enter inner
     for(int i = 0; i < leftTable.size(); i++){
            //for each iteration a is stored as the Author ID from the book table only used if match later
            a = leftTable[i][1];
            cout << endl;

            for (int j = 0; j < rightTable.size(); j++) {
               //nested loop for each iteration b is stored as the ID from the Author table only used if match later
               b = rightTable[j][0];
               //if match case where a and b are compared
               if (a==b){
                   //if a match occurs steal i and j to use as the indexes since that's where they were found
                   index1 = i;
                   index2 = j;
                   //increment the counter for every match this will make a numerically increasing list
                   count++;
                   //create a new vector with each match and push it as the inner argument to the 2d vector
                   vector<string> newRow = {leftTable[index1][TITLE], leftTable[index1][GENRE], leftTable[index1][PUBLISHER], rightTable[index2][NAME], rightTable[index2][YEAR_OF_BIRTH], rightTable[index2][COUNTRY]};
                    joinResult.push_back(newRow);

               }//end of match a==b
            }//end of right table indexing (j)

     }//end of left table indexing (i)

    return joinResult;
}
