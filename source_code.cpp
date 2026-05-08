#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * TASK 1: System Architecture - "Goods" Abstract Data Type (ADT)
 * Implements encapsulation and information hiding.[2, 3]
 */
class Goods {
private:
    string name;
    string type;
    double weight; // Used for capacity optimization and sorting

public:
    // Initialization: Constructor handles state assignment [4]
    Goods(string n = "", string t = "", double w = 0.0) : name(n), type(t), weight(w) {}

    // Metadata Retrieval (Observers)
    string getName() const { return name; }
    string getType() const { return type; }
    double getWeight() const { return weight; }

    // Weight Update (Procedural Interface)
    void updateWeight(double newWeight) {
        if (newWeight >= 0) {
            this->weight = newWeight;
        } else {
            cerr << "Error: Weight cannot be negative." << endl;
        }
    }

    void display() const {
        cout << left << setw(20) << name << setw(15) << type << weight << " kg" << endl;
    }
};

/**
 * TASK 1: Cargo Sorting Logic (Descending Order)
 * Comparison of Bubble Sort ($O(n^2)$) vs QuickSort ($O(n \log n)$).
 */

void bubbleSort(vector<Goods>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].getWeight() < arr[j + 1].getWeight()) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int partition(vector<Goods>& arr, int low, int high) {
    double pivot = arr[high].getWeight();
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].getWeight() > pivot) { // Descending order
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Goods>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/**
 * TASK 3: Implementation - AVL Tree for Inventory Retrieval
 * Self-balancing BST ensures $O(\log n)$ search/retrieval.
 */
struct Node {
    Goods data;
    Node *left, *right;
    int height;
    Node(Goods g) : data(g), left(nullptr), right(nullptr), height(1) {}
};

class InventorySystem {
private:
    Node* root;

    int getHeight(Node* n) { return n? n->height : 0; }

    int getBalance(Node* n) { return n? getHeight(n->left) - getHeight(n->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, Goods g) {
        // Robustness: Manage null or invalid entries [5, 1]
        if (node == nullptr) return new Node(g);

        if (g.getName() < node->data.getName())
            node->left = insert(node->left, g);
        else if (g.getName() > node->data.getName())
            node->right = insert(node->right, g);
        else return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Rebalancing Rotations
        if (balance > 1 && g.getName() < node->left->data.getName()) return rightRotate(node);
        if (balance < -1 && g.getName() > node->right->data.getName()) return leftRotate(node);
        if (balance > 1 && g.getName() > node->left->data.getName()) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && g.getName() < node->right->data.getName()) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

public:
    InventorySystem() : root(nullptr) {}

    void addInventory(Goods g) { root = insert(root, g); }

    void search(string name) {
        Node* curr = root;
        while (curr) {
            if (curr->data.getName() == name) {
                cout << "Item Found: ";
                curr->data.display();
                return;
            }
            curr = (name < curr->data.getName())? curr->left : curr->right;
        }
        cout << "Error: Product '" << name << "' not found in inventory." << endl;
    }
};

int main() {
    // Demonstration based on product_sales_dataset.csv 
    vector<Goods> truckManifest;
    truckManifest.push_back(Goods("Lipstick", "Beauty", 7));
    truckManifest.push_back(Goods("Jacket", "Fashion", 6));
    truckManifest.push_back(Goods("Gym Gloves", "Sports", 10));
    truckManifest.push_back(Goods("Wireless Mouse", "Electronics", 10));
    truckManifest.push_back(Goods("Table", "Home", 9));
    truckManifest.push_back(Goods("Smart Watch", "Electronics", 4));

    cout << "--- Swift-Load Logistics: Sorting Manifest (QuickSort Descending) ---" << endl;
    quickSort(truckManifest, 0, truckManifest.size() - 1);
    for (const auto& item : truckManifest) item.display();

    cout << "\n--- Optimized Inventory Retrieval (AVL Tree) ---" << endl;
    InventorySystem warehouse;
    for (const auto& item : truckManifest) warehouse.addInventory(item);

    warehouse.search("Smart Watch"); // High-speed $O(\log n)$ retrieval [6]
    warehouse.search("NonExistentItem"); // Robustness test: handles missing entries

    return 0;
}