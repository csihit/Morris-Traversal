    #include <iostream>
    #include <vector>
    #include <queue>
    using namespace std;
    
    class Node {
    public:
        int data;
        Node* left;
        Node* right;
    
        Node(int x) {
            data = x;
            left = right = nullptr;
        }
    };
    
    // Morris Inorder Traversal
    vector<int> inOrder(Node* root) {
        vector<int> res;
        Node* curr = root;
    
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                res.push_back(curr->data);
                curr = curr->right;
            } else {
                Node* prev = curr->left;
                while (prev->right != nullptr && prev->right != curr) {
                    prev = prev->right;
                }
    
                if (prev->right == nullptr) {
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    prev->right = nullptr;
                    res.push_back(curr->data);
                    curr = curr->right;
                }
            }
        }
        return res;
    }
    
    // Build tree from level-order vector (-1 means NULL)
    Node* buildTreeFromLevelOrder(const vector<int>& vals) {
        if (vals.empty() || vals[0] == -1) return nullptr;
    
        Node* root = new Node(vals[0]);
        queue<Node*> q;
        q.push(root);
        size_t i = 1;
    
        while (!q.empty() && i < vals.size()) {
            Node* cur = q.front(); 
            q.pop();
    
            // Left child
            if (i < vals.size() && vals[i] != -1) {
                cur->left = new Node(vals[i]);
                q.push(cur->left);
            }
            i++;
    
            // Right child
            if (i < vals.size() && vals[i] != -1) {
                cur->right = new Node(vals[i]);
                q.push(cur->right);
            }
            i++;
        }
        return root;
    }
    
    int main() {
        int n;
        cout << "Enter number of nodes in level order (including -1 for null): ";
        cin >> n;
    
        vector<int> vals(n);
        cout << "Enter values in level order (-1 for null):\n";
        for (int i = 0; i < n; i++) {
            cin >> vals[i];
        }
    
        Node* root = buildTreeFromLevelOrder(vals);
    
        vector<int> res = inOrder(root);
    
        cout << "\nInorder Traversal using Morris Traversal: ";
        for (int data : res) {
            cout << data << " ";
        }
        cout << "\n";
    
        return 0;
    }
