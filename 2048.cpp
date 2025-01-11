#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void printboard(void) {
    srand(time(NULL));
    char matrix[4][9] = {0};
    for(int i =0;i<4;i++) {
        for(int j =0;j<9;j++) {
            if(j%2==0 and j!=0 and j!=8) {
                matrix[i][j] = ',';
            }
            else if(j==8) {
                matrix[i][j] = ']';
            }
            else if(j==0) {
                matrix[i][j] = '[';
            }
            else {
                matrix[i][j] = '0';
            }
        }
    }
    int count=0;
    while(count<2) {
        int randomi = rand() % 4;
        int randomj = (2*(rand()%4))+1;
        if(matrix[randomi][randomj]=='0') {
            matrix[randomi][randomj]='2';
            count++;
        }
    }
    for(int i=0;i<4; i++) {
        for(int j=0; j<9;j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

int main() {
    printboard();
    return 0;
}