#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct liczba_zespolona {
	float czesc_rzeczywista;
	float czesc_urojona;
};
struct element_stosu {
	struct liczba_zespolona licz_zesp;
	struct element_stosu* poprzedni;
};

int wprowadzDane(struct liczba_zespolona* licz_zesp, char* dzialanie);

struct element_stosu* PUSH(struct element_stosu* aktGora, struct liczba_zespolona* liczba);				//Poloz na gore stosu
struct element_stosu* POP(struct element_stosu* aktGora, struct liczba_zespolona* liczba);				//Zdejmij

struct liczba_zespolona Dodawanie(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2);
struct liczba_zespolona Odejmowanie(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2);
struct liczba_zespolona Iloczyn(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2);
struct liczba_zespolona Iloraz(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2);

void Wyswietl(struct element_stosu* aktGora); //Wyswietlanie stosu

int main() {
	struct liczba_zespolona wynik, liczba1, liczba2;
	struct element_stosu* aktGora = 0;		//wsk na akt gore
	char dzialanie;							//wybranie dzialania
	int bl;									//zmienna bledu wyboru

	while (1) {
		printf("Dodaj liczby zespolone do stosu, zapisujac ja w postaci - 'reZ imZ'\n\n");
		printf("Nastepnie podaj znak dzialania jakie chcesz przeprowadzic: '+' '-' '*' '/'\n\nWyjscie: ','\n\n");

		bl = wprowadzDane(&wynik, &dzialanie);

		//printf("1. bl = %d\n", bl);
		if (bl > 0) {							//wprowadzono liczbe
			aktGora = PUSH(aktGora, &wynik);
			system("cls");
			Wyswietl(aktGora);
			//printf("2. bl = %d\n", bl);
		}
		else if (bl == -1 || bl == 0) {
			switch (dzialanie) {
			case '+':
				system("cls");
				if(aktGora->poprzedni != 0){
					aktGora = POP(aktGora, &liczba1);
					aktGora = POP(aktGora, &liczba2);
					wynik = Dodawanie(liczba1, liczba2);
					aktGora = PUSH(aktGora, &wynik);
				}
				Wyswietl(aktGora, liczba1, liczba2);
				break;
			case '-':
				system("cls");
				if (aktGora->poprzedni != 0) {
					aktGora = POP(aktGora, &liczba1);
					aktGora = POP(aktGora, &liczba2);
					wynik = Odejmowanie(liczba1, liczba2);
					aktGora = PUSH(aktGora, &wynik);
				}
				Wyswietl(aktGora, liczba1, liczba2);
				break;
			case '*':
				system("cls");
				if (aktGora->poprzedni != 0) {
					aktGora = POP(aktGora, &liczba1);
					aktGora = POP(aktGora, &liczba2);
					wynik = Iloczyn(liczba1, liczba2);
					aktGora = PUSH(aktGora, &wynik);
				}
				Wyswietl(aktGora, liczba1, liczba2);
				break;
			case '/':
				system("cls");
				if (aktGora->poprzedni != 0) {
					aktGora = POP(aktGora, &liczba1);
					aktGora = POP(aktGora, &liczba2);
					wynik = Iloraz(liczba1, liczba2);
					aktGora = PUSH(aktGora, &wynik);
				}
				Wyswietl(aktGora, liczba1, liczba2);
				break;
			case ',':										//wylaczenie programu
				system("cls");
				printf("Program sie zamyka\n\n");
				return 0;
				break;
			default:										//zabezpieczenie przed wpisywaniem liter
				system("cls");
				printf("Wprowadz liczbe!\n\n");
				break;
			}
		}
		printf("Wybrany znak dzialania = %c\n\n", dzialanie);
	}
	system("pause");
	return 0;
}

int wprowadzDane(struct liczba_zespolona* licz_zesp, char* dzialanie) {
	char temp[20];
	int bl;

	gets(temp);

	bl = sscanf(temp, "%f %f", &licz_zesp->czesc_rzeczywista, &licz_zesp->czesc_urojona);

	//interpretacja wprowadzonych danych
	if (bl == 1) {							//wprowadzono znak
		licz_zesp->czesc_urojona = 0;
	}	
	else if (bl == -1 || bl == 0) {			//wprowadzono liczbe
		*dzialanie = temp[0];
	}
	return bl;
}

