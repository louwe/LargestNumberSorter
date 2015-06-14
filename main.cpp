#include <iostream>

using namespace std;

void swapNumbers(int& number1, int& number2) {
    //cout << "Swapping " << number1 << " with " << number2 << endl;
    number1 += number2;
    number2 = number1 - number2;
    number1 -= number2;
}

void printList(int* largestNumbersArray, int size) {
    for(int i = 0; i < size; i++) {
        cout << "|" << largestNumbersArray[i] << "|";
    }
    cout << endl;
}

int main() {
    char* buffer;
    FILE* f = fopen("sample.txt", "r");
    if(f == NULL) {
        exit(1);
    }

    // obtain file size:
    fseek(f , 0 , SEEK_END);
    size_t bufSize = ftell(f);
    rewind(f);

    buffer = (char*)malloc(bufSize);
    int readCount = fread((void*)buffer, sizeof(char), bufSize, f);
    fclose(f);

    cout << "Original file: " << endl;
    cout << buffer << endl;

    cout << "Parsed numbers: " << endl;
    char* tok = strtok(buffer, " \n");
    bool firstRun = true;
    int N = 0;
    int listSize = 0;
    int* numberList;
    int *head, *tail, *currentHead;
    char c;
    while(tok != NULL) {
        int currentNum = strtol(tok, NULL, 10);
        if(currentNum != 0 || (currentNum == 0 && tok[0] == '0')) {
            cout << currentNum << " ";
            if(firstRun) {
                N = currentNum > 0 ? currentNum : 0;
                firstRun = false;

                numberList = (int*)calloc(sizeof(int), N);
                head = numberList;
                tail = numberList + N - 1;

                currentHead = tail;
                *currentHead = currentNum;
                //printList(numberList, N);
            } else {
                bool numberInserted = false;
                for(int* i = tail; i >= currentHead; i--) {
                    if(currentNum > *i) {
                        int* lastElement = currentHead-1 >= head ? currentHead-1 : head;
                        for(int* j = lastElement; j < i; j++) {
                            swapNumbers(*j, *(j+1));
                            //printList(numberList, N);
                        }
                        //cout << "Inserting " << currentNum << "..." << endl;
                        numberInserted = true;
                        *i = currentNum;
                        if(currentHead-1 >= head) {
                            currentHead--;
                        }
                        //printList(numberList, N);
                        break;
                    }
                }
                if(!numberInserted && currentHead > head) {
                    //cout << "lnserting " << currentNum << " at head of queue" << endl;
                    *(--currentHead) = currentNum;
                    //printList(numberList, N);
                }
            }
        }
        tok = strtok(NULL, " \n");
    }
    cout << endl;
    cout << "Size: " << tail-currentHead+1 << endl << endl;

    printList(numberList, N);

    free(numberList);
    free(buffer);
    numberList = NULL;
    buffer = NULL;

    return 0;
}

