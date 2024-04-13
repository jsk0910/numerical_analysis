#include <stdio.h>
#include <math.h>

#define F(x) (pow(x,3) - 2*x + 1)
#define MAXITER 100

typedef struct RESULT {
    double x;
    double xs[MAXITER];
    double a[MAXITER];
    double b[MAXITER];
    int iter;
    double error[MAXITER];
}RESULT;

RESULT falseposition(double a, double b, double eps);

#ifdef F
int main(void) {
    double a, b, eps;

    printf("시작값 입력: ");
    scanf("%lf", &a);
    printf("끝값 입력: ");
    scanf("%lf", &b);
    printf("허용오차 입력: ");
    scanf("%lf", &eps);

    RESULT res;
    res = falseposition(a, b, eps);

    printf("구간 : [%.3f, %.3f], EPS: %;f\n", a, b, eps);
    printf("===============================\n");
    printf("iter a b x f(x) error\n");
    printf("===============================\n");

    for (int i = 0; i < res.iter+1; i++) {
        printf("[%3d] %lf %lf %lf %lf %lf\n", i+1, res.a[i], res.b[i], res.xs[i], F(res.xs[i]), res.error[i]);
    }

    printf("===== Result =====\n");
    printf("iter: %d\n", res.iter + 1);
    printf("x: %lf\n", res.x);
    printf("f(x) : %lf\n", F(res.x));
    printf("error: %lf\n", res.error[res.iter]);
}
#endif

RESULT falseposition(double a, double b, double eps) {
    RESULT result;
    double c;
    double fa, fb, fc, f;
    double error;
    int iter = 0;

    while(iter < MAXITER) {
        fa = F(a);
        fb = F(b);
        c = (a * fb - b * fa) / (fb - fa);
        fc = F(c);

        error = fabs(b - a);
        result.a[iter] = a;
        result.b[iter] = b;
        result.error[iter] = error;
        result.xs[iter] = c;

        f = fc * fa;
        if (f > 0.) {
            a = c;
        } else if (f < 0.) {
            if (error < eps) break;
            else b = c;
        } else {
            if (fa == 0.) c = a;
            break;
        }

        iter += 1;
    }
    result.iter = iter;
    result.x = c;

    return result;
}