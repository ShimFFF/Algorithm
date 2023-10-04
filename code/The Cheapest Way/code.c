#include <stdio.h>

int main() {
    FILE *file; // 파일 포인터 선언
    char filename[] = "matrices.txt"; // 파일 이름
    int m, n; // 행렬의 행과 열 크기
    int matrix[10][100]; // 최대 크기의 행렬을 저장하기 위한 배열

    // 파일 열기
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }

    while (fscanf(file, "%d %d", &m, &n) == 2) {
        // 행렬 요소 읽어서 저장
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                fscanf(file, "%d", &matrix[i][j]);
            }
        }

        // 행렬 출력
        printf("Matrix (%d x %d):\n", m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // 파일 닫기
    fclose(file);

    return 0;
}