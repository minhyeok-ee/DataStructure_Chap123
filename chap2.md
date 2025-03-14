# 1. recursion을 정의하시오

- recursion이란 알고리즘이나 함수가 수행 도중에 자기 자신을 다시 호출하여 문제를 해결하는 기법이다.



# 2. \sigma (k=1,n)이 recursion으로 계산 과정을 그리시오

- base case : s(1) = 1
- recursion case : s(n) = n + s(n-1)

- n == 5 라고 가정하면 
```c
sum(5) = 5 + sum(4)
sum(4) = 4 + sum(3)
sum(3) = 3 + sum(2)
sum(2) = 2 + sum(1)
sum(1) = 1  (base case)
```

- 역으로 값이 반환됨
```c
sum(2) = 2 + 1 = 3
sum(3) = 3 + 3 = 6
sum(4) = 4 + 6 = 10
sum(5) = 5 + 10 = 15 (최종 결과)
```



# 3. 알고리즘 구현을 순환과 반복, 2가지 방식으로 구현할 때, 장단점을 설명

- 순환 : 간단하게 구현 가능하지만 모든 단계가 계속해서 스택 메모리를 잡고 있기 때문에 메모리 사용량이 많고 속도가 느리다.

- 반복 : 메모리 사용량이 적고 실행 속도가 빠르다. break, continue를 통해 무한루프의 제어가 가능하다. 하지만 메모리를 직접 관리해야 하므로 코드가 복잡해 질 수 있다.



# 4. x^n을 recursion 구현할 때, O(log n) 복잡도를 가지도록 하고, 설명하시오.

- `x^n`을 일반적 재귀로 구현하면

```c
double power(double x, int n) {
    if (n == 0) return 1; // x^0 = 1
    return x * power(x, n - 1);
}
```

- n이 1씩 줄어드는 방식이므로 시간복잡도는 O(n)이 나온다. 이 경우 n이 클 경우 실행 시간이 오래걸리고 메모리를 많이 사용한다.

- n이 짝수일 때와 홀수일 때를 나누어 계산하면 

```c
double my_power(double x, int n) {
    if (n == 0) return 1;
    
    double half = my_power(x, n / 2); // x^(n/2) 계산

    if (n % 2 == 0) 
        return half * half; // 짝수일 경우
    else 
        return x * half * half; // 홀수일 경우
}
```

- 이렇게 구현할 경우 한번의 재귀 호출마다 n이 n/2로 줄어들기 때문에 전체 재귀호출 횟수는 log_2(n)번이 되어서 시간복잡도 O(log n)을 만족한다.



# 5. Fibonacci 수열 계산을 recursion 구현할 때, 문제점을 제시하고, 해결책을 구현하시오.

- Fibonacci 수열 계산을 recursion으로 구현할 경우 같은 항이 중복해서 계산되는 비효율성이 있다. 그리고 이러한 현상은 n이 커지면 커질수록 더 심해진다.

- 이 경우 반복문을 사용하여 구현한다.

```c
int fib_iter(int n) { 
    if (n == 0) return 0; 
    if (n == 1) return 1; 

    int pp = 0;   // F(n-2)
    int p = 1;    // F(n-1)
    int result = 0;

    for (int i = 2; i <= n; i++) {
        result = p + pp;  // F(n) = F(n-1) + F(n-2)
        pp = p;           // F(n-2) <- F(n-1)
        p = result;       // F(n-1) <- F(n)
    }
    return result; 
}
```

- 여기에서 pp는 두 단계 전 값, p는 한 단계 전 값으로 적용되며, 결과 result는 F(n) = F(n-1) + F(n-2)로 적용된다.



# 6. Recursion을 이용한 하노이탑 알고리즘으로 plate 4개를 옮기는 과정을, 함수 호출과 반환 과정이 보이도록 그림으로 작성하세요

```
hanoi(4, A, C, B)
├── hanoi(3, A, B, C)
│    ├── hanoi(2, A, C, B)
│    │    ├── hanoi(1, A, B, C)
│    │    │    ├── Move A → B
│    │    ├── Move A → C
│    │    ├── hanoi(1, B, C, A)
│    │         ├── Move B → C
│    ├── Move A → B
│    ├── hanoi(2, C, B, A)
│    │    ├── hanoi(1, C, A, B)
│    │    │    ├── Move C → A
│    │    ├── Move C → B
│    │    ├── hanoi(1, A, B, C)
│    │         ├── Move A → B
├── Move A → C
├── hanoi(3, B, C, A)
│    ├── hanoi(2, B, A, C)
│    │    ├── hanoi(1, B, C, A)
│    │    │    ├── Move B → C
│    │    ├── Move B → A
│    │    ├── hanoi(1, C, A, B)
│    │         ├── Move C → A
│    ├── Move B → C
│    ├── hanoi(2, A, C, B)
│    │    ├── hanoi(1, A, B, C)
│    │    │    ├── Move A → B
│    │    ├── Move A → C
│    │    ├── hanoi(1, B, C, A)
│    │         ├── Move B → C
```


# 7. 하노이탑 알고리즘으로 100개 원판을 옮길 때 걸리는 시간을 계산하시오. 원판을 1번 옮기는 시간을 1 nano-second로 가정한다.

- 하노이탑 알고리즘은 O(2^n)의 시간복잡도를 가진다.

- n개의 원판을 옮길 때 이동 횟수는 2^n -1이다.

- 따라서 total time = (2^100 -1) * 10^(-9) 초라고 볼 수 있다.

- 이는 약 3.154 * 10^7초로 40.2조 년이 걸린다고 볼 수 있다.