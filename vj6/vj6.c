#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATUM_KASNIJE -1
#define DATUM_ISTI 0
#define DATUM_PRIJE 1

struct artikl;
typedef struct artikl* artiklposition;
typedef struct artikl {
	char ime[15];
	int kolicina;
	double cijena;
	artiklposition next;
}artikl;

struct racun;
typedef struct racun* racunposition;
typedef struct racun {
	char datum[15];
	artikl head;
	racunposition next;
}racun;

int UcitajRacune(racunposition);
int UbaciSortiranoRacun(racunposition, racunposition);
int UsporediDatume(racunposition, racunposition);
int UcitajArtikleIzDatoteke(artiklposition, char[]);
int KreirajISortiranoUbaciArtikl(artiklposition, char[], int, double);
int IzlistajDatumeRacuna(racunposition);
int IzlistajArtikleIzRacuna(racunposition, int);
int PronadiArtiklUPeriodu(racunposition, char[], char[], char[], int*, double*);


int main() {
	racun head;
	head.next = NULL;
	UcitajRacune(&head);
	IzlistajDatumeRacuna(&head);
	int i = 1;
	while (IzlistajArtikleIzRacuna(&head, i) == EXIT_SUCCESS) {
		i++;
	}
	char datum1[15];
	char datum2[15];
	char trazi[15];
	int kolicina;
	double cijena;
	printf("Unesi prvi datum formata god-mj-dan: "); scanf("%s", datum1);
	printf("Unesi drugi datum formata god-mj-dan: "); scanf("%s", datum2);
	printf("Unesi trazeni artikl: "); scanf("%s", trazi);
	PronadiArtiklUPeriodu(&head, trazi, datum1, datum2, &kolicina, &cijena);
	printf("Artikl %s ima u periodu od %s do %s: %d, po cijeni %lf, odnosno sveukupno potroseno: %lf.\n", trazi, datum1, datum2, kolicina, cijena, (double)kolicina * cijena);


	return 0;
}

