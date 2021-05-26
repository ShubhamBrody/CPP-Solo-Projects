//This code is the implementation of MINMAX algorithm to create an AI which plays Tic-Tac-Toe in the optimal way.

#include<iostream>
#include<time.h>
#include<limits>
#include<map>

using namespace std;

class TicTacToe
{
private:
    char board[3][3];
    char human;
    char ai;
    int blocksFilled;
    map<char, int> scores;

public:
    TicTacToe()
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                board[i][j] = ' ';

        scores = {{'X', 1}, {'T', 0}, {'O', -1}};
        human = 'O';
        ai = 'X';
        blocksFilled = 0;
    }

    char getHuman()
    {
        return human;
    }

    char getAi()
    {
        return ai;
    }

    bool isGameOver()
    {
        if(blocksFilled == 9)
            return true;
        else
            return false;
    }

    inline bool isAvailable(int i, int j)
    { if(board[i][j] == ' ')return true; else return false; }

    void boardUpdate(char moveFor, int i,int j)
    {
        board[i][j] = moveFor;
        boardPrint();
    }

    void boardPrint()
    {
        system("cls");
        cout << "***********Top left corner is 0,0 and bottom left is 2,2. choose accordingly.***********" << "\n\n\n";
        for(int i = 0; i < 3; i++)
        {
            cout << "                    " <<board[i][0] << " | "<< board[i][1] << " | " << board[i][2] << endl;
            if(i<2)
            cout << "                   ---+---+---" << endl;
        }
    }

    char checkWinner()
    {
        for(int i = 0; i < 3; i++)
        {
            if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
                return board[i][0];
            if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] != ' ')
                return board[0][i];
        }
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
            return board[0][0];
        if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' ')
            return board[0][2];

        return ' ';
    }

    void playerMove()
    {
        int i, j;
        while(1)
        {
            cout << "PLEASE ENTER THE INDICES FOR YOUR MOVE : \n";
            cin >> i >> j;
            if(!isAvailable(i, j))
            {
                boardPrint();
                cout << "ALREADY OCCUPIED" << endl;
            }
            else
            {
                boardUpdate(human, i, j);
                break;
            }
        }
    }

    int minimax(int depth, bool isMaximising)
    {
        char win = checkWinner();
        if(win!=' ')
        {
            return scores.at(win);
        }
        else if(isGameOver())
        {
            return scores.at('T');
        }

        if(isMaximising)
        {
            int bestScore = -numeric_limits<int>::infinity();
            for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = ai;
                    int score = minimax(depth+1, false);
                    board[i][j] = ' ';
                    if(bestScore < score)
                        bestScore = score;
                }
            }
            return bestScore;
        }
        else
        {
            int bestScore = numeric_limits<int>::infinity();
            for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = human;
                    int score = minimax(depth+1, true);
                    board[i][j] = ' ';
                    if(bestScore > score)
                        bestScore = score;
                }
            }
            return bestScore;
        }
    }

    void enemyMove()
    {
        int bestScore = -numeric_limits<float>::infinity();
        int bestI, bestJ;
        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                board[i][j] = ai;
                int score = minimax(0, false);
                board[i][j] = ' ';
                if(bestScore < score)
                {
                    bestScore = score;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        boardUpdate(ai, bestI, bestJ);
    }

    // old enemy just randomly picked its place.
    /*void enemyMove()
    {
        int i, j;
        do
        {
            i = rand() % 3;
            j = rand() % 3;
        }while(!isAvailable(i, j));
        cout << i << " " << j;
        boardUpdate(ai, i, j);
    }*/

};


int main()
{
    srand(time(0));
    TicTacToe t;
    bool gameStart = true;
    t.boardPrint();
    int m = 1;
    while(gameStart)
    {
        bool anyoneWin = false;
        if(t.isGameOver())
        {
            cout << "TIE!!! NO ONE WON THIS GAME\n";
            gameStart = false;
            continue;
        }

        if(m == 0)
        {
            t.playerMove();
            if(t.checkWinner() == t.getHuman())
            {
                cout << "HUMAN WINS!!!" << endl;
                gameStart = false;
            }
        }

        else
        {
            t.enemyMove();
            if(t.checkWinner() == t.getAi())
            {
                cout << "COMPUTER WINS!!!" << endl;
                gameStart = false;
            }
        }
        m = 1-m;
    }
}
