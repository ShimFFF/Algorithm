/*
플립을 이용해서 스택을 오름차순으로 정렬 해야함
-> 큰 펜케익이 아래에, 작은게 위에

stack(스택) : 후입선출(LIFO - Last In, First Out) 자료 구조

filp(플립) : 시작 구간부터 끝까지 reversing됨
-> 제일 밑에 있는 팬케익이 1번자리
최대 팬케익 개수 -> 30
각 팬케익의 값 -> 1~10

input : 한줄의 팬케익 셋
output : original stack , 플립 순서 ,sorting pancake stack
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

// 스택 초기화
void initialize(Stack* stack) {
	stack->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* stack) {
	return stack->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* stack) {
	return stack->top == MAX_SIZE - 1;
}

// 스택에 데이터 추가 (Push)
void push(Stack* stack, int item) {
	if (isFull(stack)) {
		printf("스택이 가득 찼습니다.\n");
		return;
	}
	stack->data[++stack->top] = item;
}

// 스택에서 데이터 제거 및 반환 (Pop)
int pop(Stack* stack) {
	if (isEmpty(stack)) {
		printf("스택이 비어 있습니다.\n");
		return -1; // 에러를 나타내는 값
	}
	return stack->data[stack->top--];
}

// 스택에서 최상위 데이터 반환 (Peek)
int peek(Stack* stack) {
	if (isEmpty(stack)) {
		printf("스택이 비어 있습니다.\n");
		return -1; // 에러를 나타내는 값
	}
	return stack->data[stack->top];
}

//스택 출력
void printStack(Stack* stack) {
	for (int i = stack->top; i >= 0; i--) {
		printf("%d ", stack->data[i]);
	}
	printf("\n");
}

//지정된 위치부터 top까지 reversing 
void flip(Stack* stack, int  num) {

	int index = num - 1;

	if (isEmpty(stack) || index < 0 || index > stack->top) {
		printf("invalid input.\n");
		return;
	}

	printf("flip : %d \n", num);

	// 임시 스택을 생성하여 역순 데이터 저장
	Stack temp;
	initialize(&temp);

	// 지정된 위치(index)까지 원소를 복사
	for (int i = 0; i < index; i++) {
		push(&temp, stack->data[i]);
	}

	// 나머지 원소를 역순으로 push하여 temp 스택에 저장
	for (int i = stack->top; i >= index; i--) {
		push(&temp, stack->data[i]);
	}

	*stack = temp; // temp 스택의 내용을 원래 스택으로 복사

#ifdef DEBUG
	printStack(stack);
#endif // DEBUG


}

//팬케익 정렬용 플립
void pancakeFlip(Stack *stack, int *prvFlip, int i, bool *flipped) {
	if (*prvFlip == i + 2) { //이전에 플립과 같은 index일 경우
		flip(stack, i + 1);
		*flipped = true;
		*prvFlip = i + 1;
	}
	else {
		flip(stack, i + 2); //i+1 인덱스부터 플립됨
		*prvFlip = i + 2;
		*flipped = true;
	}
}

//플립을 이용한 sort
void pancakeSort(Stack* stack) {
	int top = stack->top;

	int prvFlip = -1;

	while(1) {
		bool flipped = false; // 뒤집기 여부

		if (stack->data[top] > stack->data[0]) {
			//끝에 값이 위에 값보다 작음
			for (int i = 0; i <= top; i++) {
				if (i == top) {
					flip(stack, 1);
					flipped = true;
					continue; // 뒤집기 후 종료 조건 확인
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
			//끝에 값이 위에 값보다 큼
			for (int i = 0; i <= top; i++) {
				if (stack->data[i+1] > stack->data[i]) {
					pancakeFlip(stack, &prvFlip, i, &flipped);
				}
				else if (stack->data[top] > stack->data[i]) {
					pancakeFlip(stack, &prvFlip, i - 1, &flipped);
				}
			}
		}
		else { //끝 값과 위의 값이 같은 경우
			flip(stack, 2); 
			prvFlip = 2;
			flipped = true;
		}

		if (!flipped) {
			return; // 뒤집지 않았으면 종료
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

		//스택에 펜케익 추가 
		token = strtok(pancakeSet, " "); //공백 기준 토큰화
		pancakeNum = 0;
		initialize(&pancake); //스택 초기화 
		while (token != NULL) {
			sscanf_s(token, "%d", &pancakeNum);
			push(&pancake, pancakeNum); //스텍에 추가
			token = strtok(NULL, " "); // 다음 토큰으로 이동
		}

		//원래 스택 출력
		printf("original pancake : ");
		printStack(&pancake);

		//stack sort
		pancakeSort(&pancake);

		//정렬된 스택 출력
		printf("\nsorted pancake : ");
		printStack(&pancake);

		
		
		printf("If you want to restart program enter 1, if not enter 0 : ");
		scanf_s("%d", &i);
		while (getchar() != '\n');


	}

	return 0;
}

