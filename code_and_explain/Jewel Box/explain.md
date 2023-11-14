## 문제 설명
이 문제는 Lisa가 아름다운 진주를 수집하고 이를 저장하기 위한 보석 상자를 구입하는 방법을 찾는 문제입니다. 두 종류의 상자가 있으며 다음과 같은 특징을 갖고 있습니다:

타입 1: <br>
> 각 상자는 c1 달러에 구입 가능하며, 정확히 n1 개의 진주를 수용할 수 있습니다.

타입 2: <br>
>각 상자는 c2 달러에 구입 가능하며, 정확히 n2 개의 진주를 수용할 수 있습니다.

Lisa는 각 상자가 최대한 수용능력까지 채워져야 하며, 동시에 총 구매 비용을 최소화하려고 합니다.

입력:<br>
입력 파일에는 여러 개의 테스트 케이스가 포함될 수 있습니다.
각 테스트 케이스는 n (0 < n < 1000)을 포함하는 줄로 시작합니다.
다음 줄에는 c1과 n1이, 세 번째 줄에는 c2와 n2가 나옵니다.
여기서 c1, c2, n1, n2는 모두 1000보다 작은 양의 정수입니다.
진주 수가 0인 테스트 케이스가 입력의 끝을 표시합니다.

출력:<br>
각 테스트 케이스에 대해 최소 비용 솔루션을 포함하는 한 줄을 출력합니다.
두 개의 음이 아닌 정수 m1과 m2를 출력하며, mi는 유형 i 상자가 필요한 개수를 나타냅니다.
그렇지 않으면 "failed"를 출력합니다.
해결책이 존재한다면 해당 해결책이 유일하다고 가정할 수 있습니다.

## 풀이 아이디어
> Greedy Algorithm 사용

1. 두 종류의 상자 중 면적당 비용이 더 적은 것을 선택하여 가능한 많은 개수의 해당 상자(A)를 구매
2. 진주가 남는 다면 다른 상자(B)를 사용
   - "남은 진주 % B의 수용량 !=0"이면 A 상자의 개수를 하나 감소 시키고 모든 진주가 B에 담겼는지 확인
   - "남은 진주 % B의 수용량 == 0"이면 그것이 답
   - 진주가 끝까지 나누어지지 않는다면 "failed" 출력