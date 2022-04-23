#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
#include <string.h>

int main() {

	int d, e;
	int lObr = 0, nrObr = 0, nr = 0;			   //lObr - liczba wczytanych obrazów, nrObr - nr aktywnego obrazu
	struct pgm* wskObrazAkt = NULL;        //definicja wskaznika do struktury pgm - aktywny obraz     
	struct pgm** wskObraz = NULL;		   //wskaźnik na tablice struktur (obrazów)
	char nazwaPliku[100];



	wskObraz = (struct pgm**)calloc(1, sizeof(struct pgm*));
	wskObrazAkt = (struct pgm*)calloc(1, sizeof(struct pgm));

	while (1) {
		printf("Wczytaj do pamieci- 1  \nWyswietl informacje o pliku - 2  \nZwolnij cala pamiec - 3 \nWybor pliku do edycji - 4\nWyjdz - 0\n");
		scanf("%d", &d);
		if (d == 0) break;

		switch (d) {
		case 1:
			system("cls");
			printf("Podaj nazwe pliku z rozszerzeniem np.: C:\\1.pgm: ");
			scanf(" %s", nazwaPliku);

			lObr = wczytaj(wskObraz, nazwaPliku, lObr);

			//printf("\n\nZamknij przegladarke plikow pgm aby kontynuowac!!!\n\n");
			//system(nazwaPliku);														//automatyczne otwieranie

			//strcpy(wskObraz->nazwaPliku, nazwaPliku);
			//wyswietl(wskObraz, lObr);
			break;
		case 2:
			system("cls");
			wyswietl(wskObraz, lObr);
			break;
		case 3:
			system("cls");
			usun(wskObraz, lObr);
			break;
		case 4:
			system("cls");
			wyswietl(wskObraz, lObr);
			printf("Wybierz plik do  edycji\n");
			scanf("%d", &nrObr);
			while (1) {
				printf("Zapisz - 1 \nNegatyw - 2\nHistogram - 3\nObrot - 4\nSzum - 5\nFiltr - 6\nCofnij - 0\n");
				scanf("%d", &e);
				if (e == 0) break;
				switch (e) {
				case 1:
					system("cls");
					zapisz(wskObraz, nrObr);
					break;
				case 2:
					system("cls");
					negatyw(wskObraz, nrObr);
					break;
				case 3:
					system("cls");
					histogram(wskObraz, nrObr);
					break;
				case 4:
					system("cls");
					obrot(wskObraz, nrObr);
					break;
				case 5:
					system("cls");
					szumSiP(wskObraz, nrObr);
					break;
				case 6:
					system("cls");
					//filtr();
					break;
				}
			}
			system("pause");
			break;

		default:
			printf("Nieprawidlowy wybor\n");
			break;
		}
	}

	system("pause");
	return 0;
}