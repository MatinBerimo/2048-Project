#include <conio.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <cmath>
#include <fstream>
using namespace std;

const int colors[] = {
    0x08, 0x0E, 0x0A, 0x0B, 0x09, 0x0D, 0x0C, 0x0E, 0x0A, 0x0B, 0x09, 0x0D};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int score = 0;
int matrix[4][4] = {{0}};

void setColor(int value)
{
    int color = 0;
    switch (value)
    {
    case 2:
        color = 0x0A;
        break; // رنگ سبز
    case 4:
        color = 0x0C;
        break; // رنگ قرمز
    case 8:
        color = 0x0E;
        break; // رنگ زرد
    case 16:
        color = 0x0D;
        break; // رنگ بنفش
    case 32:
        color = 0x09;
        break; // رنگ آبی
    case 64:
        color = 0x0B;
        break; // رنگ آبی روشن
    case 128:
        color = 0x0F;
        break; // رنگ سفید
    case 256:
        color = 0x07;
        break; // رنگ خاکی
    case 512:
        color = 0x0A;
        break; // رنگ سبز
    case 1024:
        color = 0x0C;
        break; // رنگ قرمز
    case 2048:
        color = 0x0E;
        break; // رنگ زرد
    }
    SetConsoleTextAttribute(hConsole, color); 
}

void saveGame()
{
    ofstream file("savegame.dat");
    if (file.is_open())
    {
        file << score << endl;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                file << matrix[i][j] << " ";
        file.close();
    }
}

bool loadplay()
{
    ifstream file("savegame.dat");
    if (file.is_open())
    {
        file >> score;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                file >> matrix[i][j];
        file.close();
        return true;
    }
    return false;
}

void randomize()
{
    int indexzero = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (matrix[i][j] == 0)
                indexzero++;

    if (indexzero== 0)
        return;

    int x = rand() % indexzero;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] == 0 && x--==0)
            {
                matrix[i][j] = 2;
                return;
            }
        }
    }
}

void printboard()
{
    system("cls");
    cout << "  ------------------------------\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "  |";
        for (int j = 0; j < 4; j++)
        {
            setColor(matrix[i][j]);
            if (matrix[i][j] == 0)
                cout << "      ";
            else
            cout << " " << setw(4) << matrix[i][j] << " ";  
            SetConsoleTextAttribute(hConsole, 0x07);
            cout << "|";
        }
        cout << "\n  ------------------------------\n";
    }
}

bool moveleft()
{
    bool changed = false;
    for (int i = 0; i < 4; i++)
    {
        int select = 0;
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] != 0)
            {
                if (j != select)
                {
                    matrix[i][select] = matrix[i][j];
                    matrix[i][j] = 0;
                    changed = true;
                }
                select++;
            }
        }
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == matrix[i][j + 1] && matrix[i][j] != 0)
            {
                matrix[i][j] *= 2;
                score += matrix[i][j];
                matrix[i][j + 1] = 0;
                changed = true;
                for (int k = j + 1; k < 3; k++)
                {
                    matrix[i][k] = matrix[i][k + 1];
                    matrix[i][k + 1] = 0;
                }
            }
        }
    }
    return changed;
}

bool moveright()
{
    bool changed = false;
    for (int i = 0; i < 4; i++)
    {
        int select = 3;
        for (int j = 3; j >= 0; j--)
        {
            if (matrix[i][j] != 0)
           {
                if (j != select)
                {
                    matrix[i][select] = matrix[i][j];
                    matrix[i][j] = 0;
                    changed = true;
                }
                select--;
            }
        }
        for (int j = 3; j > 0; j--)
        {
            if (matrix[i][j] == matrix[i][j - 1] && matrix[i][j] != 0)
            {
                matrix[i][j] *= 2;
                score += matrix[i][j];
                matrix[i][j - 1] = 0;
                changed = true;
                for (int k = j - 1; k > 0; k--)
                {
                    matrix[i][k] = matrix[i][k - 1];
                    matrix[i][k - 1] = 0;
                }
            }
        }
    }
    return changed;
}

bool moveup()
{
    bool changed = false;
    for (int j = 0; j < 4; j++)
    {
        int select = 0;
        for (int i = 0; i < 4; i++)
        {
            if (matrix[i][j] != 0)
            {
                if (i != select)
                {
                    matrix[select][j] = matrix[i][j];
                    matrix[i][j] = 0;
                    changed = true;
                }
                select++;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (matrix[i][j] == matrix[i + 1][j] && matrix[i][j] != 0)
            {
                matrix[i][j] *= 2;
                score += matrix[i][j];
                matrix[i + 1][j] = 0;
                changed = true;
                for (int k = i + 1; k < 3; k++)
                {
                    matrix[k][j] = matrix[k + 1][j];
                    matrix[k + 1][j] = 0;
                }
            }
        }
    }
    return changed;
}

bool movedown()
{
    bool changed = false;
    for (int j = 0; j < 4; j++)
    {
        int select = 3;
        for (int i = 3; i >= 0; i--)
        {
            if (matrix[i][j] != 0)
            {
                if (i != select)
                {
                    matrix[select][j] = matrix[i][j];
                    matrix[i][j] = 0;
                    changed = true;
                }
                select--;
            }
        }
        for (int i = 3; i > 0; i--)
        {
            if (matrix[i][j] == matrix[i - 1][j] && matrix[i][j] != 0)
            {
                matrix[i][j] *= 2;
                score += matrix[i][j];
                matrix[i - 1][j] = 0;
                changed = true;
                for (int k = i - 1; k > 0; k--)
                {
                    matrix[k][j] = matrix[k - 1][j];
                    matrix[k - 1][j] = 0;
                }
            }
        }
    }
    return changed;
}

bool winner()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (matrix[i][j] == 2048)
                return true;
    return false;
}

