#ifndef __filesystem__
#define __filesystem__

#include<iostream>
#include<vector>

// 委托+继承
class Component { //复合类
    public:
        Component (int val):val(val){}
        virtual void addfile (Component*){}
        void setlayer (int layer){this->layer = layer;}
        int getlayer () const {return layer;}
        virtual void printfile() = 0;
    protected:
        int val;
        int layer = 0;
};

class Primitive:public Component { //文件
    public:
        Primitive (int val):Component(val){}
        void printfile() {
            for (int i = 0;i < layer;i++) std::cout << "\t";
            std::cout << "文件" << val << std::endl;
        }
};

class Composite:public Component { //文件夹
    public:
        Composite (int val):Component(val){}
        void addfile (Component* file) {
            c.push_back(file);
            file->setlayer(this->layer + 1);
        }
        void printfile() {
            for (int i = 0;i < layer;i++) std::cout << "\t";
            std::cout << "文件夹" << val << std::endl;
            for (Component* file : c) {
                file->printfile();
            }
        }
    private:
        std::vector<Component*> c;
};

#endif