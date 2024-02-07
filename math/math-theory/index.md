## 积性函数

### 定义

若函数 $f(n)$ 满足 $f(1)=1$ 且 $\forall x,y\in\mathbf{N}^+,\gcd(x,y)=1$ 都有 $f(xy)=f(x)f(y)$，则 $f(n)$ 为 **积性函数**（Multiplicative function）。

若函数 $f(n)$ 满足 $f(1)=1$ 且 $\forall x,y\in\mathbf{N}^+$ 都有 $f(xy)=f(x)f(y)$，则 $f(n)$ 为 **完全积性函数**（Completely multiplicative function）。

### 性质

性质一：若 $f(x)$ 和 $g(x)$ 均为积性函数，则

- $h(x)=f(x^n)$；
- $h(x)=f^n(x)$；
- $h(x)=f(x)g(x)$；
- $h(x)=\sum\limits_{d|x}f(d)$；
- $h(x)=\sum\limits_{d|x}f(d)g\left(\dfrac xd\right)$

均为积性函数。

性质二：若函数 $f$ 满足 $g(n)=\sum\limits_{d|n}f(d)$ 是积性函数，则 $f$ 也是积性函数。

> 证明：
> 
> 使用数学归纳法证明：对于任意 $\gcd(x,y)=1$ 且 $xy\leq n$ 都满足 $f(xy)=f(x)f(y)$。
> 
> 假设对于任意 $\gcd(x,y)=1$ 且 $xy < n$ 都满足 $f(xy)=f(x)f(y)$，要证对于 $\gcd(x,y)=1$ 且 $xy=n$，$f(xy)=f(x)f(y)$ 成立。
> 
> 注意到 $x,y$ 互质，$x$ 的因子也必定和 $y$ 的因子互质，所以 $g(xy)=\sum\limits_{d|xy}f(d)=\sum\limits_{i|x}\sum\limits_{j|y}f(ij)$，又因为 $ij < xy=n$ 时 $f(xy)=f(x)f(y)$ 成立，所以 $g(xy)=\sum\limits_{i|x}f(i)\sum\limits_{j|y}f(j)-f(i)f(j)+f(ij)=g(x)g(y)-f(i)f(j)+f(ij)=g(xy)-f(i)f(j)+f(ij)$，即 $f(ij)=f(i)f(j)$。
> 
> 由数学归纳法可得 $f$ 是积性函数。

### 常见的积性函数

常见的完全积性函数：

1. 单位函数 $\varepsilon(n)=[n=1]$；
2. 恒等函数 $\operatorname{id}_k(n)=n^k$，$\operatorname{id}(n)=n$；
3. 常数函数。

其他常见的积性函数：

4. 欧拉函数 $\varphi(n)=\sum\limits_{i=1}^n[\gcd(i,n)=1]$；
5. 莫比乌斯函数 $\mu$。

<!-- problem.BZOJ2226.begin -->

### 例题 BZOJ2226 LCM Sum

$T$ 组数据，给定 $n$，求

$$
\sum_{i=1}^n\operatorname{lcm}(i,n).
$$

数据范围：$1\leq T\leq 3\times 10^5$，$1\leq n\leq 10^6$。

<!-- problem.BZOJ2226.end -->

## 狄利克雷卷积

### 定义

对于两个数论函数 $f$ 和 $g$，若

$$
h(x)=\sum_{d|x}f(d)g\left(\dfrac xd\right)=\sum_{ij=x}{f(i)g(j)}.
$$

则我们称 $h=f\ast g$，其中 $\ast$ 为两个函数进行 **狄利克雷卷积**（Dirichlet product）得到的结果。

### 性质

1. 满足交换律、结合律和分配律；

> 狄利克雷卷积满足结合律的证明：
> 
> 设 $f,g,h$ 是三个函数，则 $[(f\ast g)\ast h](x)=\sum\limits_{ik=x}(f\ast g)(i)h(k)=\sum\limits_{ijk=x}f(i)g(j)h(k)$。同理 $[f\ast(g\ast h)](x)=\sum\limits_{ijk=x}f(i)g(j)h(k)$。所以狄利克雷卷积满足结合律。

2. $\varepsilon$ 是狄利克雷卷积的单位元，即 $f\ast\varepsilon=f$。

### 常见结论

结论一：$\varphi\ast 1=\operatorname{id}$。

> 证明：要证 $\varphi\ast 1=\operatorname{id}$，即要证 $\sum\limits_{d|n}\varphi(d)=n$。
> 
> 当 $n=1$ 时，结论显然成立。
> 
> 对于素数 $p$ 和正整数 $k$，有 $\sum\limits_{d|p^k}\varphi(d)=\varphi(1)+\varphi(p)+\varphi\left(p^2\right)+\cdots+\varphi\left(p^k\right)=1+(p-1)+\left(p^2-p\right)+\cdots+\left(p^k-p^{k-1}\right)=p^k$，即结论对 $p^k$ 成立。
> 
> 对于 $n,m$ 满足 $\gcd(n,m)=1$，有 $\sum\limits_{d|nm}\varphi(d)=\sum\limits_{i|n,j|m}\varphi(ij)=\sum\limits_{i|n}\varphi(i)\sum\limits_{j|m}\varphi(j)=nm$，即结论对 $nm$ 成立。
> 
> 由此可得对于任意正整数 $n$，上述结论都成立。

