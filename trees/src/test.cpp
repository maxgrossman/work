#include "../include/trees.h"
#include <iostream>
#include <cassert>

int main()
{
    // make tree from list of unordered values
    std::vector<int> tree_nodes;
    tree_nodes.push_back(10);tree_nodes.push_back(2);tree_nodes.push_back(42);
    tree_nodes.push_back(9);tree_nodes.push_back(6);tree_nodes.push_back(3);
    tree_nodes.push_back(22);tree_nodes.push_back(1);

    // show that when we insert the list of nodes the root is what we expect it to be.
    Node * root = array_to_tree(tree_nodes);
    assert(root->value == 6);
    // show insert places node at expected location
    insert(root, 7);
    assert(root->right->left->left->value == 7);
    // all the traversals print like we expect
    inorder_traversal(root);
    std::cout << "" << std::endl;
    preorder_traversal(root);
    std::cout << "" << std::endl;
    postorder_traversal(root);
    std::cout << "" << std::endl;
    // we have 9 nodes.
    assert(get_nodes_count(root, 0) == 9);
    show_min_max(root); // min is 1, max is 42

    assert(is_in_tree(root, 22) == true);
    assert(is_in_tree(root, 32) == false);

    assert(get_height(root, 0) == 4);

    // when we search with parent, we gt expected parent at loc 0 and our node at 1
    std::array<Node*,2> search_array = search_with_parent((std::array<Node*,2>){nullptr, root}, 42);
    assert(search_array[0]->value == 22);
    assert(search_array[1]->value == 42);

    Node * root2 = new Node(15);
    root2->left = new Node(10);
    root2->left->left = new Node(8);
    root2->left->right = new Node(12);
    root2->right = new Node(20);
    root2->right->right = new Node(30);
    root2->right->left = new Node(18);
    root2->right->left->left = new Node(16);
    root2->right->left->right = new Node(19);

    // show we do indeed get the inorder predecessor
    search_array[0] = nullptr;
    search_array[1] = root2;
    search_array = search_inorder_predecessor(search_array, 20);
    assert(search_array[1]->value == 19);


    search_array[0] = nullptr;
    search_array[1] = root2;
    // show we delete 20 and also that the value at its location is its inorder predecessor
    delete_node(search_array, 20);
    assert(is_in_tree(root2, 20) == false);
    assert(root2->right->value == 19);
    // show we delete 8, which has no children.
    delete_node(search_array, 8);
    assert(is_in_tree(root2, 8) == false);
    // show we delete 18 which now has just one child.
    delete_node(search_array, 18);
    assert(is_in_tree(root2, 18) == false);
    // both trees are binary search trees
    assert(is_binary_search_tree(root) == true);
    assert(is_binary_search_tree(root2) == true);
    // this tree is not a binary search tree
    root2->left->left = new Node(11);
    assert(is_binary_search_tree(root2) == false);
    return 0;
}
