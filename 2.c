#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include<fcntl.h>
#include <unistd.h>
#include <io.h>
#define ESC 27
 
struct Produkt 
{
	char nazwa[25];
	char typ[25];
	char producent[25];
	double cena;
	int VAT;
};
 
struct Produkt p={"procesor", "i7", "intel",2000,23};
char nazwa[11];
FILE *fp1=NULL,*fp2=NULL;
char menu ();
void gotoxy(short x, short y);
void utworzBaze ();
void otworzBaze ();
void usunBaze();
void przegladBazy(int);
void drukujStatus();
struct Produkt wczytajStrukt();
void drukujStrukt(struct Produkt);
void usunStrukture();
void sortujStruktury();
int compare();
void usuwanieStrukturyZbazy();
int main()
{
	while(1)
	{
	system("cls");
	menu();
	}
	if(fp1) fclose(fp1);
	if(fp2) fclose(fp2);
	printf("\n Zakonczenie programu");
	getchar();
	return 0;
}

void gotoxy(short x, short y) 
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

char menu (void)
{
	char ch;
	int x,y;
	x=20; y=8;
	gotoxy(x,y);
	printf("============================");
	gotoxy(x,y+1);
	printf("1.Otworz baze danych");
	gotoxy(x,y+2);
	printf("2.Utworz nowa baze");
	gotoxy(x,y+3);
	printf("3. Usun baze");
	gotoxy(x,y+4);
	printf("4.Zakoncz program");
	gotoxy(x,y+5);
	printf(" Wybierz opcje :");
	fflush(stdin);
	do
	{
		fflush(stdin);
		ch=getch();
	}
	while ( ch!='1' && ch!='2'&& ch!='3'&& ch!='4');
	switch(ch)
	{
		case '1':
		gotoxy(20,18);
		printf(" Wybrano opcja 1 - Enter");
		
		getchar();
		otworzBaze();
		if(!fp1)return;
		przegladBazy(1);
		break;
		case '2':
		gotoxy(20,18);
		printf(" Wybrano opcja 2 - Enter ");
		getchar();
		utworzBaze();
		przegladBazy(2);
		break;
		case '3':
		gotoxy(20,18);
		fclose(fp1);
		printf(" Wybrano opcja 3 - Enter ");
		getchar();
		usunBaze();
		break;
		case '4':
		gotoxy(20,18);
		printf(" Wybrano opcja 4 - Enter ");
		getchar();
		exit(0);
	}
}

void utworzBaze ()
{
	fp1 = NULL;
	char kon[]=".dat";
	int x=20,y=20;
	system("cls");
	gotoxy(x,y);
	printf("Metoda utworzBaze - enter");
	int valid=0;
	while (!valid) {
        printf("Podaj napis w formacie 'bazaXX': ");
     	gotoxy(x+4,y+2);   
        scanf("%6s", nazwa);

        if (strlen(nazwa) == 6 && strncmp(nazwa, "baza", 4) == 0) {
            int i;
            valid = 1;
            for (i = 4; i < 6; i++) {
                if (nazwa[i] < '0' || nazwa[i] > '9') {
                    valid = 0;
                    break;
                }
            }
        }

        if (!valid) {
            printf("Niepoprawny napis! Spróbuj ponownie.\n");
            getchar();
        }
        system("cls");
		gotoxy(x,y);
		printf("Metoda utworzBaze - enter");
    }
	strcat(nazwa,kon);
	fp1=fopen(nazwa,"w+b");
	if(fp1==NULL)
	printf("\n Plik %s nie zostal utworzony", nazwa);
	else
	printf("\n Nowy plik %s zostal utworzony", nazwa);
	getchar();
	return;
}

void otworzBaze (void)
{
	fp1 = NULL;
	char kon[]=".dat";
	int x=20,y=20;
	system("cls");
	gotoxy(x,y);
	printf("Metoda otworzBaze");
	printf(" Podaj nazwe bazy bazaXX :\n");
	gotoxy(x,y+2);
	scanf("%6s",nazwa);
	strcat(nazwa,kon);
	fp1=fopen(nazwa,"r+b");
	if(fp1==NULL) printf("\n Plik %s nie zostal otworzony", nazwa);
	else printf("\n Nowy plik %s zostal otworzony", nazwa);
	getchar();
}

