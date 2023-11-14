//Graham's scan 알고리즘을 사용
/*
신입생들이 있는 영역의 둘레를 따라 
걸어가며 실크를 당겨 모두를 에워싸려고 합니다.
선배는 모든 신입생을 에워쌀 최소한의 실크를 사용
말뚝(0,0)
신입생 수는 최대 100명

입력
첫 줄에는 신입생의 수 N이 주어집니다. (1 ≤ N ≤ 100)
두 번째 줄부터 N개의 줄에는 신입생의 좌표가 주어집니다.

출력
첫 줄에는 모든 신입생을 에워싸기 위해 필요한 실크의 길이를 
소수점 두 자리까지 출력합니다.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

typedef struct {
    int x, y;
} Point;

int N; // 신입생 수
Point p[MAX]; // 신입생 좌표 배열

// Graham's scan 알고리즘
double grahamScan() {
    int i, j, k, m;
    double sum = 0;
    Point tmp;
    Point hull[MAX]; // 볼록 껍질
    int hullSize = 0; // 볼록 껍질 크기

    // 가장 아래 점 찾기
    k = 0;
    for (i = 1; i < N; i++) {
        if (p[i].y < p[k].y) k = i; // y좌표가 가장 작은 점
    }

    // 가장 아래 점을 p[0]과 교환
    tmp = p[0];
    p[0] = p[k];
    p[k] = tmp;

    // p[0]을 기준으로 각도순으로 정렬
    for (i = 1; i < N - 1; i++) {
        k = i;
        for (j = i + 1; j < N; j++) {
            // 외적이 양수인 점 찾기
            if ((p[j].x - p[0].x)*(p[k].y - p[0].y) - (p[j].y - p[0].y)*(p[k].x - p[0].x) > 0) {
                k = j;
            }
        }
    }
}

//모든 신입생을 에워싸기 위해 필요한 실크의 길이를 
//소수점 두 자리까지 출력
int main(void) {
    int i;
    double result;

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d %d", &p[i].x, &p[i].y);
    }

    result = grahamScan();
    printf("%.2lf\n", result);

    return 0;
}