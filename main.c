#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define PI 3.141592

void parametry(float *wspolczynniki)
{
	printf("Podaj amplitude funkcji: ");
	while (scanf("%f", wspolczynniki + 0) == 0 || wspolczynniki[0] == 0)
	{
		printf("Popraw na wartosc liczbowa niezerowa: ");
		while ('\n' != getchar());
	}
	printf("Podaj czestotliwosc funkcji: ");
	while (scanf("%f", wspolczynniki + 1) == 0 || wspolczynniki[1] == 0)
	{
		printf("Popraw na wartosc liczbowa niezerowa: ");
		while ('\n' != getchar());
	}
	printf("Podaj przesuniecie fazowe: ");
	while (scanf("%f", wspolczynniki + 2) == 0)
	{
		printf("Popraw na wartosc liczbowa: ");
		while ('\n' != getchar());
	}
	printf("Podaj przesuniecie gora-dol: ");
	while (scanf("%f", wspolczynniki + 3) == 0)
	{
		printf("Popraw na wartosc liczbowa: ");
		while ('\n' != getchar());
	}
}
void rozmiar_tablic(int *rozmiar)
{
	printf("Podaj ilosc elementow funkcji: ");
	while (scanf("%i", rozmiar) == 0 || *rozmiar <= 0)
	{
		printf("Popraw na wartosc liczbowa dodatnia: ");
		while ('\n' != getchar());
	}
}
void dziedzina(float *dMin, float *dMax)
{
	printf("Podaj dolna granice dziedziny: ");
	while (scanf("%f", dMin) == 0)
	{
		printf("Popraw na wartosc liczbowa: ");
		while ('\n' != getchar());
	}
	printf("Podaj gorna granice dziedziny: ");
	while (scanf("%f", dMax) == 0 || *dMax <= *dMin)
	{
		printf("Popraw na wartosc liczbowa wieksza od dolnej granicy: ");
		while ('\n' != getchar());
	}
}
void generator(float wspolczynniki[], float dMin, float dMax, float wyniki[], int rozmiar_tablicy)
{
	int i = 0;
	for (float x = dMin; x <= dMax && i < rozmiar_tablicy; x += ((dMax - dMin) / rozmiar_tablicy), ++i)
	{
		wyniki[i] = (wspolczynniki[0] * (float) sin(wspolczynniki[1] * x + wspolczynniki[2]) + wspolczynniki[3]);
		printf("%f\n", wyniki[i]);
	}
}
void zaszumienie(float tablica_parametrow[], float a, float b, float dMin, float dMax, float wyniki[], int rozmiar_tablicy, float tabela_zaszumiona[])
{
	srand(time(NULL));
	a = ((float)(rand())*(dMax - dMin)) / ((float) RAND_MAX) + dMin;
	while (b <= a || b > (a + ((dMax - dMin) / 2)) || b > dMax)
	{
		b = ((float)(rand())*(dMax - dMin)) / ((float)RAND_MAX) + dMin;
	}
	int miejscepocz = (a - dMin) * (rozmiar_tablicy) / (dMax - dMin);
	int miejscekon = (b - dMin) * (rozmiar_tablicy) / (dMax - dMin);
	printf("Szumienie moze zostac wygenerowane od %i do %i miejsca tablicy.\n", miejscepocz, miejscekon);
	printf("Ponizej znajduje sie tablica po operacji zaszumienia:\n");
	for (int i = 0; i < miejscepocz; i++)
	{
		tabela_zaszumiona[i] = wyniki[i];
		printf("%f\n", tabela_zaszumiona[i]);
	}
	for (int i = miejscepocz; i < miejscekon; i++)
	{
		int prawdopod = rand() % 3;
		if (prawdopod != 0)
		{
			tabela_zaszumiona[i] = wyniki[i];
			printf("%f\n", tabela_zaszumiona[i]);
		}
		else
		{
			float szum = ((float)(rand()) * 2) / ((float)RAND_MAX) - 1;
			tabela_zaszumiona[i] = wyniki[i] + szum;
			printf("%f\n", tabela_zaszumiona[i]);
		}
	}
	for (int i = miejscekon; i < rozmiar_tablicy; i++)
	{
		tabela_zaszumiona[i] = wyniki[i];
		printf("%f\n", tabela_zaszumiona[i]);
	}

}
void zapisz_do_pliku(float *tabela, int rozmiar_tablicy)
{
	char nazwa[100];
	FILE* plik;
	printf("Podaj nazwe pliku, w ktorym chcesz zapisac dane: ");
	scanf("%s", &nazwa);
	plik = fopen(strcat(nazwa, ".csv"), "w");
	for (int i = 0; i < rozmiar_tablicy; i++)
	{
		fprintf(plik, "%f\n", tabela[i]);
	}
	fclose(plik);
	printf("Dane zostaly zapisane w pliku %s.\n", nazwa);
}
void czytaj_tablice(float  *tablica, int *rozmiar_tablicy)
{
	char nazwa[100];
	float x;
	int iloscwpliku = 0;
	FILE* plik;
	printf("Podaj nazwe pliku, z ktorego chcesz wczytac dane: ");
	scanf("%s", &nazwa); 
	while ((plik = fopen(strcat(nazwa, ".csv"), "r")) == NULL)
	{
		printf("Plik nie istnieje. Podaj prawidlowa nazwe pliku: ");
		scanf("%s", nazwa);
	}
	while (feof(plik) == 0)
	{
		iloscwpliku++;
		fscanf(plik, "%f", &x);
	}
	*rozmiar_tablicy = iloscwpliku - 1;
	printf("W pliku znajduje sie %d wartosci.\n", *rozmiar_tablicy);
	rewind(plik);
	if ((tablica = calloc(*rozmiar_tablicy, sizeof(*tablica))) == EOF)
	{
		printf("Blad odczytu tablicy wartosci.\n");
	}
	for (int i = 0; i < *rozmiar_tablicy; i++)
	{
		fscanf(plik, "%f", &tablica[i]);
		printf("%f\n", tablica[i]);
	}
	printf("Zostaly odczytane dane z %s.\n", nazwa);
	fclose(plik);
}
float sortowanie_babelkowe(float *tab, int szerokosc_okna_filtra)
{
	float temp;
	int i;
	do
	{
		for (i = 0; i < (szerokosc_okna_filtra - 1); i++)
		{
			if (tab[i] > tab[i + 1])
			{
				temp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = temp;
			}
		}
		szerokosc_okna_filtra--;
	} while (szerokosc_okna_filtra > 1);
	return tab[2];
}
void filtr_medianowy(float *wyniki, float *tabela_zaszumiona, float *tablica_medianowa, int rozmiar_tablicy)
{
	float tab[5];
	tablica_medianowa[0] = tabela_zaszumiona[0];
	tablica_medianowa[1] = tabela_zaszumiona[1];
	tablica_medianowa[rozmiar_tablicy - 1] = tabela_zaszumiona[rozmiar_tablicy - 1];
	tablica_medianowa[rozmiar_tablicy - 2] = tabela_zaszumiona[rozmiar_tablicy - 2];
	for (int j = 2; j < rozmiar_tablicy - 2; j++)
	{
		tab[0] = tabela_zaszumiona[j - 2];
		tab[1] = tabela_zaszumiona[j - 1];
		tab[2] = tabela_zaszumiona[j];
		tab[3] = tabela_zaszumiona[j + 1];
		tab[4] = tabela_zaszumiona[j + 2];
		tablica_medianowa[j] = sortowanie_babelkowe(tab, 5);
	}
	printf("Ponizej znajduje sie tablica po odfiltrowaniu filtrem medianowym:\n");
	for (int i = 0; i < rozmiar_tablicy; i++)
	{
		printf("%f\n", tablica_medianowa[i]);
	}
}
void filtr_sredniej(float tabela_zaszumiona[], int rozmiar_tablicy, float tablica_filtr_sredniej[])
{
	tablica_filtr_sredniej[0] = tabela_zaszumiona[0];
	tablica_filtr_sredniej[1] = tabela_zaszumiona[1];
	tablica_filtr_sredniej[rozmiar_tablicy - 1] = tabela_zaszumiona[rozmiar_tablicy - 1];
	tablica_filtr_sredniej[rozmiar_tablicy - 2] = tabela_zaszumiona[rozmiar_tablicy - 2];
	int i;
	for (i = 2; i < (rozmiar_tablicy - 2); i++)
	{
		tablica_filtr_sredniej[i] = (tabela_zaszumiona[i - 2] + tabela_zaszumiona[i - 1] + tabela_zaszumiona[i] + tabela_zaszumiona[i + 1] + tabela_zaszumiona[i + 2]) / 5;
	}
	printf("Ponizej znajduje sie tablica po odfiltrowaniu filtrem sredniej ruchomej:\n");
	for (int j = 0; j < rozmiar_tablicy; j++)
	{
		printf("%f\n", tablica_filtr_sredniej[j]);
	}

}

