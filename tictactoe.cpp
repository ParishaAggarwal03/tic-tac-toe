#include <bits/stdc++.h>
using namespace std;
#define HUMAN 2
#define COMPUTER 1
#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void initialize(char board[][SIDE]) // first of all initializes all board values to *
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            board[i][j] = '*';
        }
    }
}

void show_instructions() // as the game starts, this function shows instructions to the user
{
    cout << "\nChoose a cell numbered from 1 to 9 as shown below\n\n";
    cout << "\t\t\t1 | 2 | 3 \n\t\t\t----------\n\t\t\t4 | 5 | 6\n\t\t\t----------\n\t\t\t7 | 8 | 9";
}

void declareWinner(int whoseturn) // check whose the winner
{
    if (whoseturn == COMPUTER)
        cout << "\nCOMPUTER HAS WON\n";
    else
        cout << "\nYOU WON\n";
}

bool rowcrossed(char board[][SIDE]) // check if complete row has been crossed by someone
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}

bool columncrossed(char board[][SIDE]) // check if complete column has been crossed by someone
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}

bool diagonalcrossed(char board[][SIDE]) // check if complete diagonal (of 2) has been crossed by someone
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;

    return false;
}

void showBoard(char board[][SIDE])
{
    cout << "\t\t\t" << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n\t\t\t----------\n\t\t\t" << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n\t\t\t----------\n\t\t\t" << board[2][0] << " | " << board[2][1] << " | " << board[2][2];
}

bool gameOver(char board[][SIDE])
{
    return (rowcrossed(board) || columncrossed(board) || diagonalcrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestscore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -10; // human has won already in the last move and now the game is over
        if (isAI == false)
            return 10; // now is the human turn but computer has already won in the last turn
    }
    else
    {
        if (depth < 9) // index should be within the bounds otherwise its a draw
        {
            if (isAI == true) // this function maximizer
            {
                bestscore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestscore)
                            {
                                bestscore = score;
                            }
                        }
                    }
                }
                return bestscore;
            }
            else // code for human move
            {
                bestscore = 999; // minimizer
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth + 1, true); // true indicates that next turn is of computer
                            board[i][j] = '*';
                            if (score < bestscore)
                            {
                                bestscore = score;
                            }
                        }
                    }
                }
                return bestscore;
            }
        }
        else
            return 0; // its a draw
    }
    return bestscore;
}

int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestscore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false); // false depicts that next move is of human
                board[i][j] = '*';
                if (score > bestscore)
                {
                    bestscore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return (x * 3) + y; // returns index in the form 1,2,3,4,....,9
}

void playTicTacToe(int whoseturn)
{
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;

    initialize(board);
    show_instructions();
    while (gameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        int n;
        if (whoseturn == COMPUTER)
        {
            n = bestMove(board, moveIndex); // most important function which makes use of minimax algorithm
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "\n\nCOMPUTER has put " << COMPUTERMOVE << " in cell " << n + 1 << "\n\n";

            showBoard(board);
            moveIndex++;
            whoseturn = HUMAN;
        }
        else if (whoseturn == HUMAN)
        {
            cout << "\n\nYou can insert in the following positions : ";
            for (int i = 0; i < SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == '*')
                        cout << (i * 3 + j) + 1 << "  ";
                }
            }
            cout << "\n\nENTER THE POSITION = ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = HUMANMOVE;
                cout << "YOU have put " << HUMANMOVE << " in cell " << n + 1 << "\n\n";
                showBoard(board);
                moveIndex++;
                whoseturn = COMPUTER;
            }
            else if (board[x][y] != '*' && n < 9 && n >= 0)
                cout << "\nThis position is already occupied, please one place from the available places\n\n";

            else if (n < 0 || n > 8)
                cout << "\n\nInvalid position\n\n";
        }
    }

    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        cout << "\n\nIt's a draw\n";
    else
    {
        if (whoseturn == COMPUTER)
            whoseturn = HUMAN;
        else if (whoseturn == HUMAN)
            whoseturn = COMPUTER;

        declareWinner(whoseturn);
    }
}

int main()
{
    cout << "\n------------------------------\n"
         << "\tTIC-TAC-TOE\n"
         << "\n------------------------------\n";
    char cont = 'y';
    do
    {
        char choice;
        cout << "Do you want to make first move?(y/n) : ";
        cin >> choice;

        if (choice == 'n')
            playTicTacToe(COMPUTER);
        else if (choice == 'y')
            playTicTacToe(HUMAN);
        else
            cout << "\nINVALID CHOICE\n";

        cout << "\nDo you want to stop playing(y/n): ";
        cin >> cont;
    } while (cont == 'n');
    return 0;
}