/*
 *
 *Johnathan Baugh
 *jxb141430@utdallas.edu
 *CS 3377.501
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <cdk.h>
#include <stdlib.h>
#include <string>
#include <curses.h>



//various constants used in CDK
//WIDTH for width of matrix
//HEIGHT for height of matrix
//NAME fo the name of the matrix
#define WIDTH 5
#define HEIGHT 3
#define BOX_WIDTH 20
#define NAME "HW6 Matrix"

using namespace std;


//class for Binary header containing the magic number, version number, and number of records
class BinaryFileHeader{

public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

//constant int for the maximum length of a string in record
const int maxRecordLength = 25;

//class for Binary record containing length of string and the string itself
class BinaryFileRecord{

public:
  uint8_t strlength;
  char stringbuffer[maxRecordLength];

};

int main(){


   
  
  WINDOW *window;
  CDKSCREEN *screen;
  CDKMATRIX *matrix;


  //titles for the rows and columns
  //Weird bit, CDK seems to swap width and height, so rowtitles, is the number of columns
  //and row titles is the number of rows
  const char * rowTitles[HEIGHT+1] = {"C0", "C1", "C2", "C3"};  
  const char * colTitles[WIDTH+1] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  
  //widths of the boxes and type of boxes
  int widths[WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int types[WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};
  
  //initialization of window, color,  and screen for CDK
  window = initscr();
  screen = initCDKScreen(window);
  initCDKColor();

  //create the CDK matrix
  matrix = newCDKMatrix(screen, CENTER, CENTER, WIDTH, HEIGHT, WIDTH, HEIGHT, NAME, (char**) colTitles,(char**) rowTitles, widths, types, 1,1, ' ', ROW, true, true, false);

  //check if matrix was created properly
  if(matrix == NULL){

    printf("Error creating matrix \n");
    _exit(1);
  }


  //draw base matrix;
  drawCDKMatrix(matrix, true);
  
  //initial setup for reading binary file
  //pos for position to edit in the matrix
  int pos = 2;
  FILE *file;
  
  //binary header and record classes
  BinaryFileHeader header;
  BinaryFileRecord record;

  //open the binary file and check if it opened properly
  file = fopen("cs3377.bin", "rb");
  if(!file){

    printf("Cannot open file\n");
    return 1;
  }

  //read initial header of the binary file
  fread(&header, sizeof(BinaryFileHeader), 1, file);
  
  //buffer for the process of appending strings for adding into the matrix
  char buffer[maxRecordLength];
  
  //turn magic number in header file into a string, append it to the string object head, and add it to the CDK matrix
  snprintf(buffer, maxRecordLength, "%X", header.magicNumber);
  string head = "Magic: 0x";
  head.append(buffer);
  setCDKMatrixCell(matrix, 1,1, head.c_str());  


  //turn version number in header file into a string, append it to the string object head and add it to the CDK matrix
  snprintf(buffer, maxRecordLength, "%u", header.versionNumber);
  head = "Version: ";
  head.append(buffer);
  setCDKMatrixCell(matrix, 1,2, head.c_str());
  
  //turn number of records into a string, append it to the string object head, and add to CDK matrix
  snprintf(buffer, maxRecordLength, "%lu", header.numRecords);
  head = "NumRecords: ";
  head.append(buffer);
  setCDKMatrixCell(matrix, 1,3, head.c_str());
  
  //count for making sure to not read more than four structs in the binary file
  int count = 0;

  //read the next struct from the binary file and make sure it does not pass the fourth record
  while(fread(&record, sizeof(BinaryFileRecord), 1, file) && count < 4){
    
    //turn the string length field in record into a string, append it to the head string objext and add it to the CDK matrix
    snprintf(buffer, maxRecordLength, "%u", record.strlength);
    head = "strlen: ";
    head.append(buffer);
    setCDKMatrixCell(matrix,pos,1,head.c_str());

    //add stringbuffer into the CDK matrix
    setCDKMatrixCell(matrix, pos, 2, record.stringbuffer);
    
    //add one to pos for moving down the matrix and count for making sure not to pass the fourth record
    pos++;
    count++;

  }

  //draw the final CDK matrix
  drawCDKMatrix(matrix,true);



  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  while (1){
    drawCDKMatrix(matrix,true);
    if(getch() != ERR){
      endwin();
      endCDK();
      return 0;
      }
   
  }
  sleep(10);
  endCDK();
}
