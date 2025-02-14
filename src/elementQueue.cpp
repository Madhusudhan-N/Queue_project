#include "elementQueue.h"

template <typename T>
Queue<T>::Queue(int size) : max_size(size), count(0), front(0), back(0) {
    m_data = new T[size];
}

template <typename T>
Queue<T>::~Queue() {
    delete[] m_data;
}

template <typename T>
void Queue<T>::elementPush(T element) {
    std::unique_lock<std::mutex> lock(m_mtx);
    if (count == max_size) {
        front = (front + 1) % max_size;
        count--;
    }
    m_data[back] = element;
    back = (back + 1) % max_size;
    count++;
    std::cout << "Pushed element: " << element << std::endl;
    m_cv.notify_one();
}

template <typename T>
T Queue<T>::elementPop() {
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]() { return count > 0; });
    T element = m_data[front];
    front = (front + 1) % max_size;
    count--;
    std::cout << "Popped element: " << element << std::endl;
    return element;
}

template <typename T>
T Queue<T>::elementPopWithTimeout(int milliseconds) {
    std::unique_lock<std::mutex> lock(m_mtx);
    if (!m_cv.wait_for(lock, std::chrono::milliseconds(milliseconds), [this]() { return count > 0; })) {
        throw std::runtime_error("Timeout waiting for element");
    }
    T element = m_data[front];
    front = (front + 1) % max_size;
    count--;
    std::cout << "Popped element: " << element << std::endl;
    return element;
}

template <typename T>
int Queue<T>::elementCount() {
    std::lock_guard<std::mutex> lock(m_mtx);
    return count;
}

template <typename T>
int Queue<T>::maxSize() {
    return max_size;
}

template <typename T>
void Queue<T>::printQueue() {
    std::lock_guard<std::mutex> lock(m_mtx);
    std::cout << "elements in Queue: ";
    for (int i = 0, idx = front; i < count; i++, idx = (idx + 1) % max_size) {
        std::cout << m_data[idx] << " ";
    }
    std::cout << std::endl;
}

// Explicit template instantiation
template class Queue<int>;
