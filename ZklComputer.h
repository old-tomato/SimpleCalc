//
// Created by zkl on 18-8-19.
//

#ifndef MATHTESTPLUS_ZKLCOMPUTER_H
#define MATHTESTPLUS_ZKLCOMPUTER_H

#include <string>
#include <string.h>
#include <list>
#include <iostream>

#define LLI long long int

using namespace std;

// 计算例子
// 不考虑空格及其他特殊符号的情况
// 1+2*10+5*(10+4/2*(5+6))*6
// 1 2*10 5*(10+4/2*(5+6))*6 + +
//   2 10                    *
//        5 (10+4/2*(5+6)) 6 * *
//           10 4/2*(5+6)    +
//              4 2 (5+6)    / *
//                   5 6     +

class ZklComputer {

private:
    string equation;

    char * cEquation;

    bool isNumber = false;

    // 符号的集合
    list<char> symbolList;

    // 如果存在与当前等级不同的内容需要计算,那么需要创建新的对象进行计算
    list<ZklComputer *> computerList;

    // 结果值,也可能是当前对象唯一的值
    LLI result;

    bool format();

    void splitStr(int x , int startPosition);

    LLI computer();

    LLI doMath(LLI number1 , LLI number2 , char symbol);
public:
    ZklComputer(string equation);

    ~ZklComputer();
};


#endif //MATHTESTPLUS_ZKLCOMPUTER_H
