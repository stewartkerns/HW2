#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <mutex>
#include <condition_variable>
using namespace std;

int minList, maxList, avgList;
vector<int> * globalArray;
int allowed_ID = 1;
mutex mutexLock;
condition_variable condVar;



// This method takes in input from the user through the standard input and
// returns a vector of the numbers that are entered
// PRE-CONDITION: none
// PROCESS: Take in user input and create a vector based on it
// POST-CONDITION: vector of any number the user entered is created
vector<int> * takeInput();

// This method gets the average of an arrray of numbers passed in
// PRE-CONDITION: array has numbers in it
// PROCESS: get the average of the array
// POST-CONDITION: vector is unchanged, average is printed
void getAvg(vector<int>);

// This method gets the max of an array passed in
// PRE-CONDITION: array has numbers in it
// PROCESS: find the maximum number
// POST-CONDITION: print the max number, array is unchanged
void getMax(vector<int>);

// This method gets the min of an array passed in
// PRE-CONDITION: array has numbers in it
// PROCESS: find the minimum number
// POST-CONDITION: array unchanged, print the minimum number
void getMin(vector<int>);

// This method runs the three methods required for question 1 of the homework
// assignment and assigns them each to a thread
// PRE-CONDITION: none
// PROCESS: get input from user, run methods on it, print results
// POST-CONDITION: printed statements to the standard output
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

// This method runs the sorting algorithm for question 2 using threads to
// solve the problem
// PRE-CONDITION: none
// PROCESS: get input, sort the input, return the sorted input to the
// standard output
// POST-CONDITION: printed statements
void question2();

// This method runs the methods for question 3 of the homework using threads
// PRE-CONDITION: Run the same method in three threads that all need to
// access the same variable
// PROCESS: Run each of the threads
// POST-CONDITION: printed statements
void question3();

// This method checks the id input against a global id and returns printed
// statements on whether they match or not
// PRE-CONDITION: none
// PROCESS: check if the id input matches the value of the global id and
// increment if so. Continue checking until two matches are made
// POST-CONDITION: printed statements if the id matches
void idChecker(int);

// This method prints out an array that's passed in
// PRE-CONDITION: Array exists
// PROCESS: print each of the elements in the array
// POST-CONDITION: printed statements, array is unchanged
void printArray(vector<int> *);

int main() {
//    question1();

//    question2();
    question3();
    return 0;
}

