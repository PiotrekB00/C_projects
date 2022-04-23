//Projekt nr 4 - Ksiazka telefooniczna
//Piotr Barabasz
//nr indeksu 255294
//wersja 30.01.2021
//grupa M10-31i

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct dane {
	char imie[15];
	char nazwisko[15];
	int numer[9];
	char grupa[15];
}kontakt;

struct element {
	struct element* poprzedni_el;
	struct dane kontakt;
	struct element* nastepny_el;
};

void wczytaj(struct element** pierwszy, char* nazwa, int* nr);
void wyswietl(struct element* kontakt);
void sortowanie(struct element** pierwszy, int* nr);
void dodaj(struct element* pierwszy, int* nr);
void superscan(int* x);
void znajdz(struct element* pierwszy, int* nr);
void usun(struct element* pierwszy, int* nr);

main() {
	struct element* pierwszy = 0, * ostatni = 0;
	char nazwaPliku[50];
	int nr = 14, x = 0;

	printf("Ksiazka telefoniczna\n");

	while (1) {

		printf("\n1 - Wczytaj z pliku csv\n2 - Wyswietl\n3 - Posortuj dane\n4 - Dodaj element\n5 - Znajdz element\n6 - Usun element\n\n");
		//scanf("%d", &x);
		superscan(&x);
		switch (x) {
		case 1:
			system("cls");
			printf("Podaj nazwe pliku z rozszerzeniem np.: C:\\arkusz.csv ");
			scanf(" %s", nazwaPliku);
			wczytaj(&pierwszy, nazwaPliku, &nr);
			wyswietl(pierwszy);
			break;
		case 2:
			system("cls");
			wyswietl(pierwszy);
			break;
		case 3:
			system("cls");
			sortowanie(&pierwszy, &nr);
			wyswietl(pierwszy);
			break;
		case 4:
			system("cls");
			dodaj(&pierwszy, &nr);
			wyswietl(pierwszy);
			break;
		case 5:
			system("cls");
			znajdz(&pierwszy, &nr);
			//wyswietl(pierwszy);
			break;
		case 6:
			system("cls");
			usun(&pierwszy, &nr);
			wyswietl(pierwszy);
			break;
		default:
			system("cls");
			printf("Nieprawidlowy wybor\n");
			break;
		}
	}
	system("pause");
	return 0;
}

void wczytaj(struct element** pierwszy, char* nazwa, int* nr) {
	struct element* aktualny = 0, * zrodlo = 0;
	int x = 0, y = 0;

	FILE* plik;
	plik = fopen(nazwa, "r");

	while (x < *nr) {
		aktualny = malloc(sizeof(struct element));
		if (y == 0) {
			y++;
			zrodlo = aktualny;
			aktualny->poprzedni_el = 0;
			*pierwszy = aktualny;

		}
		x++;
		(*pierwszy)->nastepny_el = aktualny;
		aktualny->poprzedni_el = *pierwszy;
		(*pierwszy) = (*pierwszy)->nastepny_el;
		(*pierwszy)->nastepny_el = 0;
		
		fscanf(plik, " %[^;] ; %[^;] ; %[^;] ; %s\n", (*pierwszy)->kontakt.imie, (*pierwszy)->kontakt.nazwisko, (*pierwszy)->kontakt.numer, (*pierwszy)->kontakt.grupa);
	}
	(*pierwszy) = zrodlo;

	printf("\nDane zostaly wczytane!\n");

	fclose(plik);

	//printf("imie: %s\n", (*pierwszy)->kontakt.imie);
	//printf("nazwisko: %s\n", (*pierwszy)->kontakt.nazwisko);
	//printf("numer: %s\n", (*pierwszy)->kontakt.numer);
	//printf("grupa: %s\n", (*pierwszy)->kontakt.grupa);

}

void wyswietl(struct element* pierwszy) {
	setlocale(LC_ALL, "polish_poland");
	struct element* aktualny = pierwszy;
	int i = 1;

	if (pierwszy == 0) {
		printf("brak kontaktow z pamieci!\n");
		system("pause");
	}

	while (aktualny != 0) {
		printf("\nKONTAKT NR - %d\n", i);
		printf("imie: %s\n", aktualny->kontakt.imie);
		printf("nazwisko: %s\n", aktualny->kontakt.nazwisko);
		printf("numer: %s\n", aktualny->kontakt.numer);
		printf("grupa: %s\n", aktualny->kontakt.grupa);
		aktualny = aktualny->nastepny_el;
		i++;
	}
}

