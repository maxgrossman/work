#include <vector>
#include <array>

struct Node {
    struct Node *left, *right;
    int value;
    Node(int value) {
        this->value = value;
        left = right = nullptr;
    }
};
// insert value into tree
Node * sorted_array_to_tree(std::vector<int> tree_vec, int start, int end);
Node * array_to_tree(std::vector<int> tree_vec);

Node * _insert(Node * tree_root, int new_value);
void insert(Node * tree_root, int new_value);

void delete_node(std::array<Node*,2> search_array, int del_value);
void delete_tree(Node * tree_root);

void inorder_traversal(Node * tree_root);   // (Right, Root, Left)
void preorder_traversal(Node * tree_root);  // (Root, Left, Right)
void postorder_traversal(Node * tree_root); // (Left, Right, Root)

int get_height(Node * tree_root, int count);
int get_nodes_count(Node * tree_root, int count);
int get_min(Node * tree_root);
int get_max(Node * tree_root);
void show_min_max(Node * tree_root);

bool is_in_tree(Node * tree_root, int value);
Node * search(Node * tree_root, int value);
std::array<Node*,2> search_inorder_predecessor(std::array<Node*, 2>, int value);
std::array<Node*,2> search_with_parent(std::array<Node*, 2> search_array, int value);
// is_binary_search_tree
// delete_value
// get_successor