#include <iostream>
#include <string>
// vector.h is needed to use vectors.
#include <vector>
// algorithms.h is needed for using the random_shuffle function.
#include <algorithm>
// time.h is needed for using the time() function.
#include "time.h"
#include <ctime>
// fstream for files
#include <fstream>

//Aarón A García Guzmán

using namespace std;

string getFileContents(ifstream& File)
{
   string sLines = ""; //All lines

   if(File)   //Check if everything is good
   {
      while(File.good())
      {
         string tempLine;                 //tempLine
         getline(File, tempLine);         //get tempLine
         tempLine += "\n";                //add new line character

         sLines += tempLine;              //add new line
      }
      return sLines;
   }
   else           //Return error
   {
      return "ERROR, inexistent file.";
   }
}

// Final message
void gameEnd()
{
   ifstream Reader("youWon.txt"); //Open file
   string sArt = getFileContents(Reader); //Get file
   cout << sArt << "\n\n\n"; //Print it to the screen
   Reader.close(); //Close file
}

//Validar que se pueda mover para algun lado, que no se salga del tablero
bool validarMovimiento(string map[5][5], int mapSize, char cMov, int iRow, int iCol, int iAddRow, int iAddCol)
{
   if(map[iRow + iAddRow][iCol + iAddCol] == "-")
      return false;
   return true;
}

//Pone el tablero
void setTablero(string map[5][5], int mapSize, string sHeader, int movimiento, vector<string>& data)
{
   cout << "\t    ROMPECABEZAS DE NUMEROS\n";

   int iNum = 0;

   srand(time(0)); // Sets seed
	random_shuffle(data.begin(), data.end()); // Shuffles the contents of the vector.

   for (int iRen = 0, iTop = 0, iLeft = 0; iRen < mapSize; iRen++, cout << "\n")
   {
      cout << "|\t";
      for (int iCol = 0; iCol < mapSize; iCol++, cout << "\t")
      {
         if (iRen == 0 && iCol == 0)
            map[iRen][iCol] = ' ';
         else if(iRen == 0)
            cout << sHeader[iTop++];
         else if(iCol == 0)
            cout << sHeader[iLeft++];
         else if(movimiento == 0)
            map[iRen][iCol] = data.at(iNum++); // Assign elements in random order

         cout << map[iRen][iCol];
      } cout << "|\t";
   }
}

void makeMovement(string map[5][5], int mapSize, char cMov, int iRow, int iCol)
{
   char cRow, cCol;
   bool bRepeat;

   do
   {
      cout << "Column: ";
      cin >> cCol;
      if(cCol == 'a')
         iCol = 1;
      else if(cCol == 'b')
         iCol = 2;
      else if(cCol == 'c')
         iCol = 3;
      else if(cCol == 'd')
         iCol = 4;

      cout << "Row: ";
      cin >> cRow;
      if(cRow == 'a')
         iRow = 1;
      else if(cRow == 'b')
         iRow = 2;
      else if(cRow == 'c')
         iRow = 3;
      else if(cRow == 'd')
         iRow = 4;


      if((cCol == 'a' || cCol == 'b' || cCol == 'c' || cCol == 'd') &&
         (cRow == 'a' || cRow == 'b' || cRow == 'c' || cRow == 'd'))
         bRepeat = false;
      else
         bRepeat = true;

   }while(bRepeat); //Hasta que elijan a-d en rows y a-d en cols deja de repetirse

   int iAddCol = 0, iAddRow = 0;

   do{
   cout << "Movements \n l = left \t u = up \t r = right \t d = down\nChoose: ";
   cin >> cMov;

   if( cMov == 'l')
   {
      iAddCol = -1;
   }
   else if ( cMov == 'u')
   {
      iAddRow = -1;
   }
   else if( cMov == 'r')
   {
      iAddCol = 1;
   }
   else if ( cMov == 'd')
   {
      iAddRow = 1;
   }
}while(validarMovimiento(map, mapSize, cMov, iRow, iCol, iAddRow, iAddCol)); // Hasta que lo mueva hacia un '-' va dejar de repetirse
   map[iRow + iAddRow][iCol + iAddCol] = map[iRow][iCol];// mueve el numero a la posicion de '-'
   map[iRow][iCol] = "-"; // asigna '-' a donde estaba el numero que se movio
}

void increaseMovement(int &mov)
{
   mov++;
}

bool checkWin(string map[5][5], int mapSize)
{
   int iNum = 1;
   int iChecker = 0;
   //This loop checks if 1-15 is in order
   for (int iRen = 1; iRen < mapSize; iRen++)
   {
      for (int iCol = 1; iCol < mapSize; iCol++)
      {
         if (map[iRen][iCol] == to_string(iNum++))
            iChecker++;
         else
            break;
      }
   }
   if(iChecker == 15)
      return false;
   return true;
}

void rules()
{
   cout << "\t\tRULES" << endl;
   cout << "You can only move the numbers to the \'-\' sign." << endl;
   cout << "Order the numbers from 1 to 15." << endl;
   cout << "Good luck! - Aarón" << endl;
}


int main()
{
   char cAgain;

   do{
      const int mapSize = 5;
      char cMov = 'a';
      int movimiento = 0, iRow = 0, iCol = 0;
      string map[5][5], sHeader = "abcd";
      string tmp[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "-"};
      // Loads the data into a vector.
   	vector<string> data(tmp, tmp + 16);

      rules();

      do
      {
         setTablero(map, mapSize, sHeader, movimiento, data);
         makeMovement(map, mapSize, cMov, iRow, iCol);
         increaseMovement(movimiento);
      } while(checkWin(map, mapSize));

      gameEnd();

      do{
         cout << "Play again? (y/n): ";
         cin >> cAgain;
         cAgain = tolower(cAgain);
      }while(cAgain != 'y' && cAgain != 'n');

   }while(cAgain == 'y');

   cout << "Thanks for playing!" << endl;
   return 0;
}
