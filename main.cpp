#include <iostream>
#include <thread>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;
vector<int> *& takeInput();

int main() {
    std::cout << "Hello, World!" << std::endl;


    vector<int> * vectorObj = takeInput();

    cout << "Here are your numbers fuckface" << endl;
    for (int i = 0; i < vectorObj->size(); i++){
        cout << vectorObj->at(i) << ", ";
    }

    return 0;
}

vector<int> *& takeInput(){
    vector<int> * vectorObj = new vector<int>();
    vector<int> stack;
    string num;
    cout << "Please enter some fucking numbers: ";
    getline(cin, num);
    int count = 0, sum = 0;
    stringstream ss;

    for (int i = 0; i < num.size(); i++) {
        cout << "Number being looked at " << num[i] << endl;
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
        if (i == num.size() - 1 && (num[i] > '0' && num[i] < '9')) {
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
