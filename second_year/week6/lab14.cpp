#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MinMaxHeap {
  public:
    MinMaxHeap() = default;

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
        if (heap.size() == 1) {
            return heap[0];
        }
        if (heap.size() == 2 || heap[1] > heap[2]) {
            return heap[1];
        }
        return heap[2];
    }

    void deleteMin() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            bubbleDown(0);
        }
    }

    void deleteMax() {
        if (heap.size() <= 1) {
            deleteMin();
            return;
        }
        int maxIdx = (heap.size() == 2 || heap[1] > heap[2]) ? 1 : 2;
        heap[maxIdx] = heap.back();
        heap.pop_back();
        if (maxIdx < heap.size()) {
            bubbleDown(maxIdx);
        }
    }

    int count() const {
        return heap.size();
    }

  private:
    std::vector<T> heap;

    bool isMinLevel(int index) const {
        int level{0};
        while (index > 0) {
            index = (index - 1) / 2;
            level++;
        }
        return level % 2 == 0;
    }

    void bubbleUp(int index) {
        if (index == 0) {
            return;
        }

        int parentIdx = (index - 1) / 2;
        if ((isMinLevel(index) && heap[index] > heap[parentIdx]) ||
            (!isMinLevel(index) && heap[index] < heap[parentIdx])) {
            std::swap(heap[index], heap[parentIdx]);
            bubbleUp(parentIdx);
        } else {
            int grandparentIdx = (index - 3) / 4;
            if (grandparentIdx >= 0) {
                if ((isMinLevel(index) && heap[index] < heap[grandparentIdx]) ||
                    (!isMinLevel(index) && heap[index] > heap[grandparentIdx])) {
                    std::swap(heap[index], heap[grandparentIdx]);
                    bubbleUp(grandparentIdx);
                }
            }
        }
    }

    void bubbleDown(int index) {
        if (isMinLevel(index)) {
            bubbleDownMin(index);
        } else {
            bubbleDownMax(index);
        }
    }

    void bubbleDownMin(int index) {
        int smallestChildOrGrandchild = findChildOrGrandchild(index, std::less<>());
        if (smallestChildOrGrandchild == -1) {
            return;
        }

        if (smallestChildOrGrandchild >= index * 2 + 3) {
            if (heap[smallestChildOrGrandchild] < heap[index]) {
                std::swap(heap[smallestChildOrGrandchild], heap[index]);
                int parentOfSmallest = (smallestChildOrGrandchild - 1) / 2;
                if (parentOfSmallest >= 0 && heap[smallestChildOrGrandchild] > heap[parentOfSmallest]) {
                    std::swap(heap[smallestChildOrGrandchild], heap[parentOfSmallest]);
                }
                bubbleDownMin(smallestChildOrGrandchild);
            }
        } else if (heap[smallestChildOrGrandchild] < heap[index]) {
            std::swap(heap[smallestChildOrGrandchild], heap[index]);
        }
    }

    void bubbleDownMax(int index) {
        int largestChildOrGrandchild = findChildOrGrandchild(index, std::greater<>());
        if (largestChildOrGrandchild == -1) {
            return;
        }

        if (largestChildOrGrandchild >= index * 2 + 3) {
            if (heap[largestChildOrGrandchild] > heap[index]) {
                std::swap(heap[largestChildOrGrandchild], heap[index]);
                int parentOfLargest = (largestChildOrGrandchild - 1) / 2;
                if (parentOfLargest >= 0 && heap[largestChildOrGrandchild] < heap[parentOfLargest]) {
                    std::swap(heap[largestChildOrGrandchild], heap[parentOfLargest]);
                }
                bubbleDownMax(largestChildOrGrandchild);
            }
        } else if (heap[largestChildOrGrandchild] > heap[index]) {
            std::swap(heap[largestChildOrGrandchild], heap[index]);
        }
    }

    template <typename Compare>
    int findChildOrGrandchild(int index, Compare cmp) const {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int bestIdx = (left < heap.size()) ? left : -1;

        if (right < heap.size() && cmp(heap[right], heap[bestIdx])) {
            bestIdx = right;
        }

        for (int i{0}; i < 4; i++) {
            int grandchild = 4 * index + 3 + i;
            if (grandchild < heap.size() && cmp(heap[grandchild], heap[bestIdx])) {
                bestIdx = grandchild;
            }
        }

        return (bestIdx >= 0 && bestIdx < heap.size()) ? bestIdx : -1;
    }
};

int main(void) {
    MinMaxHeap<int> mmHeap;
    srand(static_cast<unsigned int>(time(NULL)));

    for (int j{0}; j < 10; j++) {
        mmHeap.insert(rand() % 100);
    }

    while (true) {
        try {
            std::cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        } catch (const std::exception &e) {
            break;
        }
    }
    std::cout << std::endl;

    for (int j{0}; j < 10; j++) {
        mmHeap.insert(rand() % 100);
    }

    while (true) {
        try {
            std::cout << mmHeap.getMax() << " ";
            mmHeap.deleteMax();
        } catch (const std::exception &e) {
            break;
        }
    }
}
