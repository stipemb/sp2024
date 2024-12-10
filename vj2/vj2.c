#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 1024
#define MALLOC_ERROR (-1)
#define PERSON_ERROR (-2)
#define ELEMENT_ERROR (-3)
#define PRINT_ERROR (-4)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* new_osoba;

typedef struct osoba {
	char ime[64];
	char prezime[64];
	int godina;
	new_osoba Next;
} osoba;

int unosP(char ime[64], char prezime[64], int godina, new_osoba P);

int unosK(char ime[64], char prezime[64], int godina, new_osoba P);

int ispis(new_osoba P);

int traziPrez(char prezime[64], new_osoba P);

int brisiEl(char ime[64], char prezime[64], new_osoba P);


int main()
{
	new_osoba head = NULL;
	head = (new_osoba)malloc(sizeof(osoba));
	if (head == NULL) {
		printf("greska");
		return MALLOC_ERROR;
	}
	head->Next = NULL;
	unosP("Pero", "Peric", 2005, head);
	unosP("Ivo", "Ivic", 1985, head);
	unosK("Andro", "Andric", 1991, head);
	unosK("Duje", "Dujic", 1905, head);
	ispis(head->Next);
	traziPrez("Andric", head->Next);
	brisiEl("Pero", "Peric", head);
	brisiEl("Andro", "Andric", head);
	ispis(head->Next);
	traziPrez("Andric", head->Next);
	return EXIT_SUCCESS;

	return 0;
}

int unosP(char ime[64], char prezime[64], int godina, new_osoba P) {
	new_osoba Q = NULL;
	Q = (new_osoba)malloc(sizeof(osoba));
	if (Q == NULL) {
		printf("greska\n");
		return MALLOC_ERROR;
	}
	Q->Next = P->Next;
	P->Next = Q;
	strcpy(Q->ime, ime);
	strcpy(Q->prezime, prezime);
	Q->godina = godina;
	return EXIT_SUCCESS;

}

int unosK(char ime[64], char prezime[64], int godina, new_osoba P) {
	new_osoba Q = NULL;
	Q = (new_osoba)malloc(sizeof(osoba));
	
	if (Q == NULL) {
		printf("greska\n");
		return MALLOC_ERROR;
	}

	while (P->Next != NULL) {
		P = P->Next;
	}

	Q->Next = P->Next;
	P->Next = Q;
	strcpy(Q->ime, ime);
	strcpy(Q->prezime, prezime);
	Q->godina = godina;
	return EXIT_SUCCESS;
}

int ispis(new_osoba P) {
	if (P == NULL) {
		printf("greska\n");
		return PRINT_ERROR;
	}
	printf("Ispis:\n");
	while (P != NULL) {
		printf(" %s %s %d\n", P->ime, P->prezime, P->godina);
		P = P->Next;
	}
	return EXIT_SUCCESS;

}

int traziPrez(char prezime[64], new_osoba P) {
	while (P != NULL) {
		P = P->Next;
		if (strcmp(P->prezime, prezime) == 0) {
			printf(" %s: %s %s\n", prezime, P->ime, P->prezime);
			return EXIT_SUCCESS;
		}
		else if (strcmp(P->prezime, prezime) != 0 && P->Next == NULL) {
			printf("greska\n");
			return PERSON_ERROR;
		}
	}

	return EXIT_SUCCESS;
}

int brisiEl(char ime[64], char prezime[64], new_osoba P) {
	new_osoba Q = NULL;
	while (P->Next != NULL) {
		Q = P;
		P = P->Next;
		if (strcmp(P->ime, ime) == 0 && strcmp(P->prezime, prezime) == 0) {
			Q->Next = P->Next;
			P->Next = NULL;
			free(P);
			return EXIT_SUCCESS;
		}
		if (P->Next == NULL) {
			printf("nema\n");
			return ELEMENT_ERROR;
		}
	}
	return EXIT_SUCCESS;
}