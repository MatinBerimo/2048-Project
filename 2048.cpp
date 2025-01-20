#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int matrix[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

void randomize()
{
		
	int count=0,randomi=0,randomj=0;
	while(count<1){
		moji:
		randomi=rand()%4;
		randomj=rand()%4;
		if(matrix[randomi][randomj]==0)
		matrix[randomi][randomj]=2;
		else
		goto moji;
		count++;
	}
}
void printboard()
{
	system("cls");

	for(int i=0;i<4;i++){
		cout<<"[";
		for(int j=0;j<4;j++){
			if((to_string(matrix[i][j]).size())==1){
				cout<<"  "<<matrix[i][j]<<" ";
			}
			else if((to_string(matrix[i][j]).size())==2){
				cout<<" "<<matrix[i][j]<<" ";
			}
			else if((to_string(matrix[i][j]).size())==3){
				cout<<" "<<matrix[i][j];
				
			}
			else if((to_string(matrix[i][j]).size())==4){
				cout<<matrix[i][j];
			}
			if(j!=3)
			{
				cout << " ";
			}
		}
		cout<<"]";
		cout<<endl;
	}
}

void moveright() {
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (matrix[i][j] != 0) {
                int k = j;
                while (k < 3 && matrix[i][k + 1] == 0) {
                    matrix[i][k + 1] = matrix[i][k];
                    matrix[i][k] = 0;
                    k++;
                }
                if (k < 3 && matrix[i][k] == matrix[i][k + 1]) {
                    matrix[i][k + 1] += matrix[i][k];
                    matrix[i][k] = 0;
                }
            }
        }
    }
}

void moveleft() {
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (matrix[i][j] != 0) {
                int k = j;
                while (k > 0 && matrix[i][k - 1] == 0) {
                    matrix[i][k - 1] = matrix[i][k];
                    matrix[i][k] = 0;
                    k--;
                }
                if (k > 0 && matrix[i][k - 1] == matrix[i][k]) {
                    matrix[i][k - 1] += matrix[i][k];
                    matrix[i][k] = 0;
                }
            }
        }
    }
}

void moveup() {
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            if (matrix[i][j] != 0) {
                int k = i;
                while (k > 0 && matrix[k - 1][j] == 0) {
                    matrix[k - 1][j] = matrix[k][j];
                    matrix[k][j] = 0;
                    k--;
                }
                if (k > 0 && matrix[k - 1][j] == matrix[k][j]) {
                    matrix[k - 1][j] += matrix[k][j];
                    matrix[k][j] = 0;
                }
            }
        }
    }
}
void movedown() {
    for (int j = 0; j < 4; j++) {
        for (int i = 2; i >= 0; i--) {
            if (matrix[i][j] != 0) {
                int k = i;
                while (k < 3 && matrix[k + 1][j] == 0) {
                    matrix[k + 1][j] = matrix[k][j];
                    matrix[k][j] = 0;
                    k++;
                }
                if (k < 3 && matrix[k + 1][j] == matrix[k][j]) {
                    matrix[k + 1][j] += matrix[k][j];
                    matrix[k][j] = 0;
                }
            }
        }
    }
}
bool winner(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(matrix[i][j]==2048){
                return true;
            }
        }
    }
    return false;
}
bool loser()
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(matrix[i][j]==0){
                return true;
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            if(matrix[i][j]==matrix[i][j+1]){
                return true;
            }
            if(matrix[j][i]==matrix[j+1][i]){
                return true;
            }
        }
    }
    return false;
}

int main() {
    srand(time(NULL));
    randomize();
    char move;
    while (true) {
    	randomize();
        printboard();
        cin >> move;
        switch (move) {
            case 'a':
                moveleft();
                break;
            case 'd':
                moveright();
                break;
            case 's':
                movedown();
                break;
            case 'w':
                moveup();
                break;
            case 'r':
            	matrix;
            	randomize();
            	randomize();
            	break;
            }
            if(winner()){
            	cout<<"you win the game";
			}
			if(loser()){
				cout<<"you lose the game";
			}
		}
		return 0;
}