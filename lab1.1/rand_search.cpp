#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>

// Функция поиска полным перебором
bool linear_search(const std::vector<int>& arr, int target) {
    for (int num : arr) {
        if (num == target) {
            return true;
        }
    }
    return false;
}

// Функция бинарного поиска
bool binary_search(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return true;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

int rand(int i) {

    unsigned seed = 1001; // Начальное значение (seed) для генератора случайных чисел
    std::default_random_engine rng(seed); // Генератор случайных чисел
    std::uniform_int_distribution<unsigned> dstr(0, i);

    return dstr(rng);
}

// Функция для измерения времени выполнения
int measure_time(int i, const std::vector<int>& arr, bool (*search_func)(const std::vector<int>&, int)) {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, i);
    int x = dstr(rng);
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt) {
        search_func(arr, x); // Ищем случайный элемент
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return time_span.count();
}

int writeFile(int arr[], const std::string name){
    std::string filename = name + ".txt";
    std::ofstream outFile(filename); // Создаем объект ofstream и открываем файл output.txt


    // Записываем массив в файл
    for (int i = 0; i < 100; ++i) {
        outFile << arr[i] << "\n"; // Записываем каждый элемент массива в файл
    }

    outFile.close(); // Закрываем файл
    std::cout << "Массив успешно записан в файл!" << std::endl;

    return 0;
}

int main() {
    int arr_length[100], rand_linear_search_time[100], rand_binary_search_time[100];
    for (int i = 0; i < 100; ++i) {
        arr_length[i] = 100 + i * 10000;
    }
    

    // Выполняем алгоритм с разными длинами массива
    for (int i = 0; i < 100; ++i) {
        std::vector<int> arr;

        // Заполняем массив числами
        for (int j = 0; j < arr_length[i]; ++j) {
            arr.push_back(i);
            
        }
        
        // Сортируем массив для бинарного поиска
        std::sort(arr.begin(), arr.end());


        // Измеряем время для линейного поиска
        rand_linear_search_time[i] = measure_time(i, arr, linear_search);

        // Измеряем время для бинарного поиска
        rand_binary_search_time[i] = measure_time(i, arr, binary_search);

        std::cout << "Array length: " << arr_length[i] << "\n";
        std::cout << "Linear search time: " << rand_linear_search_time[i] << " us\n";
        std::cout << "Binary search time: " << rand_binary_search_time[i] << " us\n";
        std::cout << "------------------------\n";

    }

    writeFile(rand_linear_search_time, "rand_linear_search_time");
    writeFile(rand_binary_search_time, "rand_binary_search_time");

    
    return 0;
}