#ifndef __mystring__
#define __mystring__

#include<iostream>

class String {
    public:
        String(const char* cstr = 0);
        String(const String& str); //拷贝构造
        String& operator= (const String& str); //拷贝复制
        ~String(); //析构函数
        char* get_c_str() const {return my_data;}
    private:
        char* my_data;
};

inline int 
my_strlen(const char* cstr)
{
    if (cstr == nullptr) throw "Invalid argument";
	char* cstr_temp = (char*)cstr;
	while (*cstr_temp != '\0') {
        cstr_temp++;
    }
	return cstr_temp - cstr;
}

inline char*
my_strcpy (char* c1, const char* c2) {
    char* ret = c1;
    if ((c1 == nullptr) || (c2 == nullptr)) throw "Invalid argument";
    while (*c2 != '\0') {
        *c1 = *c2;
        c1++;
        c2++;
    }
    *c1 = '\0';
    return ret;
}

inline
String::String(const char* cstr) {
    if (cstr) {
        my_data = new char[my_strlen(cstr) + 1];
        my_strcpy(my_data, cstr);
    } else { //未指定初值
        my_data = new char[1];
        *my_data = '\0';
    }
}

inline
String::String(const String& s) {
    my_data = new char[my_strlen(s.my_data) + 1];
    my_strcpy(my_data, s.my_data);
}

inline String&
String::operator= (const String& s) {
    if (this == &s) { //检测自我赋值,防止把唯一的值delete
        return *this;
    }
    delete[] my_data;
    my_data = new char[my_strlen(s.my_data) + 1];
    my_strcpy(my_data, s.my_data);
    return *this;
}

inline
String::~String() {
    delete[] my_data; //array new要搭配array delete
}

std::ostream&
operator<< (std::ostream& os, const String& s) {
    return os << s.get_c_str();
}

#endif