#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>

int score=0, check=0;
using namespace std;

int board[4][4];
int dirLine[]= {1, 0, -1, 0};
int dirColumne[]={0, 1, 0, -1};

void newGame();
void addPiece();
void printb();
bool candomove();
void continuegame();

pair<int,int>generateUnoccupiedPosition()
{
    int occupied=1, line, column;
    while(occupied)
    {
        line=rand()%4;
        column=rand()%4;
        if(board[line][column]==0)
            occupied=0;
    }
    return make_pair(line,column);
}

void addPiece()
{
    pair<int,int> pos=generateUnoccupiedPosition();
    board[pos.first][pos.second]=2;
}

void newGame()
{
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            board[i][j]=0;
    addPiece();
    continuegame();
}

void printUI()
{
    system("cls");       //clear screen
    cout<<endl<<right<<setw(30)<<"Score:"<<score<<endl;
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
            if(board[i][j]==0)
                cout<<setw(5)<<" . ";
            else
                cout<<setw(5)<<board[i][j];
        }
        cout<<endl;
    }
    cout<<"n: new game, w: up, s: down, d: right, a:left, q: quit"<<endl;
    cout<<"   w   "<<endl;
    cout<<"a  s  d"<<endl;
}

bool canDoMove(int line,int column,int nextLine,int nextColumn)
{
    if(nextLine<0 || nextColumn<0 || nextLine>=4 || nextColumn>=4 || (board[line][column]!=board[nextLine][nextColumn] && board[nextLine][nextColumn]!=0))
        return false;
    return true;
}

void applyMove(int direction)
{
    int startLine=0,startColumn=0, lineStep=1, columnStep=1;
    switch(direction)
    {
    case 0:
        startLine=3;
        lineStep=-1;
        break;
    case 1:
        startColumn=3;
        columnStep=-1;
        break;
    }
    int movePossible,canAddPiece=0;
    do
    {
        movePossible=0;
        for(int i=startLine;i>=0 && i<4;i+=lineStep)
            for(int j=startColumn;j>=0 && j<4;j+=columnStep)
            {
                int nextI= i+dirLine[direction], nextJ= j+dirColumne[direction];
                //cout<<i<<" "<<j<<" "<<nextI<<" "<<nextJ<<endl;
                if(board[i][j] && canDoMove(i,j,nextI,nextJ))
                {
                    board[nextI][nextJ]+=board[i][j];
                    board[i][j]=0;
                    movePossible=canAddPiece=1;
                }
            }
        printUI();
    }while(movePossible);
    score++;
    if(canAddPiece)
        addPiece();
}

int main()
{
    system("cls");
    ofstream fout;
    cout<<"         2048 Game        "<<endl;
    cout<<"\n\nPress N for new game ";
    cout<<"\nPress R for continue playing ";
    cout<<"\nPress Q for Quiting";
    cout<<"\nEnter your choice: ";
    char c;
    cin>>c;
    switch(c)
    {
    case 'N':
        if(check)
        {
            fout.open("score.txt", ios::app);
            fout<<score<<endl;
            fout.close();
            score=0;
        }
        newGame();
        break;
    case 'R':
        continuegame();
        break;
    case 'Q':
        fout.open("score.txt", ios::app);
        fout<<score<<endl;
        fout.close();
        exit(0);
        break;
    }
    return 0;
}

void continuegame()
{
    srand(time(0));
    char commandtoDir[128];
    commandtoDir['s']=0;
    commandtoDir['d']=1;
    commandtoDir['w']=2;
    commandtoDir['a']=3;
    while(true)
    {
        printUI();
        char move;
        cin>>move;
        if(move=='n')
        {
            check=0;
            newGame();
        }
        else if(move=='q')
        {
            check++;
            main();
        }
        else
        {
            int currentDir=commandtoDir[move];
            applyMove(currentDir);
        }
    }
}