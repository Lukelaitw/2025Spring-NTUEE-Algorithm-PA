// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int len = data.size();
    for(int i = 1; i < len; i++){
        int temp = data[i] , j = i - 1;
        while(j >= 0 && data[j] > temp) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(low<high){
        if (flag == 0 ){
            int pivot_index = Partition(data , low , high);
            QuickSortSubVector(data, low , pivot_index-1 , 0);
            QuickSortSubVector(data , pivot_index+1, high , 0);
        }
        else if(flag == 1){
            int pivot_index = RandomizedPartition(data , low , high);
            QuickSortSubVector(data, low , pivot_index-1 , 1);
            QuickSortSubVector(data , pivot_index+1, high , 1);
        }
    }
}

int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // Exercise : Please complete the function
    int rand_index = low + rand() % (high - low + 1);
    swap(data[high], data[rand_index]);
    return Partition(data , low ,high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int  i = low -1 ;
    int pivot = data[high] ;

    for(int k=low; k<high ; k++){
        if (data[k]< pivot){
            swap(data[++i],data[k]);
        }
    }
    swap(data[i+1],data[high]);
    
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low < high) {
            int middle = (low + high) / 2;
            MergeSortSubVector(data, low, middle);
            MergeSortSubVector(data, middle + 1, high);
            Merge(data, low, middle, middle + 1, high);
        }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int i=0 , j=0 , n = low;
    vector<int> left(data.begin() + low, data.begin() + middle1 + 1);
    vector<int> right(data.begin() + middle2, data.begin() + high + 1);
    while (i< left.size() && j< right.size()) {
        if (left[i]<=right[j]){
            data[n] = left[i++];
        }
        else{
            data[n] = right[j++];
        }
        n++;
    }
    while (i < left.size()) {
        data[n++] = left[i++];
    }
    while (j < right.size()) {
        data[n++] = right[j++];
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2*root+1,  right = 2*root +2, largest = root;
    if (left < heapSize && data[left] > data[largest]){
        largest = left ;
    }
    if (right < heapSize && data[right] > data[largest]){
        largest = right ;
    }
    if (largest != root){
        swap(data[largest], data[root]);
        MaxHeapify(data, largest) ;
        
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = heapSize/2 - 1 ; i>=0 ; i--){
        MaxHeapify(data , i);
    }
    
}
