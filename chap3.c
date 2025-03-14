// 3장 문제
// 최대 5차수, 정수 계수를 가지는, 2개의 다항식을 입력으로 받아 합을 구하는 프로그램을 작성하시오.

// 다항식의 모든 항을 배열에 저장하는 방법
#if 0
#include <stdio.h>

#define MAX_DEGREE 5

// 다항식을 저장하는 구조체
struct POLY
{
    int coef[MAX_DEGREE + 1]; // 계수 배열, 인덱스가 차수를 나타냄
};

// 두 다항식을 더하는 함수
struct POLY addPoly(struct POLY _p1, struct POLY _p2)
{
    struct POLY result;
    for (int i = 0; i <= MAX_DEGREE; i++)
    {
        result.coef[i] = _p1.coef[i] + _p2.coef[i];
    }
    return result;
}

// 다항식을 출력하는 함수
void showPolynomial(struct POLY _p)
{
    int first = 1; // 첫 번째 항인지 확인하는 플래그
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        if (_p.coef[i] != 0)
        {
            if (!first && _p.coef[i] > 0)
            {
                printf(" + ");
            }
            printf("%d * x ^ %d", _p.coef[i], i);
            first = 0;
        }
    }
    printf("\n");
}

int main()
{
    struct POLY p1 = {0}; // 첫 번째 다항식 초기화
    struct POLY p2 = {0}; // 두 번째 다항식 초기화

    // 첫 번째 다항식 입력
    printf("첫 번째 다항식의 계수를 입력하세요 (최대 차수는 %d):\n", MAX_DEGREE);
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        printf("x^%d의 계수: ", i);
        scanf("%d", &p1.coef[i]);
    }

    // 두 번째 다항식 입력
    printf("두 번째 다항식의 계수를 입력하세요 (최대 차수는 %d):\n", MAX_DEGREE);
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        printf("x^%d의 계수: ", i);
        scanf("%d", &p2.coef[i]);
    }

    // 두 다항식의 합 계산
    struct POLY p3 = addPoly(p1, p2);

    // 결과 출력
    printf("첫 번째 다항식: ");
    showPolynomial(p1);
    printf("두 번째 다항식: ");
    showPolynomial(p2);
    printf("두 다항식의 합: ");
    showPolynomial(p3);

    return 0;
}
#endif

// 다항식의 0이 아닌 항만을 배열에 저장하는 방법
#if 0
#include <stdio.h>

#define MAX_TERMS 10 // 최대 항의 개수
#define MAX_DEGREE 5 // 최대 차수

// 각 항을 저장하는 구조체
struct term
{
    int coef;   // 계수
    int degree; // 차수
};

// 다항식을 저장하는 구조체
struct ePOLY
{
    struct term terms[MAX_TERMS];
    int num; // 유효한 항의 개수
};

// 두 다항식을 더하는 함수
struct ePOLY addEfficientPoly(struct ePOLY _p1, struct ePOLY _p2)
{
    struct ePOLY result;
    result.num = 0;

    int i = 0, j = 0, k = 0;

    while (i < _p1.num && j < _p2.num)
    {
        if (_p1.terms[i].degree > _p2.terms[j].degree)
        {
            result.terms[k] = _p1.terms[i];
            i++;
        }
        else if (_p1.terms[i].degree < _p2.terms[j].degree)
        {
            result.terms[k] = _p2.terms[j];
            j++;
        }
        else
        {
            result.terms[k].degree = _p1.terms[i].degree;
            result.terms[k].coef = _p1.terms[i].coef + _p2.terms[j].coef;
            i++;
            j++;
        }
        k++;
    }

    while (i < _p1.num)
    {
        result.terms[k] = _p1.terms[i];
        i++;
        k++;
    }

    while (j < _p2.num)
    {
        result.terms[k] = _p2.terms[j];
        j++;
        k++;
    }

    result.num = k;
    return result;
}

// 다항식을 출력하는 함수
void showEfficientPoly(struct ePOLY _p)
{
    for (int i = 0; i < _p.num; i++)
    {
        printf("%d * x ^ %d ", _p.terms[i].coef, _p.terms[i].degree);
        if (i < _p.num - 1)
        {
            printf("+ ");
        }
    }
    printf("\n");
}

int main()
{
    struct ePOLY p1, p2;
    p1.num = 0;
    p2.num = 0;

    // 첫 번째 다항식 입력
    printf("첫 번째 다항식의 계수를 입력하세요 (최대 차수는 %d):\n", MAX_DEGREE);
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        int coef;
        printf("x^%d의 계수: ", i);
        scanf("%d", &coef);
        if (coef != 0)
        {
            p1.terms[p1.num].coef = coef;
            p1.terms[p1.num].degree = i;
            p1.num++;
        }
    }

    // 두 번째 다항식 입력
    printf("두 번째 다항식의 계수를 입력하세요 (최대 차수는 %d):\n", MAX_DEGREE);
    for (int i = MAX_DEGREE; i >= 0; i--)
    {
        int coef;
        printf("x^%d의 계수: ", i);
        scanf("%d", &coef);
        if (coef != 0)
        {
            p2.terms[p2.num].coef = coef;
            p2.terms[p2.num].degree = i;
            p2.num++;
        }
    }

    // 두 다항식의 합 계산
    struct ePOLY p3 = addEfficientPoly(p1, p2);

    // 결과 출력
    printf("첫 번째 다항식: ");
    showEfficientPoly(p1);
    printf("두 번째 다항식: ");
    showEfficientPoly(p2);
    printf("두 다항식의 합: ");
    showEfficientPoly(p3);

    return 0;
}
#endif