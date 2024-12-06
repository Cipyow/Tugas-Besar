#ifndef GAME_H
#define GAME_H

#define MAX_CAKRAM 10


int tiang[3][MAX_CAKRAM];
int tinggi[3];
extern int totalMoves;
extern int minimalMoves;
extern int player_count;


void mmenu();
void mulai();
void howtoplay();
void keluar();
void inisialisasiTiang(int cakram);
void gambarTiang(int cakram);
void pindahCakramManual(int cakram);
int pindahCakram(int sumber, int tujuan, int cakram);
int cekKondisiMenang(int cakram);

#endif

