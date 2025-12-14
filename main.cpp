#include<iostream>
#include<random>
#include<chrono>

const int NOT_FOUND = -1;
using namespace std;

int counter1, counter2;

void reset() {
    counter1 = 0;
    counter2 = 0;
}

void BubbleSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int Betta_Linear_Search(int arr[], int len, int x) {
    reset();
    for (int i = 0; i < len; i++) {
        counter2++;
        counter1++;
        if (arr[i] == x) {
            return i;
        }
    }
    counter2++;
    return NOT_FOUND;
}

int Sentinel_Linear_Search(int arr[], int len, int x) {
    reset();

    int last = arr[len - 1];
    arr[len - 1] = x;

    int i = 0;

    counter2++;
    while (arr[i] != x) {
        counter1++;
        i++;
    }

    arr[len - 1] = last;

    if (i < len - 1 || arr[len - 1] == x) {
        return i;
    }
    else {
        return NOT_FOUND;
    }
}

int Order_Array_Search(int arr[], int len, int x) {
    reset();
    for (int i = 0; i < len; i++) {
        counter2++;
        counter1++;
        if (arr[i] == x) {
            return i;
        }
        if (arr[i] > x) {
            return NOT_FOUND;
        }
    }
    counter2++;

    return NOT_FOUND;

}

int Binary_Search(int arr[], int len, int x) {
    reset();

    int p = 0;
    int r = len - 1;
    int q;

    while (p <= r) {
        counter2++;
        q = (p + r) / 2;
        counter1++;
        if (arr[q] == x) {
            return q;
        }
        else {
            counter1++;
            if (arr[q] > x) {
                r = q - 1;
            }
            else {
                p = q + 1;
            }
        }
    }
    counter2++;

    return NOT_FOUND;
}

int main() {

    const int size = 50000;

    int* next_list = new int[size];
    int* sorted_list = new int[size];

    srand(time(0));

    for (int i = 0; i < size; i++) {
        next_list[i] = rand();
    }

    for (int i = 0; i < size; i++) {
        sorted_list[i] = next_list[i];
    }


    BubbleSort(sorted_list, size);

    int first = next_list[0];
    int midle = next_list[size / 2];
    int not_key = INT_MAX;

    int first_sorted = sorted_list[0];
    int middle_sorted = sorted_list[size / 2];

    
    // BLS - начало
    auto start = chrono::steady_clock::now();
    Betta_Linear_Search(next_list, size, first);
    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tBLS\t\tfirst\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // BLS - середина
    start = chrono::steady_clock::now();
    Betta_Linear_Search(next_list, size, midle);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tBLS\t\tmidle\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // BLS - нет ключа
    start = chrono::steady_clock::now();
    Betta_Linear_Search(next_list, size, not_key);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tBLS\t\tnot_key\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // SLS - начало
    start = chrono::steady_clock::now();
    Sentinel_Linear_Search(next_list, size, first);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tSLS\t\tfirst\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // SLS - середина 
    start = chrono::steady_clock::now();
    Sentinel_Linear_Search(next_list, size, midle);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tSLS\t\tmidle\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // SLS - нет ключа
    start = chrono::steady_clock::now();
    Sentinel_Linear_Search(next_list, size, not_key);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tSLS\t\tnot_key\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // OAS - начало
    start = chrono::steady_clock::now();
    Order_Array_Search(sorted_list, size, first_sorted);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tOAS\t\tfirst\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // OAS - середина
    start = chrono::steady_clock::now();
    Order_Array_Search(sorted_list, size, middle_sorted);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tOAS\t\tmidle\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    // OAS - нет ключа
    start = chrono::steady_clock::now();
    Order_Array_Search(sorted_list, size, not_key);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tOAS\t\tnot_key\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    //BS - начало
    start = chrono::steady_clock::now();
    Binary_Search(sorted_list, size, first_sorted);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tBS\t\tfirst\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    //BS - середина
    start = chrono::steady_clock::now();
    Binary_Search(sorted_list, size, middle_sorted);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tBS\t\tmidle\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    //BS - нет ключа
    start = chrono::steady_clock::now();
    Binary_Search(sorted_list, size, not_key);
    end = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << size << "\tBS\t\tnot_key\t" << time.count() << "\t\t" << counter1 << "\t" << counter2 << endl;

    delete[] next_list;
    delete[] sorted_list;

    return 0;
}