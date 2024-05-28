#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__

#include <iostream>

class complex;  // 下面三个函数的参数列表中用了complex，所以要在此声明；
// 下面类的定义中有这三个函数，所以要提前声明；
complex& __doapl(complex* ths, const complex& r);
complex& __doami(complex* ths, const complex& r);
complex& __doaml(complex* ths, const complex& r);

class complex {
 public:
  // 构造函数：用好初值列表
  complex(double r = 0, double i = 0) : re(r), im(i) {}

  // 操作符重载
  complex& operator+=(const complex&);
  complex& operator-=(const complex&);
  complex& operator*=(const complex&);
  complex& operator/=(const complex&);

  double real() const { return re; }
  double imag() const { return im; }

 private:
  double re, im;

  friend complex& __doapl(complex*, const complex&);
  friend complex& __doami(complex*, const complex&);
  friend complex& __doaml(complex*, const complex&);
};

// 引用返回的前提：返回的变量不是函数内的局部变量；
inline complex& __doapl(complex* ths, const complex& r) {
  // 因为 __doapl 已经被声明为友元，所以可以写为 r.re
  ths->re += r.re;
  ths->im += r.im;
  return *ths;  // * return语句不需要关心函数的返回类型是否为引用
}

// 类的成员函数都建议加上 inline
inline complex& complex::operator+=(const complex& r) {
  return __doapl(this, r);
}

inline complex& __doami(complex* ths, const complex& r) {
  ths->re -= r.re;
  ths->im -= r.im;
  return *ths;
}

inline complex& complex::operator-=(const complex& r) {
  return __doami(this, r);
}

// 复数的乘法：(a+bi)(c+di)=(ac-bd)+(ad+bc)i
inline complex& __doaml(complex* ths, const complex& r) {
  double f = ths->re * r.re - ths->im * r.im;
  ths->im = ths->re * r.im + ths->im * r.re;
  ths->re = f;
  return *ths;
}

inline complex& complex::operator*=(const complex& r) {
  return __doaml(this, r);
}

inline double imag(const complex& x) { return x.imag(); }

inline double real(const complex& x) { return x.real(); }

// 返回的是函数内部的变量，函数结束后便销毁了，所以必须要用值返回；
inline complex operator+(const complex& x, const complex& y) {
  return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex operator+(const complex& x, double y) {
  return complex(real(x) + y, imag(x));
}

inline complex operator+(double x, const complex& y) {
  return complex(x + real(y), imag(y));
}

inline complex operator-(const complex& x, const complex& y) {
  return complex(real(x) - real(y), imag(x) - imag(y));
}

inline complex operator-(const complex& x, double y) {
  return complex(real(x) - y, imag(x));
}

inline complex operator-(double x, const complex& y) {
  return complex(x - real(y), -imag(y));
}

inline complex operator*(const complex& x, const complex& y) {
  return complex(real(x) * real(y) - imag(x) * imag(y),
                 real(x) * imag(y) + imag(x) * real(y));
}

inline complex operator*(const complex& x, double y) {
  return complex(real(x) * y, imag(x) * y);
}

inline complex operator*(double x, const complex& y) {
  return complex(x * real(y), x * imag(y));
}

complex operator/(const complex& x, double y) {
  return complex(real(x) / y, imag(x) / y);
}

// * +a, -b 这种写法。参数列表中为操作符右侧的参数，左侧留空了
inline complex operator+(const complex& x) { return x; }

inline complex operator-(const complex& x) {
  return complex(-real(x), -imag(x));
}

inline bool operator==(const complex& x, const complex& y) {
  return real(x) == real(y) && imag(x) == imag(y);
}

inline bool operator==(const complex& x, double y) {
  return real(x) == y && imag(x) == 0;
}

inline bool operator==(double x, const complex& y) {
  return x == real(y) && imag(y) == 0;
}

inline bool operator!=(const complex& x, const complex& y) {
  return real(x) != real(y) || imag(x) != imag(y);
}

inline bool operator!=(const complex& x, double y) {
  return real(x) != y || imag(x) != 0;
}

inline bool operator!=(double x, const complex& y) {
  return x != real(y) || imag(y) != 0;
}

#include <cmath>

inline complex polar(double r, double t) {
  return complex(r * cos(t), r * sin(t));
}

inline complex conj(const complex& x) { return complex(real(x), -imag(x)); }

inline double norm(const complex& x) {
  return real(x) * real(x) + imag(x) * imag(x);
}

#endif  //__MYCOMPLEX__
