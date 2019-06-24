#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
// you need the below prototype only if you attempt the bonus part
int computerPlaysToBlock(char [N][N], int * , int * );


int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';

   srand(time(NULL));

   printf("This tic-tac-toe board is of size %d by %d\n", N, N);

   printf("Player symbol: X \n Computer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);			// create a 3 X 3 board with '?' in each cell

   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {
	   taken = 0;

		while (!(taken))                  // loop used to accept valid row and col values from the user
		{
			readUserMove(&userRow, &userCol);                  //get user's move
			printf("You chose row %d and column %d \n", userRow, userCol);

			while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
			{
				printf("That's is an invalid row or column number - try again\n");
				readUserMove(&userRow, &userCol);
				printf("You chose row %d and column %d \n", userRow, userCol);
			}

			if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
			{
				board[userRow-1][userCol-1] = 'X';			// store an X there
				taken = 1;
			}
			else
			{
				taken = 0;									// otherwise inform the user to enter values again
				printf("That spot is taken - please try another one\n");
			}

		} //end of while (!taken)

	   if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
	   {
		   printf("Congrats - you won against the computer :)\n");
		   winner = 'Y';
	   }

	   else  if (!(isBoardFull(board)))            //check if the board is already full
	   {
		   taken = 0;

		   while (!(taken))
		   {
				getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col

				if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
				{
					board[computerRow][computerCol] = 'O';
					taken = 1;

				}
				else
				{
					taken = 0;		//That spot is taken - computer - try another one
				}
		   }

		   printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);

		   if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
		   {
			   printf("\nOh the computer won this time :(( think hard next time\n");
			   winner = 'Y';
		   }
	   }

	printCurrentBoard(board);

	printf("\nPress enter to continue \n");
	getchar();

   } //end of while

   if (winner != 'Y')
			printf("Game was a tie - no winner!\n\n");

   return 0;
}


