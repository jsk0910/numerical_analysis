#include <stdio.h>
#include <math.h>>

#define F(x) (pow(x,3) - 2*x + 1)
#define MAXITER 100

void bisection(double a, double b, double eps);

#ifdef F(x)
int main(void) {
    double a, b, eps;

    printf("시작값 입력: ");
    scanf("%lf", &a);
    printf("끝값 입력: ");
    scanf("%lf", &b);
    printf("허용오차 입력: ");
    scanf("%lf", &eps);
}
#endif

void bisection(double a, double b, double eps) {
    double c;
    double fa, fc, f;
    double error;
    int iter = 0;

    printf("구간 : [%.3f, %.3f], EPS : %lf\n", a, b, eps);
    printf("===============================\n");
    printf("iter a b x f(x) error\n");
    printf("===============================\n");
    while (iter < MAXITER) {
        c = 0.5 * (a + b);
        fa = F(a);
        fc = F(c);

        error = fabs(b - a);
        printf("[%3d] %lf %lf %lf %lf %lf\n", iter+1, a, b, c, fc, error);
        
        f = fa * fc;
        if (f > 0.) {
            a = c;
        } else if (f < 0.) {
            if (error < eps) break;
            else b = c;
        } else {
            if (fa == 0.) c = a;
            break;
        }
    }

    if (iter < MAXITER) {
        printf("\n***** Result *****\n");
        printf("    iteration: %d\n", iter+1);
        printf("    x   = %f\n", c);
        printf("    f(x)= %f\n", Function(c));
        printf("    b-a = %f\n", b-a);
    } else {
        printf("Error: MAXITER 초과\n");
    }
}