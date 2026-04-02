#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <stdexcept>


void queue_new(std::size_t &read, std::size_t &write, int* &data, std::size_t &capacity) {
    read = 0;
    write = 0;
    capacity = 1;
    data = new int[capacity];

}

void queue_del(int* &data) {
    delete[] data;
    data = nullptr;
}

bool queue_poll(std::size_t &read, std::size_t &write, int* &data, std::size_t &capacity, int &element) {
    if (read == write) return false;
    element = data[read];
    read = (read + 1) % capacity;
    return true;
}

bool queue_push(std::size_t &read, std::size_t &write, int* &data, std::size_t &capacity, int element) {
    if ((write + 1) % capacity == read) { // Нужно увеличить capacity
        std::size_t new_capacity = capacity * 2;
        int* new_data = new int[new_capacity];
        if (!new_data) return false;

        // Копирование данных
        std::size_t i = 0;
        while (read != write) {
            new_data[i] = data[read];
            ++i;
            read = (read + 1) % capacity;
        }
        delete[] data;
        data = new_data;
        read = 0;
        write = i;
        capacity = new_capacity;
    }
    data[write] = element;
    write = (write + 1) % capacity;
    return true;
}

void writeFile(std::vector<int>& time, std::string name) {
    std::string filename = name + ".txt";
    std::ofstream outFile(filename);
    for (size_t i = 0; i < time.size(); ++i) {
        outFile << time[i] << "\n";
    }
    outFile.close();
    std::cout << "Массив успешно записан в файл " << filename << "!" << std::endl;
}

int main() {
    std::vector<int> push_times, poll_times;

    for (int i = 0; i < 500; ++i) {
        std::size_t read, write, capacity;
        int* data;
        queue_new(read, write, data, capacity);

        // Измерение времени для push
        auto begin_push = std::chrono::steady_clock::now();
        for (unsigned cnt = 100 + i; cnt != 0; --cnt) {
            if (!queue_push(read, write, data, capacity, cnt)) {
                std::cerr << "Ошибка push!" << std::endl;
                break;
            }
        }
        auto end_push = std::chrono::steady_clock::now();
        auto time_span_push = std::chrono::duration_cast<std::chrono::microseconds>(end_push - begin_push);
        push_times.push_back(time_span_push.count());

        // Измерение времени для poll
        auto begin_poll = std::chrono::steady_clock::now();
        for (unsigned cnt = 100 + i; cnt != 0; --cnt) {
            int element;
            if (!queue_poll(read, write, data, capacity, element)) {
                std::cerr << "Ошибка poll!" << std::endl;
                break;
            }
        }
        auto end_poll = std::chrono::steady_clock::now();
        auto time_span_poll = std::chrono::duration_cast<std::chrono::microseconds>(end_poll - begin_poll);
        poll_times.push_back(time_span_poll.count());

        queue_del(data);
    }

    writeFile(push_times, "push_times");
    writeFile(poll_times, "poll_times");

    return 0;
}