void usunBaze()
{
	fp1 = NULL;
    char  kon[] = ".dat";
    int x = 20, y = 20, wynik;
    system("cls");
    gotoxy(x, y);
    printf("Metoda usunBaze");
    printf(" Podaj nazwe bazy bazaXX:\n");
    gotoxy(x, y + 2);
    scanf("%6s", nazwa);
    strcat(nazwa, kon);
    gotoxy(x, 22);
    fp1 = fopen(nazwa, "rb");
    if (fp1 == NULL) {
        printf("Plik nie istnieje");
        system("pause");
        return;
    }
    fclose(fp1);
    wynik = remove(nazwa);
    if (!wynik)
        printf("Plik zostal usuniety");
    else
        printf("Plik nie zostal usuniety");
    system("pause");
    return;
}

void przegladBazy(int wybor)
{
	struct Produkt st;
	int x=1,y=24,l=0,i;
	size_t r = sizeof(struct Produkt);

	char ch;
	system("cls");
	gotoxy(x,y);
	printf(" Metoda przegladBazy\n");
	struct Produkt produkt;
	if(wybor==2)
	{
		int liczbaRekordow,i;
	    printf("Podaj liczbê rekordów do wczytania: ");
	    scanf("%d", &liczbaRekordow);
	    for ( i = 0; i < liczbaRekordow; i++)
	    {
	        produkt=wczytajStrukt();
	        fwrite(&produkt, sizeof(struct Produkt), 1, fp1);
	        printf("\n");
	    }
	}
	fseek(fp1, 0, SEEK_END);
    int ilosc_struktur = ftell(fp1) / r;
    fseek(fp1, 0, SEEK_SET);
	system("cls");
	fseek(fp1, l, SEEK_SET);
	fread(&produkt, sizeof(struct Produkt), 1, fp1);
    drukujStrukt(produkt);
	drukujStatus();
	
	while (1)
	{
		drukujStatus();
		do
		{
			fflush(stdin);
			ch=toupper(getch());
		}
		while (ch!='Y' && ch!='B'&& ch!='G'&& ch!='H'&&ch!='A'&& ch!='M'&&ch!='S'&&ch!='D'&&ch!=ESC);
		
		switch(ch)
		{
			case 'Y':
			gotoxy(20,18);
			printf(" Wybrano opcja Y - Enter");
		//	getchar();
			if(l)l--;
			
			break;
			case 'B':
			gotoxy(20,18);
			printf(" Wybrano opcja B - Enter ");
		//	getchar();
			if(l!=ilosc_struktur - 1)l++;
			break;
			case 'G':
			gotoxy(20,18);
	//		printf(" Wybrano opcja G - Enter ");
			getchar();
			l=0;
			break;
			case 'H':
			gotoxy(20,18);
			printf(" Wybrano opcja H - Enter ");
		//	getchar();
			l=ilosc_struktur - 1;
			break;
			case 'S':
			gotoxy(20,18);
			printf(" Wybrano opcja S - sortowanie Enter ");
			getchar();
			struct Produkt bufs1, bufs2,bufs;
			sortujStruktury(bufs,bufs1,bufs2,nazwa);
			break;
			case 'A':
			gotoxy(20,18);
			printf(" Wybrano opcja A - Enter ");
			getchar();
			st=wczytajStrukt();
			l=0;
			fseek(fp1, 0, SEEK_END);
			fwrite(&st, r, 1, fp1);
    		ilosc_struktur ++;
			break;
			case 'M':
			gotoxy(20,18);
			printf(" Wybrano opcja M - Enter ");
			getchar();
			st=wczytajStrukt();
			fseek(fp1,l*r,SEEK_SET);
			fwrite(&st,r,1,fp1);
			break;
			case 'D': // opcja usuwania aktualnie wyœwietlanej struktury
			gotoxy(20,18);
			printf(" Wybrano opcja D - Enter ");
			getchar();
			fseek(fp1, -r, SEEK_END);
			fread(&produkt,r,1,fp1);
			fseek(fp1, l*r, SEEK_SET);
			fwrite(&produkt,r,1,fp1);
			fseek(fp1, 0, SEEK_END);
    		int rozmiar = ftell(fp1);
    		rozmiar -= r;
    		ftruncate(fileno(fp1), rozmiar);
    		rewind(fp1);
    		ilosc_struktur--;
			break;
			case ESC:
			gotoxy(20,18);
			printf(" Wybrano opcja ESC - Menu ");
			getchar();
			return;// powrót do g³ównego menu
		}
		system("cls");
		fseek(fp1, l*r, SEEK_SET);
		fread(&produkt, sizeof(struct Produkt), 1, fp1);
    	drukujStrukt(produkt);	
	}
	return;
}

