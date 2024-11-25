#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class TaskPriorityQueue 
{
private:
    priority_queue<pair<int, pair<int, string>>> heap;
    unordered_map<string, pair<int, int>> task_map;
    int counter;

public:
    TaskPriorityQueue() : counter(0) {}

    void add_task(const string& task_name, int priority) 
    {
        heap.push({priority, {counter, task_name}});
        task_map[task_name] = {priority, counter};
        counter++;
    }

    string get_highest_priority_task() 
    {
        while (!heap.empty()) 
        {
            auto top = heap.top();
            heap.pop();
            string task_name = top.second.second;
            if (task_map.find(task_name) != task_map.end()) {
                task_map.erase(task_name);
                return task_name;
            }
        }
        return "";
    }

    vector<pair<string, int>> get_remaining_tasks() 
    {
        vector<pair<string, int>> remaining_tasks;
        for (const auto& entry : task_map) 
        {
            remaining_tasks.push_back({entry.first, entry.second.first});
        }
        sort(remaining_tasks.begin(), remaining_tasks.end(), [](const pair<string, int>& a, const pair<string, int>& b) 
        {
            return a.second > b.second;
        });
        return remaining_tasks;
    }
};

int main() 
{
    int n;
    cin >> n;
    cin.ignore();
    TaskPriorityQueue task_queue;

    for (int i = 0; i < n; ++i) 
    {
        string operation;
        getline(cin, operation);
        if (operation.substr(0, 3) == "ADD") 
        {
            size_t space1 = operation.find(' ', 4);
            string task_name = operation.substr(4, space1 - 4);
            int priority = stoi(operation.substr(space1 + 1));
            task_queue.add_task(task_name, priority);
        } else if (operation == "GET") 
        {
            string highest_priority_task = task_queue.get_highest_priority_task();
            if (!highest_priority_task.empty()) 
            {
                cout << highest_priority_task << endl;
            }
        }
    }

    vector<pair<string, int>> remaining_tasks = task_queue.get_remaining_tasks();
    cout << "Remaining tasks: [";
    for (size_t i = 0; i < remaining_tasks.size(); ++i) 
    {
        cout << "(" << remaining_tasks[i].first << ", " << remaining_tasks[i].second << ")";
        if (i < remaining_tasks.size() - 1) 
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
