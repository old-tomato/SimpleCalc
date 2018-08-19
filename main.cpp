#include <iostream>
#include <string>
#include <string.h>
#include "ZklComputer.h"

using namespace std;

int main() {
    // 不考虑空格及其他特殊符号的情况
    // 1+2*10+5*(10+4/2*(5+6))*6
    // 1 2*10 5*(10+4/2*(5+6))*6 + +
    //   2 10                    *
    //        5 (10+4/2*(5+6)) 6 * *
    //           10 4/2*(5+6)    +
    //              4 2 (5+6)    / *
    //                   5 6     +

    // 1+2*10+5*(10+4/2*(5+6))*6
    // 1+20+30*(10+22)
    // 1+20+30*32
    // 21+960
    // 981
    string str = "1+2*10+5*(10+4/2*(5+6))*6";
    //string str = "1+2+3*4";
    // 4/2*3/2
    // 4 2 2
    // 2 * 3 6
    // 6 / 2
    //string str = "1+4/2*3/2+10";
    ZklComputer computer(str);

    return 0;
}