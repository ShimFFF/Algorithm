/*
* �Ϸ� ������ �޾� ���� ���� ������ �� �� �ִ� �ð� ã��
* input : �� ���� ���� (Int) (100 ���� ����)
* input : "HH:MM hh:mm ���� ����"
* -> (��� ������ 10:00���� 18:00 ���̿� ����)(�� ���� ���� ��ŭ �Է� ��)
* -> HH:MM (���� �ð�), hh:mm (���� �ð�)
* output : "Day#n : the longest nap starts at hh:mm and will last for Y hours and X minutes"
* n(day �� ����), hh:mm(���� ���� �ð�), Y hours and X minutes(���� �� �� �ִ� �ð�)
*
* */

//#define DEBUG
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct
{
	int startHour;
	int startMin;
	int endHour;
	int endMin;

}ScheduleTime;

void ClearLineFromReadBuffer(void);
bool setScheduleTimeFromString(char schedule[], ScheduleTime* scheduleTime);
bool isScheduleBefore(ScheduleTime* a, ScheduleTime* b);
void ScheduleSwap(ScheduleTime schedule[], int a, int b);
int calculateTimeDifferenceInMinutes(ScheduleTime* early, ScheduleTime* late);


int main() {

	int a = 1;
	int i = 0;

	while (a==1) {
		i++;
		printf("Enter your Schedules number : ");
		int num = 0; //����� ����
		scanf_s("%d", &num);
#ifdef DEBUG
		printf("\n\n������ %d��\n\n", num);
#endif // DEBUG

		printf("Enter your Schedules\n");
		char scheduleStr[100]; //���ڿ� �����
		ScheduleTime scheduleTime[100]; //������ �ð� �����
		ClearLineFromReadBuffer();

		//10�� ���� ����
		char startTime[50] = "10:00 10:00";
		sscanf_s(startTime, "%d:%d %d:%d", &scheduleTime[0].startHour, &scheduleTime[0].startMin, &scheduleTime[0].endHour, &scheduleTime[0].endMin);

		for (int i = 1; i <= num; i++) {
			printf("Schedules %d :", i);
			fgets(scheduleStr, sizeof(scheduleStr), stdin);

#ifdef DEBUG
			printf("%d�����ڿ� Ȯ�� : %s", i+1, scheduleStr);
#endif // DEBUG

			// ���� ����('\n') ����
			size_t len = strlen(scheduleStr);
			if (len > 0 && scheduleStr[len - 1] == '\n') {
				scheduleStr[len - 1] = '\0';
			}

			// ��ȿ�� �Է��� ���� ������ ��õ�
			if (!setScheduleTimeFromString(scheduleStr, &scheduleTime[i])) {
				printf("Invalid input. Please enter the schedule in the correct format.\n");
				i--; // �ٽ� �Է��ϵ��� �ε����� �ϳ� ���ҽ�Ŵ
				continue;
			}

			//����
			if (i != 0) {
				if (!isScheduleBefore(&scheduleTime[i - 1], &scheduleTime[i])) {
					ScheduleSwap(scheduleTime, i - 1, i);
				}
			}


			//���ڿ� �ʱ�ȭ
			for (int i = 0; i < sizeof(scheduleStr); i++) {
				scheduleStr[i] = '\0';
			}
		}

		//18�� ���� ����
		char endTime[50] = "18:00 18:00";
		sscanf_s(endTime, "%d:%d %d:%d", &scheduleTime[num+1].startHour, &scheduleTime[num+1].startMin, &scheduleTime[num+1].endHour, &scheduleTime[num+1].endMin);


		ScheduleTime napStartScheduleTime; //���� �� �ִ� ���� �ð��� �� �� �ִ� ������
		int napMaxMin = 0; //�ִ� ���� �ð�

		int tempMin = 0; //���� �ð� ���� �����

		//�� ������ ������ �ð� ���ϱ�
		for (int i = 0; i <= num; i++) {
			tempMin = calculateTimeDifferenceInMinutes(&scheduleTime[i], &scheduleTime[i+1]);

			//maxMin ������Ʈ
			if (napMaxMin < tempMin) { 
				napMaxMin = tempMin;
				napStartScheduleTime = scheduleTime[i];
			}
			tempMin = 0; //�ʱ�ȭ

		}

		//��� ���
		printf("Day#%d : the longest nap starts at %d:%d and will last for %d hours and %d minutes\n\n",
			i, napStartScheduleTime.endHour, napStartScheduleTime.endMin, napMaxMin / 60, napMaxMin % 60);

		printf("If you want to calculate Day %d sweet nap enter 1 , if not enter 0 : ", i+1);
		scanf_s("%d", &a);
		printf("\n\n\n\n");
	}

	return 0;
}

