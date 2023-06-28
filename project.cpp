#include <bits/stdc++.h> 
#include <cstdlib>
#include <cstring>
using namespace std; 
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

const int N=9;

bool isSafe(int board[][N],int row,int col,int num){
    //Check if num is already in row
    for(int i=0;i<N;i++){
        if(board[row][i]==num) return false;
    }
    //Check if num is already in column
    for(int j=0;j<N;j++){
        if(board[j][col]==num) return false;
    }
    //Check if num is in the same 3*3 box
    int boxrowstart=row-row%3;
    int boxcolumnstart=col-col%3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i+boxrowstart][j+boxcolumnstart]==num) return false;
        }
    }
    return true;
}

void printboard(int grid[N][N]){
    system("cls");
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(j==3||j==6){
                cout<<" | ";
            }
            cout<<grid[i][j]<<" ";
        }
        if(i==2||i==5){
            cout<<endl;
            for(int k=0;k<N;k++){
                cout<<"---";
            }
        }
        cout<<endl;
    }
}

bool SudokuSolver(int board[N][N],int row,int col){
    //if all cells are filled
    if(row==N-1 && col==N) return true;
    //if col are filled in a row change row
    if(col==N){
        row++;
        col=0;
    }
    //Skipping cells already having a value
    if(board[row][col]!=0)
        return SudokuSolver(board,row,col+1);
    //Filling current cells with all possible value
    for(int num=1;num<=9;num++){
        if(isSafe(board,row,col,num)){
            board[row][col]=num;
            if(SudokuSolver(board,row,col+1)){
                return true;
            }
            board[row][col]=0;
        }
    }
    return false;
}

bool isSolvedCompletely(int grid[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j]==0) return false;
        }
    }
    return true;
}

void playGame(int board[N][N]){
    int ch;
    int row,col,num;
    while(true){
        printboard(board);
        cout<<endl<<endl;
        cout << "Unable to solve? Enter -1 as row, col and num to view the solved sudoku."<<endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;
        if(row==-1||col==-1||num==-1){
            SudokuSolver(board,0,0);
            printboard(board);
            cout<<endl;
            cout<<"Better luck next time!"<<endl;
            return;
        }
        if(isSolvedCompletely(board)){
            break;
        }
        row--;
        col--;
        if(!isSafe(board,row,col,num)){
            cout<<"Invalid Move! Try again!!"<<endl;
            continue;
        }
        board[row][col]=num;
    }
    //Check if it has been solved completely
    bool solved=true;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(board[i][j]==0) 
            {
                solved=false;
                break;
            }
    if(solved) 
    {
        cout<<"Congratulations! You have solved the puzzle"<<endl;
        printboard(board);
    }
    else{
        cout<<"Puzzle not solved.Better luck next time!"<<endl;
    }
}

int main()
{
    system("title Sudoku Game @copyassignment");
    system("color B0");   
    int board[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    while(true){
        int choice;
        cout<<endl<<endl;
        cout << "\t\t[1] Solve the Sudoku" << endl;
        cout << "\t\t[2] Unable to solve? View the solved Sudoku" << endl;
        cout << "\t\t[3] Exit" << endl;
        cout << "\t\tEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                playGame(board);
                break;
            case 2:
                if(SudokuSolver(board,0,0)){
                    cout<<"Completely solved Sudoku is: "<<endl;
                    cout<<endl<<endl;
                    for(int row=0;row<N;row++){
                        for(int column=0;column<N;column++){
                            if(column==3||column==6) cout<<" | ";
                            cout<<board[row][column]<<" ";
                        }
                        if(row==2||row==5){
                            cout<<endl;
                            for(int i=0;i<N;i++){
                                cout<<"---";
                            }
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                    cout<<"Better luck next time!"<<endl;
                }
                else{
                    cout<<"No solution found!"<<endl;
                }
                break;
            case 3:
                exit(0);
            default:
                cout<<"Invalid choice"<<endl;
        }
        return 0;
    }
}