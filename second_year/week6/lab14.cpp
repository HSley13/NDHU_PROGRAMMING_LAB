#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MinMaxHeap {
  public:
    MinMaxHeap() {
    }

    void insert(T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    T getMin() const {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    T getMax() const {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        if (heap.size() == 1) {
            return heap[0];
        }
        return (heap.size() > 2) ? std::max(heap[1], heap[2]) : heap[1];
    }

    void deleteMin() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        swap(0, heap.size() - 1);
        heap.pop_back();
        trickleDown(0);
    }

    void deleteMax() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        int maxIdx = (heap.size() > 2 && heap[2] > heap[1]) ? 2 : 1;
        swap(maxIdx, heap.size() - 1);
        heap.pop_back();
        trickleDown(maxIdx);
    }

  private:
    std::vector<T> heap;

    bool isMinLevel(int index) const {
        int level = 0;
        while (index > 0) {
            index = (index - 1) / 2;
            level++;
        }
        return (level % 2 == 0);
    }

    void bubbleUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;

        if (isMinLevel(index)) {
            if (heap[index] > heap[parent]) {
                swap(index, parent);
                bubbleUpMax(parent);
            } else {
                bubbleUpMin(index);
            }
        } else {
            if (heap[index] < heap[parent]) {
                swap(index, parent);
                bubbleUpMin(parent);
            } else {
                bubbleUpMax(index);
            }
        }
    }

    void bubbleUpMin(int index) {
        int grandparent = (index - 3) / 4;
        if (index > 2 && heap[index] < heap[grandparent]) {
            swap(index, grandparent);
            bubbleUpMin(grandparent);
        }
    }

    void bubbleUpMax(int index) {
        int grandparent = (index - 3) / 4;
        if (index > 2 && heap[index] > heap[grandparent]) {
            swap(index, grandparent);
            bubbleUpMax(grandparent);
        }
    }

    void trickleDown(int index) {
        if (isMinLevel(index)) {
            trickleDownMin(index);
        } else {
            trickleDownMax(index);
        }
    }

    void trickleDownMin(int index) {
        if (2 * index + 1 >= heap.size()) return;

        int minChildIndex = getMinChildOrGrandchild(index);
        if (minChildIndex != -1 && heap[minChildIndex] < heap[index]) {
            swap(minChildIndex, index);
            if (minChildIndex >= 4 * index + 3) {
                int parent = (minChildIndex - 1) / 2;
                if (heap[minChildIndex] > heap[parent]) {
                    swap(minChildIndex, parent);
                }
                trickleDownMin(minChildIndex);
            }
        }
    }

    void trickleDownMax(int index) {
        if (2 * index + 1 >= heap.size()) return;

        int maxChildIndex = getMaxChildOrGrandchild(index);
        if (maxChildIndex != -1 && heap[maxChildIndex] > heap[index]) {
            swap(maxChildIndex, index);
            if (maxChildIndex >= 4 * index + 3) {
                int parent = (maxChildIndex - 1) / 2;
                if (heap[maxChildIndex] < heap[parent]) {
                    swap(maxChildIndex, parent);
                }
                trickleDownMax(maxChildIndex);
            }
        }
    }

    int getMinChildOrGrandchild(int index) {
        int minIndex = -1;
        int minValue = std::numeric_limits<T>::max();

        for (int i = 2 * index + 1; i <= 2 * index + 2 && i < heap.size(); i++) {
            if (heap[i] < minValue) {
                minIndex = i;
                minValue = heap[i];
            }
        }
        for (int i = 4 * index + 3; i <= 4 * index + 6 && i < heap.size(); i++) {
            if (heap[i] < minValue) {
                minIndex = i;
                minValue = heap[i];
            }
        }
        return minIndex;
    }

    int getMaxChildOrGrandchild(int index) {
        int maxIndex = -1;
        int maxValue = std::numeric_limits<T>::min();

        for (int i = 2 * index + 1; i <= 2 * index + 2 && i < heap.size(); i++) {
            if (heap[i] > maxValue) {
                maxIndex = i;
                maxValue = heap[i];
            }
        }
        for (int i = 4 * index + 3; i <= 4 * index + 6 && i < heap.size(); i++) {
            if (heap[i] > maxValue) {
                maxIndex = i;
                maxValue = heap[i];
            }
        }
        return maxIndex;
    }

    void swap(int i, int j) {
        std::swap(heap[i], heap[j]);
    }
};

int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for (j = 0; j < 10; j++) {
        mmHeap.insert(rand() % 100);
    }

    while (true) {
        try {
            std::cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        } catch (std::exception &) {
            break;
        }
    }
    std::cout << std::endl;

    for (j = 0; j < 10; j++) {
        mmHeap.insert(rand() % 100);
    }

    while (true) {
        try {
            std::cout << mmHeap.getMax() << " ";
            mmHeap.deleteMax();
        } catch (std::exception &) {
            break;
        }
    }

    return 0;
}
