#include <stdio.h>
#include <math.h>

#define MAX_DOTS 30
#define MAX_EDGES (MAX_DOTS * (MAX_DOTS - 1) / 2)

typedef struct { //(x,y) 좌표 저장용도
    double x, y;
} Point;

typedef struct { //edge와 edge의 가중치 저장용도
    int start, end;
    double weight;
} Edge;

int parent[MAX_DOTS]; //MAX_DOTS 30
Edge edges[MAX_EDGES]; //최대 dege의 개수

// edge의 가중치 비교
// 앞(a)이 크면 1
// 뒤(b)가 크면 -1 
int compareEdges(const void *a, const void *b) {
    return (*(Edge *)a).weight > (*(Edge *)b).weight ? 1 : -1;
}

//find와 unionVertices는 유니온-파인드 자료구조에서 사용
//유니온-파인드 자료구조는 Kruskal 알고리즘에서 사용

//특정 노드의 루트 노드를 찾는 데 사용
int find(int vertex) {
    if (parent[vertex] == -1) return vertex; //parent[vertex] == -1이면 루트임
    return find(parent[vertex]);
}

//두 노드가 속한 서로 다른 집합을 합침
void unionVertices(int x, int y) {
    int xSet = find(x); //루트 찾기
    int ySet = find(y); //루트 찾기
    parent[xSet] = ySet; //하나로 합치기
}

//정점 간의 거리를 계산 (edge의 가중치르 구하기 위해)
double calculateDistance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n; //정점의 개수
    scanf("%d", &n);

    //정점을 입력받음
    Point dots[MAX_DOTS];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &dots[i].x, &dots[i].y);
    }

    //모든 정점 간의 거리(가중치)와 정점의 좌표를 edges에 저장
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges[edgeCount].start = i;
            edges[edgeCount].end = j;
            edges[edgeCount].weight = calculateDistance(dots[i], dots[j]);
            edgeCount++;
        }
    }

    // 간선을 가중치순으로 정렬, Kruskal 알고리즘 사용할 것이기 때문에
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    // 부모 배열 초기화
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }

    //Kruskal 알고리즘 진행
    double minimumLength = 0.0;
    int selectedEdges = 0;
    //정점의 개수 <= 선택된 edge의 개수 면 종료 (다 찾은 것음)
    for (int i = 0; i < edgeCount && selectedEdges < n - 1; i++) {
        int start = edges[i].start;
        int end = edges[i].end;

        // 루트가 같으면 사이클이 있는 것임
        if (find(start) != find(end)) { //사이클이 없으면
            unionVertices(start, end); // 두 노드를 합쳐
            minimumLength += edges[i].weight; //가중치를 더해
            selectedEdges++; //선택된 edge의 개수를 올림
        }
    }

    printf("%.2lf\n", minimumLength);

    return 0;
}
