#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>

void fast_search(std::vector<int>& arr, int sum) {
    int n = arr.size();
    int check = 0;
    int left = 0;
    int right = n - 1;
    while (left != right && check == 0){
        int mid = arr[left] + arr[right];
        if (mid < sum)
            left++;
        else if (mid > sum)
            right--;
        else{
            check = 1;
        }
    }
    
}

int measure_time(int i, std::vector<int>& arr){
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, i);
    
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt) {
        fast_search(arr, arr[dstr(rng)] + arr[dstr(rng)]);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return time_span.count();
}

int writeFile(int arr[], const std::string name){
    std::string filename = name + ".txt";
    std::ofstream outFile(filename);


    // Записываем массив в файл
    for (int i = 0; i < 100; ++i) {
        outFile << arr[i] << "\n"; // Записываем каждый элемент массива в файл
    }

    outFile.close(); // Закрываем файл
    std::cout << "Массив успешно записан в файл!" << std::endl;

    return 0;
}

int main(){
    int arr_length[100], fast_search_time[100];
    for (int i = 0; i < 100; ++i) {
        arr_length[i] = 100 + i * 500;
    }

     // Выполняем алгоритм с разными длинами массива
    for (int i = 0; i < 100; ++i) {
        std::vector<int> arr;
    
        unsigned seed = 1001;
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<unsigned> dstr(0, i);

        for (int j = 0; j < arr_length[i]; ++j) {
            arr.push_back(dstr(rng));
            
        }
        
        std::sort(arr.begin(), arr.end());


        fast_search_time[i] = measure_time(i, arr);

        std::cout << "Array length: " << arr_length[i] << "\n";
        std::cout << "Fast search time: " << fast_search_time[i] << " us\n";
        std::cout << "------------------------\n";
    }

    writeFile(fast_search_time, "fast_search_time");
    // writeFile(arr_length, "arr_length");

    return 0;
}