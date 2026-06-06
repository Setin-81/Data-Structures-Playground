/*
 * ============================================================
 *   Data Structures Playground — Beginner C++ Project
 * ============================================================
 *  Covers:
 *    1. Dynamic Array  (resizable array)
 *    2. Linked List    (singly linked)
 *    3. Stack          (LIFO)
 *    4. Queue          (FIFO)
 *    5. Binary Search  (algorithm bonus)
 *
 *  Build:  g++ -std=c++17 -o ds data_structures.cpp
 *  Run:    ./ds
 * ============================================================
 */

#include <iostream>
#include <string>

// ─────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────
void pause() {
    std::cout << "\n  Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void printHeader(const std::string& title) {
    std::cout << "\n══════════════════════════════════\n";
    std::cout << "  " << title << "\n";
    std::cout << "══════════════════════════════════\n";
}

// ─────────────────────────────────────────────
// 1. DYNAMIC ARRAY
//    Wraps a raw array; doubles capacity when full.
// ─────────────────────────────────────────────
class DynamicArray {
    int* data;
    int  size;      // number of elements currently stored
    int  capacity;  // total slots allocated

public:
    DynamicArray() : size(0), capacity(4) {
        data = new int[capacity];
    }
    ~DynamicArray() { delete[] data; }

    void push(int value) {
        if (size == capacity) {          // no room left → grow
            capacity *= 2;
            int* bigger = new int[capacity];
            for (int i = 0; i < size; i++) bigger[i] = data[i];
            delete[] data;
            data = bigger;
            std::cout << "  [Array grew to capacity " << capacity << "]\n";
        }
        data[size++] = value;
    }

    void pop() {
        if (size == 0) { std::cout << "  Array is empty!\n"; return; }
        std::cout << "  Removed: " << data[--size] << "\n";
    }

    void print() const {
        std::cout << "  Array [size=" << size << "]: ";
        for (int i = 0; i < size; i++) std::cout << data[i] << " ";
        std::cout << "\n";
    }
};

void demoDynamicArray() {
    printHeader("1. Dynamic Array");
    DynamicArray arr;

    std::cout << "\n  Pushing values 10, 20, 30, 40, 50 ...\n";
    for (int v : {10, 20, 30, 40, 50}) arr.push(v);
    arr.print();

    std::cout << "\n  Popping twice ...\n";
    arr.pop();
    arr.pop();
    arr.print();
    pause();
}

// ─────────────────────────────────────────────
// 2. SINGLY LINKED LIST
//    Each node holds a value and a pointer to the next node.
// ─────────────────────────────────────────────
struct Node {
    int   value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

class LinkedList {
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        Node* cur = head;
        while (cur) { Node* tmp = cur->next; delete cur; cur = tmp; }
    }

    void pushFront(int value) {
        Node* n = new Node(value);
        n->next = head;
        head = n;
    }

    void pushBack(int value) {
        Node* n = new Node(value);
        if (!head) { head = n; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }

    void popFront() {
        if (!head) { std::cout << "  List is empty!\n"; return; }
        Node* tmp = head;
        std::cout << "  Removed front: " << head->value << "\n";
        head = head->next;
        delete tmp;
    }

    void print() const {
        std::cout << "  List: ";
        Node* cur = head;
        while (cur) { std::cout << cur->value << " -> "; cur = cur->next; }
        std::cout << "NULL\n";
    }
};

void demoLinkedList() {
    printHeader("2. Singly Linked List");
    LinkedList list;

    std::cout << "\n  pushBack 1, 2, 3 then pushFront 0\n";
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(0);
    list.print();

    std::cout << "\n  popFront twice\n";
    list.popFront();
    list.popFront();
    list.print();
    pause();
}

// ─────────────────────────────────────────────
// 3. STACK  (LIFO — Last In, First Out)
//    Built on a linked list internally.
// ─────────────────────────────────────────────
class Stack {
    Node* top;

public:
    Stack() : top(nullptr) {}
    ~Stack() {
        while (top) { Node* tmp = top->next; delete top; top = tmp; }
    }

    void push(int value) {
        Node* n = new Node(value);
        n->next = top;
        top = n;
        std::cout << "  Pushed: " << value << "\n";
    }

