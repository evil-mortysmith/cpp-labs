#include <iostream>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <fstream>

int* add_element(int* array, int& size, int value) {
    int* new_array = new int[size + 1];
    
    for (size_t i = 0; i < size; ++i) {
        new_array[i] = array[i];
    }
    
    new_array[size] = value;
    
    delete[] array;
    
    size++;
    
    return new_array;
}


void writeFile(std::vector<int>& time, std::string name){
    std::string filename = name + ".txt";
    std::ofstream outFile(filename); // Создаем объект ofstream и открываем файл output.txt


    // Записываем массив в файл
    for (int i = 0; i < 100; ++i) {
        outFile << time[i] << "\n"; // Записываем каждый элемент массива в файл
    }

    outFile.close(); // Закрываем файл
    std::cout << "Массив успешно записан в файл!" << std::endl;


}

int main() {
    int size = 0;
    int* arr = nullptr;
    std::vector<int> time;
    

    for (int i = 0; i < 100; ++i) {
        auto begin = std::chrono::steady_clock::now();

        for (unsigned cnt = 100; cnt != 0; --cnt) {
            arr = add_element(arr, size, 1);
        }

        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        time.push_back(time_span.count());


    }

    writeFile(time, "data_1.1");
    
    
    delete[] arr;
    
    return 0;
}