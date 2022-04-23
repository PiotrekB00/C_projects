#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

struct pgm* wczytaj(struct pgm **foto, char *nazwa, int liczbaObrazow) {
	int i, j, err;
	FILE *plik;

	liczbaObrazow++;																//zwiekszenie licznika obrazow o 1
	(*foto) = (struct pgm*)realloc((*foto), liczbaObrazow * sizeof(*(*foto)));		//dodanie wskaznika na strukture do tablicy obrazow
	err = strcpy((*foto)[liczbaObrazow - 1].nazwaPliku, nazwa);						//zapis nazwy nowego pliku do struktury

	plik = fopen(nazwa, "r");
	if (plik == NULL) {
		printf("Nie mozna otworzyc pliku\n");
	}
	else {


	//numerObrazu;
	/*
	(*foto)[liczbaObrazow - 1].nrObrazu = (int*)calloc(1, sizeof(int*));				//alokacja na id obrazu
	for (i = 0; i < (*foto)[liczbaObrazow - 1]; i++) {
		((*foto)[liczbaObrazow - 1].nrObrazu
	}*/
	

	(*foto)[liczbaObrazow - 1].koment = (char*)calloc(100, sizeof(char));								//alokacja tablicy na komentarz

	fgets((*foto)[liczbaObrazow - 1].p2, 10, plik);
	fgets((*foto)[liczbaObrazow - 1].koment, 100, plik);													//pobranie komentarza z tablicy

	fscanf(plik, "%d %d", &((*foto)[liczbaObrazow - 1].k), &((*foto)[liczbaObrazow - 1].w));				//pobranie parametrów obrazu z pliku i zapis do struktury
	fscanf(plik, "%d", &((*foto)[liczbaObrazow - 1].sk));

	//alokacja pamieci na tablice 2D
	((*foto)[liczbaObrazow - 1].dane) = (int**)calloc((*foto)[liczbaObrazow - 1].k, sizeof(int*));			//alokacja pamieci na kolumny

	for (i = 0; i < ((*foto)[liczbaObrazow-1].k); i++) {
		(*foto)[liczbaObrazow - 1].dane[i] = (int*)calloc((*foto)[liczbaObrazow - 1].w, sizeof(int));		// akolacja pamieci na wiersze
	}

	//wczytanie obrazu do tablicy//
	for (i = 0; i < ((*foto)[liczbaObrazow - 1].w); i++) {								// indeks i - numer wiersza
		for (j = 0; j < ((*foto)[liczbaObrazow - 1].k); j++) {
			fscanf(plik, "%d", &((*foto)[liczbaObrazow - 1].dane[j][i]));				// indeks j - numer kolumny
		}
	}
	fclose(plik);
	}
	return liczbaObrazow;
}

void wyswietl(struct pgm** wskObraz, int liczbaObrazow) {       //wyswietla informacje o pliku
	if (*wskObraz == 0) {
		printf("Brak obrazow w pamieci\n");
		system("pause");
	}
	else {
		printf("Liczba obrazow: %d\n\n\n", liczbaObrazow);

		for (int i = 0; i < liczbaObrazow; i++) {
			//printf("\nObraz nr ze struktury %d:\n\n", (*wskObraz)[i].nrObrazu);
			printf("\nObraz nr %d:\n\n", i + 1);
			printf("Nazwa pliku to: %s\n", (*wskObraz)[i].nazwaPliku);
			printf("P2: %s", (*wskObraz)[i].p2);
			printf("Komantarz: %s", (*wskObraz)[i].koment);
			printf("Parametry k,w,sk: %d %d %d\n\n", (*wskObraz)[i].k, (*wskObraz)[i].w, (*wskObraz)[i].sk);
		}
		printf("\n");
	}
}

void usun(struct pgm** foto, int liczbaObrazow) {
	if ((foto[liczbaObrazow - 1]->dane) != NULL) {
		for (int i = 0; i < (foto[liczbaObrazow - 1]->k); i++) {
			free(foto[liczbaObrazow - 1]->dane[i]);
		}
		free(foto[liczbaObrazow - 1]->dane);
		free(foto[liczbaObrazow - 1]);
		printf("Paniec zwolniona\n");
	}
	else {
		printf("Pamiec zostala juz wczesniej zwolniona\n");
		system("pause");
	}
}

