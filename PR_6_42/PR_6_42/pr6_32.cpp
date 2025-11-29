#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <windows.h>

using namespace std;

double* create_dynamic_array(int n) {
    if (n <= 0) return nullptr;
    double* arr = new double[n];
    srand(time(0));

    for (int i = 0; i < n; ++i) {
        arr[i] = -10.0 + (rand() / (double)RAND_MAX) * 20.0;
    }
    return arr;
}

void print_array_recursive_helper(const double* arr, int n, int index) {
    if (index >= n) {
        cout << "]";
        return;
    }

    cout << fixed << setprecision(2) << setw(8) << arr[index];
    if (index < n - 1) {
        cout << ", ";
    }

    print_array_recursive_helper(arr, n, index + 1);
}

void print_array(const double* arr, int n) {
    if (n <= 0 || arr == nullptr) {
        cout << "(Масив порожній)" << endl;
        return;
    }
    cout << "[";
    print_array_recursive_helper(arr, n, 0);
    cout << endl;
}

double calculate_sum_of_negative_elements_recursive(const double* arr, int n, int index) {
    if (index >= n) {
        return 0.0;
    }

    double current_sum = 0.0;
    if (arr[index] < 0) {
        current_sum = arr[index];
    }

    return current_sum + calculate_sum_of_negative_elements_recursive(arr, n, index + 1);
}

int find_min_max_element_index_recursive_helper(const double* arr, int n, int index, int current_best_index, bool is_max_search) {

    if (index >= n) {
        return current_best_index;
    }

    int next_best_index = current_best_index;
    if (is_max_search) {
        if (arr[index] > arr[current_best_index]) {
            next_best_index = index;
        }
    }
    else {
        if (arr[index] < arr[current_best_index]) {
            next_best_index = index;
        }
    }

    return find_min_max_element_index_recursive_helper(arr, n, index + 1, next_best_index, is_max_search);
}

int find_max_element_index(const double* arr, int n) {
    if (n <= 0) return -1;
    return find_min_max_element_index_recursive_helper(arr, n, 1, 0, true);
}

int find_min_element_index(const double* arr, int n) {
    if (n <= 0) return -1;
    return find_min_max_element_index_recursive_helper(arr, n, 1, 0, false);
}

double calculate_product_recursive_helper(const double* arr, int start_idx, int end_idx) {
    if (start_idx >= end_idx) {
        return 1.0;
    }

    return arr[start_idx] * calculate_product_recursive_helper(arr, start_idx + 1, end_idx);
}

double calculate_product_between_min_max(const double* arr, int n) {
    if (n < 3) return 1.0;

    int max_idx = find_max_element_index(arr, n);
    int min_idx = find_min_element_index(arr, n);

    int start = min(max_idx, min_idx) + 1;
    int end = max(max_idx, min_idx);

    return calculate_product_recursive_helper(arr, start, end);
}

void collect_even_elements_recursive(const double* arr, int n, int index,
    vector<double>& even_elements, vector<int>& even_indices) {
    if (index >= n) return;

    if (fmod(abs(arr[index]), 2.0) == 0.0 && arr[index] == round(arr[index])) {
        even_elements.push_back(arr[index]);
        even_indices.push_back(index);
    }

    collect_even_elements_recursive(arr, n, index + 1, even_elements, even_indices);
}

void place_sorted_elements_recursive(double* arr, const vector<double>& even_elements,
    const vector<int>& even_indices, size_t index) {
    if (index >= even_elements.size()) return;

    arr[even_indices[index]] = even_elements[index];

    place_sorted_elements_recursive(arr, even_elements, even_indices, index + 1);
}

void sort_even_elements(double* arr, int n) {
    if (n <= 1) return;

    vector<double> even_elements;
    vector<int> even_indices;

    collect_even_elements_recursive(arr, n, 0, even_elements, even_indices);

    sort(even_elements.begin(), even_elements.end());

    place_sorted_elements_recursive(arr, even_elements, even_indices, 0);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int n;
    cout << "Введіть розмір динамічного масиву n: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Помилка: Введено некоректний розмір масиву." << endl;
        return 1;
    }

    double* array = create_dynamic_array(n);

    cout << "\n--- Початковий масив ---" << endl;
    print_array(array, n);

    double sum_neg = calculate_sum_of_negative_elements_recursive(array, n, 0);
    double product_min_max = calculate_product_between_min_max(array, n);

    sort_even_elements(array, n);

    cout << "\n--- Результати обчислень ---" << endl;
    cout << "1.1. Сума від'ємних елементів: " << fixed << setprecision(2) << sum_neg << endl;
    cout << "1.2. Добуток елементів між max і min: " << fixed << setprecision(2) << product_min_max << endl;

    cout << "\n--- Модифікований масив (парні елементи відсортовані) ---" << endl;
    print_array(array, n);

    delete[] array;

    return 0;
}