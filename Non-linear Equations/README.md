## Non-Linear Equations (비선형 방정식)

$f(x) = a^2x + bx + c = 0$ 꼴의 방정식의 근을 구하는 문제를 비선형 방정식이라고 한다.  
수치해석에서는 $f(x)  = 0$를 만족하는 $x$를 구하는 것을 목표로 한다.  
이를 위해 다음과 같은 방법을 사용할 수 있다.

- 구간법
    + [이분법](#이분법)
    + 가위치법
- 개구간법
    + 고정점 반복법
    + Newton-Raphson법
    + 할선법

#### 이분법
> 구간법 중 하나. 구간법은 범위 $[a, b]$를 정하여 해를 찾는다.  
> 그래프를 사용하여  접근하기 때문에 실제값을 구하는 데에는 한계가 있지만,  
> 대략적인 추정 값을 얻기에 유용하다.  
>
> 방법 : $f(a) < 0$이고, $f(b) > 0$이면 그 사이에 $f(x) = 0$인 점이 적어도 하나 이상 존재한다.  따라서, 구간을 두개로 분할하여 값을 대입해보고 구간을 다시 분할하는 방식으로 접근한다.  
> 구하고자 하는 해를 $r$이라고 하면, $|r-c_n| \le \dfrac{b_n-a_n}{2^{n+1}}$의 근사 오차를 얻을 수 있다. 이를 바탕으로 다시 이분법을 반복해야 하는 횟수를 구할 수 있다.  
> 미리 정의된 허용 오차를 $\epsilon$이라고 할때,  
> $n > \dfrac{log(b-a)-log(2\epsilon)}{log2}$이다.
>
> 이를 알고리즘으로 나타내면 아래와 같다.
```mermaid
flowchart TD;
    INPUT["INPUT: a, b, eps"] --> A
    A["iter = 0"]
    subgraph while ["subroutine for calculate"]
        whileif{"iter < MAXITER"} --> whileB
        whileB["c = 0.5 * (a+b)\n fa = F(a)\n fc = F(c)"] --> whileE
        whileE["error = abs(b - a)"] --> whileF
        whileF["f = fa * fc"] --> whileIf1
        whileIf1{"f > 0.0"} -- "True" --> whileIf1True
        whileIf1True["a = c"]
        whileIf1 -- "False" --> whileIf2
        whileIf2{"f < 0.0"} -- "True" --> if1
        if1{"error < eps"} -- "True" --> break
        if1 -- "False" --> else
        else["else: b=c"]
        whileIf2 -- "False" --> if2
            if2{"fa == 0.0"} -- "Treu" --> change
            change["c = a"]
            change --> break
        iter["iter = iter + 1"]
        whileIf1True --> iter
        else --> iter
    end
    print["print result"]
    A --> while --> print
```
> 이에 대한 코드는 https://github.com/jsk0910/numerical_analysis/blob/main/Non-linear%20Equations/bisection.c 에 있다.

#### 가위치법
> 마찬가지로 구간법이다.  
> 앞선 이분법과 달리 점 a와 점 b 사이에 직선을 긋고 해당 직선이 x축과 만나는 점을 c로 잡는다.  
> 이때, 만들어지는 삼각형에 대하여 다음과 같은 식이 성립한다.
> $$\dfrac{b-c}{f(b)} = - \dfrac{c-a}{f(a)}$$  
> 이를 통해 c의 위치를 특정할 수 있다.