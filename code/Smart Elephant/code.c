# include <stdio.h>

typedef struct code
{
    int weight;
    int iq;
    int idx;
}Elephant;

//무게 기준으로 sort (증가하는 순으로)4
// weightSortList에 인덱스를 저장
void weightSort(Elephant ele [], int weightSortList [], int len){
    for(int i=1;i<len;i++){
        for(int j=0;j<i;j++){
            if(ele[j].weight>ele[i].weight)
        }
    }
}

//swap int List
void swap(int * a, int * b){
    int temp;
    temp=a;
    a=b;
    b=a;
}

int main(){
    FILE *file; // 파일 포인터 선언 
    char filename[] = "input.txt"; // 파일 이름
    int line_count = 0; // 행의 개수 카운트
    Elephant elephants[1000]; // Elephant 구조체 배열

    // 파일 열기
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }

    // 파일 끝까지 데이터 읽기
    while (!feof(file)) {
        int weight, iq;
        if (fscanf(file, "%d %d", &weight, &iq) != 2) {
            break; // 파일 끝에 도달하면 종료
        }

        // Elephant 구조체에 데이터 저장
        elephants[line_count].weight = weight;
        elephants[line_count].iq = iq;
        elephants[line_count].idx = line_count+1; // 인덱스는 1부터 시작

        line_count++; // 행 개수 증가
    }

    // 파일 닫기
    fclose(file);

    // 읽어온 데이터 출력 (예시)
    for (int i = 0; i < line_count; i++) {
        printf("Idx: %d, Weight: %d, IQ: %d\n", elephants[i].idx, elephants[i].weight, elephants[i].iq);
    }

    return 0;
}