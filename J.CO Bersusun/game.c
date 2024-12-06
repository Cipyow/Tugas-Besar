#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "highscore.h"
#include "umum.h"

void mmenu() {
    int pilihan;
    char playerName[MAX_NAME_LEN] = ""; // Variabel lokal untuk nama pemain

    while (1) {
        system("cls");
        gotoxy(65,12); printf("=====================================");
        gotoxy(65,13); printf("           TOWER OF HANOI");
        gotoxy(65,14); printf("=====================================");
        gotoxy(65,15); printf("[1] MULAI PERMAINAN\n");
        gotoxy(65,16); printf("[2] CARA BERMAIN\n");
        gotoxy(65,17); printf("[3] HIGHSCORES\n");
        gotoxy(65,18); printf("[4] KELUAR\n");
        gotoxy(65,19); printf("=====================================");
        gotoxy(65,21); printf("Pilih opsi (1-4): ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            gotoxy(65,23); printf("Input tidak valid! Masukkan angka 1-4.");
            continue;
        }

        switch (pilihan) {
            case 1: 
                mulai(playerName); // Teruskan nama pemain (bisa kosong)
                break;
            case 2: 
                howtoplay(); 
                break;
            case 3: 
                highscore(); 
                break;
            case 4: 
                keluar(); 
                break;
            default:
                gotoxy(65,23); printf("Pilihan tidak valid! Tekan Enter untuk kembali ke menu.");
                getchar(); getchar();
        }
    }
}


// Fungsi mulai permainan
void mulai(char *playerName) {
    int jumlahCakram;
    time_t start_time, end_time;

    system("cls");
    gotoxy(65,14); printf("=====================================");
    gotoxy(65,15); printf("           MULAI PERMAINAN");
    gotoxy(65,16); printf("=====================================");

    // Jika nama belum ada, minta input
    if (strlen(playerName) == 0) {
        gotoxy(65,18); printf("Masukkan nama Anda: ");
        getchar(); // Membersihkan newline dari buffer
        fgets(playerName, MAX_NAME_LEN, stdin);
        playerName[strcspn(playerName, "\n")] = '\0'; // Hapus newline
    }

    gotoxy(65,19); printf("Masukkan jumlah cakram (3-10): ");
    while (scanf(" %d", &jumlahCakram) != 1 || jumlahCakram < 3 || jumlahCakram > 10) {
        while (getchar() != '\n');
        gotoxy(65,20); printf("Input tidak valid! Masukkan angka 3-10: ");
    }
    getchar();

    inisialisasiTiang(jumlahCakram);
    minimalMoves = (1 << jumlahCakram) - 1; // Menghitung 2^n - 1
    totalMoves = 0; // Reset langkah pemain

    start_time = time(NULL);
    pindahCakramManual(jumlahCakram);
    end_time = time(NULL);

    if (cekKondisiMenang(jumlahCakram)) {
        time_t completion_time = end_time - start_time;

        // Tambahkan skor pemain
        int previousPlayerCount = player_count;
        update_or_add_player(playerName, jumlahCakram, completion_time);
        sort_scores();
        save_scores();

        system("cls");
        gotoxy(65,10); printf("=======================================================");
        gotoxy(65,12); printf("   SELAMAT, %s!", playerName);
        gotoxy(65,16); printf("   Kamu telah menyelesaikan permainan dengan %d cakram.", jumlahCakram);
        gotoxy(65,17); printf("   Total langkah: %d | Langkah Minimal: %d", totalMoves, minimalMoves);
        gotoxy(65,18); printf("   Waktu penyelesaian: %ld detik.", completion_time);
        gotoxy(65,21); printf("=======================================================");
        
        if (player_count > 0 && strcmp(players[0].name, playerName) == 0) {
            if (previousPlayerCount == 0 || players[0].score > players[1].score || 
                (players[0].score == players[1].score && players[0].completion_time < players[1].completion_time)) {
                gotoxy(65,14); printf("*** ANDA MENDAPATKAN HIGHSCORE TERBARU! ***");
            }
        }        
    } else {
        system("cls");
        gotoxy(65,10); printf("=====================================");
        gotoxy(65,12); printf("   PERMAINAN BERAKHIR (GAME OVER)");
        gotoxy(65,13); printf("   Skor tidak dimasukkan ke highscore.");
        gotoxy(65,15); printf("=====================================");
    }

    // Opsi untuk bermain lagi
    gotoxy(65,27); printf("Apa yang ingin Anda lakukan selanjutnya?");
    gotoxy(65,29); printf("[1] Main lagi");
    gotoxy(65,30); printf("[2] Lihat highscore");
    gotoxy(65,31); printf("[3] Kembali ke menu utama");
    gotoxy(65,33); printf("Pilihan Anda: ");

    int pilihan;
    if (scanf(" %d", &pilihan) != 1 || (pilihan != 1 && pilihan != 2) && pilihan != 3) {
        while (getchar() != '\n');
        gotoxy(65,28); printf("Input tidak valid! Kembali ke menu utama.");
        return;
    }

    if (pilihan == 1) {
        mulai(playerName); // Main lagi tanpa meminta nama ulang
    } else if (pilihan == 2) {
        highscore();
    } else {
        return; // Kembali ke menu utama
    }
}



