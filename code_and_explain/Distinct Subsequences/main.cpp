/*
문자열 X 안에서 문자열 Z가 서로 다른 인덱스 순서를 가지고
등장하는 서로 다른 서브시퀀스의 수를 세기

입력:
- 첫 번째 줄에는 정수 N이 주어지며, 이는 테스트 케이스의 수를 나타냄
- 각 테스트 케이스는 두 줄로 구성
- 첫 번째 줄에는 문자열 X가 주어짐
    이 문자열은 소문자 알파벳으로 이루어져 있으며 길이는 최대 10,000임
- 두 번째 줄에는 문자열 Z가 주어짐
    이 문자열도 소문자 알파벳으로 이루어져 있으며 길이는 최대 100임

출력:
각 테스트 케이스에 대해, 문자열 X에서 문자열 Z가
서로 다른 인덱스 순서로 등장하는 서로 다른 서브시퀀스의 수를 출력
- 각 입력에 대한 출력은 다른 줄에 출력
*/

/*
접근 방법
1. dp[0][i], dp[j][0]을 0으로 초기화 해줌
1. 문자열 X를 순회하면서 문자열 Z의 첫 번째 문자와 일치하는 문자를 찾음
2. 일치하면 +1 값을 해서 할당. (끝까지 해줌 dp[j][1]++;) (일치하지 않으면 dp[j][1]=dp[j-1][1])
2. 그 후 dp 값을 모두 채워감.
2. 일치하는 문자를 찾으면, dp[j][i]=dp[j-1][i]+dp[j][i-1] 의 값을 할당
3. dp[x'][z']의 값이 서로 다른 인덱스 순서로 등장하는 서로 다른 서브시퀀스의 수
    (x'=X의 길이 z'=Z의 길이)
*/

#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

//입력 버퍼 지우기
void ClearLineFromReadBuffer(void)
{
    while (getchar() != '\n');

}

//DistinctSubsequence의 주요 로직
int DistinctSub( char strx[], char strz[]) {

    int m = strlen(strx);
    int n = strlen(strz);

    // dp[i][j]에 저장
    int** dp = (int**)malloc((m+1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int*)malloc((n+1) * sizeof(int));
    }

    //초기화
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[j][i] = 0;
        }
    }
    for (int j = 1; j <= m; j++) {
        dp[j][1] = dp[j - 1][1];
        if (strx[j - 1] == strz[0]) {
            dp[j][1]++;
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j=1; j <= m; j++) {
            if (strx[j - 1] == strz[i - 1]) {//같음, 옆 값과 위 값을 더한 값
                dp[j][i] = dp[j-1][i] + dp[j][i-1];
            }
            else { //다르면 바로 전값
                dp[j][i] = dp[j - 1][i];
            }
        }
    }

    int result= dp[m][n];

    //동적 할당 해제
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {

    //test case
    /*int result1, result2, result3;
    char strx1[] = "abcbcdab";
    char strz1[] = "bcd";
    result1=DistinctSub(strx1, strz1);
    printf("Result 1: %d\n", result1);

    char strx2[] = "banana";
    char strz2[] = "ana";
    result2=DistinctSub(strx2, strz2);
    printf("Result 2: %d\n", result2);

    char strx3[] = "mississippi";
    char strz3[] = "issip";
    result3=DistinctSub(strx3, strz3);
    printf("Result 3: %d\n", result3);

    return 0;*/


    int testNum=0;
     printf("Enter the test case number : ");
     scanf_s("%d", &testNum);
     ClearLineFromReadBuffer();

     int *result;
     result=(int *)malloc(sizeof(int)*testNum);
     if(result == NULL){
         printf("malloc error"); //메모리 할당에 실패
         return 0;
     }

     char strX[10001];
     char strZ[101];

     //문자열 입력받고 DistinctSub 계산
     for(int i=0;i<testNum;i++){
         printf("Enter the String X : ");
         fgets(strX, sizeof(strX), stdin);
         if (strX[strlen(strX) - 1] == '\n') {
             strX[strlen(strX) - 1] = '\0'; // 개행 문자 제거
         }

         printf("Enter the String Z : ");
         fgets(strZ, sizeof(strZ), stdin);
         if (strZ[strlen(strZ) - 1] == '\n') {
             strZ[strlen(strZ) - 1] = '\0'; // 개행 문자 제거
         }

         result[i]=DistinctSub(strX, strZ);
     }

     //정답 출력
     for(int i=0;i<testNum;i++){
         printf("\n\nCase %d : %d", i+1, result[i]);
     }
     free(result);
     return 0;
}