void zapisz(struct pgm** foto, int nrObr) {
	int i, j;
	char nazwa[100];
	FILE* plik;

	printf("Podaj nazwe pliku z rozszerzeniem .pgm\n");
	scanf("%s", &nazwa);

	plik = fopen(nazwa, "w");
	if (plik == NULL) {
		printf("Nie mozna otworzyc obrazu\n");
	}
	else {
		fprintf(plik, "%s\n", (foto[nrObr - 1]->p2));
		fprintf(plik, "%s\n", (foto[nrObr - 1]->koment));
		fprintf(plik, "%d %d\n", (foto[nrObr - 1]->k), (foto[nrObr - 1]->w));
		fprintf(plik, "%d\n", (foto[nrObr - 1]->sk));

		for (i = 0; i < (foto[nrObr - 1]->w); i++) {					    // indeks i - numer wiersza
			for (j = 0; j < (foto[nrObr - 1]->k); j++) {
				fprintf(plik, "%d ", (foto[nrObr - 1]->dane[j][i]));        // indeks j - numer kolumny
			}
			fprintf(plik, "\n");
		}
		printf("\nZapisano\n");
	}
	fclose(plik);
	system(nazwa);
}

void negatyw(struct pgm** foto, int nrObr) {
	char nazwa[100];
	FILE* plik;

	printf("Podaj nazwe pliku z rozszerzeniem .pgm\n");
	scanf("%s", &nazwa);

	plik = fopen(nazwa, "w");
	if (plik == NULL) {
		printf("Nie mozna otworzyc obrazu\n");
	}
	else {
		fprintf(plik, "%s\n", (foto[nrObr - 1]->p2));
		fprintf(plik, "%s\n", (foto[nrObr - 1]->koment));
		fprintf(plik, "%d %d\n", (foto[nrObr - 1]->k), (foto[nrObr - 1]->w));
		fprintf(plik, "%d\n", (foto[nrObr - 1]->sk));

		for (int i = 0; i < (foto[nrObr - 1]->w); i++) {					  // indeks m - numer nowego wiersza
			for (int j = 0; j < (foto[nrObr - 1]->k); j++) {
				foto[nrObr - 1]->dane[j][i] = foto[nrObr - 1]->k - foto[nrObr - 1]->dane[j][i];
				fprintf(plik, "%d ", (foto[nrObr - 1]->dane[j][i]));        // indeks l - numer nowej kolumny
			}
		}
		printf("\nZapisano\n");
	}
	fclose(plik);

	system(nazwa);	
}

void histogram(struct pgm** foto, int nrObr) {
	int i, j, l, m, n;
	int liczba = 0;
	char nazwa[100];
	int* dlugosc;
	int wysokosc[255];
	FILE* plik;

	//wysokosc = NULL;
	//free(wysokosc);

	//dlugosc = NULL;
	//free(dlugosc);
	//wysokosc = calloc((foto[nrObr - 1]->sk), sizeof(*wysokosc));
	dlugosc = calloc((foto[nrObr - 1]->sk), sizeof(*dlugosc));
	//free(dlugosc);

	for (i = 0; i < foto[nrObr - 1]->sk; i++) {
		for (j = 0; j < foto[nrObr - 1]->k; j++) {
			for (l = 0; l < foto[nrObr - 1]->w; l++) {
				if (i == (foto[nrObr - 1]->dane)[l][j]) {
					liczba++;
				}
			}
		}
		dlugosc[i] = liczba;
	}

	plik = fopen("histogram.csv", "w");
	if (plik == NULL) {
		printf("Nie mozna otworzyc pliku\n");
	}
	else {
		for (m = 0; m < 255; m++) {
			wysokosc[m] = m + 1;
			fprintf(plik, "%d ; %d\n", wysokosc[m], dlugosc[m]);
		}
		printf("Zapisano do pliku csv\n");
	}
	fclose(plik);
}

void szumSiP(struct pgm** foto, int nrObr) {
	int i;
	char nazwa[100];
	srand((unsigned int)time(NULL));
	FILE* plik;

	for (i = 0; i < foto[nrObr - 1]->w; i++) {
		for (int j = 0; j < foto[nrObr - 1]->k; j++) {
			if (rand() % 100 == 1) {
				(foto[nrObr - 1]->dane[j][i]) = 255;
			}
			else if (rand() % 100 == 0) {
				(foto[nrObr - 1]->dane[j][i]) = 0;
			}
		}
	}
	//zapisz(foto, nrObr);
	printf("Podaj nazwe pliku z rozszerzeniem .pgm\n");
	scanf("%s", &nazwa);

	plik = fopen(nazwa, "w");
	if (plik == NULL) {
		printf("Nie mozna otworzyc obrazu\n");
	}
	else {
		fprintf(plik, "%s\n", (foto[nrObr - 1]->p2));
		fprintf(plik, "%s\n", (foto[nrObr - 1]->koment));
		fprintf(plik, "%d %d\n", (foto[nrObr - 1]->k), (foto[nrObr - 1]->w));
		fprintf(plik, "%d\n", (foto[nrObr - 1]->sk));

		for (i = 0; i < (foto[nrObr - 1]->w); i++) {										// indeks i - numer wiersza
			for (int j = 0; j < (foto[nrObr - 1]->k); j++) {
				fprintf(plik, "%d ", (foto[nrObr - 1]->dane[j][i]));						// indeks j - numer kolumny
			}
			fprintf(plik, "\n");
		}
		printf("\nZapisano\n");
	}
	fclose(plik);
	system(nazwa);
}

