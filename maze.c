#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DOWN 0 
#define RIGHT 1 
#define UP 2 
#define LEFT 3 

#define POSSIBLE_ZEROS 100 

void mazeTraversal (char maze[12][12], int xCoordinate, int yCoordinate, int xStart2, int yStart2, int direction, int MoveCount); 
int printMaze(const char maze [][12], int b); 
int edges(int x, int y); 
int validMove(const char maze [][12], int r, int c); 
void mazeGenerator(char maze[][12], int *xPtr, int *yPtr); 




int main (void) 
{ 
    int x, y, i, j;
    
    char maze [12][12]; 
    for (i=0;i<12;i++) { 
      for (j = 0; j<12; j++) { 
        maze[i][j]='#'; 
      }
    }
      
      int xStart; 
      int yStart;
      mazeGenerator(maze, &xStart, &yStart);
      
      x = xStart;
      y = yStart;
      mazeTraversal(maze, x, y, xStart, yStart, RIGHT, 1); 
      
  return 0; 
} 

void mazeTraversal (char maze[12][12], int xCoordinate, int yCoordinate, int xStart2, int yStart2, int direction, int MoveCount)
{ 
  static int flag = 0; 
  
  maze[xCoordinate][yCoordinate] = 'X'; /* X is assigned to the first location visited before recursion continues*/

  printMaze(maze, MoveCount++); 
  
  if ( edges(xCoordinate, yCoordinate) && xCoordinate != xStart2 && yCoordinate != yStart2) { 
    printf("\n\nMaze successfully exited!!!!\n");
    return;
    } 
      else if (xCoordinate == xStart2 && yCoordinate == yStart2 && flag == 1) { 
      printf("\n\nArrived back at the starting location\n");
      } 
        else { 
          int count; 
          int move; 
          flag = 1;
          
          for (move = direction, count = 0; count < 4; count++, move++, move %= 4) { /*for loop to cycle through 0123 (the assigned directions). modulo operator to keep the numbers at 0123 regardless of where the loop starts*/
            
            switch (move) { 
              
              case DOWN:
              if (validMove(maze, xCoordinate + 1, yCoordinate)) { /*check if validMove is returns true*/
                
                mazeTraversal(maze, xCoordinate + 1, yCoordinate, xStart2, yStart2, LEFT, MoveCount++); /*if move is valid recursively call mazeTraversal again adding one move "down" on the x value of the array and starting with the next direction to the right (clockwise)*/
                return;  
              }
              break;
              
              case RIGHT:
              if (validMove(maze, xCoordinate, yCoordinate + 1)) { /*check if validMove is returns true*/
                
                mazeTraversal(maze, xCoordinate, yCoordinate + 1, xStart2, yStart2, DOWN, MoveCount++); /*if move is valid recursively call mazeTraversal again adding one move the "right" on the y value of the array and starting with the next direction to the right (clockwise)*/
                return; 
              } 
              break; 
              
              case UP:
              if (validMove(maze, xCoordinate - 1, yCoordinate)) { /*check if validMove is returns true*/
                
                mazeTraversal(maze, xCoordinate - 1, yCoordinate, xStart2, yStart2, RIGHT, MoveCount++); /*if move is valid recursively call mazeTraversal again adding one move "up" on the x value of the array and starting with the next direction to the right (clockwise)*/
                return; 
              } 
              break; 
              
              case LEFT:
              if (validMove(maze, xCoordinate, yCoordinate - 1)) { /*check if validMove is returns true*/
                
                mazeTraversal(maze, xCoordinate, yCoordinate - 1, xStart2, yStart2, UP, MoveCount++); /*if move is valid recursively call mazeTraversal again adding one move the "left" on the y value of the array and starting with the next direction to the right (clockwise)*/
                return; 
              } 
              break; 
              
            } 
          }
        }
    
}

int validMove(const char maze [][12], int r, int c) /*check if a move is valid function (r is x and c is y)*/
{ /*start validMove */
  return (r >= 0 && r <= 11 && c >= 0 && c<= 11 && maze[r][c] != '#'); /*if x and y (r and c) are both inside the maze and are not at a wall than it is valid and the expression returns true (1).*/
} 

int edges(int x, int y) /* function to check if we have made it to the edge */
{ 
  if ((x==0 || x == 11) && (y >= 0 && y <= 11)) { /*if statement to check if we reached the first or last edge of the a row */
  return 1;
  } 
    else if ((y==0 || y == 11) && (x >= 0 && x <= 11)) { /*if statement to check if we reached the top or bottom edge of a column */
      return 1;
    } 
      else {
        return 0; /*if no edge, return false*/
      } 
} 

int printMaze(const char maze [][12], int b) /*function to print the maze*/
{ 
  int row; /*initialize the variables*/
  int col;
 
  printf("\nMOVE %d\n", b); /*print the move number*/
  for (row = 0; row < 12; row++) { 
    for (col = 0; col < 12; col++) { 
      printf(" %c ", maze[row][col]); 
    } 
    
    printf("\n"); /*print new line*/
  } 

} 

void mazeGenerator(char maze[][12], int *xPtr, int *yPtr)
{
  int in;
  int out;
  int x, y, j, i;
  
  srand(time(NULL)); /*seed random number generator*/
  
  /* generate random entry and exit positions */
  do {
    in = rand()%4; /*generate random numbers between 1 and 4 (four walls) as the starting point */
    out = rand()%4; /*generate random numbers between 1 and 4 (four walls) as the exit point */
  }
   while (in == out); /*loop back around for new random numbers if they come out equal*/
   
   /* determine entry points while avoiding corners by capping the random variable position at the 11th and 1st positions*/
   if (in == 0) {   /*if statement for the Leftmost wall*/
    *xPtr = 1 + rand()%10;
    *yPtr = 0;
    maze [*xPtr][0] = '.'; /*assign entry*/
   } 
    else if (in == 1) { /*if statement for the Top wall*/
      *xPtr = 0;
      *yPtr = 1 + rand()%(10);
      maze[0][*yPtr] = '.'; /*assign entry*/
    } 
        else if (in == 2) { /*if statement for the Rightmost side*/
          *xPtr = 1 + rand()%(10);
          *yPtr = 11;
          maze[*xPtr][11] = '.'; /*assign entry*/
        }
          else {
            *xPtr = 11; /*if statement for the Bottom wall*/
            *yPtr = 1 + rand()%(10);
            maze[*xPtr][*yPtr] = '.'; /*assign entry*/
          } 
          
   /* determine exits points while avoiding corners by capping the random variable position at the 11th and 1st positions. */
   
   if (out == 0) { /*if statement for the Leftmost wall*/
     j = 1 + rand()%(10);
     maze[j][0] = '.'; 
   } 
    else if (out == 1) { 
      j = 1 + rand()%(10);
     maze[0][j] = '.';
    } 
      else if (out == 2) { 
        j = 1 + rand()%(10); 
        maze[j][11] = '.'; 
      } 
        else {             
          j = 1 + rand()%(10);
          maze[11][j] = '.'; 
        }
  
 /* Add zeros to maze grid randomly*/
   for (i=1; i<POSSIBLE_ZEROS; i++) { 
     x = 1 + rand()%(10);
     y = 1 + rand()%(10);
     maze[x][y] = '.';
   } 
 
} /*end mazeGenerator function */