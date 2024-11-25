#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(const vector<int>& levelOrder) 
{
    if (levelOrder.empty() || levelOrder[0] == -1) 
    {
        return nullptr;
    }

    TreeNode* root = new TreeNode(levelOrder[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (i < levelOrder.size()) 
    {
        TreeNode* current = q.front();
        q.pop();

        if (levelOrder[i] != -1) 
        {
            current->left = new TreeNode(levelOrder[i]);
            q.push(current->left);
        }
        i++;

        if (i < levelOrder.size() && levelOrder[i] != -1) 
        {
            current->right = new TreeNode(levelOrder[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;
}

pair<int, int> heightAndDiameter(TreeNode* node) 
{
    if (!node) 
    {
        return {0, 0};
    }

    auto leftResult = heightAndDiameter(node->left);
    auto rightResult = heightAndDiameter(node->right);

    int leftHeight = leftResult.first;
    int leftDiameter = leftResult.second;
    int rightHeight = rightResult.first;
    int rightDiameter = rightResult.second;

    int currentHeight = 1 + max(leftHeight, rightHeight);
    int currentDiameter = max(leftHeight + rightHeight, max(leftDiameter, rightDiameter));

    return {currentHeight, currentDiameter};
}

int diameterOfBinaryTree(TreeNode* root) 
{
    return heightAndDiameter(root).second;
}

int main() 
{
    cout << "Enter the level-order traversal of the binary tree (use -1 for null nodes): ";
    string input;
    getline(cin, input);
    istringstream iss(input);
    vector<int> levelOrder;
    int val;
    while (iss >> val) 
    {
        levelOrder.push_back(val);
    }

    TreeNode* root = buildTree(levelOrder);
    cout << "Diameter of the binary tree: " << diameterOfBinaryTree(root) << endl;

    return 0;
}
