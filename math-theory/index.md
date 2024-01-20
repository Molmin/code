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

## 狄利克雷卷积

### 定义

对于两个数论函数 $f$ 和 $g$，若

$$
h(x)=\sum_{d|x}f(d)g\left(\dfrac xd\right)=\sum_{ij=x}{f(i)g(j)}.
$$

则我们称 $h=f*g$，其中 $*$ 为两个函数进行 **狄利克雷卷积**（Dirichlet product）得到的结果。

### 性质

1. 满足交换律、结合律和分配律；

> 狄利克雷卷积满足结合律的证明：
> 
> 设 $f,g,h$ 是三个函数，则 $[(f*g)*h](x)=\sum\limits_{ik=x}(f*g)(i)h(k)=\sum\limits_{ijk=x}f(i)g(j)h(k)$。同理 $[f*(g*h)](x)=\sum\limits_{ijk=x}f(i)g(j)h(k)$。所以狄利克雷卷积满足结合律。

2. $\varepsilon$ 是狄利克雷卷积的单位元，即 $f*\varepsilon=f$。

## 莫比乌斯函数

### 定义

定义一：莫比乌斯函数（Möbius function）$\mu$ 满足 $\mu*1=\varepsilon$，即对于任意正整数 $n$ 都满足

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
