#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "highscore.h"
#include "umum.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	system("color 70");
    load_scores();
    mmenu();
	return 0;
}
