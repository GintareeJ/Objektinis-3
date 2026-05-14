#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

public:

    Vector()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~Vector() {
        delete[] data_;
    } //destruktorius

    Vector(const Vector& other)
    : data_(nullptr),
      size_(other.size_),
      capacity_(other.capacity_) {

    data_ = capacity_ ? new T[capacity_] : nullptr;

    for (size_t i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
    } //copy kons.

    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    } //move kons.

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;

            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = capacity_ ? new T[capacity_] : nullptr;

            for (size_t i = 0; i < size_; i++) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    } //copy assigment k.

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    } //move assigment k.

    void push_back(const T& value) {

        if (size_ == capacity_) {

            size_t newCapacity;

            if (capacity_ == 0)
                newCapacity = 1;
            else
                newCapacity = capacity_ * 2;

            T* newData = new T[newCapacity];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
        }

        data_[size_] = value;
        size_++;
    } //push_back funckija

    void push_back(T&& value) {
        if (size_ == capacity_) {

            size_t newCapacity;

            if (capacity_ == 0)
                newCapacity = 1;
            else
                newCapacity = capacity_ * 2;

            T* newData = new T[newCapacity];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = std::move(data_[i]);
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
        }

        data_[size_] = std::move(value);
        size_++;
    } //move push_back funckija

    size_t size() const {
        return size_;
    } //size getteris

    T& operator[](size_t index) {
        return data_[index];
    } //index operatorius

    const T& operator[](size_t index) const {
        return data_[index];
    } //const index operatorius

    size_t capacity() const {
        return capacity_;
    } //capacity getteris

    bool empty() const {
        return size_ == 0;
    } //empty getteris

    T& front() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    } //front getteris

    T& back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    } //back getteris

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    } //const front getteris\

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    } //const back getteris

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        size_--;
    } //pop_back funckija

    void clear() {
        size_ = 0;
    } //clear funckija

    void resize(size_t newSize) {
        if (newSize > capacity_) {
            size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
            while (newCapacity < newSize) {
                newCapacity *= 2;
            }

            T* newData = new T[newCapacity];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
        }
        size_ = newSize;
    } //resize funckija

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            T* newData = new T[newCapacity];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
        }
    } //reserve funckija

    void assign(size_t newSize, const T& value) {
        if (newSize > capacity_) {
            size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
            while (newCapacity < newSize) {
                newCapacity *= 2;
            }

            T* newData = new T[newCapacity];

            for (size_t i = 0; i < size_; i++) {
                newData[i] = data_[i];
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
        }
        for (size_t i = 0; i < newSize; i++) {
            data_[i] = value;
        }
        size_ = newSize;
    } //assign funckija

    void assign(T* first, T* last) {
    size_t newSize = last - first;

    if (newSize > capacity_) {
        T* newData = new T[newSize];

        delete[] data_;

        data_ = newData;
        capacity_ = newSize;
    }

    for (size_t i = 0; i < newSize; i++) {
        data_[i] = first[i];
    }

    size_ = newSize;
}

    void insert(size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (size_ == capacity_) {
            size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
            T* newData = new T[newCapacity];

            for (size_t i = 0; i < index; i++) {
                newData[i] = data_[i];
            }

            newData[index] = value;

            for (size_t i = index; i < size_; i++) {
                newData[i + 1] = data_[i];
            }

            delete[] data_;

            data_ = newData;
            capacity_ = newCapacity;
        } else {
            for (size_t i = size_; i > index; i--) {
                data_[i] = data_[i - 1];
            }
            data_[index] = value;
        }
        size_++;
    } //insert funckija

    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; i++) {
            data_[i] = data_[i + 1];
        }
        size_--;
    } //erase funckija

T* erase(T* pos) {
    size_t index = pos - data_;
    erase(index);
    return data_ + index;
}

T* erase(T* first, T* last) {
    size_t indexFirst = first - data_;
    size_t indexLast = last - data_;

    if (indexFirst > size_ || indexLast > size_ || indexFirst > indexLast) {
        throw std::out_of_range("Invalid erase range");
    }

    size_t count = indexLast - indexFirst;

    for (size_t i = indexFirst; i + count < size_; i++) {
        data_[i] = std::move(data_[i + count]);
    }

    size_ -= count;

    return data_ + indexFirst;
}
    
void swap(Vector& other) {

    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
} //swap funckija

    T* begin() {
        return data_;
    } //begin getteris

    T* end() {
        return data_ + size_;
    } //end getteris

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    } //at getteris

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    } //const at getteris

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; i++) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    } //equality operatorius

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    } //inequality operatorius

    bool operator<(const Vector& other) const {
        size_t minSize = size_ < other.size_ ? size_ : other.size_;
        for (size_t i = 0; i < minSize; i++) {
            if (data_[i] < other.data_[i]) {
                return true;
            } else if (data_[i] > other.data_[i]) {
                return false;
            }
        }
        return size_ < other.size_;
    } //less than operatorius

    bool operator>(const Vector& other) const {
        return other < *this;
    } //greater than operatorius

    bool operator<=(const Vector& other) const {
        return !(*this > other);
    } //less than or equal operatorius

    bool operator>=(const Vector& other) const {
        return !(*this < other);
    } //greater than or equal operatorius

    const T* begin() const {
        return data_;
    } //const begin getteris

    const T* end() const {
        return data_ + size_;
    } //const end getteris
};
#endif