void sortowanie(struct element** pierwszy, int* nr) {
	setlocale(LC_ALL, "polish_poland");
	struct element* aktualny = *pierwszy;
	struct element* temp;
	int x;

	for (int p = 1; p < *nr; p++) {
		for (int b = 1; b < (*nr - 1); b++) {
			x = strcoll(aktualny->kontakt.imie, aktualny->nastepny_el->kontakt.imie);
			if (x == 1) {
				if (aktualny->nastepny_el == 0) {	//skrajny warunek

					temp = aktualny->poprzedni_el;
					aktualny->poprzedni_el = aktualny->poprzedni_el->poprzedni_el;
					aktualny->poprzedni_el->poprzedni_el = temp;
				}

				else if (aktualny->poprzedni_el == 0) { //skrajny warunek

					temp = aktualny->nastepny_el;
					aktualny->nastepny_el = aktualny->nastepny_el->nastepny_el;
					aktualny->nastepny_el->nastepny_el = temp;
				}

				else {	//zmiana elementu

					aktualny->poprzedni_el->nastepny_el = aktualny->nastepny_el;
					aktualny->nastepny_el->poprzedni_el = aktualny->poprzedni_el;
					aktualny->poprzedni_el = aktualny->nastepny_el;
					aktualny->nastepny_el = aktualny->poprzedni_el->nastepny_el;
					aktualny->poprzedni_el->nastepny_el = aktualny;
					aktualny->nastepny_el->poprzedni_el = aktualny;
				}

				aktualny = aktualny->poprzedni_el;
			}
			aktualny = aktualny->nastepny_el;
		}
		if (aktualny->poprzedni_el != 0) {
			do {
				aktualny = aktualny->poprzedni_el;
			} while (aktualny->poprzedni_el != 0);
		}
		
	}
	*pierwszy = aktualny; //STOP
	printf("\nDane zostaly posortowane!\n");
}

void dodaj(struct element* pierwszy, int* nr) {
	setlocale(LC_ALL, "polish_poland");
	struct element* aktualny;
	aktualny = malloc(sizeof(struct element));

	printf("wprowadz kontakt:\n");
	scanf("%s %s %s %s", &aktualny->kontakt.imie, &aktualny->kontakt.nazwisko, &aktualny->kontakt.numer, &aktualny->kontakt.grupa);

	(*nr)++;

	//aktualny->nastepny_el = 0;
	/*
	if (aktualny->nastepny_el != 0) {
		do {
			aktualny = aktualny->nastepny_el;
		} while (aktualny->nastepny_el == 0);
	}
	aktualny->poprzedni_el = pierwszy;
	pierwszy->nastepny_el = aktualny;
	pierwszy = aktualny;
	*/

	if (pierwszy == 0) {
		pierwszy->nastepny_el = 0;
		pierwszy->poprzedni_el = 0;
	}
	
	pierwszy = aktualny;
	while (aktualny->nastepny_el != 0) {
		aktualny = aktualny->nastepny_el;
	}
	aktualny->nastepny_el->poprzedni_el = aktualny;
	aktualny->nastepny_el->nastepny_el = 0;
	
	printf("\nwartosc w dodaj:\n");
	printf("imie: %s\n", aktualny->kontakt.imie);
	printf("nazwisko: %s\n", aktualny->kontakt.nazwisko);
	printf("numer: %s\n", aktualny->kontakt.numer);
	printf("grupa: %s\n", aktualny->kontakt.grupa);

}


void superscan(int *x) { //zabezpieczenie przed literami przy wyborze 
	int licz = -1, lit = -1;
	do {
		lit = scanf("%d", &licz);
		scanf("%c");
	} while (lit != 1);
	fflush(stdin);
	*x = licz;
}

void znajdz(struct element* pierwszy, int* nr) {
	struct element* aktualny = pierwszy;
	char* tab, * x;
	tab = NULL;

	printf("wyszukaj:");
	scanf("%s", tab);

	x = strstr(aktualny->kontakt.imie, tab);

	if (pierwszy == 0) {
		printf("brak kontaktow z pamieci!\n");
		system("pause");
	}

	while (aktualny != 0) {
		if (x != 0) {
			printf("imie: %s\n", aktualny->kontakt.imie);
			printf("nazwisko: %s\n", aktualny->kontakt.nazwisko);
			printf("numer: %s\n", aktualny->kontakt.numer);
			printf("grupa: %s\n", aktualny->kontakt.grupa);
		}
		aktualny = aktualny->nastepny_el;
	}

}

void usun(struct element* pierwszy, int* nr) {
	struct element* aktualny = pierwszy;
	struct element* temp;
	char* tab, *x;
	tab = NULL;

	printf("wybierz element do usuniecia (imie)\n");
	scanf("%s", tab);

	(*nr)--;

	x = strstr(aktualny->kontakt.imie, tab);

	if (aktualny == 0) {
		printf("brak kontaktow z pamieci!\n");
		system("pause");
	}

	while (aktualny != 0) {
		aktualny = aktualny->nastepny_el;
	}

	if (x == 0) {
		aktualny->nastepny_el = aktualny->nastepny_el->poprzedni_el;
		aktualny->nastepny_el->nastepny_el = 0;
	}
	
}