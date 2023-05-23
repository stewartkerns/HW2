#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <mutex>
using namespace std;

int minList, maxList, avgList;
vector<int> * globalArray;
int allowed_ID = 1;
mutex mutexLock;


//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
vector<int> * takeInput();

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void getAvg(vector<int>);

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void getMax(vector<int>);

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void getMin(vector<int>);

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void question1();

// This method takes in an array and sorts it using a recursive merge sort
// technique.
// PRE-CONDITION: Array and size of array passed in
// PROCESS: Sort the array in ascending order using merge sort
// POST-CONDITION: Array passed in is sorted in ascending order
void sort(vector<int> *);

// This method takes in three arrays, one to write to using the other two
// arrays. As the first array is overwritten by the contents of the other
// two, they are put in ascending order.
// PRE-CONDITION: three arrays with the first as the sum of the other two and
// each of their sizes are passed in
// PROCESS: Copy the values from the second two into the first in ascending
// order
// POST-CONDITION: first array contains the contents of the other two arrays
// sorted in ascending order
void merge(vector<int> *, vector<int> *, vector<int> *);

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void question2();

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void question3();

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION
void idChecker(int);

//
// PRE-CONDITION:
// PROCESS:
// POST-CONDITION


int main() {
//    question1();

//    question2();
question3();
    return 0;
}

vector<int> * takeInput(){
    vector<int> * vectorObj = new vector<int>();
    vector<int> stack;
    string num;
    cout << "Please enter some fucking numbers: ";
    getline(cin, num);
    int count = 0, sum = 0;
    bool negativeFlag = false;

    for (int i = 0; i < num.size(); i++) {
        if (num.at(i) == '-'){
            negativeFlag = true;
        }
        else if (num[i] < 58 && num[i] > 47) {
            stack.push_back(num[i] - 48);
        } else {
            if (stack.size() > 0) {
                for (int j = 0; j < stack.size(); j++) {
                    sum += stack[j] * (int) pow(10,
                                                (double)(stack.size() - 1 - j));
                }
                stack.clear();
                if (negativeFlag){
                    sum *= -1;
                }
                vectorObj->push_back(sum);
                sum = 0;
            }
            negativeFlag = false;
        }
        if (i == num.size() - 1 && (num[i] > 47 && num[i] < 58)) {
            for (int j = 0; j < stack.size(); j++) {
                sum += stack[j] * (int) pow(10,
                                            (double) (stack.size() - 1 - j));
            }
            stack.clear();
            if (negativeFlag){
                sum *= -1;
            }
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
void getMin(vector<int> vectorObj){
    minList = vectorObj[0];
    for (int i = 0; i < vectorObj.size(); i++){
        if (vectorObj[i] < minList){
            minList = vectorObj[i];
        }
    }
}
void getMax(vector<int> vectorObj){
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

    delete vectorObj;
}
void question2(){
    globalArray = takeInput();
    //left side will be the lower half, right will be the longer half
    int leftSize = globalArray->size()/2;
//        int rightSize = (int)(intArray->size()/2) + (int)(intArray->size() % 2);

    //two arrays to hold the left and right values
    vector<int> * intArrLeft = new vector<int>;
    vector<int> * intArrRight = new vector<int>;

    //copy over values into the left and right array
    int count = 0;
    for (int i = 0; i < leftSize; i++){
        intArrLeft->push_back(globalArray->at(i));
    }
    count = 0;
    for (int i = leftSize; i < globalArray->size(); i++){
        intArrRight->push_back(globalArray->at(i));
    }

//    sort(globalArray);

//    sort(intArrLeft);
//    sort(intArrRight);
//    merge(globalArray, intArrLeft, intArrRight);

    thread t1(sort, intArrLeft);
    thread t2(sort, intArrRight);

    t1.join();
    t2.join();
    merge(globalArray, intArrLeft, intArrRight);

    for (int i = 0;i < globalArray->size(); i++){
        cout << globalArray->at(i) << ", ";
    }

    delete intArrRight;
    delete intArrLeft;

}
void sort(vector<int> * intArray){

    //continue to split with recursion until the arrays are of size 1
    if (intArray->size() > 1){

        //left side will be the lower half, right will be the longer half
        int leftSize = intArray->size()/2;
//        int rightSize = (int)(intArray->size()/2) + (int)(intArray->size() % 2);

        //two arrays to hold the left and right values
        vector<int> * intArrLeft = new vector<int>;
        vector<int> * intArrRight = new vector<int>;

        //copy over values into the left and right array
        int count = 0;
        for (int i = 0; i < leftSize; i++){
            intArrLeft->push_back(intArray->at(i));
        }
        count = 0;
        for (int i = leftSize; i < intArray->size(); i++){
            intArrRight->push_back(intArray->at(i));
        }

        //recursively split the arrays down and sort them
        sort(intArrLeft);
        sort(intArrRight);

        //merge the arrays after they've ben broken down and sorted
        merge(intArray, intArrLeft, intArrRight);

        //deallocate the memory for the arrays
        delete intArrLeft;
        delete intArrRight;
    }
}
void merge(vector<int>* intArray, vector<int>* intArrLeft,
           vector<int>* intArrRight){

    //create a counter for each side of arrays
    int countLeft = 0;
    int countRight = 0;

    //check each side of the smaller arrays and insert the smallest value of
    // the two until one is fully depleted and then dump the rest of the
    // other array into the main array, creating a sorted main array of the
    // other two sides

    for (int i = 0; i < intArray->size(); i++){
        if (countLeft < intArrLeft->size() && countRight < intArrRight->size()){
            if (intArrLeft->at(countLeft) <= intArrRight->at(countRight)){
//                intArray->push_back(intArrLeft->at(countLeft++));
                intArray->at(i) = intArrLeft->at(countLeft++);
//                intArray[i] = intArrLeft[countLeft++];
            }
            else{
//                intArray->push_back(intArrRight->at(countLeft++));
                intArray->at(i) = intArrRight->at(countRight++);
//                intArray[i] = intArrRight[countRight++];
            }
        }
        else if (countLeft < intArrLeft->size()){
//            intArray->push_back(intArrLeft->at(countLeft++));
            intArray->at(i) = intArrLeft->at(countLeft++);
//            intArray[i] = intArrLeft[countLeft++];
//            intArray[i] = intArrLeft->at(countLeft++);
        }
        else{
//            intArray->push_back(intArrRight->at(countRight++));
            intArray->at(i) = intArrRight->at(countRight++);
//            intArray[i] = intArrRight[countRight++];
        }
    }
}

void question3(){

    const int ONE = 1, TWO = 2, THREE = 3;

    thread t1(idChecker, ONE);
    thread t2(idChecker, TWO);
    thread t3(idChecker, THREE);

    t1.join();
    t2.join();
    t3.join();

}

void idChecker(int id){

    int count = 0;
    const int MAX_TURNS = 2;

    while (count < MAX_TURNS) {
        if (allowed_ID == id) {
            printf("Thread %d's turn.\n", id);
            allowed_ID++;

            if (allowed_ID > 3){
                allowed_ID = 1;
            }

            count++;

            if (count == MAX_TURNS){
                printf("Thread %d's completed.\n", id);
            }
        }
        else{
            printf("Not thread %d's turn.\n", id);
        }
    }
}