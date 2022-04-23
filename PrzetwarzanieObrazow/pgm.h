#ifndef _PGM_            //sprawdzamy czy wczesniej nie definiowano podobnego pliku
#define _PGM_            //jesli NIE to definiujemy

struct pgm {
	char nazwaPliku[100];
	char p2[10];
	int nrObrazu;			   //ID obrazu
	char *koment;
	int k,w,sk;				   //k-kolumny w-wiersze sk-skala szarosci
	int **dane;
};


struct pgm* wczytaj(struct pgm**, char*, int);   // wczytanie danych z pliku pgm 
void wyswietl(struct pgm**, int);   // wyswietla dane
void usun(struct pgm**, int);       // czysci pamiec
void zapisz(struct pgm**, int);	  // zapisuje dane
void negatyw(struct pgm**, int);
void histogram(struct pgm**, int);
void obrot(struct pgm**, int);
void szumSiP(struct pgm**, int);

#endif                        //koniec definicji 