/*
입력
- 입력 집합은 점의 개수를 나타내는 정수 N(0 ≤ N ≤ 30)으로 시작합니다.
- 다음 N개의 줄에는 N개의 2차원 점들의 좌표가 포함됩니다.
⎼ 두 숫자는 각각 N개의 2차원 점의 x 및 y 좌표를 나타냅니다.
- N = 0인 세트는 처리되지 않아야 합니다. (입력 종료를 의미)
- 모든 좌표는 40,000보다 작은 값을 가지며 음수가 아닙니다.

출력
- 각 입력 세트에 대해, 두 가장 가까운 점 사이의 거리를 나타내는 소수점 둘째 자리까지의 부동 소수점 수를 포함하는 한 줄을 출력합니다.
- 거리가 10,000보다 작은 두 점이 존재하지 않으면, "Infinity"라는 줄을 출력합니다.
*/

#include <stdio.h>

#define MAX 30000 
#define INF 1000000000

typedef struct { // 좌표 구조체
    int x, y;
} Point;

int N; // 점의 개수
Point p[MAX]; // 좌표 배열

// 작은 값 구하기
int min(int a, int b) {
    return a < b ? a : b;
}

// x좌표 기준 정렬
int compareX(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->x - p2->x;
}

// y좌표 기준 정렬
int compareY(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->y - p2->y;
}

// 두 점 사이의 거리 구하기
int dist(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// 가장 가까운 두 점 사이의 거리 구하기
int closestPair(int left, int right) {
    int d = INF;
    if (left == right) return d; // 점이 하나인 경우
    if (left + 1 == right) return dist(p[left], p[right]); // 점이 두 개인 경우
    int mid = (left + right) / 2; // 중간 값
    int d1 = closestPair(left, mid); // 왼쪽 절반
    int d2 = closestPair(mid + 1, right); // 오른쪽 절반

    d = min(d1, d2); // 두 절반 중 작은 값

    Point midPoint = p[mid]; // 중간 값
    Point strip[MAX]; // 중간을 기준으로 가까운 거리에 있는 점들

    int j = 0; // strip 배열의 인덱스
    for (int i = left; i <= right; i++) {
        int dx = midPoint.x - p[i].x; // 중간 값과의 x좌표 차이
        if (dx * dx < d) { // x좌표 차이가 d보다 작은 경우
            strip[j++] = p[i]; // strip 배열에 추가
        }
    }
    qsort(strip, j, sizeof(Point), compareY); // y좌표 기준 정렬
    for (int i = 0; i < j; i++) { // strip 배열의 모든 점에 대해
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y)*(strip[k].y - strip[i].y) < d; k++) { // y좌표 차이가 d보다 작은 경우
            int d3 = dist(strip[i], strip[k]); 
            d = min(d, d3); // 두 점 사이의 거리가 d보다 작은 경우 d 갱신
        }
    }
    return d;
}

int main() {
    while (1) {
        scanf("%d", &N);
        if (N == 0) break;

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);// 좌표 입력
        }
        // x좌표 기준 정렬
        qsort(p, N, sizeof(Point), compareX);
        int d = closestPair(0, N - 1); // 가장 가까운 두 점 사이의 거리 구하기

        if (d < 10000) {
            printf("%.4lf\n", sqrt(d)); // 거리 출력
        }
        else {
            printf("Infinity\n");
        }
    }
    return 0;
}

// Path: code_and_explain/A%20Marketing%20Strategy/explain.txt