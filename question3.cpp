//Alvin s1123530 11/27/2024
#include <iostream>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

struct Element 
{
    int value;
    int arrayIndex;
    int elementIndex;

    bool operator>(const Element& other) const 
    {
        return value > other.value;
    }
};

vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) 
{
    priority_queue<Element, vector<Element>, greater<Element>> minHeap;
    vector<int> result;

    // Step 1: Insert the first element of each array into the heap
    for (int i = 0; i < arrays.size(); ++i) 
    {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    // Step 2: Extract the smallest element from the heap and insert the next element from the same array
    while (!minHeap.empty()) 
    {
        Element current = minHeap.top();
        minHeap.pop();
        result.push_back(current.value);

        // If there is another element in the same array, add it to the heap
        if (current.elementIndex + 1 < arrays[current.arrayIndex].size()) 
        {
            int nextValue = arrays[current.arrayIndex][current.elementIndex + 1];
            minHeap.push({nextValue, current.arrayIndex, current.elementIndex + 1});
        }
    }

    return result;
}

int main() 
{
    int k;
    cout << "Enter the number of sorted arrays: ";
    cin >> k;
    cin.ignore(); // To ignore the newline character after the integer input
    vector<vector<int>> arrays(k);

    cout << "Enter the elements of each sorted array, separated by spaces:\n";
    for (int i = 0; i < k; ++i) 
    {
        cout << "Array " << i + 1 << ": ";
        string line;
        getline(cin, line);
        istringstream iss(line);
        int num;
        while (iss >> num) 
        {
            arrays[i].push_back(num);
        }
    }

    vector<int> mergedArray = mergeKSortedArrays(arrays);
    cout << "Merged Array: [";
    for (size_t i = 0; i < mergedArray.size(); ++i) 
    {
        cout << mergedArray[i];
        if (i < mergedArray.size() - 1) 
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
