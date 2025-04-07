#include <iostream>
#include <clocale>
using namespace std;

const int N = 8; 
int chet = 0;


void printBoard(bool board[N][N]) {
    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < N; ++j) 
        {
            if (board[i][j])
            {
                cout << "0 "; 
            }
            else
            {
                cout << ". "; 
            }
        }
        cout << endl;
    }
    cout << endl;
}


bool isSafe(bool board[N][N], int row, int col)
{
    for (int i = 0; i < row; ++i) 
    {
        if (board[i][col]) 
        {
            return false;
        }
    }

    
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        {
        if (board[i][j])
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j) 
    {
        if (board[i][j])
        {
            return false;
        }
    }

    return true;
}

bool solveNQueens(bool board[N][N], int row)
{
    if (row == N) 
    {
        ++chet;
        cout << chet << "-вое решение" << endl;
        printBoard(board);
        return true;
    }

    bool res = false; 
    for (int col = 0; col < N; ++col)
        {
        if (isSafe(board, row, col)) 
        {
            board[row][col] = true;
            cout << "Попытка поставить ферзя на (" << row << ", " << col << "):\n";
            printBoard(board);
            res = solveNQueens(board, row + 1) || res;
            board[row][col] = false; 
            cout << "Откат на (" << row << ", " << col << "):\n";
            printBoard(board);
        }
    }

    return res;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    bool board[N][N] = { false }; 
    solveNQueens(board, 0); 
    return 0;
}