#ifndef __fraction__
#define __fraction__

#include<iostream> //预处理指令
#include<string.h>

class fraction {
    public:
        explicit fraction (int numerator, int denominator = 1) //explicit阻止隐式转换
        :numerator(numerator), denominator(denominator) 
        {this->reduction();}

        fraction& operator+= (const fraction& f); //如果要把operator在类内声明或者定义，只可以有一个参数
        fraction operator+ (const fraction& f2);
        fraction operator* (const fraction& f2);

        operator double() const { //转换函数
            return (double) numerator / denominator;
        }

        std::string getfraction() const {
            return std::to_string(numerator)+"/"+std::to_string(denominator);
        }
    private:
        int numerator; //分子
        int denominator; //分母
        fraction& reduction (); //约分
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

inline fraction
fraction::operator+ (const fraction& f2) {
    fraction f_ans(0);
    f_ans.numerator = this->numerator * f2.denominator + this->denominator * f2.numerator;
    f_ans.denominator = this->denominator * f2.denominator;
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