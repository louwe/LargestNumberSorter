#include <iostream>

using namespace std;

/**
 * Swap the contents of the argument list (number1 and number2).
 */
void swapNumbers(int& number1, int& number2) {
    number1 += number2;
    number2 = number1 - number2;
    number1 -= number2;
}

void printList(int* largestNumbersArray, int size) {
    // Pretty print the list.
    for(int i = 0; i < size; i++) {
        cout << "|" << largestNumbersArray[i] << "|";
    }
    cout << endl;
}

int main() {
    // Allocate buffer for sample file.
    char* buffer;
    FILE* f = fopen("sample.txt", "r");
    if(f == NULL) {
        exit(1);
    }

    // obtain file size:
    fseek(f , 0 , SEEK_END);
    size_t bufSize = ftell(f);
    rewind(f);

    // Copy the contents of the file to the buffer.
    buffer = (char*)malloc(bufSize);
    int readCount = fread((void*)buffer, sizeof(char), bufSize, f);
    fclose(f);

    // Show the contents of the original file.
    cout << "Original file: " << endl;
    cout << buffer << endl;

    // Initialize temporary variables that will be used for parsing and sorting the number list.
    char* tok = strtok(buffer, " \n");
    bool firstRun = true;
    int N = 0;
    int listSize = 0;
    int* numberList;
    int *head, *tail, *currentHead;
    char c;

    // Keep parsing until there are no more numbers to parse.
    while(tok != NULL) {
        // Convert the number.
        int currentNum = strtol(tok, NULL, 10);

        // If the number is a valid number, start processing.
        if(currentNum != 0 || (currentNum == 0 && tok[0] == '0')) {

            // For first run, always store the nummber and initialize pointers for the list.
            if(firstRun) {
                N = currentNum > 0 ? currentNum : 0;
                firstRun = false;

                numberList = (int*)calloc(sizeof(int), N);
                head = numberList;
                tail = numberList + N - 1;

                currentHead = tail;
                *currentHead = currentNum;
            } else {
                // On subsequent runs,
                // loop from largest number to smallest number.
                bool numberInserted = false;
                for(int* i = tail; i >= currentHead; i--) {
                    // If the current parsed number is greater,
                    // Shift the list from the smallest number to the current number to make room for insertion of the current parsed number.
                    // Else, check if it is a duplicate. If it is, mark duplicate and exit the loop to parse the next number.
                    // Additionally, exit the loop, update the current end of the list for list size calculation,
                    // and parse the next number after insertion
                    if(currentNum > *i) {
                        int* lastElement = currentHead-1 >= head ? currentHead-1 : head;
                        for(int* j = lastElement; j < i; j++) {
                            swapNumbers(*j, *(j+1));
                        }
                        numberInserted = true;
                        *i = currentNum;
                        if(currentHead-1 >= head) {
                            currentHead--;
                        }
                        break;
                    }
                }

                // If by the time we reach this point,
                // there have been no insertion, no duplicate, and the list is not yet full,
                // Insert the current number at the beginning of the list.
                if(!numberInserted && currentHead > head) {
                    *(--currentHead) = currentNum;
                }
            }
        }
        // Parse the next number.
        tok = strtok(NULL, " \n");
    }
    cout << endl;

    // Print out the current size of the list.
    // And output the contents of the list.
    cout << "Size: " << tail-currentHead+1 << endl << endl;
    printList(numberList, N);

    // Free up buffers.
    free(numberList);
    free(buffer);
    numberList = NULL;
    buffer = NULL;

    return 0;
}