int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/*
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   // int blocked = 1;            this declaration is required if you attempt the bonus part

   winningSpot = computerPlaysToWin(board, computerRow, computerCol);

   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user
   {
	   //computerPlaysRandom(computerRow, computerCol, userRow, userCol);


	   //If you attempt the bonus part, then uncomment the code below and use it to first try and block user move
	   //If unsuccessful, then it pick row and col (pseudo) randomly


	 int  blocked = computerPlaysToBlock(board, computerRow, computerCol);
	   if (blocked == 0)
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);


   }

   return winningSpot;
}

int isInputValid (int entered, int minimum, int maximum) //checks weather the input is in the constrain or not
{
    if(entered>=minimum && entered<=maximum)
        return 1;
    else
        return 0;
}
int isBoardFull (char board [N][N])  //this function checks whether there is space for next move or not
{
    int i,j;
    for(i=0;i<3;i++)

    for(j=0;j<3;j++)
        {
            if(board[i][j]=='?')
                 return 0;
        }

    return 1;
}
void createInitialBoard (char board [N][N])   // creates the board for tic-tac toe
{
    int i,j;
    for(i=0;i<3;i++)
    for(j=0;j<3;j++)
       board[i][j]='?';
    for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                printf(" %c",board[i][j]);
                if(j<2)
                printf(" | ");
            }
            printf("\n------------\n");
        }
}
void readUserMove (int * userRow, int * userCol)   //takes the input from user for users turn 
{
    printf("Your move - enter numbers between 1 and 3:\n");
    printf("Enter row number:");
    scanf(" %d",userRow);
    printf("Enter column number:");
    scanf(" %d",userCol);
}
void printCurrentBoard (char board [N][N]) //prints the board after you and computer play there move and reprints the board again
{
    int i,j;
    for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                printf(" %c",board[i][j]);
                if(j<2)
                printf(" | ");
            }
            printf("\n--------------\n ");
        }
}
int gameWon (char board [N][N], char symbol) //checks if user or computer wins the game or not and if they then exit the game 
{

    int i;
    for(i=0;i<3;i++)
    {
        if((board[i][0]== symbol )&& (board[i][0]==board[i][1]) && (board[i][0] == board[i][2]) && (board[i][1] == board[i][2]))
        {
            return 1;
        }
    }

    for(i=0;i<3;i++)
    {
       if((board[0][i] == symbol ) && (board[0][i] == board[1][i]) && (board[0][i]==board[2][i]) && (board[1][i] == board[2][i]))
       {
           return 1;
       }
    }
      if((board[0][0]== symbol) && (board[0][0]==board[1][1]) && (board[0][0]==board[2][2]))
       {
           return 1;
       }
        
       if((board[2][0]== symbol) && (board[2][0]==board[1][1]) && (board[2][0]==board[0][2]))
       {
            return 1;
       }
      else
      return 0;
}
int computerPlaysToWin (char board [N][N], int * cRow, int * cCol)//in this computer checks all  column and row to win the game
{
     if(board[0][0]==board[0][1] && board[0][0]=='O' && board[0][2]=='?')   //row 1
     {
         *cRow=0;*cCol=2;
           return 1;
    }

    else if(board[0][1]==board[0][2] && board[0][1]=='O' && board[0][0]=='?')
    {
        *cRow=0;*cCol=0;
           return 1; 
    }

    else if(board[0][0]==board[0][2] && board[0][0]=='O' && board[0][1]=='?')
    {
        *cRow=0;*cCol=0;
          return 1;
    }
                                                                            
    else if(board[1][0]==board[1][1] && board[1][0]=='O' && board[1][2]=='?')    //row2
    {
        *cRow=1; *cCol=2; 
        return 1; 
    }

    else if(board[1][1]==board[1][2] && board[1][1]=='O' && board[1][0]=='?')
    {
        *cRow=1; *cCol=0; 
        return 1; 
    }
 
    else if(board[1][0]==board[1][2] && board[1][0]=='O' && board[1][1]=='?')
    {
        *cRow=1; *cCol=1;
        return 1;
    }
                                                                              
    else if(board[2][0]==board[2][1] && board[2][0]=='O' && board[2][2]=='?') //row3
    {
        *cRow=2;*cCol=2; 
         return 1;
    }
    else if(board[2][1]==board[2][2] && board[2][1]=='O' && board[2][0]=='?')
    {  
         *cRow=2;*cCol=0;
          return 1;
    }
    else if(board[2][0]==board[1][2] && board[2][0]=='O' && board[2][1]=='?')
    {
        *cRow=2;*cCol=1; 
         return 1; 
    }

    else if(board[0][0]==board[1][0] && board[0][0]=='O' && board[2][0]=='?') //column1
    {
        *cRow=2;*cCol=0;
         return 1;
    }
    else if(board[1][0]==board[2][0] && board[1][0]=='O' && board[0][0]=='?')
    {
        *cRow=0; *cCol=0; 
        return 1;
    }
    else if(board[0][0]==board[0][2] && board[0][0]=='O' && board[0][1]=='?')
    {
        *cRow=0; *cCol=1;
         return 1;
    }

    else if(board[0][1]==board[1][1] && board[0][1]=='O' && board[2][1]=='?')//column2
    {
        *cRow=2;*cCol=1; 
         return 1;
    }
    else if(board[1][1]==board[2][1] && board[1][1]=='O' && board[0][1]=='?')
    {
        *cRow=0;*cCol=1;
         return 1;
    }
     else if(board[1][0]==board[1][2] && board[1][0]=='O' && board[1][1]=='?')
     {
         *cRow=1;*cCol=1;
         return 1;
     }

     else if(board[0][2]==board[1][2] && board[0][2]=='O' && board[2][2]=='?')//column3
     {
        *cRow=2;*cCol=2;
         return 1;
     }
     else if(board[1][2]==board[2][2] && board[1][2]=='O' && board[0][2]=='?')
     {
         *cRow=0;*cCol=2;
          return 1;
     }
     else if(board[1][0]==board[1][2] && board[1][0]=='O' && board[1][1]=='?')
     {
          *cRow=1;*cCol=1;
           return 1;
     }

     else if(board[0][0]==board[1][1] && board[0][0]=='O' && board[2][2]=='?')// checks for left diagonal
     {
         *cRow=2;*cCol=2;
          return 1;
     }
     else if(board[1][1]==board[2][2] && board[1][1]=='O' && board[0][0]=='?')
     {
         *cRow=0;*cCol=0; 
          return 1;
     }
     else if(board[0][0]==board[2][2] && board[0][0]=='O' && board[1][1]=='?')
     {
         *cRow=1;*cCol=1;
          return 1;
     }

     else if(board[0][2]==board[1][1] && board[0][2]=='O' && board[2][0]=='?')//checks for right diagonal
     {
          *cRow=2;*cCol=0;
          return 1;
     }
     else if(board[1][1]==board[2][0] && board[1][1]=='O' && board[0][2]=='?')
     {
         *cRow=0;*cCol=2;
          return 1;
     }
     else if(board[0][2]==board[2][0] && board[0][2]=='O' && board[1][1]=='?')
     {
         *cRow=1;*cCol=1;
          return 1;
     }
      else
      return 0;
}
void computerPlaysRandom (int * cRow, int * cCol, int uRow, int uCol)//in this function computer play any move if it does not win
{

   do
    {
        *cRow=rand() % 3;
        *cCol=rand() % 3;
    }
    while(*cRow==uRow || *cCol==uCol);
}
 void sumAllDimensions (char board [N][N], int sumR[N], int sumC[N], int * sumLD, int *sumRD)
 {                //checks the sum of all rows,colums,left diagonal and right diagonal
     int i;
     int j;
     for(int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
            if(board[i][j]=='O')
             sumR+=4;
        else if (board[i][j] == 'X')
          sumR[i]+=1;
     }

     for(i=0;i<3;i++)
     {
         for(j=0;j<3;j++)
         if(board[i][j]=='O')
            sumC+=4;
         else if(board[i][j]=='X')
            sumC[j]+=1;
     }

     for(i=0;i<3;i++)
     {
        if(board[i][i]=='O')
        sumLD+=4;
        else if (board[i][i]=='X')
        sumLD+=1;
     }
        for(i=0;i<3;i++)
        for(j=2;j<=0;j--)

     {
        if(board[i][j]=='O')
             sumLD+=4;
        else if (board[i][j]=='X')
        sumLD+=1;
     }

}
int memberOf (int aNum, int someArray [N])/* if someArray has the following
                                           values [10,20,30], then memberOf (30, someArray) returns 1 but memberOf (3,
                                                    someArray) returns 0.*/
{
        if(aNum==30)
    {
        int i;
        for(i=0;i<3;i++)
        if(i==10||i==20||i==30)
        return 1;
    }
      else
      return 0;
      return 0;
}


