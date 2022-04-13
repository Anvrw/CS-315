#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace std;

//implement a binary search tree
    vector<int> readIn(const string &filename) {
        vector<int> BST;
        ifstream myFile(filename);
        string line;
        if (!myFile.is_open()) throw runtime_error("Could not open file");
        vector<int> result;
        while (getline(myFile, line)) {
            string data;
            result.push_back(stoi(line));
        }
        return result;
    }

//Insert
    void insertNode(int tree[], int x) {
        int index = 0;
        while (tree[index] != -1) {
            if (x > tree[index]) {
                index = index * 2 + 2; //right
            } else {
                index = index * 2 + 1; //left
            }
        }
        tree[index] = x;
    }

    void buildTree(int tree[], vector<int> data, int size) {
        for (int i = 0; i < size; i++) {
            insertNode(tree, data[i]);
        }
    }

//Search
    void treeSearch(const int tree[], int k) {
        int index = 0;
        while (true) {
            if (tree[index] == -1) { //can't find it
                cout << k << " is not found" << endl;
                return;
            }
            if (tree[index] == k) { //find it
                cout << k << " is found" << endl;
                return;
            }
            if (k > tree[index]) {
                index = index * 2 + 2;
            } else {
                index = index * 2 + 1;
            }
        }
    }

//Minimum
    int treeMinimum(int tree[]) {
        int index = 0;
        int left = index * 2 + 1;
        while (true) {
            if (tree[left] != -1) {
                index = left;
                left = index * 2 + 1;
            } else {
                return tree[index];
            }
        }
    }

//Maximum
    int treeMaximum(int tree[]) {
        int index = 0;
        int right = index * 2 + 2;
        while (true) {
            if (tree[right] != -1) {
                index = right;
                right = index * 2 + 2;
            } else {
                return tree[index];
            }
        }
    }


//Traversal

//Inorder
    void inorderTraversal(int tree[], int index, int size) {
        if (index > size) {
            return;
        }
        if (tree[index] != -1) {
            inorderTraversal(tree, index * 2 + 1, size);
            cout << tree[index] << " ";
            inorderTraversal(tree, index * 2 + 2, size);
        }
    }

//Preorder
    void preorderTraversal(int tree[], int index, int size) {
        if (index > size) {
            return;
        }
        if (tree[index] != -1) {
            cout << tree[index] << " ";
            preorderTraversal(tree, index * 2 + 1, size);
            preorderTraversal(tree, index * 2 + 2, size);
        }
    }


    void postorderTraversal(int tree[], int index, int size) {
        if (index > size) {
            return;
        }
        if (tree[index] != -1) {
            postorderTraversal(tree, index * 2 + 1, size);
            postorderTraversal(tree, index * 2 + 2, size);
            cout << tree[index] << " ";
        }
    }

//Max Heaps
//Max-Heapify
    void maxHeapify(int heap[], int index, int size) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;
        if ((left < size) && (heap[left] > heap[index])) {
            largest = left;
        }
       if ((right < size) && (heap[right] > heap[largest])) {
            largest = right;
        }
       if (largest != index) {
            swap(heap[largest], heap[index]);
            maxHeapify(heap, largest, size);
        }
    }

//Create Max Heap
    void createMaxHeap(int heap[], int size) {

        for (int i = ((size - 2) / 2); i > -1; i--) {
            maxHeapify(heap, i, size);
        }
    }

    void printHeap(int heap[], int size) {
        for (int i = 0; i < size; ++i)
            cout << heap[i] << " ";
    }

    void Heapsort(int heap[], int heapSize){
        createMaxHeap(heap, heapSize);
        int temp;

        for (int i = heapSize - 1; i >= 1; i--){
            temp = heap[i];
            heap[i] = heap[0];
            heap[0] = temp;
            heapSize--;
            maxHeapify(heap, 0, heapSize);
        }
    }

    void printVector(vector<int> toPrint) {
        for (vector<int>::const_iterator i = toPrint.begin(); i != toPrint.end(); i++)
            cout << *i << ' ';
    }

    int main() {

        //string inputString = argv[1];
        vector<int> data = readIn("test3.csv");
        int searchValue;

        int const bTreeSize = 100000;

        int tree[bTreeSize];
        for (int i = 0; i < bTreeSize; i++) {
            tree[i] = -1;
        }
        buildTree(tree, data, data.size());
        cout << "Enter a Search Value: " ;
        cin >> searchValue;
        int key = searchValue;
        treeSearch(tree, key);
        cout << endl;

        cout << "Minimum: " << treeMinimum(tree) << endl << endl;
        cout << "Maximum: " << treeMaximum(tree) << endl << endl;

        //Inorder, Preorder, and Postorder traversal
        cout << "Inorder: ";
        inorderTraversal(tree, 0, bTreeSize);
        cout << endl;
        cout << endl;

        cout << "Preorder: ";
        preorderTraversal(tree, 0, bTreeSize);
        cout << endl;
        cout << endl;

        cout << "Post-order: ";
        postorderTraversal(tree, 0, bTreeSize);
        cout << endl;
        cout << endl;

        int *heap = data.data();

        cout << "Heaps: ";
        createMaxHeap(heap, data.size());
        printHeap(heap, data.size());
        cout << endl;

        cout << endl;
        cout << "Heap Sort: " << endl;
        Heapsort(heap, data.size());
        printHeap(heap, data.size());
        cout << endl;

    }