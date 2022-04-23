//Projekt nr 1 - Przetwarzanie sygnalow
//Piotr Barabasz
//wersja 19.11.2020

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void parFun(float* tabParam);														//parametry funkcji
float* alokTab(int dlTab);															

void przebiegFunkcjiKwadr(float* tabParam, float* tx, float* ty, int dlTab);		//f kwadratowa
void przebiegFunkcjiSin(float* tabParam, float* tx, float* ty, int dlTab);			//f sinexp

void wykres(int, float*, float*, char*);
void szum(float* ty, int dlTab);													//funkcja generujaca szum

void zapisCsv(float* tx, float* ty, int dlTab);
void wczytajCsv(float* tx, float* ty, int r);

void filtrSrednia(float* ty, int dlTab);											//srednia ruchoma
float srednia(float* sort);
void filtrMediana(float* wynSzum, int dlTab);										//mediana
float babel(float* sortM, int szerokoscFiltra);

int main() {
	int dlTab;
	float tabParam[7];
	float* tabX;
	float* tabY;
	int wybor = 0;
	tabX = NULL;
	tabY = NULL;
	free(tabX);
	free(tabY);

	printf("Przetwarzanie sygnalow\n	Menu\n");
	printf("1.Stworz nowa funkcja\n2.Zapisz wartosci funkcji\n3.Zakoncz program\n");
	scanf("%d", &wybor);
	switch (wybor) {
	case 1:
		system("cls");
		parFun(tabParam);
		dlTab = abs((int)tabParam[6] + 1);					//parametry funcji
		tabX = alokTab(dlTab);
		tabY = alokTab(dlTab);

		system("cls");
		printf("Wybierz funkcje:\n1.Funkcja kwadratowa\n2.Funkcja expsin\n");
		scanf("%d", &wybor);
		switch (wybor) {
		case 1:
			przebiegFunkcjiKwadr(tabParam, tabX, tabY, dlTab);
			break;
		case 2:
			przebiegFunkcjiSin(tabParam, tabX, tabY, dlTab);
			break;
		}

		system("cls");
		printf("Wybierz filtr:\n1.Filtr srednia ruchoma\n2.Filtr medianowy\n3.Brak filtra - funkcja zaszumiona\n4.Funkcja podstawowa - niezaszumiona\n");
		scanf("%d", &wybor);
		switch (wybor) {
		case 1:
			szum(tabY, dlTab);
			filtrSrednia(tabY, dlTab);
			break;
		case 2:
			szum(tabY, dlTab);
			filtrMediana(tabY, dlTab);
			break;
		case 3:
			szum(tabY, dlTab);
			break;
		}

		system("cls");
		setlocale(LC_ALL, "polish_poland");
		zapisCsv(tabX, tabY, dlTab);
		setlocale(LC_ALL, "English"); 

		wykres(dlTab, tabX, tabY, "wykres.html");

		system("pause");
		break;
	case 2:
		system("cls");
		FILE* plik;
		plik = fopen("D:\\arkusz.csv", "r");
		if (plik == 0) {
			printf("brak pliku");
			break;
		}
		fclose(plik);
		wczytajCsv(&tabX, &tabY, &dlTab);
		break;
	case 3:
		system(EXIT_SUCCESS);
		break;
	default:
		system("cls");
		printf("Wybrano bledna liczbe\n");
		break;
	}

	return 0;
}

void wczytajCsv(float* tx, float* ty, int r) {
	FILE* plik;
	plik = fopen("D:\\arkusz.csv", "r");

	for (int i = 0; i <= r; i++) {
		fscanf(plik, "%f ; %f \n", &*(tx + i), &*(ty + i));
	}
	fprintf(plik, "\n");

	fclose(plik);
	if (feof(plik) == 0) {
		printf("Wczytano plik\n");
	}
	else
		printf("Nie udalo sie wczytac pliku\n");
}

float babel(float* sortM, int szerokoscFiltra) {
	float pomocnicza;
	int i, j;

	for (i = 0; i < szerokoscFiltra - 1; i++) {
		for (j = 0; j < szerokoscFiltra - 1; j++) {
			if (sortM[j] > sortM[j + 1]) {
				pomocnicza = sortM[j + 1];
				sortM[j + 1] = sortM[j];
				sortM[j] = pomocnicza;
			}
		}
	}
	return sortM[2];
}

void filtrMediana(float* ty,  int dlTab) {
	
	
	float sortM[5] = { 0 };
	int dlugosc = 5; //szerokosc filtra medianowego

	for (int i = 2; i < dlTab - 2; i++) {
		sortM[0] = ty[i - 2];
		sortM[1] = ty[i - 1];
		sortM[2] = ty[i];
		sortM[3] = ty[i + 3];
		sortM[4] = ty[i + 4];
		ty[i] = babel(sortM, dlugosc);
		//printf("mediana: %f\n", ty[i]);
	}

}

float srednia(float* sort) {
	float wynik;

	wynik = (sort[0] + sort[1] + sort[2] + sort[3] + sort[4]) / 5;
	return wynik;
} 

