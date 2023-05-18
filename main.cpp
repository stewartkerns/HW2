#include <iostream>
#include <thread>
#include <vector>
#include <sstream>
#include <cmath>

int minList, maxList, avgList;

using namespace std;
vector<int> * takeInput();
void getAvg(vector<int>);
int getMax(vector<int>);
int getMin(vector<int>);
void question1();

int main() {
    question1();

    return 0;
}

vector<int> * takeInput(){
    vector<int> * vectorObj = new vector<int>();
    vector<int> stack;
    string num;
    cout << "Please enter some fucking numbers: ";
    getline(cin, num);
    int count = 0, sum = 0;
    stringstream ss;

    for (int i = 0; i < num.size(); i++) {
//        cout << "Number being looked at " << num[i] << endl;
        if (num[i] < 58 && num[i] > 47) {
            stack.push_back(num[i] - 48);
        } else {
            if (stack.size() > 0) {
                int test = stack.size();
                for (int j = 0; j < stack.size(); j++) {
                    sum += stack[j] * (int) pow(10,
                                                (double) (stack.size() - 1 -
                                                          j));
                }
                stack.clear();
                vectorObj->push_back(sum);
                sum = 0;
            }
        }
        if (i == num.size() - 1 && (num[i] > 47 && num[i] < 58)) {
            int test = stack.size();
            for (int j = 0; j < stack.size(); j++) {
                sum += stack[j] * (int) pow(10,
                                            (double) (stack.size() - 1 - j));
            }
            stack.clear();
            vectorObj->push_back(sum);
            sum = 0;
        }
    }
    return vectorObj;
}

void getAvg(vector<int> vectorObj){
    int sum = 0;
    for (int i = 0; i < vectorObj.size(); i++){
        sum += vectorObj[i];
    }
    avgList = sum/(int)vectorObj.size();
}
int getMin(vector<int> vectorObj){
    minList = vectorObj[0];
    for (int i = 0; i < vectorObj.size(); i++){
        if (vectorObj[i] < minList){
            minList = vectorObj[i];
        }
    }
}
int getMax(vector<int> vectorObj){
    maxList = vectorObj[0];
    for (int i = 0; i < vectorObj.size(); i++){
        if (vectorObj[i] > maxList){
            maxList = vectorObj[i];
        }
    }
}
void question1(){

    vector<int> * vectorObj = takeInput();

    thread t1(getAvg, *vectorObj);
    thread t2(getMax, *vectorObj);
    thread t3(getMin, *vectorObj);

    t1.join();
    t2.join();
    t3.join();
    cout << "Average: " << avgList << "\nMinimum: " << minList << "\nMaximum: "
    << maxList << endl;
}