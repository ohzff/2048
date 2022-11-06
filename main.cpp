#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "system_test.hpp"
#include "keyboard.hpp"
#include "win-keyboard.hpp"

using namespace std;
typedef long long ll;
const int inf = 15;
const int N = 4;
const int M = 4;

class Pos
{
    public:
    int x, y;
    Pos () {}
    Pos (int rx, int ry) { x = rx, y = ry; }
};

ll a[inf][inf], blank_top, score;
Pos blank[inf * inf];

inline int keyboard()
{
	return key::getkey();
}

inline int check(int num){
	if(num==72||num=='w'||num=='W')return 1;
	if(num==80||num=='s'||num=='S')return 2;
	if(num==75||num=='a'||num=='A')return 3;
	if(num==77||num=='d'||num=='D')return 4;
	if(num==10)return 13;
	if(num==114)return 7;
	if(num==112)return 8;
	if(num==113)return 9;
	if(num==27)return 27;
    if(num==224||num==-32||num == 91)return -1;
	else return 0;
}

void keyboard_check ()
{
    while (true)
    {
        printf ("%d\n", check (keyboard ()));
    }
}


void init ()
{
    srand (time (NULL));
    int startx = rand () % N + 1, starty = rand () % M + 1;
    a[startx][starty] = 2;
}

void print_area ()
{
    for (int i = 1; i <= N; i ++)
    {
        for (int j = 1; j <= M * 6 + 1; j ++)
        {
            printf ("-");
        }
        printf ("\n|");
        for (int j = 1; j <= M; j ++)
        {
            printf ("%5.lld|", a[i][j]);
        }
        printf ("\n");
    }
    for (int j = 1; j <= M * 6 + 1; j ++) printf ("-");
    printf ("\n");
}

bool status_check ()
{
    blank_top = 0;
    for (int i = 1; i <= N; i ++)
    {
        for (int j = 1; j <= M; j ++)
        {
            if (a[i][j] == 0)
            {
                blank[++ blank_top] = Pos (i, j);
            }
        }
    }
    return blank_top == 0;
}

void move_up ()
{
    for (int j = 1; j <= M; j ++)
    {
        int last = 1;
        for (int i = 1; i <= N; i ++)
        {
            if (a[i][j] != 0)
            {
                if (a[last - 1][j] == a[i][j])
                {
                    a[last - 1][j] <<= 1;
                    score += a[last - 1][j];
                    a[i][j] = 0;
                }
                else
                {
                    a[last][j] = a[i][j];
                    if (i != last) a[i][j] = 0;
                    last ++;
                }
            }
        }
    }
}

void move_down ()
{
    for (int j = 1; j <= M; j ++)
    {
        int last = N;
        for (int i = N; i > 0; i --)
        {
            if (a[i][j] != 0)
            {
                if (a[last + 1][j] == a[i][j])
                {
                    a[last + 1][j] <<= 1;
                    score += a[last + 1][j];
                    a[i][j] = 0;
                }
                else
                {
                    a[last][j] = a[i][j];
                    if (i != last) a[i][j] = 0;
                    last --;
                }
            }
        }
    }
}

void move_left ()
{
    for (int i = 1; i <= N; i ++)
    {
        int last = 1;
        for (int j = 1; j <= M; j ++)
        {
            if (a[i][j] != 0)
            {
                if (a[i][last - 1] == a[i][j])
                {
                    a[i][last - 1] <<= 1;
                    score += a[i][last - 1];
                    a[i][j] = 0;
                }
                else
                {
                    a[i][last] = a[i][j];
                    if (j != last) a[i][j] = 0;
                    last ++;
                }
            }
        }
    }
}

void move_right ()
{
    for (int i = 1; i <= N; i ++)
    {
        int last = M;
        for (int j = M; j > 0; j --)
        {
            if (a[i][j] != 0)
            {
                if (a[i][last + 1] == a[i][j])
                {
                    a[i][last + 1] <<= 1;
                    score += a[i][last + 1];
                    a[i][j] = 0;
                }
                else
                {
                    a[i][last] = a[i][j];
                    if (j != last) a[i][j] = 0;
                    last --;
                }
            }
        }
    }
}

void newpos ()
{
    int pos = rand () % blank_top + 1;
    a[blank[pos].x][blank[pos].y] = 2;
}

int game ()
{
    clear ();
    int read = 0;
    while (true)
    {
        if (status_check ())
        {
            printf (":( You lose! Score %lld.\n", score);
            print_area ();
            return 0;
        }
        newpos ();
        printf (":) Score %lld\n", score);
        print_area ();
        printf ("USE ARROW TO PLAY.\n");
        read = 0;
        while ((read < 1 || read > 4) && read != 9)
        {
            read = check (keyboard ());
            // read = keyverify ();
            // read = 1;
        }
        clear ();
        if (read == 1) move_up ();
        if (read == 2) move_down ();
        if (read == 3) move_left ();
        if (read == 4) move_right ();
        if (read == 9)
        {
            printf (":( Abort! Score %lld.\n", score);
            print_area ();
            return 0;
        }
    }
    return 0;
}

int main ()
{
    init ();
    game ();
    return 0;
}