struct element_stosu* PUSH(struct element_stosu* aktGora, struct liczba_zespolona* liczba) {	//Poloz 
	struct element_stosu* nowy;

	nowy = malloc(sizeof(struct element_stosu));

	nowy->licz_zesp.czesc_rzeczywista = liczba->czesc_rzeczywista;
	nowy->licz_zesp.czesc_urojona = liczba->czesc_urojona;

	nowy->poprzedni = aktGora;

	return nowy;
}

struct element_stosu* POP(struct element_stosu* aktGora, struct liczba_zespolona* liczba) {		//Zdejmij
	struct element_stosu* temp;

	temp = aktGora->poprzedni;

	liczba->czesc_rzeczywista = aktGora->licz_zesp.czesc_rzeczywista;
	liczba->czesc_urojona = aktGora->licz_zesp.czesc_urojona;

	free(aktGora);

	return temp;
}

void Wyswietl(struct element_stosu* aktGora) {
	struct element_stosu* temp;
	
	temp = aktGora;

	while (temp != 0) {
		if (temp->licz_zesp.czesc_urojona < 0) {
			printf("%f -i*%f\n\n", temp->licz_zesp.czesc_rzeczywista, (temp->licz_zesp.czesc_urojona) * (-1));		//znak -i jesli Im < 0
			temp = temp->poprzedni;
		}
		else if (temp->licz_zesp.czesc_urojona >= 0) {
			printf("%f +i*%f\n\n", temp->licz_zesp.czesc_rzeczywista, temp->licz_zesp.czesc_urojona);				//znak +i
				temp = temp->poprzedni;
		}
	}
}

struct liczba_zespolona Dodawanie(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2) {
	struct liczba_zespolona wynik;

	wynik.czesc_rzeczywista = liczba1.czesc_rzeczywista + liczba2.czesc_rzeczywista;
	wynik.czesc_urojona = liczba1.czesc_urojona + liczba2.czesc_urojona;

	return wynik;
}

struct liczba_zespolona Odejmowanie(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2) {
	struct liczba_zespolona wynik;

	wynik.czesc_rzeczywista = liczba1.czesc_rzeczywista - liczba2.czesc_rzeczywista;
	wynik.czesc_urojona = liczba1.czesc_urojona - liczba2.czesc_urojona;

	return wynik;
}

struct liczba_zespolona Iloczyn(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2) {
	struct liczba_zespolona wynik;

	wynik.czesc_rzeczywista = (liczba1.czesc_rzeczywista * liczba2.czesc_rzeczywista) - (liczba1.czesc_urojona * liczba2.czesc_urojona);
	wynik.czesc_urojona = (liczba1.czesc_rzeczywista * liczba2.czesc_urojona) + (liczba1.czesc_urojona * liczba2.czesc_rzeczywista);

	return wynik;
}

struct liczba_zespolona Iloraz(struct liczba_zespolona liczba1, struct liczba_zespolona liczba2) {
	struct liczba_zespolona wynik;

	//zawsze (Re2*Re2)+(Im2*Im2) > 0
	wynik.czesc_rzeczywista = ((liczba1.czesc_rzeczywista * liczba2.czesc_rzeczywista) + (liczba1.czesc_urojona * liczba2.czesc_urojona)) / ((liczba2.czesc_rzeczywista * liczba2.czesc_rzeczywista) + (liczba2.czesc_urojona * liczba2.czesc_urojona));
	wynik.czesc_urojona = ((liczba1.czesc_urojona * liczba2.czesc_rzeczywista) - (liczba1.czesc_rzeczywista * liczba2.czesc_urojona)) / ((liczba2.czesc_rzeczywista * liczba2.czesc_rzeczywista) + (liczba2.czesc_urojona * liczba2.czesc_urojona));
	
	return wynik;
}
