// 问题描述
// 　　有一个学校的老师共用N个教室，按照规定，所有的钥匙都必须放在公共钥匙盒里，老师不能带钥匙回家。每次老师上课前，都从公共钥匙盒里找到自己上课的教室的钥匙去开门，上完课后，再将钥匙放回到钥匙盒中。
// 　　钥匙盒一共有N个挂钩，从左到右排成一排，用来挂N个教室的钥匙。一串钥匙没有固定的悬挂位置，但钥匙上有标识，所以老师们不会弄混钥匙。
// 　　每次取钥匙的时候，老师们都会找到自己所需要的钥匙将其取走，而不会移动其他钥匙。每次还钥匙的时候，还钥匙的老师会找到最左边的空的挂钩，将钥匙挂在这个挂钩上。如果有多位老师还钥匙，则他们按钥匙编号从小到大的顺序还。如果同一时刻既有老师还钥匙又有老师取钥匙，则老师们会先将钥匙全还回去再取出。
// 　　今天开始的时候钥匙是按编号从小到大的顺序放在钥匙盒里的。有K位老师要上课，给出每位老师所需要的钥匙、开始上课的时间和上课的时长，假设下课时间就是还钥匙时间，请问最终钥匙盒里面钥匙的顺序是怎样的？
// 输入格式
// 　　输入的第一行包含两个整数N, K。
// 　　接下来K行，每行三个整数w, s, c，分别表示一位老师要使用的钥匙编号、开始上课的时间和上课的时长。可能有多位老师使用同一把钥匙，但是老师使用钥匙的时间不会重叠。
// 　　保证输入数据满足输入格式，你不用检查数据合法性。
// 输出格式
// 　　输出一行，包含N个整数，相邻整数间用一个空格分隔，依次表示每个挂钩上挂的钥匙编号。
// 样例输入
// 5 2
// 4 3 3
// 2 2 7
// 样例输出
// 1 4 3 2 5
// 样例说明
// 　　第一位老师从时刻3开始使用4号教室的钥匙，使用3单位时间，所以在时刻6还钥匙。第二位老师从时刻2开始使用钥匙，使用7单位时间，所以在时刻9还钥匙。
// 　　每个关键时刻后的钥匙状态如下（X表示空）：
// 　　时刻2后为1X345；
// 　　时刻3后为1X3X5；
// 　　时刻6后为143X5；
// 　　时刻9后为14325。
// 样例输入
// 5 7
// 1 1 14
// 3 3 12
// 1 15 12
// 2 7 20
// 3 18 12
// 4 21 19
// 5 30 9
// 样例输出
// 1 2 3 5 4
// 评测用例规模与约定
// 　　对于30%的评测用例，1 ≤ N, K ≤ 10, 1 ≤ w ≤ N, 1 ≤ s, c ≤ 30；
// 　　对于60%的评测用例，1 ≤ N, K ≤ 50，1 ≤ w ≤ N，1 ≤ s ≤ 300，1 ≤ c ≤ 50；
// 　　对于所有评测用例，1 ≤ N, K ≤ 1000，1 ≤ w ≤ N，1 ≤ s ≤ 10000，1 ≤ c ≤ 100。

// 存的时间和对应的钥匙一起排序，取的时间和对应的钥匙一起排序
// 遍历每个时间点，在每个时间点看看有没有存取操作
// 取的时候需要考虑要取的钥匙对应在哪个位置然后拿走，存的时候需要考虑将钥匙放在第几个位置上

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 取钥匙
void takeKey(int N, int keyBox[], vector<int> &keytakelist, vector<int> &startTime){
    int k=0;
    for(int i=0;i<N;i++){
        if(keyBox[i]==keytakelist.front()){
            keyBox[i]=0;
            keytakelist.erase(keytakelist.begin());
            startTime.erase(startTime.begin());
            k=1; 
        }
        if(k==1)
            break;
    }
}

// 放钥匙
void putKey(int i,int N, int keyBox[],vector<int> &keyputlist, vector<int> &endTime){
    vector<int> hand;
    while(endTime.front()==i && endTime.size()!=0){
        hand.push_back(keyputlist.front());
        keyputlist.erase(keyputlist.begin());
        endTime.erase(endTime.begin());
    }
    sort(hand.begin(),hand.end());
    for(int p=0;p<N;p++){
        if(keyBox[p]==0 && hand.size()!=0){
            keyBox[p]=hand.front();
            hand.erase(hand.begin());
        }
    }
}

// 时间表带着钥匙号一起排序
void mySort(vector<int> &keyUseList, vector<int> &time){
    for (int i = 0; i < time.size() - 1; i++) {
        for (int j = 0; j < time.size() - i - 1; j++) {
            if (time[j] > time[j + 1]) {
                int temp = time[j], temp2 = keyUseList[j];
                time[j] = time[j + 1];
                time[j + 1] = temp;
                keyUseList[j] = keyUseList[j + 1];
                keyUseList[j + 1] = temp2;
            }
        }
    }
}

int main(){
    int N,K;
    cin >> N >> K;
    int keyBox[N];
    vector<int> keytakelist(K,0), startTime(K,0),keyputlist(K,0) , endTime(K,0) ;

    //初始化钥匙盒
    for(int i=1;i<=N;i++)
        keyBox[i-1] = i;

    //初始化存取钥匙时间
    for(int i=0;i<K;i++){
        cin >> keytakelist[i] >> startTime [i] >> endTime[i];
        keyputlist[i] = keytakelist[i];
        endTime[i] += startTime[i];
    }

    //排序
    mySort(keytakelist,startTime);
    mySort(keyputlist,endTime);

    //以对应时间进行操作
    int lasttime = endTime.back();
    for(int i=1; i<=lasttime; i++){
        while(endTime.front()==i && endTime.size()!=0)
            putKey(i, N, keyBox, keyputlist, endTime);
        while(startTime.front()==i && startTime.size()!=0)
            takeKey(N, keyBox, keytakelist, startTime);
    }
    for(int i=0;i<N;i++)
        cout << keyBox[i] << ' ';
    return 0;
}