bool loser()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (matrix[i][j] == 0)
                return false;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == matrix[i][j + 1])
                return false;
            if (matrix[j][i] == matrix[j + 1][i])
                return false;
        }
    }
    return true;
}

void restart()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = 0;
    randomize();
    randomize();
    score = 0;
}

int showMenu()
{
    system("cls");
    cout << "==============================\n";
    cout << "      Welcome to 2048!\n";
    cout << "==============================\n";
    cout << "1. Play a New Game\n";
    cout << "2. Continue Previous Game\n";
    cout << "3. Exit\n";
    cout << "==============================\n";
    cout << "Enter Choice: ";

    int choice;
    cin >> choice;
    return choice;
}

int main()
{
    SetConsoleOutputCP(65001);
    srand(time(NULL));

    while (true)
    {
        int choice = showMenu();

        switch (choice)
        {
        case 1:
            restart();
            break;
        case 2:
            if (!loadplay())
            {
                cout << "No saved game found!\n";
                _getch();
            }
            break;
        case 3:
            system("cls");
            cout << "#####                                                             ### ### ### \n";
            cout << "#     # #        ##     ##     ##     ##     ##   #    # ######    ### ### ### \n";
            cout << "#       #       #  #   #  #   #  #   #  #   #  #  #    # #         ### ### ### \n";
            cout << " #####  #      #    # #    # #    # #    # #    # #    # #####      #   #   # \n";
            cout << "      # #      ###### ###### ###### ###### ###### #    # # \n";
            cout << "#     # #      #    # #    # #    # #    # #    #  #  #  #         ### ### ### \n";
            cout << " #####  ###### #    # #    # #    # #    # #    #   ##   ######    ### ### ### \n";
            Sleep(10000);
            return 0;
        default:
            cout << "Invalid choice!\n";
            _getch();
            continue;
        }
        char move;
        while (true)
        {
            if (winner())
            {
                printboard();
                cout << "Score: " << score << "\nYou Win!\n";
                _getch();
                break;
            }
            if (loser())
            {
                printboard();
                cout << "Score: " << score << "\nGame Over!\n";
                _getch();
                break;
            }
            printboard();
            cout << "Controls: Arrow Keys (← ↑ → ↓)\nPress R to Restart, S to Save, E to Exit\n";
            cout << "Score: " << score << endl;

            move = _getch();
            bool moved = false;
            switch (move)
            {
            case 3:
                return 0;
            case 75:
                moved = moveleft();
                break;
            case 77:
                moved = moveright();
                break;
            case 72:
                moved = moveup();
                break;
            case 80:
                moved = movedown();
                break;
            case 'r':
            case 'R':
                restart();
                moved = false;
                break;
            case 's':
            case 'S':
                saveGame();
                cout << "Game Saved!\n";
                _getch();
                break;
            case 'e':
            case 'E':
                system("cls");
                cout << "Do You Want To Save This Checkpoint ???" << endl << "1.Yes" << endl << "2.No" << endl << ":";
                int choice2 = _getch();
                switch (choice2)
                {
                    case '1':
                        system("cls");
                        saveGame();
                        restart();
                        cout << "#####                                                             ### ### ### \n";
                        cout << "#     # #        ##     ##     ##     ##     ##   #    # ######    ### ### ### \n";
                        cout << "#       #       #  #   #  #   #  #   #  #   #  #  #    # #         ### ### ### \n";
                        cout << " #####  #      #    # #    # #    # #    # #    # #    # #####      #   #   # \n";
                        cout << "      # #      ###### ###### ###### ###### ###### #    # # \n";
                        cout << "#     # #      #    # #    # #    # #    # #    #  #  #  #         ### ### ### \n";
                        cout << " #####  ###### #    # #    # #    # #    # #    #   ##   ######    ### ### ### \n";
                        Sleep(10000);
                        return 0;
                        break;
                    case '2':
                        system("cls");
                        restart();
                        cout << "#####                                                             ### ### ### \n";
                        cout << "#     # #        ##     ##     ##     ##     ##   #    # ######    ### ### ### \n";
                        cout << "#       #       #  #   #  #   #  #   #  #   #  #  #    # #         ### ### ### \n";
                        cout << " #####  #      #    # #    # #    # #    # #    # #    # #####      #   #   # \n";
                        cout << "      # #      ###### ###### ###### ###### ###### #    # # \n";
                        cout << "#     # #      #    # #    # #    # #    # #    #  #  #  #         ### ### ### \n";
                        cout << " #####  ###### #    # #    # #    # #    # #    #   ##   ######    ### ### ### \n";
                        Sleep(10000);
                        return 0;
                        break;
                    
                    default:
                        cout << "Invalid choice!\n";
                        choice2 = _getch();
                        continue;

                }
                break;
            }
            if (moved)
                randomize();
        }
    }
    return 0;
}