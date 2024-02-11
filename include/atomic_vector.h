#pragma once

#include <mutex>
#include <vector>

template <typename T> class atomic_vector {
  public:
    atomic_vector() {}
    atomic_vector(std::vector<T> &&vector) { this->vec = std::move(vector); }
    void push_back(T value) {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.push_back(value);
    }
    void clear() noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.clear();
    }
    void erase(size_t index) {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.erase(index);
    }
    T at(size_t index) {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.at(index);
    }
    auto size() noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.size();
    }
    auto begin() noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.begin();
    }
    auto end() noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.end();
    }
    auto rbegin() const noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.rbegin();
    }
    auto rend() const noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.rend();
    }
    bool empty() const noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        return this->vec.empty();
    }
    void reserve(size_t capacity) {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.reserve(capacity);
    }
    void pop_back() noexcept {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.pop_back();
    }
    T back() const {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.back();
    }
    T front() const {
        const std::lock_guard<std::mutex> lock(this->mutex);
        this->vec.front();
    }

  private:
    std::mutex mutex;
    std::vector<T> vec;
};