## 莫比乌斯函数

### 定义

定义一：莫比乌斯函数（Möbius function）$\mu$ 满足 $\mu\ast 1=\varepsilon$，即对于任意正整数 $n$ 都满足

$$
\sum_{d|n}\mu(d)=[n=1].
$$

定义二：若正整数 $n$ 有 $x$ 个本质不同质因子，则

$$
\mu(n)=\begin{cases}
1,      & n=1                \\
0,      & \exists\ d>1,d^2|n \\
(-1)^x, & \text{otherwise}
\end{cases}.
$$

> 两个定义等价的证明：
> 
> 若已知定义一，则因为 $\varepsilon(n)=[n=1]$ 是积性函数，由积性函数的性质可知 $\mu$ 也是积性函数。
> 
> 对于素数 $p$ 和正整数 $k$，由定义一可知
> 
> $$
> \mu(1)+\mu(p)+\mu\left(p^2\right)+\cdots+\mu\left(p^k\right)=\mu(1)+\mu(p)+\mu\left(p^2\right)+\cdots+\mu\left(p^{k+1}\right)=0.
> $$
> 
> 易知 $\mu(1)=1$，$\mu\left(p^{k+1}\right)=0$，所以 $\mu(p)=1$。即对于任意素数 $p$ 和正整数 $k$，都有 $\mu(p)=1$，$\mu\left(p^k\right)=0$。又因为 $\mu$ 是积性函数，所以定义二成立。
> 
> 若已知定义二则分解质因数容易得到定义一。

### 线性筛求莫比乌斯函数值

因为莫比乌斯函数是积性函数，所以可以使用线性筛来求莫比乌斯函数值。

```cpp
bool vis[100001];
int mu[100001],cntPrime,prime[100001];

void calcMu(int n=100000){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])prime[++cntPrime]=i,mu[i]=-1;
        for(int j=1;j<=cntPrime&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
    }
}
```

<!-- problem.P2522.begin -->

### 例题 P2522 \[HAOI2011\] Problem B

$T$ 组数据，给定 $a,b,c,d,k$，求

$$
\sum_{i=a}^b\sum_{j=c}^d[\gcd(i,j)=k].
$$

数据范围：$1\leq T,a,b,c,d,k\leq 5\times 10^4$。

<!-- problem.P2522.end -->

## 莫比乌斯反演

### 定义

设 $f,g$ 为数论函数，那么有：

- 结论一：若 $f(n)=\sum\limits_{d|n}g(d)\Leftrightarrow f=g\ast 1$，则 $g(n)=\sum\limits_{d|n}\mu(d)f\left(\dfrac nd\right)\Leftrightarrow g=f\ast\mu$，此时函数 $f$ 称为函数 $g$ 的 **莫比乌斯变换**（Möbius transformation），函数 $g$ 称为数论函数 $f$ 的 **莫比乌斯反演**（Möbius inversion）；
- 结论二：若 $f(n)=\sum\limits_{n|d}g(d)$，则 $g(n)=\sum\limits_{n|d}\mu\left(\dfrac{d}{n}\right)f(d)$。

> 两个结论的证明：
> 
> 对于结论一，将 $f=g\ast 1$ 两边同时与 $\mu$ 做卷积可得 $f\ast\mu=g\ast(1\ast\mu)=g\ast\varepsilon=g$。
> 
> 对于结论二，考虑从结果开始推导。
> 
> 枚举 $k$ 表示 $d$ 是 $n$ 的多少倍，则 $\sum\limits_{n|d}\mu\left(\dfrac dn\right)f(d)=\sum\limits_{k=1}^{+\infty}\mu(k)f(kn)=\sum\limits_{k=1}^{+\infty}\mu(k)\sum\limits_{kn|d}g(d)$。
> 
> 变换枚举顺序，可得上式等于 $\sum\limits_{n|d}g(d)\sum\limits_{k|\frac nd}\mu(k)=\sum\limits_{n|d}g(d)\left[\dfrac nd=1\right]=g(n)$。
> 
> 至此，两个结论均得证。

### 应用

我们已经知道 $\varphi\ast 1=\operatorname{id}$，对其使用莫比乌斯反演，可得 $\varphi=\operatorname{id}\ast\mu$。

<!-- problem.P1829.begin -->

### 例题 P1829 \[国家集训队\] Crash 的数字表格

给定 $n,m$，求下式模 $20101009$（一个素数）的值：

$$
\sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j).
$$

数据范围：$1\leq n,m\leq 10^7$。

<!-- problem.P1829.end -->

<!-- problem.P3327.begin -->

### 例题 P3327 \[SDOI2015\] 约数个数和

$T$ 组数据，给定 $n,m$，求：

$$
\sum_{i=1}^n\sum_{j=1}^md(ij).
$$

其中 $d(x)$ 表示 $x$ 的约数个数。

数据范围：$1\leq T,n,m\leq 5\times 10^4$。

<!-- problem.P3327.end -->
