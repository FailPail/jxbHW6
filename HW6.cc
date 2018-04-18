/*
 *
 *Johnathan Baugh
 *jxb141430@utdallas.edu
 *CS 3377.501
 *
 */


#include <cdk.h>

#define WIDTH 3
#define HEIGHT 5
#define BOX_WIDTH 15
#define NAME "HW6 Matrix"

int main(){


    WINDOW *window;
  CDKSCREEN *screen;
  CDKMATRIX *matrix;

  const char * rowTitles[HEIGHT+1] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char * colTitles[WIDTH+1] = {"C0", "C1", "C2"};
  int widths[WIDTH+1] = {WIDTH, WIDTH, WIDTH, WIDTH};
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

}
