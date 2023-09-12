/*
�ø��� �̿��ؼ� ������ ������������ ���� �ؾ���
-> ū �������� �Ʒ���, ������ ����

stack(����) : ���Լ���(LIFO - Last In, First Out) �ڷ� ����

filp(�ø�) : ���� �������� ������ reversing��
-> ���� �ؿ� �ִ� �������� 1���ڸ�
�ִ� ������ ���� -> 30
�� �������� �� -> 1~10

input : ������ ������ ��
output : original stack , �ø� ���� ,sorting pancake stack
*/

#define _CRT_SECURE_NO_WARNINGS
#define DEBUG

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX_SIZE 30

typedef struct {
	int data[MAX_SIZE];
	int top;
}Stack;

// ���� �ʱ�ȭ
void initialize(Stack* stack) {
	stack->top = -1;
}

// ������ ����ִ��� Ȯ��
int isEmpty(Stack* stack) {
	return stack->top == -1;
}

// ������ ���� á���� Ȯ��
int isFull(Stack* stack) {
	return stack->top == MAX_SIZE - 1;
}

// ���ÿ� ������ �߰� (Push)
void push(Stack* stack, int item) {
	if (isFull(stack)) {
		printf("������ ���� á���ϴ�.\n");
		return;
	}
	stack->data[++stack->top] = item;
}

// ���ÿ��� ������ ���� �� ��ȯ (Pop)
int pop(Stack* stack) {
	if (isEmpty(stack)) {
		printf("������ ��� �ֽ��ϴ�.\n");
		return -1; // ������ ��Ÿ���� ��
	}
	return stack->data[stack->top--];
}

// ���ÿ��� �ֻ��� ������ ��ȯ (Peek)
int peek(Stack* stack) {
	if (isEmpty(stack)) {
		printf("������ ��� �ֽ��ϴ�.\n");
		return -1; // ������ ��Ÿ���� ��
	}
	return stack->data[stack->top];
}

//���� ���
void printStack(Stack* stack) {
	for (int i = stack->top; i >= 0; i--) {
		printf("%d ", stack->data[i]);
	}
	printf("\n");
}

//������ ��ġ���� top���� reversing 
void flip(Stack* stack, int  num) {

	int index = num - 1;

	if (isEmpty(stack) || index < 0 || index > stack->top) {
		printf("invalid input.\n");
		return;
	}

	printf("flip : %d \n", num);

	// �ӽ� ������ �����Ͽ� ���� ������ ����
	Stack temp;
	initialize(&temp);

	// ������ ��ġ(index)���� ���Ҹ� ����
	for (int i = 0; i < index; i++) {
		push(&temp, stack->data[i]);
	}

	// ������ ���Ҹ� �������� push�Ͽ� temp ���ÿ� ����
	for (int i = stack->top; i >= index; i--) {
		push(&temp, stack->data[i]);
	}

	*stack = temp; // temp ������ ������ ���� �������� ����

#ifdef DEBUG
	printStack(stack);
#endif // DEBUG


}

//������ ���Ŀ� �ø�
void pancakeFlip(Stack *stack, int *prvFlip, int i, bool *flipped) {
	if (*prvFlip == i + 2) { //������ �ø��� ���� index�� ���
		flip(stack, i + 1);
		*flipped = true;
		*prvFlip = i + 1;
	}
	else {
		flip(stack, i + 2); //i+1 �ε������� �ø���
		*prvFlip = i + 2;
		*flipped = true;
	}
}

//�ø��� �̿��� sort
void pancakeSort(Stack* stack) {
	int top = stack->top;

	int prvFlip = -1;

	while(1) {
		bool flipped = false; // ������ ����

		if (stack->data[top] > stack->data[0]) {
			//���� ���� ���� ������ ����
			for (int i = 0; i <= top; i++) {
				if (i == top) {
					flip(stack, 1);
					flipped = true;
					continue; // ������ �� ���� ���� Ȯ��
				}
				if (stack->data[i+1] < stack->data[i]) {
					pancakeFlip(stack, &prvFlip, i, &flipped);
				}
				else if (stack->data[top] < stack->data[i]) {
					pancakeFlip(stack, &prvFlip, i-1, &flipped);
				}
			}
		}
		else if (stack->data[top] < stack->data[0]) {
			//���� ���� ���� ������ ŭ
			for (int i = 0; i <= top; i++) {
				if (stack->data[i+1] > stack->data[i]) {
					pancakeFlip(stack, &prvFlip, i, &flipped);
				}
				else if (stack->data[top] > stack->data[i]) {
					pancakeFlip(stack, &prvFlip, i - 1, &flipped);
				}
			}
		}
		else { //�� ���� ���� ���� ���� ���
			flip(stack, 2); 
			prvFlip = 2;
			flipped = true;
		}

		if (!flipped) {
			return; // ������ �ʾ����� ����
		}
	}
	
}

int main() {

	int i = 1;
	char pancakeSet[61];
	char* token;
	int pancakeNum = 0;
	Stack pancake;

	while (i == 1) {
		printf("Enter the pancake set  : ");
		fgets(pancakeSet, sizeof(pancakeSet), stdin);

		//���ÿ� ������ �߰� 
		token = strtok(pancakeSet, " "); //���� ���� ��ūȭ
		pancakeNum = 0;
		initialize(&pancake); //���� �ʱ�ȭ 
		while (token != NULL) {
			sscanf_s(token, "%d", &pancakeNum);
			push(&pancake, pancakeNum); //���ؿ� �߰�
			token = strtok(NULL, " "); // ���� ��ū���� �̵�
		}

		//���� ���� ���
		printf("original pancake : ");
		printStack(&pancake);

		//stack sort
		pancakeSort(&pancake);

		//���ĵ� ���� ���
		printf("\nsorted pancake : ");
		printStack(&pancake);

		
		
		printf("If you want to restart program enter 1, if not enter 0 : ");
		scanf_s("%d", &i);
		while (getchar() != '\n');


	}

	return 0;
}

