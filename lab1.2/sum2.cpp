#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

void search(std::vector<int>& arr, int sum) {
    int l = arr.size();
    int check = 0;
    int i = 0;
    while (i < l && check == 0){
        int j = i + 1;
        while (j < l && check ==0){
            if (arr[i] + arr [j] == sum){
                check = 1;
            }
            j += 1;
        }
        i += 1;
    }
    
}

int measure_time(std::vector<int>& arr){

    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 3; cnt != 0; --cnt) {
        search(arr, -1);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
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
    int arr_length[100], search_time[100];
    for (int i = 0; i < 100; ++i) {
        arr_length[i] = 100 + i * 500;
    }

     // Выполняем алгоритм с разными длинами массива
    for (int i = 0; i < 100; ++i) {
        std::vector<int> arr;

        for (int j = 0; j < arr_length[i]; ++j) {
            arr.push_back(i);
        }

        search_time[i] = measure_time(arr);

        std::cout << "Array length: " << arr_length[i] << "\n";
        std::cout << "Search time: " << search_time[i] << " ms\n";
        std::cout << "------------------------\n";
    }

    writeFile(search_time, "search_time");
    writeFile(arr_length, "arr_length");

    return 0;
}