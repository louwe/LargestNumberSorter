#include <iostream>

using namespace std;

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
    char* tok = strtok(buffer, " ");
    bool firstRun = true;
    int N = 0;
    int* nLargestNumbers;
    int *tail, *currentPtr;
    int* currentLargestPtr;
    while(tok != NULL) {
        long int currentNum = strtol(tok, NULL, 10);
        if(currentNum != 0 || (currentNum == 0 && tok[0] == '0')) {
            if(firstRun) {
                N = currentNum;
                firstRun = false;

                nLargestNumbers = (int*)malloc(N * sizeof(int));
                currentPtr = nLargestNumbers;
                tail = nLargestNumbers + N - 1;
                currentLargestPtr = nLargestNumbers;
            }

            if(currentNum >= *currentLargestPtr) {
                *currentPtr = currentNum;
                if(currentPtr == tail) {
                    currentPtr = nLargestNumbers;
                } else {
                    currentPtr++;
                }
            }
            cout << currentNum << " ";
        }
        tok = strtok(NULL, " ");
    }

    cout << endl;

    for(int i = 0; i < N; i++) {
        cout << nLargestNumbers[i] << " ";
    }
    cout << endl;

    free(nLargestNumbers);
    free(buffer);
    nLargestNumbers = NULL;
    buffer = NULL;

    return 0;
}

