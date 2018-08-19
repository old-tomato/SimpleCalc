//
// Created by zkl on 18-8-19.
//

#include "ZklComputer.h"

list<string> testList;

bool ZklComputer::format(){

    // 检查是否存在加减符号,注意,这里查找要求是在相同等级下查找的
    // 既 1 * (2 + 3) 这里的 + 就不应该在这个级别被找到
    // 如果存在,那么需要首先构建新的对象
    // 上一步如果判断存在,那么就应该到此为止而不是继续执行下去
    // 如果不存在,需要查看是否存在括号或者是乘除符号
    // 如果存在,也需要构建新的对象
    // 上一步与加减法时操作相同
    // 如果没有任何符号,只是单纯的数字,那么就应该直接设定为当前类型的值
    int startPosition = -1;
    int levelNum = 0;

    bool levelFlag = false;
    // 这里不判断公式是否正确的问题
    for(int x = 0 ; x <= strlen(cEquation) ; ++ x){
        // 开始时可能为-1,同时运行中,如果是重置后也可能为-1
        if(startPosition == -1){
            startPosition = x;
        }
        // 如果公式里面碰到了加减号,同时当前的 ( 的数量为0
        if((cEquation[x] == '+' || cEquation[x] == '-') && levelNum == 0){
            // 表示这个算式在加减级别就算在符号
            levelFlag = true;
            // 获取当前的符号
            symbolList.push_back(cEquation[x]);
            // 获得这里前面半段的数值/算式
            splitStr(x , startPosition);
            // 重置当前的起始位置
            startPosition = -1;
        }
        if(cEquation[x] == '('){
            ++ levelNum;
        }
        if(cEquation[x] == ')'){
            -- levelNum;
        }
        if(x == strlen(cEquation) && levelFlag){
            // 说明当前的字符查询已经到了头,同时也确实存在加减符号存在,那么需要将最后的一些位置的内容提取出来了
            splitStr(x , startPosition);
        }
    }

    if(levelFlag){
        // TODO 这里可能需要做些什么
        return true;
    }else{
        levelFlag = false;
        startPosition = -1;

        for(int x = 0 ; x <= strlen(cEquation) ; ++ x){
            // 开始时可能为-1,同时运行中,如果是重置后也可能为-1
            if(startPosition == -1){
                startPosition = x;
            }
            // 如果公式里面碰到了加减号,同时当前的 ( 的数量为0
            if((cEquation[x] == '*' || cEquation[x] == '/') && levelNum == 0){
                // 表示这个算式在加减级别就算在符号
                levelFlag = true;
                // 获取当前的符号
                symbolList.push_back(cEquation[x]);
                // 获得这里前面半段的数值/算式
                splitStr(x , startPosition);
                // 重置当前的起始位置
                startPosition = -1;
            }
            if(cEquation[x] == '('){
                ++ levelNum;
            }
            if(cEquation[x] == ')'){
                -- levelNum;
            }
            if(x == strlen(cEquation) && levelFlag){
                // 说明当前的字符查询已经到了头,同时也确实存在加减符号存在,那么需要将最后的一些位置的内容提取出来了
                splitStr(x , startPosition);
            }
        }
    }

    if(levelFlag){
        return true;
    }else{
        isNumber = true;
        this->result = atoll(cEquation);
    }

}

void ZklComputer::splitStr(int x , int startPosition){
    char * temp = new char[x - startPosition + 1];
    memset(temp , 0 , x - startPosition + 1);
    strncpy(temp , cEquation + startPosition , x - startPosition);
    // TODO 测试使用字段
    // testList.push_back(string(temp));
    ZklComputer * computer = new ZklComputer(temp);
    computerList.push_back(computer);
}

LLI ZklComputer::computer(){

    bool isFirst = true;
    auto symbolIt = symbolList.begin();
    LLI tempResult = 0;
    for(auto it = computerList.begin() ; it != computerList.end() ; ++ it){
        LLI temp = 0;
        if(isFirst){
            isFirst = false;
            tempResult = (*it)->result;
            temp = (*(++it))->result;
        }else{
            temp = (*it)->result;
        }
        char symbol = *symbolIt;
        ++ symbolIt;
        tempResult = doMath(tempResult , temp ,  symbol);
        cout << "tempResult : " << tempResult << endl;
    }
    return tempResult;
}

LLI ZklComputer::doMath(LLI number1 , LLI number2 , char symbol){
    cout << number1 << symbol << number2 << endl;
    switch (symbol){
        case '+':
            return number1 + number2;
        case '-':
            return number1 - number2;
        case '*':
            return number1 * number2;
        case '/':
            return number1 / number2;
        default:
            return 0;
    }
}

ZklComputer::ZklComputer(string equation):equation(equation){
    // 虽然字符串通过string类型的保存了一遍,但是还是通过char * 类型再存储一遍
    // 如果算式的前后两端是括号,那么就先去除掉
    int rightCut = 0;
    int leftCut = 0;
    if(equation.c_str()[0] == '(' ){
        leftCut = 1;
    }

    if(equation.c_str()[equation.size() - 1] == ')'){
        rightCut = 1;
    }
    cEquation = new char[equation.size() + 1 - rightCut - leftCut];
    memset(cEquation , 0 , equation.size() + 1);

    if(rightCut == 1 && leftCut == 1){
        strncpy(cEquation , equation.c_str() + leftCut , equation.size() - rightCut - leftCut);
    }else {
        strncpy(cEquation , equation.c_str() , equation.size());
    }

    format();
    if(!isNumber){
        this->result = computer();
    }

    cout << "result : " << result << endl;
}

ZklComputer::~ZklComputer(){

}
