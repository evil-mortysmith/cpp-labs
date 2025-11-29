#include <iostream>

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;
    size_type y_size, x_size;

public:
    //1.
    Grid(T const &t) : y_size(1), x_size(1) {
        data = new T[1];
        data[0] = t;
    }

    // 2.
    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = T();
        }
    }

    // 3.
    Grid(size_type y_size, size_type x_size, T const &t) : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
    }

    // правило пяти
    // 1. деструктор
    ~Grid() {
        delete[] data;
    }

    // 2. конструктор копирования
    Grid(Grid<T> const &other) : y_size(other.y_size), x_size(other.x_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = other.data[i];
        }
    }

    // 3. оператор присваивания копированием
    Grid<T>& operator=(Grid<T> const &other) {
        if (this != &other) {
            delete[] data;
            
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size * x_size];
            for (size_type i = 0; i < y_size * x_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // 4. конструктор перемещения
    Grid(Grid<T>&& other) : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    // 5. оператор присваивания перемещением
    Grid<T>& operator=(Grid<T>&& other) {
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const &t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};