void filtrSrednia(float* ty, int dlTab) {
	float sort[5];

	for (int i = 2; i < dlTab - 2; i++) {
		sort[0] = ty[i - 2];
		sort[1] = ty[i - 1];
		sort[2] = ty[i];
		sort[3] = ty[i + 1];
		sort[4] = ty[i + 2];
		ty[i] = srednia(sort);
		//printf("srednia: %f\n", ty[i]);
	}
}

void zapisCsv(float* tx, float* ty, int w) {
	FILE* plik;
	plik = fopen("D:\\arkusz.csv", "w");

	for (int i = 0; i < w; i++) {
		fprintf(plik, "%f ; %f;\n", tx[i], ty[i]);
	}
	fprintf(plik, "\n");

	fclose(plik);

	if (feof(plik) == 0) {
		printf("Zapisano plik\n");
	}
	else
		printf("Nie udalo sie zapisac pliku\n");
}

void szum(float* ty, int dlTab) { 
	float szum, losowa;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < dlTab; i++) {
		losowa = (float)rand() / 500;
		szum = losowa / 50;
		if (szum >= 0 && szum <= 0.3 || szum > 0.7 && szum <= 0.9) {
			ty[i] = ty[i] - szum;
		}
		else if (szum > 0.3 && szum <= 0.7 || szum > 0.9 && szum < 1.3) {
			ty[i] = ty[i] + szum;
		}
		//printf("szum: %f\n", szum);
	}
}

void przebiegFunkcjiSin(float* tabParam, float* tx, float* ty, int dlTab) { //uwaga na wspolczynniki (szum i filtracje widac np dla 1 1 1)
	int i;
	float a, b, c, xmin, xmax, dx, x;

	a = tabParam[0];
	b = tabParam[1];
	c = tabParam[2];
	xmin = tabParam[3];
	xmax = tabParam[4];
	dx = tabParam[5];

	for (i = 0; i < dlTab; i++) {
		tx[i] = xmin + i * dx;
		//printf("x=%f\n", tx[i]);
	}
	for (i = 0; i < dlTab; i++) {
		x = xmin + i * dx;
		ty[i] = a* expf((-b) * x)* sinf(c * x);	
		//printf("y=%f\n", ty[i]);
	}
}

void przebiegFunkcjiKwadr(float* tabParam, float* tx, float* ty, int dlTab) {
	int i;
	float a, b, c, xmin, xmax, dx, x;

	a = tabParam[0];
	b = tabParam[1];
	c = tabParam[2];
	xmin = tabParam[3];
	xmax = tabParam[4];
	dx = tabParam[5];

	for (i = 0; i < dlTab; i++) {
		tx[i] = xmin + i * dx;
		//printf("x=%f\n", tx[i]);
	}
	for (i = 0; i < dlTab; i++) {
		x = xmin + i * dx;
		ty[i] = a * x * x + b * x + c;
		//printf("y=%f\n", ty[i]);
	}
}

float* alokTab(int dlTab) {
	float* tab;

	tab = (float*)malloc(dlTab * sizeof(float));
	return tab;
}

void parFun(float* tabParam) {
	printf("Podaj kolejno parametry a,b,c: ");	
	scanf(" %f %f %f", &tabParam[0], &tabParam[1], &tabParam[2]);

	printf("\nPodaj dziedzine i skok X min, X max, dX : ");	
	scanf("%f %f %f", &tabParam[3], &tabParam[4], &tabParam[5]);

	tabParam[6] = (tabParam[4] - tabParam[3]) / tabParam[5];
}

void wykres(int l, float* tx, float* ty, char nazwa[]) {
	FILE* fp;
	int i;

	printf("Rysuj %s\n", nazwa);
	fp = fopen(nazwa, "w");

	fprintf(fp, "<html>\n");
	fprintf(fp, "<head>\n");
	fprintf(fp, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(fp, "<script type=\"text/javascript\">\n");
	fprintf(fp, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(fp, "google.setOnLoadCallback(drawChart);\n");
	fprintf(fp, "function drawChart() {\n");
	fprintf(fp, "var data = google.visualization.arrayToDataTable([\n");

	fprintf(fp, "['i', 'Wartosc'],\n");
	for (i = 0; i < l; i++) {
		fprintf(fp, "[%f, %f],\n", tx[i], ty[i]);
	}
	fprintf(fp, "[%f, %f]\n", tx[i - 1], ty[i - 1]);
	fprintf(fp, "]);\n");

	fprintf(fp, "var options = {\n");
	fprintf(fp, "title: 'Wybrany sygnal'\n");
	fprintf(fp, "};\n");

	fprintf(fp, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(fp, "chart.draw(data, options);\n");
	fprintf(fp, "}\n");
	fprintf(fp, "</script>\n");
	fprintf(fp, "</head>\n");
	fprintf(fp, "<body>\n");
	fprintf(fp, "<div id=\"chart_div\" style=\"width: 900px; height: 500px;\"></div>\n");
	fprintf(fp, "</body>\n");
	fprintf(fp, "</html>\n");

	fclose(fp);

	system(nazwa);
}