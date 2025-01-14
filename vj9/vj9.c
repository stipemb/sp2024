#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct _node;
typedef struct _node* Position;
typedef struct _node {
	int element;
	Position left;
	Position right;
} Node;


Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root, FILE* filePointer);
int replace(Position root);
int random();


int main() {
	Position root = NULL;
	srand(time(0));
	FILE* filePointer = fopen("inorder.txt", "w");

	root = insert(root, random());
	for (int i = 0; i < 10; i++) {
		insert(root, random());
	}

	inorder(root, filePointer);
	replace(root);

	fprintf(filePointer, "\n");
	inorder(root, filePointer);
	fclose(filePointer);
	return 0;
}


Position createNode(int value) {
	Position newNode = NULL;
	newNode = (Position)malloc(sizeof(Node));
	if (!newNode) {
		printf("Can't allocate memory!\n");
		return NULL;
	}

	newNode->element = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}


Position insert(Position root, int value) {
	if (root == NULL) {
		return createNode(value);
	}

	if (value < root->element)
		root->left = insert(root->left, value);
	else if (value >= root->element)
		root->right = insert(root->right, value);

	return root;
}


int inorder(Position root, FILE* filePointer) {
	if (!root) return;
	inorder(root->left, filePointer);
	fprintf(filePointer, "%d ", root->element);
	inorder(root->right, filePointer);
}



int replace(Position root) {
	int	leftElement = 0;
	int rightElement = 0;
	int originalElement = 0;
	if (root == NULL) {
		return 0;
	}
	leftElement = replace(root->left);
	rightElement = replace(root->right);
	originalElement = root->element;

	root->element = leftElement + rightElement;
	return originalElement + root->element;
}


int random() {
	int value = 0;
	value = rand() % 81 + 10;
	return value;
}