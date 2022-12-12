#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

#define fast()                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(0)

#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define sqr(a) ((a) * (a))
#define vout(a) cout << #a << ": " << (a) << '\n'

using ll = long long;
using ld = long double;

const int INF = 0x7fffffff;
const ll MOD = 1e9 + 7;
const ld EPS = 1e-8;
const ld PI = 3.14159265358979323;
const int MAXN = 1e5 + 1000;

// AVLTree is a self-balancing binary search tree.
// More read on wiki on other edu. resources.
template <class T>
struct AVLTree {
    struct Node {
        T key;

        // Balancing requires the info about sub-tree height.
        // Notice that balance can be negative, so size_t won't do.
        long long height = 1;

        Node* l = nullptr;
        Node* r = nullptr;

        explicit Node(T key) : key(key) {}
    };

    Node* root_ = nullptr;
    size_t size_ = 0;

    // Destructor is a necessity while raw memory management involved.
    ~AVLTree() {
        clean();
    }

    bool empty() const {
        return size_ == 0;
    }

    void clean() {
        root_ = clean(root_);
    }

    Node* clean(Node* node) {
        if (!node) {
            return node;
        }

        if (node->l_) {
            node->l_ = clean(node->l_);
        }

        if (node->r_) {
            node->r_ = clean(node->r_);
        }

        delete node;
        --size_;

        return node = nullptr;
    }

    void insert(T key) {
        root_ = insert(key, root_);
    }

    Node* insert(T key, Node* node) {
        // If not a valid node than it is insertion point.
        if (!node) {
            ++size_;
            return new Node(key);
        }

        // Default search for insertion point.
        if (key < node->key_) {
            node->l_ = insert(key, node->l_);
        }
        else if (key > node->key_)
            node->r_ = insert(key, node->r_);
        else {
            return node; // If exists just return existing.
        }

        // Recalculate height after insertion.
        node->height_ = max(height(node->l_), height(node->r_)) + 1;

        // Balance after insertion.
        long long bbal = node_bbal(node);

        if (bbal < -1) {
            if (node_bbal(node->l_) <= 0) {
                return right_turnaround(node);
            }
            node->l_ = left_turnaround(node->l_);
            return right_turnaround(node);
        }
        if (bbal > 1) {
            if (node_bbal(node->r_) >= 0) {
                return left_turnaround(node);
            }
            node->r_ = right_turnaround(node->r_);
            return left_turnaround(node);
        }
        return node;
    }

    void remove(T key) {
        root_ = remove(key, root_);
    }

    Node* remove(T key, Node* node) {
        // If not a valid node than return it (i.e. nullptr).
        if (!node) {
            return node;
        }

        // Search for a node to remove.
        if (key < node->key_) {
            node->l_ = remove(key, node->l_);
        }
        else if (key > node->key_) {
            node->r_ = remove(key, node->r_);
        }
        else if (!node->l_ && !node->r_) {
            // If both parents not valid than simply remove node.
            --size_;
            delete node;

            node = nullptr;
        }
        else if (node->l_) {
            // Otherwise find "swappable" node from left sub-tree.
            Node* tmp = node->l_;
            while (tmp->r_) {
                tmp = tmp->r_;
            }

            // And "copy" it to current node.
            node->key_ = tmp->key_;

            // Than remove copy source, as it now duplicate.
            node->l_ = remove(tmp->key_, node->l_);
        }
        else {
            // Same but if left node is not a valid one.
            Node* tmp = node->r_;
            while (tmp->l_) {
                tmp = tmp->l_;
            }
            node->key_ = tmp->key_;
            node->r_ = remove(tmp->key_, node->r_);
        }

        // Check if remove looking at the deleted node.

        if (!node) {
            return node;
        }

        // Recalculate height while going back to root.
        node->height_ = max(height(node->l_), height(node->r_)) + 1;

        // Balance after insertion.
        long long bbal = node_bbal(node);

        if (bbal < -1) {
            if (node_bbal(node->l_) <= 0) {
                return right_turnaround(node);
            }
            node->l_ = left_turnaround(node->l_);
            return right_turnaround(node);
        }
        if (bbal > 1) {
            if (node_bbal(node->r_) >= 0) {
                return left_turnaround(node);
            }
            node->r_ = right_turnaround(node->r_);
            return left_turnaround(node);
        }

        // Return child so parent can update its pointer.
        return node;
    }

    Node* find(T key) {
        return find(key, root_);
    }

    // Find just like in the BST.
    Node* find(T key, Node* node) {
        if (!node) {
            return node;
        }

        if (key < node->key_) {
            return find(key, node->l_);
        }
        if (key > node->key_) {
            return find(key, node->r_);
        }
        return node;
    }

    // Big turns are being done by combining left & right turns.

    // Right turn.
    static Node* right_turnaround(Node* a) {
        Node* b = a->l_;
        Node* c = b->r_;

        b->r_ = a;
        a->l_ = c;

        a->height_ = max(height(a->l_), height(a->r_)) + 1;
        b->height_ = max(height(b->l_), height(b->r_)) + 1;

        return b;
    }

    // Left turn.
    static Node* left_turnaround(Node* a) {
        Node* b = a->r_;
        Node* c = b->l_;

        b->l_ = a;
        a->r_ = c;

        a->height_ = max(height(a->l_), height(a->r_)) + 1;
        b->height_ = max(height(b->l_), height(b->r_)) + 1;

        return b;
    }

    // Returns 0 if not a valid node was provided.
    static long long height(Node* node) {
        return node ? node->height_ : 0;
    }

    // Returns balance of the node provided.
    static long long node_bbal(Node* node) {
        return node ? height(node->r_) - height(node->l_) : 0;
    }
};

int main() {
#ifdef _LOCAL
    auto rtime = high_resolution_clock::now();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fast();

    AVLTree<int> tree;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        int x;
        cin >> c >> x;

        switch (c) {
        case 'A':
            // Insert.
            tree.insert(x);
            cout << AVLTree<int>::node_bbal(tree.root_)
                << '\n'; // Print balance of the root.
            break;
        case 'D':
            // Delete.
            tree.remove(x);
            cout << AVLTree<int>::node_bbal(tree.root_) << '\n';
            break;
        case 'C':
            // Find.
            cout << (tree.find(x) ? 'Y' : 'N') << '\n';
            break;
        default:
            break;
        }
    }

#ifdef _LOCAL
    duration<double> diff = high_resolution_clock::now() - rtime;
    cerr << "Runtime: " << diff.count() << " s.\n";
#endif
    return 0;
}
