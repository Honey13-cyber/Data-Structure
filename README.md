# Data Structures & Algorithms - Logistics & Inventory System

This project implements core Data Structures and Algorithms concepts in C++ to solve problems related to logistics and inventory management, specifically for a system referred to as "Swift-Load Logistics".

## Project Structure

- `source_code.cpp`: The main C++ source file containing the implementation of the tasks.
- `product_sales_dataset.csv`: A dataset containing product sales data, used for demonstration and testing.
- `2025_DSA_AssignmentBrief.pdf`: The assignment brief detailing the requirements.

## Implemented Features

### Task 1: System Architecture & Cargo Sorting
- **Goods Abstract Data Type (ADT)**: Implements encapsulation and information hiding for product details (Name, Type, Weight).
- **Sorting Algorithms**: 
  - **Bubble Sort**: $O(n^2)$ time complexity implementation for sorting cargo by weight.
  - **QuickSort**: $O(n \log n)$ time complexity implementation for efficient sorting of cargo by weight in descending order.

### Task 3: Inventory Retrieval System
- **AVL Tree**: A self-balancing Binary Search Tree (BST) used to store and retrieve inventory items efficiently.
- **Search**: Ensures $O(\log n)$ time complexity for searching products by name, maintaining high performance even with large datasets.
- **Robustness**: Handles missing entries gracefully with error messages.

## How to Compile and Run

To compile the source code, you need a C++ compiler (like `g++`).

1. Open your terminal.
2. Navigate to the project directory:
   ```bash
   cd "/Users/kukue/Documents/Saigon Business School/Data Structure & Algorithms"
   ```
3. Compile the code:
   ```bash
   g++ -o solution source_code.cpp
   ```
4. Run the executable:
   ```bash
   ./solution
   ```

## Demonstration

The `main()` function demonstrates:
1. Creating a list of goods (truck manifest).
2. Sorting the manifest in descending order of weight using QuickSort.
3. Adding the items to an AVL tree-based inventory system.
4. Searching for an existing item ("Smart Watch") and a non-existent item to show error handling.
