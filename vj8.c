#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct _node;
typedef struct _node* Position;
typedef struct _node {
	int value;
	Position left;
	Position right;
} Node;


Position createNode(int value);
Position insert(Position root, int value);
void inorder(Position root);
void preorder(Position root);
void postorder(Position root);
int orderLevel(Position root);
Position Delete(Position current, int x);
Position FindBiggest(Position current);
Position FindSmallest(Position current);
Position Find(Position current, int x);

int main() {
	Position root = NULL;
	root = insert(root, 2);
	insert(root, 5);
	insert(root, 7);
	insert(root, 8);
	insert(root, 11);
	insert(root, 1);
	insert(root, 4);
	insert(root, 2);
	insert(root, 3);
	insert(root, 7);

	printf("inorder: ");
	inorder(root);
	printf("\n");

	printf("preorder: ");
	preorder(root);
	printf("\n");

	printf("postorder: ");
	postorder(root);
	printf("\n");

	printf("level order: ");
	orderLevel(root);
	printf("\n");

	Find(root, 7);


	return EXIT_SUCCESS;
}

Position createNode(int value)
{
	Position newNode = NULL;
	newNode = (Position)malloc(sizeof(Node));
	if (!newNode)
	{
		printf("couldn't allocate memory\n");
		return NULL;
	}
	newNode->value = value;
	newNode->right = NULL;
	newNode->left = NULL;
	return newNode;
}

Position insert(Position root, int value) {
	if (root == NULL)
		return createNode(value);

	if (value < root->value)
		root->left = insert(root->left, value);
	else if (value >= root->value)
		root->right = insert(root->right, value);

	return root;
}

void inorder(Position root)
{
	if (root == NULL)
		return;
	inorder(root->left);
	printf("%d ", root->value);
	inorder(root->right);
}

void preorder(Position root)
{
	if (root == NULL)
		return;
	printf("%d ", root->value);
	preorder(root->left);
	preorder(root->right);
}


void postorder(Position root)
{
	if (root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->value);
}

int orderLevel(Position root) {
	if (root == NULL)
		return EXIT_SUCCESS;

	Position queue[100] = { 0 };
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear) {
		Position current = queue[front++];

		printf("%d ", current->value);

		if (current->left != NULL)
			queue[rear++] = current->left;

		if (current->right != NULL)
			queue[rear++] = current->right;
	}

	return EXIT_SUCCESS;
}

Position Delete(Position current, int x)
{
	Position temp = NULL;
	if (current == NULL)
		printf("that element does not exist\n");
	else if (x < current->value)
		current->left = Delete(current->left, x);
	else if (x > current->value)
		current->right = Delete(current->right, x);
	else if (current->left != NULL && current->right != NULL)
	{
		temp = FindSmallest(current->right);
		current->value = temp->value;
		current->right = Delete(current->right, current->value);
	}
	else
	{
		temp = current;
		if (current->left == NULL)
			current = current->right;
		else
			current = current->left;
		free(temp);
	}
	return current;
}

Position FindSmallest(Position current)
{
	while (current->left != NULL)
		current = current->left;
	return current;
}

Position FindBiggest(Position current)
{
	while (current->right != NULL)
		current = current->right;
	return current;
}

Position Find(Position current, int x)
{
	if (current == NULL)
		return NULL;
	else if (x < current->value)
		return Find(current->left, x);
	else if (x > current->value)
		return Find(current->right, x);
	return current;
}