void obrot(struct pgm** foto, int nrObr) {
	char nazwa[100];
	int d;

	FILE* plik;

	printf("Obrot o k*90\nk=");
	scanf("%d", &d);
	d = d % 4;
	if (d == 0) {
		//0*k

		zapisz(foto, nrObr);
	}
	else if (d == 1) {
		//1*k

		printf("Podaj nazwe pliku z rozszerzeniem .pgm\n");
		scanf("%s", &nazwa);

		plik = fopen(nazwa, "w");
		if (plik == NULL) {
			printf("Nie mozna otworzyc obrazu\n");
		}
		else {
			fprintf(plik, "%s\n", (foto[nrObr - 1]->p2));
			fprintf(plik, "%s\n", (foto[nrObr - 1]->koment));
			fprintf(plik, "%d %d\n", (foto[nrObr - 1]->k), (foto[nrObr - 1]->w));
			fprintf(plik, "%d\n", (foto[nrObr - 1]->sk));

			for (int i = 0; i < (foto[nrObr - 1]->w); i++) {								// indeks i - numer wiersza
				for (int j = 0; j < (foto[nrObr - 1]->k); j++) {
					fprintf(plik, "%d ", (foto[nrObr - 1]->dane[i][foto[nrObr - 1]->k - 1 - j]));					// indeks j - numer kolumny
				}
				fprintf(plik, "\n");
			}
			printf("\nZapisano\n");
		}
		fclose(plik);
		system(nazwa);

	}

	else if (d == 2) {
		//2*k

		printf("Podaj nazwe pliku z rozszerzeniem .pgm\n");
		scanf("%s", &nazwa);

		plik = fopen(nazwa, "w");
		if (plik == NULL) {
			printf("Nie mozna otworzyc obrazu\n");
		}
		else {
			fprintf(plik, "%s\n", (foto[nrObr - 1]->p2));
			fprintf(plik, "%s\n", (foto[nrObr - 1]->koment));
			fprintf(plik, "%d %d\n", (foto[nrObr - 1]->k), (foto[nrObr - 1]->w));
			fprintf(plik, "%d\n", (foto[nrObr - 1]->sk));

			for (int i = 0; i < (foto[nrObr - 1]->w); i++) {								// indeks i - numer wiersza
				for (int j = 0; j < (foto[nrObr - 1]->k); j++) {
					fprintf(plik, "%d ", (foto[nrObr - 1]->dane[j][i]));					// indeks j - numer kolumny
				}
				fprintf(plik, "\n");
			}
			printf("\nZapisano\n");
		}
		fclose(plik);
		system(nazwa);
	}
	else if (d == 3) {
		//3*k

		printf("Podaj nazwe pliku z rozszerzeniem .pgm\n");
		scanf("%s", &nazwa);

		plik = fopen(nazwa, "w");
		if (plik == NULL) {
			printf("Nie mozna otworzyc obrazu\n");
		}
		else {
			fprintf(plik, "%s\n", (foto[nrObr - 1]->p2));
			fprintf(plik, "%s\n", (foto[nrObr - 1]->koment));
			fprintf(plik, "%d %d\n", (foto[nrObr - 1]->k), (foto[nrObr - 1]->w));
			fprintf(plik, "%d\n", (foto[nrObr - 1]->sk));

			for (int i = 0; i < (foto[nrObr - 1]->w); i++) {								// indeks i - numer wiersza
				for (int j = 0; j < (foto[nrObr - 1]->k); j++) {
					fprintf(plik, "%d ", (foto[nrObr - 1]->dane[i][foto[nrObr - 1]->k - 1 - j]));					// indeks j - numer kolumny
				}
				fprintf(plik, "\n");
			}
			printf("\nZapisano\n");
		}
		fclose(plik);
		system(nazwa);
	}
}