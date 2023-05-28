#ifndef __fraction__
#define __fraction__

#include<iostream> //预处理指令
#include<string.h>

class fraction {
    public:
        fraction (int numerator = 0, int denominator = 1)
        :numerator(numerator), denominator(denominator) 
        {this->reduction();}

        fraction& operator+= (const fraction& f); //如果要把operator在类内声明或者定义，只可以有一个参数
        const friend fraction operator+ (const fraction& f1, const fraction& f2); //友元函数
        fraction operator* (const fraction& f2);

        operator double() const {
            return (double) numerator / denominator;
        }

        std::string getfraction() const {
            return std::to_string(numerator)+"/"+std::to_string(denominator);
        }
    private:
        int numerator;
        int denominator;
        fraction& reduction ();
};
//inline 内联函数
inline int
gcd (int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline fraction&
fraction::reduction () {
    int divisor = gcd (this->numerator, this->denominator);
    this->numerator /= divisor;
    this->denominator /= divisor;
    return *this;
}

inline fraction&
fraction::operator+= (const fraction& f) {
    this->numerator = this->numerator * f.denominator + this->denominator * f.numerator;
    this->denominator = this->denominator * f.denominator;
    this->reduction();
    return *this;
}

inline const fraction
operator+ (const fraction& f1, const fraction& f2) {
    fraction f_ans;
    f_ans.numerator = f1.numerator * f2.denominator + f1.denominator * f2.numerator;
    f_ans.denominator = f1.denominator * f2.denominator;
    return f_ans.reduction();
}

inline fraction
fraction::operator* (const fraction& f2) {
    int f_ans_numerator = this->numerator * f2.numerator;
    int f_ans_denominator = this->denominator * f2.denominator;
    return fraction(f_ans_numerator, f_ans_denominator).reduction();
}

std::ostream& //重载'<<'只能在类外作为全局函数实现
operator<< (std::ostream& os, fraction& f) {
    return os << f.getfraction();
}

#endif