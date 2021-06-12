#include "../include/trees.h"
#include <iostream>

Node * sorted_vec_to_tree(std::vector<int> tree_vec, int start, int end) {
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;

    Node * root = new Node(tree_vec[mid]);

    root->left = sorted_vec_to_tree(tree_vec, start, mid - 1);
    root->right = sorted_vec_to_tree(tree_vec, mid + 1, end);
    return root;
}

Node * array_to_tree(std::vector<int> tree_vec) {
    std::sort(tree_vec.begin(), tree_vec.end());
    return sorted_vec_to_tree(tree_vec, 0, tree_vec.size() - 1);
}

Node * _insert(Node * tree_root, int new_value) {
    if (tree_root == nullptr) {
        tree_root = new Node(new_value);
    } else {
        if (new_value < tree_root->value) {
            tree_root->left = _insert(tree_root->left, new_value);
        } else {
            tree_root->right = _insert(tree_root->right, new_value);
        }
    }
    return tree_root;
}
void insert(Node * tree_root, int new_value) {
    tree_root = _insert(tree_root, new_value);
};

void inorder_traversal(Node * tree_root) {
    if (tree_root == nullptr) return;
    inorder_traversal(tree_root->left);
    std::cout << tree_root->value << " ";
    inorder_traversal(tree_root->right);
}

void preorder_traversal(Node * tree_root) {
    if (tree_root == nullptr) return;
    std::cout << tree_root->value << " ";
    preorder_traversal(tree_root->left);
    preorder_traversal(tree_root->right);
}

void postorder_traversal(Node * tree_root) {
    if (tree_root == nullptr) return;
    postorder_traversal(tree_root->left);
    postorder_traversal(tree_root->right);
    std::cout << tree_root->value << " ";
}

int get_height(Node * tree_root, int count) {
    if (tree_root == nullptr) return 0;
    int left_count = get_height(tree_root->left, count);
    int right_count = get_height(tree_root->right, count);
    count += left_count < right_count ? right_count : left_count;
    count++;
    return count;
}

int get_nodes_count(Node * tree_root, int count) {
    if (tree_root == nullptr) return count;
    count = get_nodes_count(tree_root->left, count);
    ++count;
    count = get_nodes_count(tree_root->right, count);
    return count;
}

int get_min(Node * tree_root) {
    Node * min_node = tree_root;
    while (min_node->left != nullptr)
        min_node = min_node->left;

    return min_node->value;
}

int get_max(Node * tree_root) {
    Node * max_node = tree_root;
    while (max_node->right != nullptr)
        max_node = max_node->right;

    return max_node->value;
}

void show_min_max(Node * tree_root) {
    std::cout << "MIN: " << get_min(tree_root) << " MAX: " << get_max(tree_root) << std::endl;
}

Node * search(Node * tree_root, int value) {
    if (tree_root == nullptr) return nullptr;
    Node * search_node = nullptr;

    if (value < tree_root->value)
        search_node = search(tree_root->left, value);
    else if (tree_root->value < value)
        search_node = search(tree_root->right, value);
    else
        search_node = tree_root;

    return search_node;
}

std::array<Node*, 2> search_with_parent(std::array<Node*, 2> search_array, int value) {
    if (search_array[1] == nullptr) return search_array;

    if (value < search_array[1]->value) {
        search_array[0] = search_array[1];
        search_array[1] = search_array[1]->left;
        search_array = search_with_parent(search_array, value);
    } else if (search_array[1]->value < value) {
        search_array[0] = search_array[1];
        search_array[1] = search_array[1]->right;
        search_array = search_with_parent(search_array, value);
    }

    return search_array;
}

std::array<Node*, 2> search_inorder_predecessor(std::array<Node*, 2> search_array, int value) {
    // get the node in question
    search_array = search_with_parent(search_array, value);
    search_array[0] = search_array[1];
    search_array[1] = search_array[1]->left;

    while (search_array[1]->right != nullptr) {
        search_array[0] = search_array[1];
        search_array[1] = search_array[1]->right;
    }

    return search_array;
}

/**
 *  https://www.techiedelight.com/deletion-from-bst/
 * - 1. delete node without children; just remove the child
 * - 2. delete node with one child; just replace with child and delete.
 * - 3. delete node with two children; find 'inorder' predecessor, replace, then delete the predecessor
 */
void delete_node(std::array<Node*,2> search_array, int del_value) {
    search_array = search_with_parent(search_array, del_value);

    if (search_array[1] == nullptr) return;

    // 0 = no children; 1 = left; 2 = right; 3 = both;
    int root_direction = 0;  // is search_array[1] the left or right child of search_array[0];
    int child_direction = 0; // does search_array[1] have no kids, left kid, right kid, or left and right kid.

    if (search_array[0]->left != nullptr && search_array[0]->left->value == del_value)
        root_direction++;
    else if (search_array[0]->right != nullptr && search_array[0]->right->value == del_value)
        root_direction += 2;

    if (search_array[1]->left != nullptr)
        ++child_direction;
    if (search_array[1]->right != nullptr)
        child_direction += 2;

    // deleting node without children.
    if (child_direction == 0) { // 1.
        if (root_direction == 1)
            search_array[0]->left = nullptr;
        else if (root_direction == 2)
            search_array[0]->right = nullptr;
        delete search_array[1];
    } else if (child_direction < 3)  { // 2.
        if (root_direction == 1)
            search_array[0]->left = child_direction == 1 ? search_array[1]->left : search_array[1]->right;
        else if (root_direction == 2)
            search_array[0]->right = child_direction == 1 ? search_array[1]->left : search_array[1]->right; ;
        delete search_array[1];
    } else { // 3.
        // get the inorder predecessor, set del node value to it,
        std::array<Node*,2> inorder_search_array = search_inorder_predecessor(search_array, del_value);
        if (inorder_search_array[1] != nullptr) {
            // replace the value node's value with inorder node's value
            search_array[1]->value = inorder_search_array[1]->value;
            // delete inorder predecessor node
            delete_node(inorder_search_array, inorder_search_array[1]->value);
        }
    }
};


void delete_tree(Node * tree_root) {
    if (tree_root == nullptr) return;
    delete_tree(tree_root->left);
    delete_tree(tree_root->right);
    delete tree_root;
}

bool is_in_tree(Node * tree_root, int value) {
    return search(tree_root, value) != nullptr;
}

bool is_left_lesser(Node * root, int value) {
    if (root == nullptr)
        return true;
    if (value < root->value)
        return false;
    return is_binary_search_tree(root);
};
bool is_right_greater(Node * root, int value) {
    if (root == nullptr)
        return true;
    if (root->value < value)
        return false;
    return is_binary_search_tree(root);
};
bool is_binary_search_tree(Node * root){
    return is_left_lesser(root->left, root->value) &&
           is_right_greater(root->right, root->value);
}