int computerPlaysToBlock(char board [N][N], int * cRow, int * cCol)/*bonus function -computer blocks the user move so that user
                                                                      cannot win easily     */
{
    if(board[0][0]==board[0][1] && board[0][0]=='X' && board[0][2]=='?')// condition for row 1
    {
         *cRow=0;*cCol=2;
         return 1;
    }
    else if(board[0][1]==board[0][2] && board[0][1]=='X' && board[0][0]=='?')
    {
          *cRow=0;*cCol=0;
          return 1;
    }
    else if(board[0][0]==board[0][2] && board[0][0]=='X' && board[0][1]=='?')
    {
          *cRow=0;*cCol=1;
           return 1;
    }
                                                                              //row 2
    else if(board[1][0]==board[1][1] && board[1][0]=='X' && board[1][2]=='?')
    {
          *cRow=1; *cCol=2;
           return 1;
    }
    else if(board[1][1]==board[1][2] && board[1][1]=='X' && board[1][0]=='?')
    {
          *cRow=1; *cCol=0;
           return 1;
    }
    else if(board[1][0]==board[1][2] && board[1][0]=='X' && board[1][1]=='?')
    {
          *cRow=1; *cCol=1;
          return 1;
    }

    else if(board[2][0]==board[2][1] && board[2][0]=='X' && board[2][2]=='?')//row3
    {
          *cRow=2;*cCol=2;
           return 1;
    }
    else if(board[2][1]==board[2][2] && board[2][1]=='X' && board[2][0]=='?')
    {
         *cRow=2;*cCol=0;
          return 1;
    }
     else if(board[2][0]==board[1][2] && board[2][0]=='X' && board[2][1]=='?')
    {
          *cRow=2;*cCol=1;
           return 1;
    }

    else if(board[0][0]==board[1][0] && board[0][0]=='X' && board[2][0]=='?')//column1
    {
          *cRow=2;*cCol=0;
           return 1;
    }
    else if(board[1][0]==board[2][0] && board[1][0]=='X' && board[0][0]=='?')
    {
          *cRow=0; *cCol=0; 
           return 1;
    }
    else if(board[0][0]==board[0][2] && board[0][0]=='X' && board[0][1]=='?')
    {
          *cRow=0; *cCol=1;
           return 1;
    }

    else if(board[0][1]==board[1][1] && board[0][1]=='X' && board[2][1]=='?')//column2
    {
         *cRow=2;*cCol=1;
          return 1;
    }
    else if(board[1][1]==board[2][1] && board[1][1]=='X' && board[0][1]=='?')
    {
         *cRow=0;*cCol=1;
          return 1;
    }
    else if(board[1][0]==board[1][2] && board[1][0]=='X' && board[1][1]=='?')
    {
         *cRow=1;*cCol=1;
          return 1;
    }

    else if(board[0][2]==board[1][2] && board[0][2]=='X' && board[2][2]=='?')//column3
    {
         *cRow=2;*cCol=2;
          return 1;
    }
    else if(board[1][2]==board[2][2] && board[1][2]=='X' && board[0][2]=='?')
    {
         *cRow=0;*cCol=2;
          return 1;
    }
    else if(board[1][0]==board[1][2] && board[1][0]=='X' && board[1][1]=='?')
    {
         *cRow=1;*cCol=1;
         return 1;
    }

    else if(board[0][0]==board[1][1] && board[0][0]=='X' && board[2][2]=='?')//condition for left diagonal
    {
         *cRow=2;*cCol=2;
          return 1;
    }
    else if(board[1][1]==board[2][2] && board[1][1]=='X' && board[0][0]=='?')
    {
         *cRow=0;*cCol=0;
         return 1;
    }
    else if(board[0][0]==board[2][2] && board[0][0]=='X' && board[1][1]=='?')
    {
         *cRow=1;*cCol=1;
          return 1;
    }

    else if(board[0][2]==board[1][1] && board[0][2]=='X' && board[2][0]=='?')// condition for right diagonal
    {
        *cRow=2;*cCol=0;
         return 1;
    }
    else if(board[1][1]==board[2][0] && board[1][1]=='X' && board[0][2]=='?')
    {
        *cRow=0;*cCol=2;
        return 1;
    }
    else if(board[0][2]==board[2][0] && board[0][2]=='X' && board[1][1]=='?')
    {
        *cRow=1;*cCol=1;
         return 1;
    }
    else
    return 0;

}


