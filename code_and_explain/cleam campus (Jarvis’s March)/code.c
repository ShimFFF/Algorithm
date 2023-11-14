//Jarvis's March 알고리즘을 사용
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

// Jarvis's March 알고리즘
double jarvisMarch() {
    int i, j, k, m;
    double sum = 0;
    Point tmp;
    Point hull[MAX]; // 볼록 껍질
    int hullSize = 0; // 볼록 껍질 크기

    // 가장 왼쪽 점 찾기
    k = 0;
    for (i = 1; i < N; i++) {
        if (p[i].x < p[k].x) k = i; // x좌표가 가장 작은 점
    }

    // 볼록 껍질 구하기
    m = k;
    do {
        hull[hullSize++] = p[m]; // 볼록 껍질에 추가
        j = m;
        m = (j + 1) % N; // 다음 점
        for (i = 0; i < N; i++) {
            // 외적이 양수인 점 찾기
            if ((p[i].x - p[j].x)*(p[m].y - p[j].y) - (p[i].y - p[j].y)*(p[m].x - p[j].x) > 0) {
                m = i;
            }
        }
    } while (m != k);

    // 볼록 껍질의 둘레 구하기
    for (i = 0; i < hullSize; i++) {
        tmp.x = hull[i].x - hull[(i + 1) % hullSize].x;
        tmp.y = hull[i].y - hull[(i + 1) % hullSize].y;
        sum += sqrt(tmp.x*tmp.x + tmp.y*tmp.y);
    }
}

//모든 신입생을 에워싸기 위해 필요한 실크의 길이를 
//소수점 두 자리까지 출력
int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &p[i].x, &p[i].y);
    }
    printf("%.2lf\n", jarvisMarch());
    return 0;
}
