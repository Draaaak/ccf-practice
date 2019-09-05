// 【题目背景】
// 二十四点是一款著名的纸牌游戏，其游戏的目标是使用3个加减乘除运算使得4 张纸牌上数字的运算结果为24。
// 【题目描述】
// 定义每一个游戏由4个从1-9的数字和3个四则运算符组成，保证四则运算符将 数字两两隔开，不存在括号和其他字符，运算顺序按照四则运算顺序进行。其中加法用 符号土表示，减法用符号二表示.乘法用小写字母X表示，除法用符号Z表示。在游 戏里除法为整除，例如2 / 3 = 0，3/2 = 1, 4/2 = 2〇
// 老师给了你》个游戏的解，请你编写程序验证每个游戏的结果是否为24。
// 【输入格式】
// 从标准输入读入数据。
// 第一行输入一个整数《，从第2行幵始到第行中，每一行包含一个长度为7 的字符串.为上述的24点游戏.保证数据格式合法。
// 【输出格式】
// 输出到标准输出。
// 包含《行，对于每一个游戏.如果其结果为24则输出字符串Yes.否则输出字符 串 No«.
// 【样例1输入】
// 10
// 9+3+4x3 
// 5+4x5x5 
// 7-9-9+8 
// 5x6/5x4 
// 3+5+7+9 
// 1x1+9-9 
// 1x9-5/9 
// 8/5+6x9 
// 6x7-3x6 
// 6x4+4/5

#include <iostream>
#include <stack>
using namespace std;
int main()
{
   int n,i,m,insert=0;
   char operation[7];
   stack<int> stack_1;
   cin >> n;
   string resultlist[n];

   for(i=0;i<n;i++){
        int result=0;
        for(m=0;m<7;m++)
            cin >> operation[m];
        for(m=0;m<7;m++){
            if(operation[m]=='x'){ //如果遇到乘法除法，将 栈中的top 与 符号右边的数字 运算的结果push入栈
                insert = stack_1.top() * (operation[m+1]-'0');
                stack_1.pop();
                stack_1.push(insert);
                m++;
            }else if(operation[m]=='/'){
                insert = stack_1.top() / (operation[m+1]-'0');
                stack_1.pop();
                stack_1.push(insert);
                m++;
            }else if(operation[m]=='-'){ //遇到除法将后面的数乘以-1，然后push入栈
                insert = (-1) * (operation[m+1]-'0');
                stack_1.push(insert);
                m++;
            }else if(operation[m]=='+'){ //遇到加法直接push
                stack_1.push(operation[m+1]-'0');
                m++;
            }else //遇到数字直接push，其实也就第一个数字需要push
                stack_1.push(operation[m]-'0');
        }
        while(!stack_1.empty()){ //将栈中元素一个个取出相加得出结果
            result+=stack_1.top();
            stack_1.pop();
            }
        resultlist[i] = (result == 24)?"Yes":"No";
    }
    for(i=0;i<n;i++)
        cout << resultlist[i] << endl;
   return 0;
}