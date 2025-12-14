#include<iostream>
#include<random>
#include<iomanip>
#include<chrono>  

using namespace std;

// Глобальные переменные для подсчета операций
// comparisons - счетчик сравнения элементов 
// swaps - счетчик перестановки элементов 
// debug - флаг, сделать подробный вывод или нет
long long comparisons = 0;
long long swaps = 0;
bool debug = false;

//Ф-ия вывода массива (StepName - Название шага)
void printArray(int arr[], int size, string stepName) {
    if (debug) {
        cout << stepName << ": ";
        //Перебираем все элементы массива и выводим
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

//Обнуляем счетчики
void resetCounters() {
    comparisons = 0;
    swaps = 0;
}

//Сортировка слиянием
void Merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int* b_list = new int[n1 + 1];
    int* c_list = new int[n2 + 1];

    for (int i = 0; i < n1; i++) {
        b_list[i] = arr[p + i];
    }

    for (int i = 0; i < n2; i++) {
        c_list[i] = arr[q + 1 + i];
    }

    b_list[n1] = INT_MAX;
    c_list[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        comparisons++;
        if (b_list[i] <= c_list[j]) {
            arr[k] = b_list[i];
            i++;
        }
        else {
            arr[k] = c_list[j];
            j++;
        }
        swaps++;
    }

    delete[] b_list;
    delete[] c_list;
}

void Merge_Sort(int arr[], int p, int r) {
    if (p >= r) {
        return;
    }

    int q = (p + r) / 2;
    Merge_Sort(arr, p, q);
    Merge_Sort(arr, q + 1, r);
    Merge(arr, p, q, r);

    if (debug) {
        static int callCount = 0;
        cout << "Merge Sort Step " << ++callCount << ": ";
        for (int i = p; i <= r; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

// Быстрая сортировка 
int Partition(int arr[], int p, int r) {
    // Выбираем случайный индекс между p и r
    int random_index = p + rand() % (r - p + 1);

    // Меняем случайный элемент с последним
    int temp_swap = arr[random_index];
    arr[random_index] = arr[r];
    arr[r] = temp_swap;
    swaps++;

    int q = p;
    int pivot = arr[r];  

    for (int u = p; u < r; u++) {
        comparisons++;
        if (arr[u] <= pivot) {
            if (u != q){
                int temp = arr[u];
                arr[u] = arr[q];
                arr[q] = temp;
                swaps++;
            }
        q++;

        }
    }

    temp_swap = arr[q];
    arr[q] = arr[r];
    arr[r] = temp_swap;
    swaps++;

    if (debug) {
        cout << "Partition - pivot index " << q << ": ";
        for (int k = p; k <= r; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
    }

    return q;
}

void Quick_Sort(int arr[], int p, int r) {
    if (p >= r) {
        return;
    }

    int q = Partition(arr, p, r);
    Quick_Sort(arr, p, q - 1);
    Quick_Sort(arr, q + 1, r);
}

// Быстрая сортировка по схеме Hoare
int Partition_Hoare(int arr[], int p, int r) {
    int pivot = arr[(p + r) / 2];
    int i = p - 1;
    int j = r + 1;

    while (true) {
        do {
            i++;
            comparisons++;
        } while (arr[i] < pivot);

        do {
            j--;
            comparisons++;
        } while (arr[j] > pivot);

        if (i >= j) {
            if (debug) {
                cout << "Partition (Hoare) - pivot index " << j << ": ";
                for (int k = p; k <= r; k++) {
                    cout << arr[k] << " ";
                }
                cout << endl;
            }
            return j;
        }

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        swaps++;
    }
}

void Quick_Sort_Hoare(int arr[], int p, int r) {
    if (p >= r) {
        return;
    }

    int q = Partition_Hoare(arr, p, r);
    Quick_Sort_Hoare(arr, p, q);
    Quick_Sort_Hoare(arr, q + 1, r);
}

int main() {
    //Тесты с n=15 
    cout << "\t\tTESTING WITH n=15" << endl;
    const int small_size = 15;
    debug = true;

    int original[small_size];
    cout << "Original array: ";
    for (int i = 0; i < small_size; i++) {
        //Заполняем исходный массив случайными числами в диапазоне от 0 до 99
        original[i] = rand() % 100;
        //Вывод массива
        cout << original[i] << " ";
    }
    cout << endl << endl;

    //Временный массив: сохраняем исходный массив и работаем с скопированным
    int test_arr[small_size];

    // Merge Sort
    for (int i = 0; i < small_size; i++) test_arr[i] = original[i];
    resetCounters();
    cout << "\tMerge Sort" << endl;
    cout << endl;
    Merge_Sort(test_arr, 0, small_size - 1);
    cout << "Result: ";
    for (int i = 0; i < small_size; i++) cout << test_arr[i] << " ";
    cout << "\nComparisons: " << comparisons << ", Swaps: " << swaps << endl << endl;
    
    cout <<"Original array: ";

    for (int i = 0; i < small_size; i++){
        cout << original[i] << " ";
    }

    cout << endl << endl;

    // Quick Sort
    for (int i = 0; i < small_size; i++) test_arr[i] = original[i];
    resetCounters();
    cout << "\tQuick Sort" << endl;
    cout << endl;
    Quick_Sort(test_arr, 0, small_size - 1);
    cout << "Result: ";
    for (int i = 0; i < small_size; i++) cout << test_arr[i] << " ";
    cout << "\nComparisons: " << comparisons << ", Swaps: " << swaps << endl << endl;

    cout <<"Original array: ";
    for (int i = 0; i < small_size; i++){
        cout << original[i] << " ";
    }

    cout << endl << endl;

    // Quick Sort Hoare
    for (int i = 0; i < small_size; i++) test_arr[i] = original[i];
    resetCounters();
    cout << "\tQuick Sort with Hoare" << endl;
    cout << endl;
    Quick_Sort_Hoare(test_arr, 0, small_size - 1);
    cout << "Result: ";
    for (int i = 0; i < small_size; i++) cout << test_arr[i] << " ";
    cout << "\nComparisons: " << comparisons << ", Swaps: " << swaps << endl << endl;

    //Тесты с другими данными
    cout << "\t\tPERFORMANCE TESTING WITH LARGE ARRAYS" << endl;
    debug = false;

    //Массив размеров для тестирования 
    int sizes[] = { 500, 1000, 10000, 50000, 100000 };

    for (int size : sizes) {
        cout << "\n--- Testing with n=" << size << " ---" << endl;

        //Тестовые массивы для проверок
        //random_arr - случайный массик (генерируется рандомными числами)
        //scending_arr - возрастающая последовательность 
        //descending_arr - убывающая последовательность 
        int* random_arr = new int[size];
        int* ascending_arr = new int[size];
        int* descending_arr = new int[size];

        //Заполняем тестовые массивы
        for (int i = 0; i < size; i++) {
            random_arr[i] = rand();
            ascending_arr[i] = i;
            descending_arr[i] = size - i;
        }

        //Временный массив для сортировки, чтоб не работать с исходным
        int* temp = new int[size];
        cout << "Random array" << endl;

        // Merge Sort
        for (int i = 0; i < size; i++) temp[i] = random_arr[i];
        resetCounters();
        auto begin = chrono::steady_clock::now();
        Merge_Sort(temp, 0, size - 1);
        auto end = chrono::steady_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << "Merge Sort - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms.count() << " (microsecond)" << endl;

        // Quick Sort 
        for (int i = 0; i < size; i++) temp[i] = random_arr[i];
        resetCounters();
        begin = chrono::steady_clock::now();
        Quick_Sort(temp, 0, size - 1);
        end = chrono::steady_clock::now();
        elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << "Quick Sort - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms.count() << " (microsecond)" << endl;

        // Quick Sort Hoare
        for (int i = 0; i < size; i++) temp[i] = random_arr[i];
        resetCounters();
        begin = chrono::steady_clock::now();
        Quick_Sort_Hoare(temp, 0, size - 1);
        end = chrono::steady_clock::now();
        elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << "Quick Sort Hoare - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms.count() << " (microsecond)" << endl;


        cout << "Ascending array" << endl;

        // Merge Sort
        for (int i = 0; i < size; i++) temp[i] = ascending_arr[i];
        resetCounters();
        auto begin_asc = chrono::steady_clock::now();
        Merge_Sort(temp, 0, size - 1);
        auto end_asc = chrono::steady_clock::now();
        auto elapsed_ms_asc = chrono::duration_cast<chrono::microseconds>(end_asc - begin_asc);
        cout << "Merge Sort - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms_asc.count() << " (microsecond)" << endl;

        // Quick Sort 
        for (int i = 0; i < size; i++) temp[i] = ascending_arr[i];
        resetCounters();
        begin_asc = chrono::steady_clock::now();
        Quick_Sort(temp, 0, size - 1);
        end_asc = chrono::steady_clock::now();
        elapsed_ms_asc = chrono::duration_cast<chrono::microseconds>(end_asc - begin_asc);
        cout << "Quick Sort - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms_asc.count() << " (microsecond)" << endl;

        // Quick Sort Hoare
        for (int i = 0; i < size; i++) temp[i] = ascending_arr[i];
        resetCounters();
        begin_asc = chrono::steady_clock::now();
        Quick_Sort_Hoare(temp, 0, size - 1);
        end_asc = chrono::steady_clock::now();
        elapsed_ms_asc = chrono::duration_cast<chrono::microseconds>(end_asc - begin_asc);
        cout << "Quick Sort Hoare - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms_asc.count() << " (microsecond)" << endl;

        cout << "Array in descending order" << endl;

        // Merge Sort
        for (int i = 0; i < size; i++) temp[i] = descending_arr[i];
        resetCounters();
        auto begin_desc = chrono::steady_clock::now();  
        Merge_Sort(temp, 0, size - 1);
        auto end_desc = chrono::steady_clock::now();    
        auto elapsed_ms_desc = chrono::duration_cast<chrono::microseconds>(end_desc - begin_desc);
        cout << "Merge Sort - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms_desc.count() << " (microsecond)" << endl;

        // Quick Sort 
        for (int i = 0; i < size; i++) temp[i] = descending_arr[i];
        resetCounters();
        begin_desc = chrono::steady_clock::now();      
        Quick_Sort(temp, 0, size - 1);
        end_desc = chrono::steady_clock::now();        
        elapsed_ms_desc = chrono::duration_cast<chrono::microseconds>(end_desc - begin_desc); 
        cout << "Quick Sort - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms_desc.count() << " (microsecond)" << endl;

        // Quick Sort Hoare
        for (int i = 0; i < size; i++) temp[i] = descending_arr[i];
        resetCounters();
        begin_desc = chrono::steady_clock::now();      
        Quick_Sort_Hoare(temp, 0, size - 1);
        end_desc = chrono::steady_clock::now();        
        elapsed_ms_desc = chrono::duration_cast<chrono::microseconds>(end_desc - begin_desc); 
        cout << "Quick Sort Hoare - Comparisons: " << comparisons << ", Swaps: " << swaps
            << ", Time: " << elapsed_ms_desc.count() << " (microsecond)" << endl;


        delete[] temp;
        delete[] random_arr;
        delete[] ascending_arr;
        delete[] descending_arr;
    }

    return 0;
}