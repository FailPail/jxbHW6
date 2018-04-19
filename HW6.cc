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
#include <string>

#define WIDTH 5
#define HEIGHT 3
#define BOX_WIDTH 15
#define NAME "HW6 Matrix"

using namespace std;

class BinaryFileHeader{

public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;



};

const int maxRecordLength = 25;

class BinaryFileRecord{

public:
  uint8_t strlength;
  char stringbuffer[maxRecordLength];

};

int main(){


    WINDOW *window;
  CDKSCREEN *screen;
  CDKMATRIX *matrix;


  //weird naming and construction here
  //height and width appear to be reversed in CDK
  //rowtitles is actually the number of columns
  //coltitles is actually the number of rows
  const char * rowTitles[HEIGHT+1] = {"C0", "C1", "C2", "C3"};
  const char * colTitles[WIDTH+1] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  int widths[WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int types[WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};
  

  window = initscr();
  screen = initCDKScreen(window);

  initCDKColor();

  matrix = newCDKMatrix(screen, CENTER, CENTER, WIDTH, HEIGHT, WIDTH, HEIGHT, NAME, (char**) colTitles,(char**) rowTitles, widths, types, 1,1, ' ', ROW, true, true, false);

  if(matrix == NULL){

    printf("Error creating matrix \n");
    _exit(1);
  }

  drawCDKMatrix(matrix, true);
  
  

  int pos;
  FILE *file;
  BinaryFileHeader header;
  BinaryFileRecord record;

  file = fopen("cs3377.bin", "wb");
  if(!file){

    printf("Cannot open file\n");
    return 1;
  }
  
  fread(&header, sizeof(class BinaryFileHeader), 1, file);
  printf("%d\n", header.versionNumber);
  string container = "" + header.magicNumber;
  setCDKMatrixCell(matrix, 1,1, container.c_str());
  container = "" + header.versionNumber;
  setCDKMatrixCell(matrix, 1,2, container.c_str());
  container = "" + header.numRecords;
  setCDKMatrixCell(matrix, 1,3, container.c_str());

  drawCDKMatrix(matrix,true);


  sleep(10);

  endCDK();
}
