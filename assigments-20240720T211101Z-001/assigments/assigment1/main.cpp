#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
const char BRIDGE = char(175), WATER = char(219), ISLAND = char(32), CAT = 'X', MOUSE = '*';
const int N = 7, STARVATION_LIMIT = 100;
int MAX_RUNS = 200;
char A[N][N];
void clear_screen();
int RandInt(int s, int e)
{
    srand((unsigned)time(NULL));
    return rand() % (e - s + 1) + s;
}
void MoveMouse(int mp[2])
{
    int i = RandInt(0, 3);

    switch (i) {
    case 0:
        mp[0]--;
        break;
    case 1:
        mp[1]++;
        break;
    case 2:
        mp[0]++;
        break;
    case 3:
        mp[1]--;
        break;
    }
}
void InitialiseScene()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // a[i][j]
            if ((!i) || (i == N - 1) || (!j) || (j == N - 1))
                A[i][j] = WATER;
            else
                A[i][j] = ISLAND;

            A[N / 2][N - 1] = BRIDGE;
           
            A[RandInt(1, N - 2)][RandInt(1, N - 2)] = CAT;
        }
    }
}
void DisplayScene(int mp[2])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if ((row == mp[0]) && (col == mp[1]))
                cout << MOUSE;
            else
                cout << A[row][col];
        }
        cout << endl;
    }
}

int main()
{
    clear_screen();
    int mouse_position[2],
        moves = 0, drowns = 0, escapes = 0, dies = 0;
    while (MAX_RUNS)
    {
        MAX_RUNS--;
        InitialiseScene();
        mouse_position[0] = mouse_position[1] = N / 2;
        DisplayScene(mouse_position);
        moves = 0;
        while (true)
        {
            moves++;
            MoveMouse(mouse_position);
            if (A[mouse_position[0]][mouse_position[1]] == BRIDGE)
            {
                escapes++;
                break;
            }
            if (A[mouse_position[0]][mouse_position[1]] == WATER)
            {
                drowns++;
                break;
            }
            if (A[mouse_position[0]][mouse_position[1]] == CAT ||
                moves == STARVATION_LIMIT)
            {
                dies++;
                break;
            }

            DisplayScene(mouse_position);
        }

        cout << moves << " moves done.\n";
    }
    cout << "Drowned: " << drowns << " Times\n"
        << "Escaped: " << escapes << " Times\n"
        << "Died:\t " << dies << " Times";
    return 0;
}
void clear_screen()
{
    char s[25][80];
    char arr[9][9];
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            for (int x = 0; x< 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    s[i][j] = arr[x][y];
                }
            }
        }
    }
}