//�Է� ���� ����
void ClearLineFromReadBuffer(void)
{
	while (getchar() != '\n');

}


void ScheduleSwap(ScheduleTime scheduleTime[], int a, int b) {
	//a�� b�� ��ȿ�� ���� �ƴ� ���
	if (a < 0 || b < 0)
		return;

	ScheduleTime temp = scheduleTime[a];
	scheduleTime[a] = scheduleTime[b];
	scheduleTime[b] = temp;
}

//substring ����, start indx���� end indx���� substring
void substring(char str[100], int start, int end, char result[100]) {
	if (start < 0 || end < 0 || start > end || start >= strlen(str)) {
		// ���� ó��: ���� ��ġ�� �� ��ġ�� ��ȿ���� �ʰų�, ���� ��ġ�� ���ڿ� ���̺��� ũ�� �� ���ڿ� ��ȯ
		strcpy(result, "");
		return;
	}

	int len = end - start + 1; // ������ �κ� ���ڿ��� ���� ���

	// ���� ���ڿ����� ������ �κ� ���ڿ��� ����
	strncpy(result, str + start, len);
	result[len] = '\0'; // �κ� ���ڿ� ���� NULL ���� �߰�
}


//���ڿ��� ������ scheduleTime�� ����
bool setScheduleTimeFromString(char schedule[], ScheduleTime* scheduleTime) {

	/*
	strtok(char* str, char* delimiters);
	-> ���ڿ� ��ūȭ, str: �Ű躯��, delimiters: ������(�� ���ڸ� �������� ���ڿ��� �ڸ�)
	��ȯ�� : ������(���ڿ��� �����͸� �ϳ��� ��ȯ)
	->  strtok(NULL, " "); �Լ��� ȣ���ϸ� ������ ã�� ������ �ں��� �ٽ� �����ڸ� ã��
	*/

	char* token = strtok(schedule, " "); //���� ���� ��ūȭ

	if (token == NULL) {
		return false; // ��ū�� ������ ��ȿ���� ���� �Է�
	}

	// ù ��° ��ū (���� �ð�) ó��
	sscanf_s(token, "%d:%d", &scheduleTime->startHour, &scheduleTime->startMin);

	token = strtok(NULL, " "); // ���� ��ū���� �̵�

	if (token == NULL) {
		return false; // ��ū�� ������ ��ȿ���� ���� �Է�
	}

	// �� ��° ��ū (���� �ð�) ó��
	sscanf_s(token, "%d:%d", &scheduleTime->endHour, &scheduleTime->endMin);
	//����ð��� �ð����� �ռ� ���
	if (scheduleTime->startHour > scheduleTime->endHour)
		return false;
	else {
		if (scheduleTime->startHour == scheduleTime->endHour && scheduleTime->startMin > scheduleTime->endMin)
			return false;
	}

	return true;

}


//���� �������� ������ true�� ����
bool isScheduleBefore(ScheduleTime* a, ScheduleTime* b) {
	if (a->startHour < b->startHour)
		return true;
	if (a->startMin < b->startMin)
		return true;

	return false;
}


// ������ ������ �ð� ���̸� ������ ����
// ���� �������� ���� �����ϴ� �������� �Է��������
int calculateTimeDifferenceInMinutes(ScheduleTime* early, ScheduleTime* late) {
	int earlierTotalMinutes = (early->endHour * 60) + early->endMin;
	int laterTotalMinutes = (late->startHour * 60) + late->startMin;

	return laterTotalMinutes - earlierTotalMinutes;
}

