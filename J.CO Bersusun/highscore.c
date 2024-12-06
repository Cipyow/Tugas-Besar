#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "highscore.h"
#include "umum.h"

void highscore() {
    int pilihan;

    while (1) {
        system("cls");
        gotoxy(65,10); printf("==============================================================");
        gotoxy(65,11); printf("                        SKOR TERTINGGI");
        gotoxy(65,12); printf("==============================================================");

        if (player_count == 0) {
            gotoxy(65,14); printf("Belum ada skor yang tercatat.");
        } else {
            gotoxy(65,14); printf("Nama Pemain          | Skor (Cakram)   | Waktu (detik)");
            gotoxy(65,15); printf("--------------------------------------------------------------");
            for (int i = 0; i < player_count && i < 10; i++) {
                gotoxy(65,17 + i); printf("%-20s | %d             	| %ld", players[i].name, players[i].score, players[i].completion_time);
            }
        }

        gotoxy(65,28); printf("==============================================================");
        gotoxy(65,29); printf("[1] Kembali ke menu utama");
        gotoxy(65,30); printf("[2] Reset skor highscore");
        gotoxy(65,32); printf("Pilihan Anda: ");
        if (scanf(" %d", &pilihan) != 1) {
            while (getchar() != '\n');
            gotoxy(65,33); printf("Input tidak valid! Masukkan angka 1 atau 2.");
            continue;
        }

        switch (pilihan) {
            case 1:
                return; // Kembali ke menu utama
            case 2:
                reset_scores();
                break;
            default:
                gotoxy(65,34); printf("Pilihan tidak valid. Tekan Enter untuk mencoba lagi");
                getchar(); getchar();
        }
    }
}

void load_scores() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return;

    player_count = fread(players, sizeof(Player), MAX_PLAYERS, file);
    fclose(file);
}

void save_scores() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) return;

    fwrite(players, sizeof(Player), player_count, file);
    fclose(file);
}

void sort_scores() {
    for (int i = 0; i < player_count - 1; i++) {
        for (int j = i + 1; j < player_count; j++) {
            if (players[i].score < players[j].score || (players[i].score == players[j].score && players[i].completion_time > players[j].completion_time)) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
}

void update_or_add_player(char *name, int score, time_t completion_time) {
    for (int i = 0; i < player_count; i++) {
        if (strcmp(players[i].name, name) == 0) {
            if (players[i].score < score || (players[i].score == score && players[i].completion_time > completion_time)) {
                players[i].score = score;
                players[i].completion_time = completion_time;
            }
            return;
        }
    }
//menambah pemain baru jika max player masih kurang//
    if (player_count < MAX_PLAYERS) {
        strcpy(players[player_count].name, name);
        players[player_count].score = score;
        players[player_count].completion_time = completion_time;
        player_count++;
    }else{
    	if (score > players[MAX_PLAYERS - 1].score || (score == players[MAX_PLAYERS - 1].score && completion_time < players[MAX_PLAYERS - 1].completion_time)){
    		strcpy(players[MAX_PLAYERS - 1].name, name);
    		players[MAX_PLAYERS - 1].score = score;
    		players[MAX_PLAYERS - 1].completion_time = completion_time;
		}
	}
}

void reset_scores() {
    player_count = 0;
    save_scores();
    gotoxy(65,34); printf("Semua skor telah direset! Tekan Enter untuk kembali.");
    getchar(); getchar();
}

