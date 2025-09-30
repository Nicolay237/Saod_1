#include <iostream>
#include <fstream>
#include <chrono>

// Вспомогательные функции для работы с массивами
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

// 1. Сортировка выбором (Selection Sort)
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

// 2. Пузырьковая сортировка (Bubble Sort)
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

// 3. Сортировка вставками (Insertion Sort)
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

// 4. Сортировка слиянием (Merge Sort)
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Слияние временных массивов обратно в arr[left..right]
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

    // Копируем оставшиеся элементы leftArr[]
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы rightArr[]
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

// 5. Пирамидальная сортировка (Heap Sort)
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
    // Построение max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Извлечение элементов из кучи один за другим
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// 6. Быстрая сортировка (Quick Sort)
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

// Функции для лексикографической сортировки строк
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

// Лексикографическая сортировка строк (Quick Sort для строк)
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

// Функции для работы с файлами
int readNumbersFromFile(const char* filename, int** arr) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла " << filename << std::endl;
        return 0;
    }

    // Сначала подсчитаем количество чисел
    int count = 0;
    int temp;
    while (file >> temp) {
        count++;
    }

    file.clear();
    file.seekg(0);

    // Выделяем память и читаем числа
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

    // Подсчет количества строк
    int count = 0;
    char buffer[256];
    while (file.getline(buffer, 256)) {
        count++;
    }

    file.clear();
    file.seekg(0);

    // Выделяем память и читаем строки
    *arr = new char* [count];
    for (int i = 0; i < count; i++) {
        file.getline(buffer, 256);
        (*arr)[i] = new char[256];
        stringCopy((*arr)[i], buffer);
    }

    file.close();
    return count;
}

// Функции для сохранения результатов в файлы
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

// Функция для измерения времени выполнения
template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Функции для тестирования сортировок с сохранением результатов
void testSortWithSave(void (*sortFunc)(int[], int), const char* name, const char* filename,
    int arr[], int n, int original[]) {
    // Восстанавливаем исходный массив
    for (int i = 0; i < n; i++) {
        arr[i] = original[i];
    }

    double time = measureTime([&]() { sortFunc(arr, n); });
    std::cout << name << ": " << time << " секунд" << std::endl;

    // Сохраняем результат
    saveNumbersToFile(filename, arr, n);
}

void testAdvancedSortWithSave(void (*sortFunc)(int[], int, int), const char* name, const char* filename,
    int arr[], int n, int original[]) {
    for (int i = 0; i < n; i++) {
        arr[i] = original[i];
    }

    double time = measureTime([&]() { sortFunc(arr, 0, n - 1); });
    std::cout << name << ": " << time << " секунд" << std::endl;

    // Сохраняем результат
    saveNumbersToFile(filename, arr, n);
}

int main() {
    // Чтение числовых данных
    setlocale(LC_ALL, "Russian");
    int* numbers = nullptr;
    int n = readNumbersFromFile("numbers.txt", &numbers);

    if (n == 0) {
        std::cout << "Файл numbers.txt пуст или не найден" << std::endl;
        return 1;
    }

    // Создаем копию исходных данных
    int* original = new int[n];
    for (int i = 0; i < n; i++) {
        original[i] = numbers[i];
    }

    std::cout << "Анализ времени выполнения сортировок для " << n << " элементов:" << std::endl;
    std::cout << "==============================================" << std::endl;

    // Тестируем все сортировки с сохранением результатов
    testSortWithSave(selectionSort, "Сортировка выбором", "selection_sorted.txt", numbers, n, original);
    testSortWithSave(bubbleSort, "Пузырьковая сортировка", "bubble_sorted.txt", numbers, n, original);
    testSortWithSave(insertionSort, "Сортировка вставками", "insertion_sorted.txt", numbers, n, original);
    testAdvancedSortWithSave(mergeSort, "Сортировка слиянием", "merge_sorted.txt", numbers, n, original);
    testSortWithSave(heapSort, "Пирамидальная сортировка", "heap_sorted.txt", numbers, n, original);
    testAdvancedSortWithSave(quickSort, "Быстрая сортировка", "quick_sorted.txt", numbers, n, original);

    // Лексикографическая сортировка
    std::cout << "\nЛексикографическая сортировка:" << std::endl;
    std::cout << "==============================================" << std::endl;

    char** strings = nullptr;
    int stringCount = readStringsFromFile("people.txt", &strings);

    if (stringCount > 0) {
        // Создаем копию исходных строк для восстановления
        char** originalStrings = new char* [stringCount];
        for (int i = 0; i < stringCount; i++) {
            originalStrings[i] = new char[256];
            stringCopy(originalStrings[i], strings[i]);
        }

        double time = measureTime([&]() { quickSortStrings(strings, 0, stringCount - 1); });
        std::cout << "Время выполнения: " << time << " секунд" << std::endl;

        // Сохраняем отсортированные строки
        saveStringsToFile("lexicographic_sorted.txt", strings, stringCount);

        std::cout << "\nПервые 10 отсортированных строк:" << std::endl;
        for (int i = 0; i < (stringCount < 10 ? stringCount : 10); i++) {
            std::cout << strings[i] << std::endl;
        }

        // Освобождаем память строк
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

    // Сохраняем исходные данные для сравнения
    saveNumbersToFile("original_numbers.txt", original, n);

    // Освобождаем память
    delete[] numbers;
    delete[] original;

    std::cout << "\nВсе отсортированные массивы сохранены в файлы:" << std::endl;
    std::cout << "- selection_sorted.txt" << std::endl;
    std::cout << "- bubble_sorted.txt" << std::endl;
    std::cout << "- insertion_sorted.txt" << std::endl;
    std::cout << "- merge_sorted.txt" << std::endl;
    std::cout << "- heap_sorted.txt" << std::endl;
    std::cout << "- quick_sorted.txt" << std::endl;
    std::cout << "- lexicographic_sorted.txt (для строк)" << std::endl;
    std::cout << "- original_numbers.txt (исходные данные)" << std::endl;

    return 0;
}