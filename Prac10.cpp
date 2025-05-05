#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
    vector<int> data;
    bool isMax;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if ((isMax && data[index] > data[parent]) || (!isMax && data[index] < data[parent])) {
            swap(data[index], data[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int size = data.size();
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int selected = index;

        if (left < size && ((isMax && data[left] > data[selected]) || (!isMax && data[left] < data[selected]))) {
            selected = left;
        }
        if (right < size && ((isMax && data[right] > data[selected]) || (!isMax && data[right] < data[selected]))) {
            selected = right;
        }

        if (selected != index) {
            swap(data[index], data[selected]);
            heapifyDown(selected);
        }
    }

public:
    Heap(bool maxHeap = true) : isMax(maxHeap) {}

    void insert(int val) {
        data.push_back(val);
        heapifyUp(data.size() - 1);
    }

    int getTop() const {
        if (data.empty()) {
            cerr << "Heap is empty.\n";
            return -1;
        }
        return data[0];
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Heap maxHeap(true);   // Max heap for maximum marks
    Heap minHeap(false);  // Min heap for minimum marks

    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; ++i) {
        int mark;
        cin >> mark;
        maxHeap.insert(mark);
        minHeap.insert(mark);
    }

    cout << "Maximum marks: " << maxHeap.getTop() << "\n";
    cout << "Minimum marks: " << minHeap.getTop() << "\n";

    return 0;
}
