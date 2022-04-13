// readFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <iostream>
using namespace std;




//Insertion Sort
void insertionSort(vector<int>& data, int n, int& count)
{
    int i, j, temp;

    for (i = 1; i < n; i++)
    {
        j = i;
        temp = data[i];
        while (j > 0 && temp < data[j - 1])
        {
            data[j] = data[j - 1];
            j--;
            count++;
        }
        data[j] = temp;
        count++;
    }

}

//Merge Sort
void MergeSortedIntervals(vector<int>& v, int s, int m, int e, int& count) {
    vector<int> temp;

    int i, j;
    i = s;
    j = m + 1;

    while (i <= m && j <= e) {

        if (v[i] <= v[j]) {
            temp.push_back(v[i]);
            ++i;
            count++;
        }
        else {
            temp.push_back(v[j]);
            ++j;
            count++;
        }

    }

    while (i <= m) {
        temp.push_back(v[i]);
        ++i;
        count++;
    }

    while (j <= e) {
        temp.push_back(v[j]);
        ++j;
        count++;
    }

    for (int i = s; i <= e; ++i)
        v[i] = temp[i - s];

}

void MergeSort(vector<int>& v, int s, int e, int& count) {
    if (s < e) {
        int m = (s + e) / 2;
        MergeSort(v, s, m, count);
        MergeSort(v, m + 1, e, count);
        MergeSortedIntervals(v, s, m, e, count);

    }
}


//Quick Sort
int Partition(vector<int> &data, int start, int end, int& count){

    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(data[i]<data[pivot]) {
            swap(data[i], data[j]);
            ++j;

        }
        count++;
    }
    swap(data[j],data[pivot]);
    return j;

}

void Quicksort(vector<int> &data, int start, int end, int& count){

    if(start<end){
        int p = Partition(data,start,end,count);
        Quicksort(data,start,p-1,count);
        Quicksort(data,p+1,end,count);
    }

}

int main()
{
    int count = 0;
    string fileName = " ";

    cout << "Enter File Name: " << endl;
    cin >> fileName;
    std::vector<int> power;
    //Define the input file stream
    std::ifstream myFile(fileName);
    std::string line;
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    int val;
    int index = 0;
    while (std::getline(myFile, line))
    {
        if (index > 0) {
            int pow;

            //Here...string manipulation
            std::stringstream s_stream(line);
            std::vector<std::string> result;
            while (s_stream.good())
            {
                std::string substr;
                getline(s_stream, substr, ',');
                result.push_back(substr);
            }
            power.push_back(stoi(result[1]));
        }
        index++;
    }

    cout << "Sorted with Insertion Sort: " << endl;
    insertionSort(power, power.size(), count);
    for (std::vector<int>::const_iterator i = power.begin(); i != power.end(); i++) {
        std::cout << *i << ' ';;
    }
    cout << endl;
    cout << "The count for this Sort is: " << count << endl;

    cout << endl;

    cout << "Sorted with Merge Sort: " << endl;
    MergeSort(power, 0, power.size() - 1, count);
    for (std::vector<int>::const_iterator i = power.begin(); i != power.end(); i++) {
        std::cout << *i << ' ';
    }
    cout << endl;
    cout << "The count for this Sort is: " << count << endl << endl;


    cout << "Sorted with Quick Sort: " << endl;
    Quicksort(power,0,power.size()-1, count);
    for (std::vector<int>::const_iterator i = power.begin(); i != power.end(); i++) {
        std::cout << *i << ' ';

    }
    cout << endl;
    cout << "The count for this Sort is: " << count << endl << endl;

    return 0;

}
