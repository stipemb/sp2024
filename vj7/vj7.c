#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

struct direktorij;
typedef struct direktorij* pozicijad;
typedef struct direktorij {
	char ime[15];
	pozicijad next;
	pozicijad below;
}direktorij;

struct stogdirektorij;
typedef struct stogdirektorij* pozicijasd;
typedef struct stogdirektorij {
	pozicijad direktorij;
	pozicijasd next;
}stogdirektorij;

pozicijad stvoridirektorij(char[]);
bool odabir(pozicijad*, pozicijasd, char[]);
int md(pozicijad, char[]);
int cddir(pozicijad*, pozicijasd, char[]);
int cddot(pozicijad*, pozicijasd);
int dir(pozicijad);
int push(pozicijasd, pozicijad);
pozicijad pop(pozicijasd);
int forbiddenstogprint(pozicijasd, pozicijad);


int main() {
	direktorij head = { 0,NULL,NULL };
	stogdirektorij shead = { NULL,NULL };
	char strodabir[30];
	bool exit = false;
	char root[3] = { 'C',':','\0' };
	pozicijad cur = stvoridirektorij(root);
	head.next = cur;
	push(&shead, cur);

	while (exit == false) {
		forbiddenstogprint(&shead, cur);
		sscanf(" %[^\n]s", strodabir);
		exit = odabir(&cur, &shead, strodabir);
	}
	return 0;
}

pozicijad stvoridirektorij(char ime[]) {
	pozicijad novi = NULL;
	novi = (pozicijad)malloc(sizeof(direktorij));
	if (novi == NULL) {
		printf("Greska u alociranju memorije...");
		return NULL;
	}
	strcpy(novi->ime, ime);
	novi->next = NULL;
	novi->below = NULL;
	return novi;
}

bool odabir(pozicijad* cur, pozicijasd shead, char strodabir[]) {
	int broj;
	char prvi[15];
	char drugi[15];
	char treci[15];
	broj = sscanf(strodabir, "%s %s %s", prvi, drugi, treci);
	if (broj == 2 && strcmp("md", prvi) == 0) {
		md(*cur, drugi);
		return false;
	}
	else if (broj == 3 && strcmp("cd", prvi) == 0 && strcmp("dir", drugi) == 0) {
		cddir(cur, shead, treci);
		return false;
	}
	else if (strcmp("cd ..", strodabir) == 0 || strcmp("cd..", strodabir) == 0) {
		cddot(cur, shead);
		return false;
	}
	else if (strcmp("dir", strodabir) == 0) {
		dir(*cur);
		return false;
	}
	else if (strcmp("exit", strodabir) == 0) {
		return true;
	}
	else {
		printf("Nepoznata komanda... Unesite opet\n");
		return false;
	}
}

int md(pozicijad cur, char ime[]) {
	pozicijad novi = stvoridirektorij(ime);
	if (novi == NULL) {
		return EXIT_FAILURE;
	}
	pozicijad temp = cur->below;
	if (cur->below == NULL) {
		cur->below = novi;
		return EXIT_SUCCESS;
	}
	while (strcmp(temp->ime, novi->ime) < 0 && temp->next != NULL) {
		if (strcmp(temp->next->ime, novi->ime) > 0 && temp->next != NULL) {
			break;
		}
		temp = temp->next;
	}
	novi->next = temp->next;
	temp->next = novi;
	return EXIT_SUCCESS;
}

int cddir(pozicijad* cur, pozicijasd shead, char ime[]) {
	if (strcmp((*cur)->ime, "C:") != 0) {
		push(shead, *cur);
	}
	pozicijad temp = (*cur)->below;
	if (temp == NULL) {
		printf("Nema poddirektorija...\n");
		if (strcmp((*cur)->ime, "C:") != 0) {
			pop(shead);
		}
		return EXIT_FAILURE;
	}
	while (strcmp(temp->ime, ime) != 0) {
		temp = temp->next;
		if (temp == NULL) {
			printf("Nije pronaden...\n");
			pop(shead);
			return EXIT_FAILURE;
		}
	}
	*cur = temp;
	return EXIT_SUCCESS;

}

int cddot(pozicijad* cur, pozicijasd shead) {
	*cur = pop(shead);
	return EXIT_SUCCESS;
}

int dir(pozicijad cur) {
	printf("%s\n", cur->ime);
	pozicijad temp = cur->below;
	if (temp == NULL) {
		printf("\tempty...\n");
		return EXIT_FAILURE;
	}
	while (temp != NULL) {
		printf("\t%s\n", temp->ime);
		temp = temp->next;
	}
	return EXIT_SUCCESS;

}


int push(pozicijasd head, pozicijad novi) {
	pozicijasd temp = NULL;
	temp = (pozicijasd)malloc(sizeof(stogdirektorij));
	if (temp == NULL) {
		printf("Neuspjesno alociranje memorije...");
		return EXIT_FAILURE;
	}
	temp->direktorij = novi;
	temp->next = head->next;
	head->next = temp;
	return EXIT_SUCCESS;
}

pozicijad pop(pozicijasd head) {
	if (strcmp(head->next->direktorij->ime, "C:") == 0) {
		return head->next->direktorij;
	}
	pozicijad ret = head->next->direktorij;
	pozicijasd del = head->next;
	head->next = head->next->next;
	free(del);
	return ret;
}

int forbiddenstogprint(pozicijasd shead, pozicijad cur) {
	pozicijasd temp = shead->next;
	pozicijasd forb = NULL;
	while (temp != forb) {
		while (temp->next != forb) {
			temp = temp->next;
		}
		forb = temp;
		printf("%s\\", temp->direktorij->ime);
		temp = shead->next;
	}
	if (strcmp(cur->ime, "C:") != 0) {
		printf("%s", cur->ime);
	}
	printf("> ");
	return EXIT_SUCCESS;
}