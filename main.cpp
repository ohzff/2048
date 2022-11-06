#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "keyboard.hpp"
using namespace std;
typedef long long ll;
const int inf = 15;
const int N = 4;
const int M = 4;

ll a[inf][inf];

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
    if(num==224||num==-32)return -1;
	else return 0;
}

void keyboard_check ()
{
    while (true)
    {
        printf ("%d\n", check (keyboard ()));
    }
}

int main ()
{
    keyboard_check ();
    return 0;
}