vector<int> * takeInput(){

    //Create an array to hold the numbers taken in from the standard input
    vector<int> * numbersArray = new vector<int>();

    //create an array that will hold the single numbers to be added together
    // into a single number later
    vector<int> nums;

    //create a string to hold the list of numbers entered by the user and
    // request said numbers from the user
    string numList;
    cout << "Please enter some numbers: ";
    getline(cin, numList);

    //create constant ints that represent the ASCII values of 0 and 9 for
    // reference
    const int NINE = 57, ZERO = 48;

    //sum is used for obtaining the actual number entered by the user after
    // breaking it down and negativeFlag is used to see if a user entered a
    // negative number
    int sum = 0;
    bool negativeFlag = false;

    //traverse through the string entered by the user to look for numbers
    for (int i = 0; i < numList.size(); i++) {

        //set the negative flag true if a - is found in the string
        if (numList.at(i) == '-'){
            negativeFlag = true;
        }

        //if the current character is a number, push it into the nums array
        else if (numList[i] <= NINE && numList[i] >= ZERO) {
            nums.push_back(numList[i] - ZERO);
        }

        //if the character isn't a number, reset the negative flag or add the
        // current number read in into the array of numbers entered
        else {
            if (nums.size() > 0) {

                //move through the nums array and calculate the number
                // represented by the array
                for (int j = 0; j < nums.size(); j++) {
                    sum += nums[j] * (int) pow(10,
                                               (double)(nums.size() - 1 - j));
                }

                //clear the array
                nums.clear();

                //if the number was negative, do so
                if (negativeFlag){
                    sum *= -1;
                }

                //put the constructed number into the array of all the numbers
                numbersArray->push_back(sum);
                sum = 0;
            }

            //reset the negative flag whether or not a number was found
            negativeFlag = false;
        }

        //if the character being looked at in the list is the last one, add
        // the current number into the array using the same techniques as above
        if (i == numList.size() - 1 && (numList[i] >= ZERO && numList[i] <= NINE)) {
            for (int j = 0; j < nums.size(); j++) {
                sum += nums[j] * (int) pow(10,
                                           (double) (nums.size() - 1 - j));
            }
            nums.clear();
            if (negativeFlag){
                sum *= -1;
            }
            numbersArray->push_back(sum);
            sum = 0;
        }
    }

    //return an array of numbers the user entered, but scrubbed of any non
    // numbers
    return numbersArray;
}
void getAvg(vector<int> vectorObj){

    //get the average of an array of numbers passed
    int sum = 0;
    for (int i = 0; i < vectorObj.size(); i++){
        sum += vectorObj[i];
    }
    avgList = sum/(int)vectorObj.size();
}
void getMin(vector<int> vectorObj){

    //get the minimum number of an array of numbers passed in
    minList = vectorObj[0];
    for (int i = 0; i < vectorObj.size(); i++){
        if (vectorObj[i] < minList){
            minList = vectorObj[i];
        }
    }
}
void getMax(vector<int> vectorObj){

    //get the maximum of an array passed in
    maxList = vectorObj[0];
    for (int i = 0; i < vectorObj.size(); i++){
        if (vectorObj[i] > maxList){
            maxList = vectorObj[i];
        }
    }
}
void question1(){

    //get input from the user
    vector<int> * vectorObj = takeInput();

    //open three threads, each doing a different method and then join them
    // back togeher before printing the calculated values
    thread t1(getAvg, *vectorObj);
    thread t2(getMax, *vectorObj);
    thread t3(getMin, *vectorObj);

    t1.join();
    t2.join();
    t3.join();
    cout << "Average: " << avgList << "\nMinimum: " << minList << "\nMaximum: "
    << maxList << endl;

    //delete the memory used
    delete vectorObj;
}
void question2(){

    //get input on the numbers from the user
    globalArray = takeInput();
    //left side will be the lower half, right will be the longer half
    int leftSize = globalArray->size()/2;

    //two arrays to hold the left and right values
    vector<int> * intArrLeft = new vector<int>;
    vector<int> * intArrRight = new vector<int>;

    //copy over values into the left and right array
    for (int i = 0; i < leftSize; i++){
        intArrLeft->push_back(globalArray->at(i));
    }
    for (int i = leftSize; i < globalArray->size(); i++){
        intArrRight->push_back(globalArray->at(i));
    }

    printArray(globalArray);
    cout << "Sorting array." << endl;

    //create two threads, each sorting their sides of the array and then join
    // them
    thread t1(sort, intArrLeft);
    thread t2(sort, intArrRight);

    t1.join();
    t2.join();

    //merge the two arrays back into the global array
    merge(globalArray, intArrLeft, intArrRight);

    //print sorted array
    printArray(globalArray);

    //clear the requested memory
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
void printArray(vector<int> * array){

    //print the input array in a formatted way
    cout << "Array: [";
    for (int i = 0;i < array->size(); i++){
        if (i < array->size() - 1){
            cout << array->at(i) << ", ";
        }
        else{
            cout << array->at(i) << "]" << endl;
        }
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
                intArray->at(i) = intArrLeft->at(countLeft++);
            }

            else{
                intArray->at(i) = intArrRight->at(countRight++);
            }
        }

        else if (countLeft < intArrLeft->size()){
            intArray->at(i) = intArrLeft->at(countLeft++);
        }

        else{
            intArray->at(i) = intArrRight->at(countRight++);
        }
    }
}
void question3(){

    //create three variables to pass into the same method in three different
    // threads
    const int ONE = 1, TWO = 2, THREE = 3;

    //create three threads doing the same thing and accessing the same
    // variable, run them until they all finish and join
    thread t1(idChecker, ONE);
    thread t2(idChecker, TWO);
    thread t3(idChecker, THREE);

    t1.join();
    t2.join();
    t3.join();

}
void idChecker(int id){

    //create a count to keep track of how many times the correct id was
    // accessed and a max number that it needs to be accessed
    int count = 0;
    const int MAX_TURNS = 2;

    //creat a unique lock to be used for locking and unlocking threads
    unique_lock<mutex> lock(mutexLock);

    //print whether or not it's this threads turn until it's achieved the
    // correct amount of turns
    while (count < MAX_TURNS) {

        if (allowed_ID == id) {
            printf("Thread %d's turn.\n", id);
            allowed_ID++;

            //reset the id if it goes over 3
            if (allowed_ID > 3){
                allowed_ID = 1;
            }

            count++;

            //once the turns are completed, print a statement
            if (count == MAX_TURNS){
                printf("Thread %d's completed.\n", id);
            }

            //notify other threads to unlock
            condVar.notify_all();
        }
        else{

            printf("Not thread %d's turn.\n", id);
            //lock this thread until another thread finishes and sends a
            // notification
            condVar.wait(lock);
        }
    }
}