int main()
{
	setlocale(LC_ALL, "polish-poland");
	int rozmiar_tablicy = 0;
	float tablica_parametrow[4];
	float dMin, dMax;
	float *wyniki;
	wyniki = calloc(rozmiar_tablicy, sizeof(*wyniki));
	float a = 0, b = 0;
	float *tabela_zaszumiona;
	tabela_zaszumiona = calloc(rozmiar_tablicy, sizeof(*tabela_zaszumiona));
	float *tablica_medianowa;
	tablica_medianowa = calloc(rozmiar_tablicy, sizeof(*tablica_medianowa));
	float *tablica_filtr_sredniej;
	tablica_filtr_sredniej = calloc(rozmiar_tablicy, sizeof(*tablica_filtr_sredniej));
	int wybor;
	printf("Dokonaj wyboru:\n 1: Generuj nowa funkcje.\n 2: Odczytaj dane z pliku.\n Inna liczba: Zakoncz.: ");
	while (scanf("%i", &wybor) == 0)
	{
		printf("Wybierz wartosc liczbowa: ");
		while ('\n' != getchar());
	}
	switch (wybor)
	{
	case 1:
		rozmiar_tablic(&rozmiar_tablicy);
		parametry(tablica_parametrow);
		dziedzina(&dMin, &dMax);
		printf("Wygenerowane liczby to:\n");
		generator(tablica_parametrow, dMin, dMax, wyniki, rozmiar_tablicy);
		printf("Czy chcesz zapisac wygenerowana tablice do pliku: 1: Tak. Inna liczba: Nie.: ");
		while (scanf("%i", &wybor) == 0)
		{
			printf("Wybierz wartosc liczbowa: ");
			while ('\n' != getchar());
		}
		if (wybor == 1)
		{
			zapisz_do_pliku(wyniki, rozmiar_tablicy);
		}
		printf("Czy chcesz zaszumic wygenerowana tablice: 1: Tak. Inna liczba: Nie.: ");
		while (scanf("%i", &wybor) == 0)
		{
			printf("Wybierz wartosc liczbowa: ");
			while ('\n' != getchar());
		}
		switch (wybor)
		{
		case 1:
			zaszumienie(tablica_parametrow, a, b, dMin, dMax, wyniki, rozmiar_tablicy, tabela_zaszumiona);
			printf("Czy chcesz zapisac zaszumiona tablice do pliku: 1: Tak. Inna liczba: Nie.: ");
			while (scanf("%i", &wybor) == 0)
			{
				printf("Wybierz wartosc liczbowa: ");
				while ('\n' != getchar());
			}
			if (wybor == 1)
			{
				zapisz_do_pliku(tabela_zaszumiona, rozmiar_tablicy);
			}
			printf("Czy chcesz odfiltrowac zaszumiona tablice medianowo: 1: Tak. Inna liczba: Nie.: ");
			while (scanf("%i", &wybor) == 0)
			{
				printf("Wybierz wartosc liczbowa: ");
				while ('\n' != getchar());
			}
			switch (wybor)
			{
			case 1:
				filtr_medianowy (wyniki, tabela_zaszumiona, tablica_medianowa, rozmiar_tablicy);
				printf("Czy chcesz zapisac odfiltrowana medianowo tablice do pliku: 1: Tak. Inna liczba: Nie.: ");
				while (scanf("%i", &wybor) == 0)
				{
					printf("Wybierz wartosc liczbowa: ");
					while ('\n' != getchar());
				}
				if (wybor == 1)
				{
					zapisz_do_pliku(tablica_medianowa, rozmiar_tablicy);
				}
				printf("Czy chcesz odfiltrowac zaszumiona tablice filtrem sredniej ruchomej: 1: Tak. Inna liczba: Nie.: ");
				while (scanf("%i", &wybor) == 0)
				{
					printf("Wybierz wartosc liczbowa: ");
					while ('\n' != getchar());
				}
				switch (wybor)
				{
				case 1:
					filtr_sredniej(tabela_zaszumiona, rozmiar_tablicy, tablica_filtr_sredniej);
					printf("Czy chcesz zapisac odfiltrowana filtrem sredniej ruchomej tablice do pliku: 1: Tak. Inna liczba: Nie.: ");
					while (scanf("%i", &wybor) == 0)
					{
						printf("Wybierz wartosc liczbowa: ");
						while ('\n' != getchar());
					}
					if (wybor == 1)
					{
						zapisz_do_pliku(tablica_filtr_sredniej, rozmiar_tablicy);
					}
					break;
				default:
					break;
				}
				break;
			default:
				printf("Czy chcesz odfiltrowac zaszumiona tablice filtrem sredniej ruchomej: 1: Tak. Inna liczba: Nie.: ");
				while (scanf("%i", &wybor) == 0)
				{
					printf("Wybierz wartosc liczbowa: ");
					while ('\n' != getchar());
				}
				switch (wybor)
				{
				case 1:
					filtr_sredniej(tabela_zaszumiona, rozmiar_tablicy, tablica_filtr_sredniej);
					printf("Czy chcesz zapisac odfiltrowana filtrem sredniej ruchomej tablice do pliku: 1: Tak. Inna liczba: Nie.: ");
					while (scanf("%i", &wybor) == 0)
					{
						printf("Wybierz wartosc liczbowa: ");
						while ('\n' != getchar());
					}
					if (wybor == 1)
					{
						zapisz_do_pliku(tablica_filtr_sredniej, rozmiar_tablicy);
					}
					break;
				default:
					break;
				}
			}
		default:
			break;
		}
		break;
	case 2:
		czytaj_tablice(wyniki, &rozmiar_tablicy);
		break;
	default:
		break;
	}
	free(wyniki);
	free(tabela_zaszumiona);
	free(tablica_medianowa);
	free(tablica_filtr_sredniej);
	system("pause");
	return 0;
}
