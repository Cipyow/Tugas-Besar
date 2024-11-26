#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

/*MODUL*/
void mmenu();
void mulai();
void aturCakram();
void game();
void howtoplay();
void highscore();
void keluar();
void gotoxy();


int main()
{
	system("color 70");
	mmenu();

    return 0;
}

void mmenu()
{
    int pilihan;

    while (1)
	{
        system("cls||clear");
        printf("\n=====================================\n");
        printf("     - SELAMAT BERMAIN HANOI TOWER -\n");
        printf("=====================================\n");
        printf("[1] MULAI PERMAINAN\n"); 
        printf("[2] CARA BERMAIN\n");
        printf("[3] LIHAT SKOR TERTINGGI\n");
        printf("[4] KELUAR\n");
        printf("=====================================\n");
        printf("PILIH DARI (1-4):");  
        

        if (scanf(" %d", &pilihan) != 1)
		{
            while (getchar() != '\n');
            printf("\nInput tidak valid! MASUKAN ANGKA 1-4. \n ");
            printf("Tekan Enter untuk kembali ke menu utama...");
            getchar();
            continue;
        }

        switch(pilihan)
		{
            case 1:
                mulai();
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
                printf("\nPilihan tidak valid! Masukkan angka 1-4.\n ");
                printf("Tekan Enter untuk kembali ke menu utama");
                getchar(); getchar();
        }
    }
}

void mulai()
{
	char nama[50];
	int cakram;
    system("cls");
    printf("%c%c%c", 555);
    gotoxy(60,5); printf("=====================================");
    gotoxy(60,6); printf("         - MULAI PERMAINAN -");
    gotoxy(60,15); printf("Masukkan nama anda: ");
    scanf("%s", &nama);
    gotoxy(60,16); printf("Masukkan jumlah cakram: ");
    scanf("%d", &cakram);

    if(cakram > 10 || cakram < 3)
    {
        system("cls");
        gotoxy(60,15);
        printf("Jumlah cakram harus diantara 3 dan 10");
        getch();
        mulai();
    }
     
    gotoxy(60,18); printf("=====================================");
    gotoxy(60,19); printf("Tekan Enter untuk kembali ke menu utama");
    getchar(); getchar();
}

void aturCakram()
{
    switch (cakram)
    {
        case 3:
            
            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:

            break;
        default:
            break;
    }
}

void game()
{

}


void howtoplay()
{
    system("cls||clear");
    printf("\n=====================================\n");
    printf("          - CARA BERMAIN -\n");
    printf("=====================================\n");
    printf("1. Pindahkan seluruh cakram dari tiang awal ke tiang tujuan.\n");
    printf("2. Hanya satu cakram yang boleh dipindahkan dalam satu waktu.\n");
    printf("3. Cakram yang lebih besar tidak boleh diletakkan di atas cakram yang lebih kecil.\n");
    printf("4. Selesaikan dengan jumlah langkah sesedikit mungkin.\n");
    printf("=====================================\n");
    printf("Tekan Enter untuk kembali ke menu utama");
    getchar(); getchar();
}

void highscore()
{
    system("cls||clear");
    printf("\n=====================================\n");
    printf("        - SKOR TERTINGGI -\n");
    printf("=====================================\n");
    printf("Tekan Enter untuk kembali ke menu utama");
    getchar(); getchar();
}

void keluar()
{
    system("cls||clear");
    printf("\n=====================================\n");
    printf("     Ikan hiu makan tomat JANCOK!!!\n");
    printf("=====================================\n");
    printf("Sampai jumpa lagi!\n");
    printf("=====================================\n");
    exit(0);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
 	
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
