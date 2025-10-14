#include <iostream>
#include <fstream>
#include <chrono>


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapStrings(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(&arr[i], &arr[minIndex]);
        }
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int stringCompare(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

void stringCopy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

int stringLength(const char* str) {
    int length = 0;
    while (*str++) length++;
    return length;
}

int partitionStrings(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (stringCompare(arr[j], pivot) < 0) {
            i++;
            swapStrings(&arr[i], &arr[j]);
        }
    }
    swapStrings(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortStrings(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partitionStrings(arr, low, high);
        quickSortStrings(arr, low, pi - 1);
        quickSortStrings(arr, pi + 1, high);
    }
}

void bubbleSortStrings(char* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (stringCompare(arr[j], arr[j + 1]) > 0) {
                swapStrings(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void insertionSortStrings(char* arr[], int n) {
    for (int i = 1; i < n; i++) {
        char* key = arr[i];
        int j = i - 1;

        while (j >= 0 && stringCompare(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int readNumbersFromFile(const char* filename, int** arr) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return 0;
    }

    int count = 0;
    int temp;
    while (file >> temp) {
        count++;
    }

    file.clear();
    file.seekg(0);

    *arr = new int[count];
    for (int i = 0; i < count; i++) {
        file >> (*arr)[i];
    }

    file.close();
    return count;
}

int readStringsFromFile(const char* filename, char*** arr) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return 0;
    }

    int count = 0;
    char buffer[256];
    while (file.getline(buffer, 256)) {
        count++;
    }

    file.clear();
    file.seekg(0);

    *arr = new char* [count];
    for (int i = 0; i < count; i++) {
        file.getline(buffer, 256);
        (*arr)[i] = new char[256];
        stringCopy((*arr)[i], buffer);
    }

    file.close();
    return count;
}

void saveNumbersToFile(const char* filename, int arr[], int n) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка создания файла " << filename << std::endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        file << arr[i];
        if (i < n - 1) file << " ";
    }
    file.close();
    std::cout << "Результат сохранен в " << filename << std::endl;
}

void saveStringsToFile(const char* filename, char* arr[], int n) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка создания файла " << filename << std::endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        file << arr[i];
        if (i < n - 1) file << std::endl;
    }
    file.close();
    std::cout << "Результат сохранен в " << filename << std::endl;
}

template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

void testSortWithSave(void (*sortFunc)(int[], int), const char* name, const char* filename,
    int arr[], int n, int original[]) {
    for (int i = 0; i < n; i++) {
        arr[i] = original[i];
    }

    double time = measureTime([&]() { sortFunc(arr, n); });
    std::cout << name << ": " << time << " секунд" << std::endl;

    saveNumbersToFile(filename, arr, n);
}

void testAdvancedSortWithSave(void (*sortFunc)(int[], int, int), const char* name, const char* filename,
    int arr[], int n, int original[]) {
    for (int i = 0; i < n; i++) {
        arr[i] = original[i];
    }

    double time = measureTime([&]() { sortFunc(arr, 0, n - 1); });
    std::cout << name << ": " << time << " секунд" << std::endl;

    saveNumbersToFile(filename, arr, n);
}

