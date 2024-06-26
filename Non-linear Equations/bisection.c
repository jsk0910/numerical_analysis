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

RESULT bisection(double a, double b, double eps);

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
    res = bisection(a, b, eps);
}
#endif

RESULT bisection(double a, double b, double eps) {
    RESULT result;
    double c;
    double fa, fc, f;
    double error;
    int iter = 0;

    while (iter < MAXITER) {
        c = 0.5 * (a + b);
        fa = F(a);
        fc = F(c);

        error = fabs(b - a);
        result.a[iter] = a;
        result.b[iter] = b;
        result.error[iter] = error;
        result.xs[iter] = c;
        
        //printf("[%3d] %lf %lf %lf %lf %lf\n", iter+1, a, b, c, fc, error);
        
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

        iter += 1;
    }
    result.iter = iter;
    result.x = c;
    return result;
}