int UcitajRacune(racunposition head) {
	FILE* dat = NULL;
	dat = fopen("racuni.txt", "r");
	if (!dat) {
		printf("Datoteka se nije otvorila...");
		return EXIT_FAILURE;
	}
	int i;
	char naziv[15];
	FILE* dat2 = NULL;
	racunposition temp = NULL;

	while (feof(dat) == 0) {
		fscanf(dat, "%[^\n]s", naziv); fgetc(dat);
		dat2 = fopen(naziv, "r");
		if (!dat2) {
			printf("Datoteka se nije otvorila...");
			fclose(dat);
			return EXIT_FAILURE;
		}
		temp = (racunposition)malloc(sizeof(racun));
		if (temp == NULL) {
			printf("Alokacija memorije nije uspijela...");
			fclose(dat);
			fclose(dat2);
			return EXIT_FAILURE;
		}
		fscanf(dat2, "%[^\n]s", temp->datum);
		if (UbaciSortiranoRacun(head, temp) == EXIT_FAILURE) {
			racunposition help = head->next;
			while (UsporediDatume(help, temp) != DATUM_ISTI) {
				help = help->next;
			}
			free(temp);
			temp = help;
		}
		UcitajArtikleIzDatoteke(&temp->head, naziv);
		temp = NULL;
		fclose(dat2);
		dat2 = NULL;
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int UbaciSortiranoRacun(racunposition head, racunposition R) {
	if (head->next == NULL) {
		R->next = head->next;
		head->next = R;
		R->head.next = NULL;
		return EXIT_SUCCESS;
	}
	racunposition temp = head;
	while (temp->next != NULL) {
		if (UsporediDatume(R, temp->next) == DATUM_KASNIJE) {
			temp = temp->next;
		}
		else if (UsporediDatume(R, temp->next) == DATUM_PRIJE) {
			R->next = temp->next;
			temp->next = R;
			R->head.next = NULL;
			return EXIT_SUCCESS;
		}
		else if (UsporediDatume(R, temp->next) == DATUM_ISTI) {
			return EXIT_FAILURE;
		}
	}
	R->next = temp->next;
	temp->next = R;
	R->head.next = NULL;
	return EXIT_SUCCESS;
}

int UsporediDatume(racunposition R1, racunposition R2) {
	int god1, god2;
	int mj1, mj2;
	int dan1, dan2;
	sscanf(R1->datum, "%d-%d-%d", &god1, &mj1, &dan1);
	sscanf(R2->datum, "%d-%d-%d", &god2, &mj2, &dan2);

	if (god1 > god2) {
		return DATUM_KASNIJE;
	}
	else if (god1 == god2 && mj1 > mj2) {
		return DATUM_KASNIJE;
	}
	else if (god1 == god2 && mj1 == mj2 && dan1 > dan2) {
		return DATUM_KASNIJE;
	}
	else if (god1 == god2 && mj1 == mj2 && dan1 == dan2) {
		return DATUM_ISTI;
	}
	else {
		return DATUM_PRIJE;
	}

}

int UcitajArtikleIzDatoteke(artiklposition head, char naziv[]) {
	FILE* dat = NULL;
	dat = fopen(naziv, "r");
	if (!dat) {
		printf("Datoteka se nije otvorila...");
		return EXIT_FAILURE;
	}
	char ime[15];
	int kolicina;
	double cijena;
	while (fgetc(dat) != '\n');
	while (1) {
		if (fscanf(dat, "%s %d %lf", ime, &kolicina, &cijena) != 3) {
			break;
		}
		fgetc(dat);
		KreirajISortiranoUbaciArtikl(head, ime, kolicina, cijena);
	}
	fclose(dat);
	return EXIT_SUCCESS;

}

int KreirajISortiranoUbaciArtikl(artiklposition head, char ime[], int kolicina, double cijena) {
	artiklposition novi = NULL;
	novi = (artiklposition)malloc(sizeof(artikl));
	if (novi == NULL) {
		printf("Memorija nije alocirana...");
		return EXIT_FAILURE;
	}
	strcpy(novi->ime, ime);
	novi->kolicina = kolicina;
	novi->cijena = cijena;
	if (head->next == NULL) {
		novi->next = head->next;
		head->next = novi;
		return EXIT_SUCCESS;
	}
	artiklposition temp = head;
	while (temp->next != NULL) {
		if (strcmp(novi->ime, temp->next->ime) > 0) {
			temp = temp->next;
		}
		else if (strcmp(novi->ime, temp->next->ime) < 0) {
			novi->next = temp->next;
			temp->next = novi;
			return EXIT_SUCCESS;
		}
		else if (strcmp(novi->ime, temp->next->ime) == 0) {
			temp->next->kolicina += kolicina;
			free(novi);
			return EXIT_SUCCESS;
		}
	}
	novi->next = temp->next;
	temp->next = novi;
	return EXIT_SUCCESS;
	return 0;
}

int IzlistajDatumeRacuna(racunposition head) {
	if (head->next == NULL) {
		printf("Nema racuna za izlistat...");
		return EXIT_FAILURE;
	}
	while (head->next != NULL) {
		head = head->next;
		printf("%s\n", head->datum);
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int IzlistajArtikleIzRacuna(racunposition head, int red) {
	if (head->next == NULL) {
		printf("Nema racuna za izlistat...");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < red; i++) {
		head = head->next;
		if (head == NULL) {
			printf("Unesen broj veci od broja racuna...");
			return EXIT_FAILURE;
		}
	}
	artiklposition arhead = &head->head;
	if (arhead == NULL) {
		printf("Nema artikala za izlistat...");
		return EXIT_FAILURE;
	}
	printf("Datum %s, racun po redu %d. sadrzaj:\n", head->datum, red);
	while (arhead->next != NULL) {
		arhead = arhead->next;
		printf("%s %d %lf\n", arhead->ime, arhead->kolicina, arhead->cijena);
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int PronadiArtiklUPeriodu(racunposition head, char trazi[], char datum1[], char datum2[], int* kolicina, double* cijena) {
	if (head->next == NULL) {
		printf("Nema racuna...");
		return EXIT_FAILURE;
	}
	*kolicina = 0;
	*cijena = 0;
	racun temp;
	strcpy(temp.datum, datum1);
	racunposition R1 = head->next;
	racunposition R2;
	while (UsporediDatume(R1, &temp) == DATUM_PRIJE) {
		R1 = R1->next;
		if (R1 == NULL) {
			printf("Datum je nakon zadnjega...\n");
			return EXIT_FAILURE;
		}
	}
	R2 = R1;
	strcpy(temp.datum, datum2);
	if (UsporediDatume(R2, &temp) == DATUM_KASNIJE) {
		printf("Datum je prije prvoga...\n");
		return EXIT_FAILURE;
	}
	while (UsporediDatume(R2, &temp) == DATUM_PRIJE) {
		R2 = R2->next;
		if (R2->next == NULL || UsporediDatume(R2->next, &temp) == DATUM_KASNIJE) {
			break;
		}
	}
	while (R1 != R2->next) {
		artiklposition temp = R1->head.next;
		if (temp == NULL) {
			printf("Nema artikala u racunu...");
			return EXIT_FAILURE;
		}
		while (strcmp(temp->ime, trazi) != 0) {
			temp = temp->next;
			if (temp == NULL) {
				break;
			}
		}
		if (temp != NULL) {
			*kolicina += temp->kolicina;
			*cijena = temp->cijena;
		}
		R1 = R1->next;
	}
	return EXIT_SUCCESS;
}