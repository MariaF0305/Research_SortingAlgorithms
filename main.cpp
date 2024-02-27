#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cstring>
#include <string.h>
#include <chrono>
#include <functional>
#include <algorithm>

using namespace std;

//1.INSERTION SORT
std::vector<int>insertionSort(int n, std::vector<int> &array) {
    if (n <= 1) {
        return array ;
    }
    int j, temp;
    int key;
    for (int i = 1; i < n; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && key < array[j]) {
            temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
            j--;
        }
    }
    return array;
}

//2.SELECTION SORT
std::vector<int> selectionSort(int n, std::vector<int> &array) {
    for (int ind = 0; ind < n; ind++) {
        int main_index = ind;
        for (int j = ind + 1; j < n; j++) {
            if (array[j] < array[main_index]) {
                main_index = j;
            }
        }
        std::swap(array[ind], array[main_index]);
    }
    return array;
}

//3.BUBBLE SORT
std::vector<int>bubbleSort(int n, std::vector<int> &arr) {
    bool swapped = false;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swapped = true;
                std::swap(arr[j], arr[j + 1]);
            }
        }
        if (!swapped) {
            return arr;
        }
    }
    return arr;
}

//4.MERGE SORT
void merge(std::vector<int>& array, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = array[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

std::vector<int> mergeSort(std::vector<int> &array, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        array = mergeSort(array, l, m);
        array = mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
    return array;
}

//5.QUICK SORT
int partition(std::vector<int>& array, int low, int high)
{
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& array, int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

//6.HEAP SORT
void heapify(std::vector<int>& array, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && array[i] < array[l])
        largest = l;

    if (r < n && array[largest] < array[r])
        largest = r;

    if (largest != i)
    {
        std::swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

std::vector<int>heapSort(std::vector<int>& array, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
    return array;
}

//7.COUNTING SORT
std::vector<int> countSort(std::vector<int>& array,int value)
{
    std::vector<int> output(array.size());
    int max_val = value; //
    std::vector<int> count(max_val + 1, 0);

    for (int i = 0; i < array.size(); i++)
        count[array[i]]++;

    for (int i = 1; i <= max_val; i++)
        count[i] += count[i - 1];

    for (int i = array.size() - 1; i >= 0; i--)
    {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }


    for (int i = 0; i < array.size(); i++) {
        array[i] = output[i];
    }
    return array;
}

//8.RADIX SORT
std::vector<int> radixSort(std::vector<int>& arr)
{
    int max_val = *std::max_element(arr.begin(), arr.end());

    for (int exp = 1; max_val / exp > 0; exp *= 10)
        countSort(arr, max_val);
    return arr;
}

//9.BUCKET SORT
std::vector<int> bucketSort(int max_val, std::vector<int>& arr) {
    std::vector<std::vector<int>> buckets(max_val);
    for (int i = 0; i < arr.size(); i++) {
        int bucket_index = arr[i] * max_val / (1 + *std::max_element(arr.begin(), arr.end()));
        buckets[bucket_index].push_back(arr[i]);
    }
    for (int i = 0; i < buckets.size(); i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }
    std::vector<int> sorted_arr;
    for (int i = 0; i < buckets.size(); i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            sorted_arr.push_back(buckets[i][j]);
        }
    }
    std::copy(sorted_arr.begin(), sorted_arr.end(), arr.begin());
    return sorted_arr;
}

//10.PANCAKE SORT
void flip(std::vector<int>& arr, int idx) {
    int i = 0, j = idx;
    while (i < j) {
        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

int findMaxIndex(std::vector<int>& arr, int end_idx) {
    int max_idx = 0;
    for (int i = 1; i <= end_idx; i++) {
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}

std::vector<int> pancakeSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 0; i--) {
        int max_idx = findMaxIndex(arr, i);
        if (max_idx != i) {
            flip(arr, max_idx);
            flip(arr, i);
        }
    }
    return arr;
}


//TIME
template<typename Func, typename... Args>
std::chrono::duration<float> measureExecutionTime(Func&& func, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::forward<Func>(func)(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float, std::milli> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << "milliseconds \n" ;

    return elapsed;
}

//RANDOM ARRAY GENERATOR
std::vector<int> generateRandomList(int n, int max_value) {
    std::vector<int> result;
    srand(time(nullptr));

    while (result.size() < n) {
        result.push_back(rand() % (max_value + 1));
    }
    return result;
}


//ALMOST SORTED ARRAY GENERATOR
std::vector<int> generate_almost_sorted_list(std::vector<int> sorted_list) {
    // create a random number generator
    std::random_device rd;

    // select 3 distinct random indices in the list
    std::vector<int> indices(sorted_list.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937{rd()});
    indices.resize(3);
    std::sort(indices.begin(), indices.end());

    // swap the elements at the selected indices
    std::swap(sorted_list[indices[0]], sorted_list[indices[2]]);
    std::swap(sorted_list[indices[2]], sorted_list[indices[1]]);

    return sorted_list;
}


//SORTED ARRAY GENERATOR
std::vector<int> generate_sorted_list(int length, int max_number) {
    std::vector<int> result;
    std::srand(std::time(nullptr));

    while (result.size() < length) {
        result.push_back(std::rand() % (max_number + 1));
    }

    std::sort(result.begin(), result.end());
    return result;
}



//DECREASING SORTED ARRAY GENERATOR
std::vector<int> generate_decreasing_sorted_list(int length, int max_number) {
    std::vector<int> result;
    srand(time(nullptr));
    while (result.size() < length) {
        result.push_back(rand() % (max_number + 1));
    }
    std::sort(result.begin(), result.end(), std::greater<int>());
    return result;
}

void menu_sorting_algorithm(void){
    std::cout<<"What algorithm do you want to execute?"<<std::endl;
    std::cout<<"1.Insertion sort"<<std::endl;
    std::cout<<"2.Selection sort"<<std::endl;
    std::cout<<"3.Bubble sort"<<std::endl;
    std::cout<<"4.Merge sort"<<std::endl;
    std::cout<<"5.Quick sort"<<std::endl;
    std::cout<<"6.Heap sort"<<std::endl;
    std::cout<<"7.Count sort"<<std::endl;
    std::cout<<"8.Radix sort"<<std::endl;
    std::cout<<"9.Bucket sort"<<std::endl;
    std::cout<<"10.Pancake sort"<<std::endl;
    std::cout<<"If you want to exit the menu press 0"<<std::endl;
}

int main() {
    int n,m;
    std::cout<<"What kind of array do you want to sort?"<<std::endl;
    std::cout<<"1.Unsorted "<<std::endl;
    std::cout<<"2.Almost sorted"<<std::endl;
    std::cout<<"3.Decreasing sorted"<<std::endl;
    std::cout<<"4.Sorted"<<std::endl;
    std::cin>>n;
    int number_elem, max_value;
    bool val = true;
    std::vector<int> arr;
    std::vector<int> help_arr;
    auto start_time = 0, end_time = 0, duration = 0;

    do{
        switch (n) {
            case 1:
                std::cout << "How many elements do you want to have in an array?" << std::endl;
                std::cin >> number_elem;
                std::cout << "What is the highest value that a number can take?" << std::endl;
                std::cin >> max_value;
                arr = generateRandomList(number_elem, max_value);
                break;
            case 2:
                std::cout << "How many elements do you want to have in an array?" << std::endl;
                std::cin >> number_elem;
                std::cout << "What is the highest value that a number can take?" << std::endl;
                std::cin >> max_value;
                arr = generate_almost_sorted_list(generate_sorted_list(number_elem, max_value));
                break;
            case 3:
                std::cout << "How many elements do you want to have in an array?" << std::endl;
                std::cin >> number_elem;
                std::cout << "What is the highest value that a number can take?" << std::endl;
                std::cin >> max_value;
                arr = generate_decreasing_sorted_list(number_elem, max_value);
                break;
            case 4:
                std::cout << "How many elements do you want to have in an array?" << std::endl;
                std::cin >> number_elem;
                std::cout << "What is the highest value that a number can take?" << std::endl;
                std::cin >> max_value;
                arr = generate_sorted_list(number_elem, max_value);
                break;
            case 0:
                std::cout << "Exiting programm" << std::endl;
            default:
                std::cout << "Invalid action" << std::endl;
                break;
        }
        do{
            help_arr.resize(arr.size());
            std::copy(std::begin(arr), std::end(arr), std::begin(help_arr));
            /*std::cout<<"This is the original array"<<std::endl;
            for (int i : help_arr) {
                std::cout<<i<<" ";
            }
            std::cout<<std::endl;*/
            menu_sorting_algorithm();
            std::cin>>m;
            bool dir = true;
            switch (m) {
                case 1:
                    measureExecutionTime(insertionSort, number_elem, arr );
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 2:
                    measureExecutionTime(selectionSort, number_elem, arr);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 3:
                    measureExecutionTime(bubbleSort, number_elem, arr);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 4:
                    measureExecutionTime(mergeSort,arr, 0, arr.size() - 1);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 5:
                    measureExecutionTime(quickSort, arr, 0, arr.size() - 1);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 6:
                    measureExecutionTime(heapSort, arr, number_elem);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 7:
                    measureExecutionTime(countSort,arr, max_value);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 8:
                    measureExecutionTime(radixSort,arr);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 9:
                    measureExecutionTime(bucketSort,max_value, arr);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 10:
                    measureExecutionTime(pancakeSort, arr);
                    /*for (int element : arr) {
                        std::cout << element << " ";
                    }*/
                    break;
                case 0:
                    std::cout<<"Exiting sorting menu"<<std::endl;
            }
            std::cout<<std::endl;
            std::copy(std::begin(help_arr), std::end(help_arr), std::begin(arr));
            /*std::cout<<"This is the original array"<<std::endl;
            for (int i : arr){
                std::cout<<i<<" ";
            }*/
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }while(m != 0);
        std::cout<<std::endl;
        std::cout<<"What kind of array do you want to sort?"<<std::endl;
        std::cout<<"1.Unsorted "<<std::endl;
        std::cout<<"2.Almost sorted"<<std::endl;
        std::cout<<"3.Decreasing sorted"<<std::endl;
        std::cout<<"4.Sorted"<<std::endl;
        std::cout<<"If you want to exit the programm press 0"<<std::endl;
        std::cin>>n;
    }while(n != 0);

    return 0;
}