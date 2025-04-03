#include <iostream>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <fstream>


int* add_element2(int* arr, int& size, int& capacity, int value) {
    // Если место закончилось, выделяем новый блок
    if (size >= capacity) {
        int new_capacity;
        if (capacity == 0){
            int new_capacity = 1;
        }
        else{
            int new_capacity = capacity*2;
        }
        int* new_arr = new int[new_capacity];
        

        for (int i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }
        
        delete[] arr;
        

        arr = new_arr;
        capacity = new_capacity;
    }
    
    arr[size] = value;
    size++;
    
    return arr;
}

void writeFile(std::vector<int>& time, std::string name){
    std::string filename = name + ".txt";
    std::ofstream outFile(filename);

    for (int i = 0; i < 500; ++i) {
        outFile << time[i] << "\n";
    }

    outFile.close();
    std::cout << "Массив успешно записан в файл!" << std::endl;


}

int main() {
    int size = 0;
    int capacity = 0;
    int* arr = nullptr;
    std::vector<int> time;
    

    for (int i = 0; i < 500; ++i) {
        auto begin = std::chrono::steady_clock::now();

        for (unsigned cnt = 100; cnt != 0; --cnt) {
            arr = add_element2(arr, size, capacity, 1);
        }

        
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        time.push_back(time_span.count());

        delete[] arr;

    }
    
    writeFile(time, "data_1.3");
    
    
    delete[] arr;
    
    return 0;

}