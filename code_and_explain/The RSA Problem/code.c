#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct {
    uint64_t n; // 모듈로 값
    uint64_t e; // 공개 지수
} RSAPublicKey;

// 함수 정의: 확장된 유클리드 알고리즘을 사용하여 역 모듈로 값을 계산
uint64_t extendedEuclidean(uint64_t a, uint64_t b, int64_t *x, int64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int64_t x1, y1;
    uint64_t gcd = extendedEuclidean(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

// RSA 문제 해결 함수: 공개 키 n, e 및 암호문 C를 사용하여 원본 메시지 M을 계산
uint64_t solveRSA(uint64_t n, uint64_t e, uint64_t C) {
    int64_t x, y;
    uint64_t gcd = extendedEuclidean(e, n - 1, &x, &y);

    if (gcd != 1) {
        printf("해당 공개 키와 암호문으로는 원본 메시지를 복원할 수 없습니다.\n");
        return 0;
    }

    // 원본 메시지 M 계산
    int64_t M = 1;
    for (uint64_t i = 0; i < e; i++) {
        M = (M * C) % n;
    }

    return M;
}

int main() {
    RSAPublicKey publicKey; // 공개키

    printf("Enter the public Key e: ");
    scanf("%" SCNu64, &publicKey.e);

    printf("Enter the public Key n: ");
    scanf("%" SCNu64, &publicKey.n);

    uint64_t ciphertext = 0; // 암호문

    while (1) { // 유효한 암호문인지 검사
        printf("Enter the ciphertext: ");
        if (scanf("%" SCNu64, &ciphertext) == 1) {
            // SCNu64 uint64_t 자료형의 서식 지정자
            break;
        } else {
            printf("Invalid input\n");
        }
    }

    uint64_t originalMessage = solveRSA(publicKey.n, publicKey.e, ciphertext);

    if (originalMessage != 0) {
        printf("원본 메시지: %" PRIu64 "\n", originalMessage);
    }

    return 0;
}