// Fungsi cara bermain
void howtoplay() {
    system("cls");
    gotoxy(41,10); printf("=======================================================================================================");
    gotoxy(41,11); printf("           				CARA DAN ATURAN BERMAIN");
    gotoxy(41,12); printf("=======================================================================================================");
    gotoxy(41,14); printf("1. Pindahkan seluruh cakram dari tiang awal (A) ke tiang tujuan (C).");
    gotoxy(41,15); printf("2. Hanya satu cakram yang boleh dipindahkan dalam satu waktu.");
    gotoxy(41,16); printf("3. Cakram yang lebih besar tidak boleh diletakkan di atas cakram yang lebih kecil.");
    gotoxy(41,17); printf("4. Highscore akan dihitung ketika pemain dapat menyelesaikan permainan.");
    gotoxy(41,18); printf("5. Jumlah cakram dan waktu untuk menyelesaikan permaianan memengaruhi posisi pemain pada highscores.");
    gotoxy(41,20); printf("=======================================================================================================");
    gotoxy(41,22); printf("Tekan Enter untuk kembali ke menu utama");
    getchar(); getchar();
}

// Fungsi melihat skor tertinggi

// Fungsi keluar
void keluar() {
    system("cls");
    gotoxy(65,19); printf("=====================================");
    gotoxy(65,20); printf("            TERIMA KASIH!");
    gotoxy(65,21); printf("=====================================");
    exit(0);
}

// Fungsi untuk menginisialisasi tiang
void inisialisasiTiang(int cakram) {
    for (int i = 0; i < cakram; i++) {
        tiang[0][i] = cakram - i;
        tiang[1][i] = 0;
        tiang[2][i] = 0;
    }
    tinggi[0] = cakram;
    tinggi[1] = 0;
    tinggi[2] = 0;
}

// Fungsi menggambar tiang
void gambarTiang(int cakram) {
    system("cls");
    int xTengah[3] = {65, 85, 105};
    int tinggiTiang = cakram + 2;

    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < tinggi[t]; i++) {
            int ukuran = tiang[t][i];
            gotoxy(xTengah[t] - ukuran, tinggiTiang - (i-10));
            for (int j = 0; j < 2 * ukuran + 1; j++) {
                printf("=");
            }
        }
    }

    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < tinggiTiang + 1; i++) {
            gotoxy(xTengah[t], i+10);
            printf("|");
        }
    }

    gotoxy(xTengah[0], tinggiTiang + 11); printf("A");
    gotoxy(xTengah[1], tinggiTiang + 11); printf("B");
    gotoxy(xTengah[2], tinggiTiang + 11); printf("C");
}

// Fungsi memindahkan cakram secara manual
void pindahCakramManual(int cakram) {
    char sumber, tujuan;
    int sumberIndex, tujuanIndex;

    while (!cekKondisiMenang(cakram)) {
        gambarTiang(cakram);

        // Tampilkan jumlah langkah
        gotoxy(65,5); printf("Total langkah: %d | Langkah minimal: %d", totalMoves, minimalMoves);

        // Petunjuk untuk keluar
        gotoxy(65,25); printf("Ketik 'X' untuk kembali ke menu utama.");

        gotoxy(65,27); printf("Masukkan tiang sumber (A, B, C): ");
        scanf(" %c", &sumber);
        if (sumber == 'X') {
            return; // Keluar dari fungsi dan kembali ke menu utama
        }

        gotoxy(65,28); printf("Masukkan tiang tujuan (A, B, C): ");
        scanf(" %c", &tujuan);
        if (tujuan == 'X') {
            return; // Keluar dari fungsi dan kembali ke menu utama
        }

        sumberIndex = sumber - 'A';
        tujuanIndex = tujuan - 'A';

        if (sumberIndex < 0 || sumberIndex > 2 || tujuanIndex < 0 || tujuanIndex > 2) {
            gotoxy(65,31); printf("Input tidak valid! Tekan Enter untuk mencoba lagi.");
            getchar(); getchar();
            continue;
        }

        if (pindahCakram(sumberIndex, tujuanIndex, cakram)) {
            totalMoves++; // Tambahkan langkah jika berhasil
        } else {
            gotoxy(65,31); printf("Tekan Enter untuk mencoba lagi.");
            getchar(); getchar();
        }
    }

    gambarTiang(cakram);
    gotoxy(65,10); printf("Selamat! Anda telah menyelesaikan permainan!");
}


// Fungsi memindahkan cakram
int pindahCakram(int sumber, int tujuan, int cakram) {
    if (tinggi[sumber] == 0) {
        gotoxy(65,30); printf("Tiang sumber kosong! Tidak ada cakram untuk dipindahkan.");
        return 0;
    }

    if (tinggi[tujuan] > 0 && tiang[sumber][tinggi[sumber] - 1] > tiang[tujuan][tinggi[tujuan] - 1]) {
        gotoxy(65,30); printf("Cakram yang lebih besar tidak boleh di atas cakram yang lebih kecil.");
        return 0;
    }

    // Pindahkan cakram
    tiang[tujuan][tinggi[tujuan]] = tiang[sumber][tinggi[sumber] - 1];
    tinggi[tujuan]++;
    tinggi[sumber]--;
    return 1; // Langkah valid
}

// Fungsi cek kondisi menang
int cekKondisiMenang(int cakram) {
    return (tinggi[2] == cakram);
}
