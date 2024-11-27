//Alvin s1123530 11/27/2024
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int profit;
    int deadline;
};

bool compareTasks(const Task& a, const Task& b) {
    return a.profit > b.profit;
}

pair<int, vector<int>> scheduleTasks(vector<Task>& tasks) {
    // Sort tasks by profit in descending order
    sort(tasks.begin(), tasks.end(), compareTasks);
    int maxDeadline = 0;
    for (const auto& task : tasks) {
        maxDeadline = max(maxDeadline, task.deadline);
    }

    vector<int> slots(maxDeadline, -1); // -1 indicates the slot is free
    int totalProfit = 0;
    vector<int> scheduledTasks;

    for (const auto& task : tasks) {
        // Find a free slot for this task (starting from the last possible slot)
        for (int i = min(task.deadline, maxDeadline) - 1; i >= 0; --i) {
            if (slots[i] == -1) {
                slots[i] = task.profit;
                totalProfit += task.profit;
                scheduledTasks.push_back(task.profit);
                break;
            }
        }
    }

    return {totalProfit, scheduledTasks};
}

int main() 
{
    int n;
    cout << "Enter the number of tasks: ";
    cin >> n;
    vector<Task> tasks(n);

    cout << "Enter the profit and deadline for each task:\n";
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].profit >> tasks[i].deadline;
    }

    auto [maxProfit, scheduledTasks] = scheduleTasks(tasks);
    cout << "Maximum Profit: " << maxProfit << endl;
    cout << "Scheduled Tasks: [";
    for (size_t i = 0; i < scheduledTasks.size(); ++i) {
        cout << scheduledTasks[i];
        if (i < scheduledTasks.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
