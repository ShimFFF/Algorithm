#include <stdio.h>

typedef struct elephant
{
    int weight;
    int iq;
    int idx;
}Elephant;

//자리 바꾸기
void swap(Elephant*a, Elephant*b){
    Elephant temp;
    temp = *a;
    *a=*b;
    *b=temp;
}

//무게 기준으로 증가
void sort(Elephant ele[], int len){
    for(int i=1;i<len;i++){
        for(int j=0;j<i;j++){
            
            if(ele[j].weight>ele[j+1].weight){ //앞에 것이 크면 swap
                swap(&ele[j], &ele[i]);
            }
            else if(ele[j].weight==ele[j+1].weight){//무게가 같으면 지능도 고려
                if(ele[j].iq<ele[j+1].iq){ //뒤의 아이큐가 크면 swap
                    swap(&ele[j], &ele[i]);
                }
            }
        }
    }

}

//맨 끝 값 리턴
int endNum(int a[]){
    int i=0;
    while (a[i]!=NULL)
    {
        i++;
    }
    return a[i-1];
}

//복사하고 element 추가
void copyPlus(int a[], int b[], int ele){
    int i=0;
    while(a[i]!=NULL){
        b[i]=a[i];
        i++;
    }
    b[i]=ele;
}

// 사이즈 찾기
int size(int a[]){
    int i=0;

    while (a[i]){
        i++;
    }
    return i;
}

int main(){
    Elephant ele [1000]; //코끼리 저장용

    int len=0; //코끼리 수
    scanf_s("%d", &len);

    //입력
    for(int i=0;i<len;i++){
        scanf_s("%d %d", &ele[i].weight, &ele[i].iq);
        ele[i].idx=i+1; //인덱스
    }
    
    //정렬
    sort(ele, len);

    //LDS 찾기
    int LDS[1000][1000];
    int eleIdxSave[1000][1000];

    int size=0; //마지막 루프 사이즈 저장에 씀
    int longIdx=0; //가장 긴거 인덱스 저장

    for(int i=0;i<len;i++){
        for(int j=i-1;j>=0;j--){

            //마지막 루프
            if(i==len-1){
                int x=0;
                while (LDS[j][x]!=NULL){
                    x++;
                }
                if(x>size){
                    size=x;
                    longIdx=j;
                }

            }

            if(endNum(LDS[j])>ele[i].iq && i!=len-1){ //마지막이 아니여야함
                //무게가 같으면 안됨
                if(ele[endNum(eleIdxSave[j])].weight != ele[i].weight){
                    copyPlus(LDS[j],LDS[i], ele[i].iq); //리스트 중 찾으면 그거 그대로
                    copyPlus(eleIdxSave[j], eleIdxSave[i], ele[i].idx);
                    break;
                }
            }
        }
        
        //마지막 루프
        if(i==len-1){
            if(endNum(LDS[longIdx])>ele[i].iq){
                copyPlus(LDS[longIdx], LDS[i], ele[i].iq);
                copyPlus(eleIdxSave[longIdx], eleIdxSave[i], ele[i].idx);
                break;
            }
        }

        LDS[i][0]=ele[i].iq;
        eleIdxSave[i][0]=ele[i].idx;
    }

    //결과 출력
    printf("%d\n", size);
    
    for(int i=0;i<size;i++){
        printf("%d\n", eleIdxSave[len-1][i]);
    }

    return 0;
}