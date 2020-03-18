#include <iostream>
#include <time.h>
using namespace std;
enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };
struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;

};


class MinesweeperBoard
{
    Field board[100][100];
    int width;
    int height;
    GameState condition;
    int mines;

public:
    MinesweeperBoard();
    MinesweeperBoard(int width, int height, GameMode mode );
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    bool hasMine(int x, int y) const;
    int countMines(int x, int y) const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    GameState getGameState() const;
    char getFieldInfo(int x, int y) const;
    void debug_display() const;
};
MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode ) {
    srand(time(NULL));
    int SizeMin = width * height;
    int lvl;
    int a, b;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            board[i][j].isRevealed = false;
            board[i][j].hasMine = false;
            board[i][j].hasFlag = false;
        }
    }
    if (mode == DEBUG) {
        lvl = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < height; j++) {
                if (i == j) {
                    board[i][j].hasMine = true;
                }
                if ((j == 0) && (i % 2 == 0)) {
                    board[i][j].hasMine = true;
                }
                if (i == 0) {
                    board[i][j].hasMine = true;
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (board[i][j].hasMine == 1) {
                    lvl += 1;
                }
            }
        }
    }


    switch (mode) {
        case EASY:
            lvl = SizeMin * 0.1;
            while (lvl != 0) {
                a = rand() % height;
                b = rand() % width;
                if (board[a][b].hasMine == 0) {
                    board[a][b].hasMine == 1;
                }
                lvl += 1;
            }
        case NORMAL:
            lvl = SizeMin * 0.2;
            while (lvl != 0) {
                a = rand() % height;
                b = rand() % width;
                if (board[a][b].hasMine == 0) {
                    board[a][b].hasMine == 1;
                }
                lvl += 1;
            }
        case HARD:
            lvl = SizeMin * 0.3;
            while (lvl != 0) {
                a = rand() % height;
                b = rand() % width;
                if (board[a][b].hasMine == 0) {
                    board[a][b].hasMine == 1;
                }
                lvl += 1;
            }
    }
}
int MinesweeperBoard::getBoardWidth() const
{
    return width;
}
int MinesweeperBoard::getBoardHeight() const
{
    return height;
}
int MinesweeperBoard::getMineCount() const {
    return mines;
}

bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if(board[x][y].hasFlag==true)
    {
        return true;
    }
    if(x>=width or x<0 or y>=height or y<0 or board[x][y].hasFlag==false or board[x][y].isRevealed==true)
    {
        return false;
    }
}


//int MinesweeperBoard::getMineCount() const;
int MinesweeperBoard::countMines(int x, int y) const {

    if(!hasMine(x,y))
        return -1;

    int ile=0;

    for(int i=-1; i<=1; i++)
        for(int j=-1; j<=1; j++)
            if( !(x+i<0 or y+j<0 or x+i>width or y+j> height))
                if(hasMine(x,y))
                    ile++;

    return ile;
}

void MinesweeperBoard::toggleFlag(int x, int y)
{
    if(board[x][y].isRevealed==false)
    {
        if(board[x][y].hasFlag==true)
        {
            board[x][y].hasFlag==false;
        }
        else if (board[x][y].hasFlag==false)
        {
            board[x][y].hasFlag==true;
        }
    }
    if(board[x][y].isRevealed==true or x>width or x<0 or y>height or y<0 or condition==FINISHED_LOSS or condition==FINISHED_WIN )
    {}
}
void MinesweeperBoard::revealField(int x, int y)
{
    board[x][y].isRevealed==true;
    if(board[x][y].isRevealed==true or x>=width or x<0 or y>=height or y<0 or condition==FINISHED_WIN or condition==FINISHED_LOSS or board[x][y].hasFlag==true)
    {}
    if(board[x][y].isRevealed==false and board[x][y].hasMine==false)
    {
        board[x][y].isRevealed==true;
    }
    if(board[x][y].isRevealed==false and board[x][y].hasMine==true)
    {
        for(int i=0 ; i<width ; i++){
            for(int j=0; j<height ; j++) {
                if (board[i][j].isRevealed == true) {
                    board[x][y].isRevealed == true;
                    condition == FINISHED_LOSS;
                } else {
                    board[x][y].isRevealed == true;
                    board[x][y].hasMine == false;
                    int p = rand() % width;
                    int q = rand() % height;
                    board[p][q].hasMine == true;
                }
            }
        }
    }
    else{
        board[x][y].isRevealed == true;
        condition==FINISHED_LOSS;
    }
}


GameState MinesweeperBoard::getGameState() const
{
    if(condition == FINISHED_LOSS)
    {
        return FINISHED_LOSS;
    }
    if(condition == FINISHED_WIN and mines==0 )
    {
        return FINISHED_WIN;
    }
    else {
        return RUNNING;
    }
}

bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if(board[x][y].isRevealed==true)
        return true;
    else
        return false;
}


MinesweeperBoard::MinesweeperBoard()
{
    width=10;
    height=10;
    for(int i=0; i<width ; i++){
        for(int j=0; j<height ; j++) {
            board[i][j].hasFlag= false;
            board[i][j].isRevealed=false;
            board[i][j].hasMine=false;
        }}
    board[0][0].hasMine=true;
    board[1][1].isRevealed=true;
    board[2][0].hasMine=true;
    board[2][0].hasFlag=true;

}

void MinesweeperBoard::debug_display() const
{
    for(int i=0; i<width ; i++ ) {
        for (int j = 0; j < height ; j++) {
            cout << "[";
            if (board[i][j].hasMine){
                cout<<"M";
            }
            else
            {
                cout<<".";
            }
            if(board[i][j].isRevealed)
            {
                cout<<"O";
            }
            else
            {
                cout<<".";
            }
            if(board[i][j].hasFlag)
            {
                cout<<"f";
            }
            else
            {
                cout<<".";
            }
            cout<<"]";

        }
        cout<<endl;
    }}
char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if(x>width or x<0 or y>height or y<0) return '#';
    if(board[x][y].isRevealed== false and board[x][y].hasFlag==false ) return '_';
    if(board[x][y].isRevealed==true and board[x][y].hasMine==true) return 'X';
    if(board[x][y].isRevealed== true and countMines(x,y) == 0) return ' ';
    if(board[x][y].isRevealed==true and countMines( x,y)!=0 )
    {
        if(countMines(x,y)==1) {return '1';
        }
        if(countMines(x,y)==2) {return '2';
        }
        if(countMines(x,y)==3) {return '3';
        }
        if(countMines(x,y)==4) {return '4';
        }
        if(countMines(x,y)==5) {return '5';
        }
        if(countMines(x,y)==6) {return '6';
        }
        if(countMines(x,y)==7) {return '7';
        }
        if(countMines(x,y)==8) {return '8';
        }

    }
}

int main()
{
    
    MinesweeperBoard board = MinesweeperBoard(9, 7, EASY);
    board.debug_display();
}