void testStringSortWithSave(void (*sortFunc)(char* [], int), const char* name, const char* filename,
    char* arr[], int n, char* original[]) {
    for (int i = 0; i < n; i++) {
        stringCopy(arr[i], original[i]);
    }

    double time = measureTime([&]() { sortFunc(arr, n); });
    std::cout << name << ": " << time << " секунд" << std::endl;

    saveStringsToFile(filename, arr, n);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int* numbers = nullptr;
    int n = readNumbersFromFile("numbers.txt", &numbers);

    if (n == 0) {
        std::cout << "Файл numbers.txt пуст или не найден" << std::endl;
        return 1;
    }

    int* original = new int[n];
    for (int i = 0; i < n; i++) {
        original[i] = numbers[i];
    }

    std::cout << "Анализ времени выполнения сортировок для " << n << " элементов:" << std::endl;
    std::cout << "==============================================" << std::endl;

    testSortWithSave(selectionSort, "Сортировка выбором", "selection_sorted.txt", numbers, n, original);
    testSortWithSave(bubbleSort, "Пузырьковая сортировка", "bubble_sorted.txt", numbers, n, original);
    testSortWithSave(insertionSort, "Сортировка вставками", "insertion_sorted.txt", numbers, n, original);
    testAdvancedSortWithSave(mergeSort, "Сортировка слиянием", "merge_sorted.txt", numbers, n, original);
    testSortWithSave(heapSort, "Пирамидальная сортировка", "heap_sorted.txt", numbers, n, original);
    testAdvancedSortWithSave(quickSort, "Быстрая сортировка", "quick_sorted.txt", numbers, n, original);

    std::cout << "\nЛексикографическая сортировка (файл people.txt):" << std::endl;
    std::cout << "==============================================" << std::endl;

    char** strings = nullptr;
    int stringCount = readStringsFromFile("people.txt", &strings);

    if (stringCount > 0) {
        char** originalStrings = new char* [stringCount];
        for (int i = 0; i < stringCount; i++) {
            originalStrings[i] = new char[256];
            stringCopy(originalStrings[i], strings[i]);
        }

        double time = measureTime([&]() { quickSortStrings(strings, 0, stringCount - 1); });
        std::cout << "Быстрая лексикографическая сортировка: " << time << " секунд" << std::endl;
        saveStringsToFile("lexicographic_quick_sorted.txt", strings, stringCount);

        std::cout << "\nПервые 10 отсортированных строк (из быстрой сортировки):" << std::endl;
        for (int i = 0; i < (stringCount < 10 ? stringCount : 10); i++) {
            std::cout << strings[i] << std::endl;
        }

        for (int i = 0; i < stringCount; i++) {
            delete[] strings[i];
            delete[] originalStrings[i];
        }
        delete[] strings;
        delete[] originalStrings;
    }
    else {
        std::cout << "Файл people.txt пуст или не найден" << std::endl;
    }

    std::cout << "\nЛексикографическая сортировка (файл few_people.txt на 10000 строк):" << std::endl;
    std::cout << "==============================================" << std::endl;

    char** fewStrings = nullptr;
    int fewStringCount = readStringsFromFile("few_people.txt", &fewStrings);

    if (fewStringCount > 0) {
        char** originalFewStrings = new char* [fewStringCount];
        for (int i = 0; i < fewStringCount; i++) {
            originalFewStrings[i] = new char[256];
            stringCopy(originalFewStrings[i], fewStrings[i]);
        }

        std::cout << "Обработка " << fewStringCount << " строк из few_people.txt..." << std::endl;

        testStringSortWithSave(bubbleSortStrings, "Пузырьковая лексикографическая сортировка",
            "lexicographic_bubble_sorted.txt", fewStrings, fewStringCount, originalFewStrings);

        testStringSortWithSave(insertionSortStrings, "Лексикографическая сортировка вставками",
            "lexicographic_insertion_sorted.txt", fewStrings, fewStringCount, originalFewStrings);

        std::cout << "\nПервые 10 отсортированных строк (из сортировки вставками):" << std::endl;
        for (int i = 0; i < (fewStringCount < 10 ? fewStringCount : 10); i++) {
            std::cout << fewStrings[i] << std::endl;
        }

        for (int i = 0; i < fewStringCount; i++) {
            delete[] fewStrings[i];
            delete[] originalFewStrings[i];
        }
        delete[] fewStrings;
        delete[] originalFewStrings;
    }
    else {
        std::cout << "Файл few_people.txt пуст или не найден" << std::endl;
    }

    saveNumbersToFile("original_numbers.txt", original, n);

    delete[] numbers;
    delete[] original;

    std::cout << "\nВсе отсортированные массивы сохранены в файлы:" << std::endl;
    std::cout << "- selection_sorted.txt" << std::endl;
    std::cout << "- bubble_sorted.txt" << std::endl;
    std::cout << "- insertion_sorted.txt" << std::endl;
    std::cout << "- merge_sorted.txt" << std::endl;
    std::cout << "- heap_sorted.txt" << std::endl;
    std::cout << "- quick_sorted.txt" << std::endl;
    std::cout << "- lexicographic_quick_sorted.txt (быстрая для строк из people.txt)" << std::endl;
    std::cout << "- lexicographic_bubble_sorted.txt (пузырьковая для строк из few_people.txt)" << std::endl;
    std::cout << "- lexicographic_insertion_sorted.txt (вставками для строк из few_people.txt)" << std::endl;
    std::cout << "- original_numbers.txt (исходные данные)" << std::endl;

    return 0;
}
