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

4. 欧拉函数 $\varphi(n)=\sum\limits_{i=1}^n[\gcd(i,n)=1]$。

## 狄利克雷卷积

### 定义

对于两个数论函数 $f$ 和 $g$，若

$$
h(x)=\sum_{d|x}f(d)g\left(\dfrac xd\right)=\sum_{ij=x}{f(i)g(j)}.
$$

则我们称 $h=f*g$，其中 $*$ 为两个函数进行 **狄利克雷卷积**（Dirichlet product）得到的结果。

