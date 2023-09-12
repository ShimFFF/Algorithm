/*
* 하루 일정을 받아 가장 많은 낮잠을 잘 수 있는 시간 찾기
* input : 총 일정 개수 (Int) (100 보다 작음)
* input : "HH:MM hh:mm 일정 설명"
* -> (모든 일정은 10:00에서 18:00 사이에 진행)(총 일정 개수 만큼 입력 됨)
* -> HH:MM (시작 시간), hh:mm (종료 시간)
* output : "Day#n : the longest nap starts at hh:mm and will last for Y hours and X minutes"
* n(day 몇 인지), hh:mm(낮잠 시작 시간), Y hours and X minutes(낮잠 잘 수 있는 시간)
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
		int num = 0; //몇개인지 저장
		scanf_s("%d", &num);
#ifdef DEBUG
		printf("\n\n스케줄 %d개\n\n", num);
#endif // DEBUG

		printf("Enter your Schedules\n");
		char scheduleStr[100]; //문자열 저장용
		ScheduleTime scheduleTime[100]; //스케줄 시간 저장용
		ClearLineFromReadBuffer();

		//10시 일정 시작
		char startTime[50] = "10:00 10:00";
		sscanf_s(startTime, "%d:%d %d:%d", &scheduleTime[0].startHour, &scheduleTime[0].startMin, &scheduleTime[0].endHour, &scheduleTime[0].endMin);

		for (int i = 1; i <= num; i++) {
			printf("Schedules %d :", i);
			fgets(scheduleStr, sizeof(scheduleStr), stdin);

#ifdef DEBUG
			printf("%d번문자열 확인 : %s", i+1, scheduleStr);
#endif // DEBUG

			// 개행 문자('\n') 제거
			size_t len = strlen(scheduleStr);
			if (len > 0 && scheduleStr[len - 1] == '\n') {
				scheduleStr[len - 1] = '\0';
			}

			// 유효한 입력을 받을 때까지 재시도
			if (!setScheduleTimeFromString(scheduleStr, &scheduleTime[i])) {
				printf("Invalid input. Please enter the schedule in the correct format.\n");
				i--; // 다시 입력하도록 인덱스를 하나 감소시킴
				continue;
			}

			//정렬
			if (i != 0) {
				if (!isScheduleBefore(&scheduleTime[i - 1], &scheduleTime[i])) {
					ScheduleSwap(scheduleTime, i - 1, i);
				}
			}


			//문자열 초기화
			for (int i = 0; i < sizeof(scheduleStr); i++) {
				scheduleStr[i] = '\0';
			}
		}

		//18시 일정 마감
		char endTime[50] = "18:00 18:00";
		sscanf_s(endTime, "%d:%d %d:%d", &scheduleTime[num+1].startHour, &scheduleTime[num+1].startMin, &scheduleTime[num+1].endHour, &scheduleTime[num+1].endMin);


		ScheduleTime napStartScheduleTime; //종료 후 최대 낮잠 시간을 잘 수 있는 스케줄
		int napMaxMin = 0; //최대 낮잠 시간

		int tempMin = 0; //낮잠 시간 차이 저장용

		//각 스케줄 사이의 시간 구하기
		for (int i = 0; i <= num; i++) {
			tempMin = calculateTimeDifferenceInMinutes(&scheduleTime[i], &scheduleTime[i+1]);

			//maxMin 업데이트
			if (napMaxMin < tempMin) { 
				napMaxMin = tempMin;
				napStartScheduleTime = scheduleTime[i];
			}
			tempMin = 0; //초기화

		}

		//결과 출력
		printf("Day#%d : the longest nap starts at %d:%d and will last for %d hours and %d minutes\n\n",
			i, napStartScheduleTime.endHour, napStartScheduleTime.endMin, napMaxMin / 60, napMaxMin % 60);

		printf("If you want to calculate Day %d sweet nap enter 1 , if not enter 0 : ", i+1);
		scanf_s("%d", &a);
		printf("\n\n\n\n");
	}

	return 0;
}

//입력 버퍼 비우기
void ClearLineFromReadBuffer(void)
{
	while (getchar() != '\n');

}


void ScheduleSwap(ScheduleTime scheduleTime[], int a, int b) {
	//a와 b가 유효한 수가 아닌 경우
	if (a < 0 || b < 0)
		return;

	ScheduleTime temp = scheduleTime[a];
	scheduleTime[a] = scheduleTime[b];
	scheduleTime[b] = temp;
}

//substring 구현, start indx부터 end indx까지 substring
void substring(char str[100], int start, int end, char result[100]) {
	if (start < 0 || end < 0 || start > end || start >= strlen(str)) {
		// 예외 처리: 시작 위치나 끝 위치가 유효하지 않거나, 시작 위치가 문자열 길이보다 크면 빈 문자열 반환
		strcpy(result, "");
		return;
	}

	int len = end - start + 1; // 추출할 부분 문자열의 길이 계산

	// 원본 문자열에서 추출할 부분 문자열을 복사
	strncpy(result, str + start, len);
	result[len] = '\0'; // 부분 문자열 끝에 NULL 문자 추가
}


//문자열의 정보를 scheduleTime에 저장
bool setScheduleTimeFromString(char schedule[], ScheduleTime* scheduleTime) {

	/*
	strtok(char* str, char* delimiters);
	-> 문자열 토큰화, str: 매계변수, delimiters: 구분자(이 문자를 기준으로 문자열을 자름)
	봔환값 : 포인터(문자열의 포인터를 하나씩 반환)
	->  strtok(NULL, " "); 함수를 호출하면 이전에 찾은 구분자 뒤부터 다시 구분자를 찾음
	*/

	char* token = strtok(schedule, " "); //공백 기준 토큰화

	if (token == NULL) {
		return false; // 토큰이 없으면 유효하지 않은 입력
	}

	// 첫 번째 토큰 (시작 시간) 처리
	sscanf_s(token, "%d:%d", &scheduleTime->startHour, &scheduleTime->startMin);

	token = strtok(NULL, " "); // 다음 토큰으로 이동

	if (token == NULL) {
		return false; // 토큰이 없으면 유효하지 않은 입력
	}

	// 두 번째 토큰 (종료 시간) 처리
	sscanf_s(token, "%d:%d", &scheduleTime->endHour, &scheduleTime->endMin);
	//종료시간이 시간보다 앞설 경우
	if (scheduleTime->startHour > scheduleTime->endHour)
		return false;
	else {
		if (scheduleTime->startHour == scheduleTime->endHour && scheduleTime->startMin > scheduleTime->endMin)
			return false;
	}

	return true;

}


//앞의 스케줄이 먼저면 true를 리턴
bool isScheduleBefore(ScheduleTime* a, ScheduleTime* b) {
	if (a->startHour < b->startHour)
		return true;
	if (a->startMin < b->startMin)
		return true;

	return false;
}


// 스케줄 사이의 시간 차이를 분으로 리턴
// 앞의 스케줄을 먼저 시작하는 스케줄을 입력해줘야함
int calculateTimeDifferenceInMinutes(ScheduleTime* early, ScheduleTime* late) {
	int earlierTotalMinutes = (early->endHour * 60) + early->endMin;
	int laterTotalMinutes = (late->startHour * 60) + late->startMin;

	return laterTotalMinutes - earlierTotalMinutes;
}