void drukujStatus()
{
	gotoxy(1,24);
	printf(" Y-up B-down G-Home H-End A-add M-modify S-sort D-del ESC-exit");
}

struct Produkt wczytajStrukt()
{
	struct Produkt st;
	fflush(stdin);
	int x=20,y=8;
	system("cls");
	gotoxy(x,y);
	fflush(stdin);
	printf("Nazwa:");
	scanf("%s",st.nazwa);
	drukujStatus();
	gotoxy(x,y+1);
	printf("Producent:");
	scanf("%s",st.producent);
	fflush(stdin);
	gotoxy(x,y+2);
	printf("Typ:");
	scanf("%s",st.typ);
	fflush(stdin);
	gotoxy(x,y+3);
	printf("Cena netto:");
	scanf("%lf",&st.cena);
	gotoxy(x,y+4);
	printf("VAT:");
	scanf("%d",&st.VAT);
	return st;
}

 void drukujStrukt( struct Produkt st)
 {
	int x=20,y=8;
	system("cls");
	gotoxy(x,y);
	printf("nazwa:%s", st.nazwa);
	gotoxy(x,y+1);
	printf("Typ :%s", st.typ);	
	gotoxy(x,y+2);
	printf("Producent:%s", st.producent);
	gotoxy(x,y+3);
	printf("Cena netto:%f",st.cena);
	gotoxy(x,y+4);
	printf("VAT:%d",st.VAT);
}

void sortujStruktury(struct Produkt bufs, struct Produkt bufs1, struct Produkt bufs2, char nazwaBazy[11]) {
    FILE *fp1 = fopen(nazwaBazy, "r+b");
    if (fp1 == NULL) {
        printf("B³¹d otwarcia pliku.\n");
        return;
    }

    int zam, n, choice3, i;
    fseek(fp1, 0, SEEK_END);
    n = ftell(fp1) / sizeof(struct Produkt);
    fseek(fp1, 0, SEEK_SET);

    printf("Wybierz wzgledem czego ma byc sortowowane:\n 1.Nazwa  2.Producent  3.Cena  4.Typ  5.VAT\n");
    do {
        scanf("%d", &choice3);
    } while (choice3 > 5 || choice3 < 1);

    do {
        zam = 0;
        for (i = 0; i < n - 1; i++) {
            fseek(fp1, i * sizeof(struct Produkt), SEEK_SET);
            fread(&bufs1, sizeof(struct Produkt), 1, fp1);
            fread(&bufs2, sizeof(struct Produkt), 1, fp1);
            int compare1 = compare(bufs1, bufs2, choice3);
            if (compare1) {
                fseek(fp1, i * sizeof(struct Produkt), SEEK_SET);
                fwrite(&bufs2, sizeof(struct Produkt), 1, fp1);
                fwrite(&bufs1, sizeof(struct Produkt), 1, fp1);
                zam = 1;
            }
        }
    } while (zam);


    fclose(fp1);
}

int compare(struct Produkt bufs1, struct Produkt bufs2, int choice3) {
    switch (choice3) {
        case 1:
            if (strcmp(bufs1.nazwa, bufs2.nazwa) > 0)
                return 1;
            break;
        case 2:
            if (strcmp(bufs1.producent, bufs2.producent) > 0)
                return 1;
            break;
        case 3:
            if (bufs1.cena > bufs2.cena)
                return 1;
            break;
        case 4:
            if (strcmp(bufs1.typ, bufs2.typ) > 0)
                return 1;
            break;
        case 5:
            if (bufs1.VAT > bufs2.VAT)
                return 1;
            break;
    }
    return 0;
}