    void pop() {
        if (!top) { std::cout << "  Stack is empty!\n"; return; }
        std::cout << "  Popped: " << top->value << "\n";
        Node* tmp = top;
        top = top->next;
        delete tmp;
    }

    void peek() const {
        if (!top) { std::cout << "  Stack is empty!\n"; return; }
        std::cout << "  Top: " << top->value << "\n";
    }
};

void demoStack() {
    printHeader("3. Stack (LIFO)");
    Stack s;

    std::cout << "\n  Pushing 5, 10, 15 ...\n";
    s.push(5); s.push(10); s.push(15);
    s.peek();

    std::cout << "\n  Popping all ...\n";
    s.pop(); s.pop(); s.pop(); s.pop();   // last pop hits empty
    pause();
}

// ─────────────────────────────────────────────
// 4. QUEUE  (FIFO — First In, First Out)
//    Enqueue at back, dequeue from front.
// ─────────────────────────────────────────────
class Queue {
    Node* front;
    Node* back;

public:
    Queue() : front(nullptr), back(nullptr) {}
    ~Queue() {
        while (front) { Node* tmp = front->next; delete front; front = tmp; }
    }

    void enqueue(int value) {
        Node* n = new Node(value);
        if (!back) { front = back = n; }
        else       { back->next = n; back = n; }
        std::cout << "  Enqueued: " << value << "\n";
    }

    void dequeue() {
        if (!front) { std::cout << "  Queue is empty!\n"; return; }
        std::cout << "  Dequeued: " << front->value << "\n";
        Node* tmp = front;
        front = front->next;
        if (!front) back = nullptr;
        delete tmp;
    }

    void peek() const {
        if (!front) { std::cout << "  Queue is empty!\n"; return; }
        std::cout << "  Front: " << front->value << "\n";
    }
};

void demoQueue() {
    printHeader("4. Queue (FIFO)");
    Queue q;

    std::cout << "\n  Enqueueing 100, 200, 300 ...\n";
    q.enqueue(100); q.enqueue(200); q.enqueue(300);
    q.peek();

    std::cout << "\n  Dequeueing all ...\n";
    q.dequeue(); q.dequeue(); q.dequeue(); q.dequeue();  // last hits empty
    pause();
}

// ─────────────────────────────────────────────
// 5. BINARY SEARCH  (Algorithm Bonus)
//    Works on a sorted array. O(log n).
// ─────────────────────────────────────────────
int binarySearch(const int arr[], int size, int target) {
    int lo = 0, hi = size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] <  target) lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;  // not found
}

void demoBinarySearch() {
    printHeader("5. Binary Search");
    const int sorted[] = {2, 5, 8, 13, 21, 34, 55, 89};
    const int n = sizeof(sorted) / sizeof(sorted[0]);

    std::cout << "\n  Sorted array: ";
    for (int i = 0; i < n; i++) std::cout << sorted[i] << " ";
    std::cout << "\n";

    for (int target : {13, 55, 42}) {
        int idx = binarySearch(sorted, n, target);
        if (idx != -1)
            std::cout << "  Search " << target << " → found at index " << idx << "\n";
        else
            std::cout << "  Search " << target << " → not found\n";
    }
    pause();
}

// ─────────────────────────────────────────────
// MAIN MENU
// ─────────────────────────────────────────────
int main() {
    std::cout << "\n╔══════════════════════════════════╗";
    std::cout << "\n║  Data Structures Playground C++ ║";
    std::cout << "\n╚══════════════════════════════════╝\n";

    bool running = true;
    while (running) {
        std::cout << "\n  Pick a demo:\n";
        std::cout << "    1. Dynamic Array\n";
        std::cout << "    2. Singly Linked List\n";
        std::cout << "    3. Stack\n";
        std::cout << "    4. Queue\n";
        std::cout << "    5. Binary Search\n";
        std::cout << "    0. Quit\n";
        std::cout << "  → ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: demoDynamicArray();  break;
            case 2: demoLinkedList();    break;
            case 3: demoStack();         break;
            case 4: demoQueue();         break;
            case 5: demoBinarySearch();  break;
            case 0: running = false;     break;
            default: std::cout << "  Invalid choice, try again.\n";
        }
    }

    std::cout << "\n  Goodbye!\n\n";
    return 0;
}