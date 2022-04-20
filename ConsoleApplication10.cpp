#include <iostream>
//#include <locale>
#include <clocale>
using namespace std;




struct Node
{
    string word;
    int value;
    struct Node* left_node;
    struct Node* right_node;
    struct Node* parent;
    char height;

};
char height(Node* (&tree))
{
    return tree ? tree->height : 0;
}

int bfactor(Node* (&tree))
{
    return height(tree->right_node) - height(tree->left_node);
}

void fixheight(Node* (&tree))
{
    char hl = height(tree->left_node);
    char hr = height(tree->right_node);
    tree->height = (hl > hr ? hl + 1 : hr + 1);
}

Node* rotateright(Node* (&tree))
{
    Node* q = tree->left_node;
    tree->left_node = q->right_node;
    q->right_node = tree;
    fixheight(tree);
    fixheight(q);
    return q;
}
Node* rotateleft(Node* (&tree))
{
    Node* p = tree->right_node;
    tree->right_node = p->left_node;
    p->left_node = tree;
    fixheight(tree);
    fixheight(p);
    return p;
}
Node* balance(Node* (&tree))
{
    fixheight(tree);
    cout << tree->height << endl;
    if (bfactor(tree) == -2)
    {
        if (bfactor(tree->left_node) > 0) {
            tree->left_node = rotateleft(tree->left_node);
        }
        return rotateright(tree);

    }
    if (bfactor(tree) == 2)
    {
        if (bfactor(tree->right_node) < 0) {
            tree->right_node = rotateright(tree->right_node);
        }
        return rotateleft(tree);
    }
    return tree;
}



void add_node(Node* (&tree), int k)
{
    if (tree == nullptr) {
        tree = new Node;
        tree->height = 1;
        tree->value = k;
        tree->left_node = nullptr;
        tree->right_node = nullptr;
        tree->parent == nullptr;

    }

    if (k < tree->value)
    {
        add_node(tree->left_node, k);
        tree->left_node->parent = tree;
    }
    if (k > tree->value)
    {
        add_node(tree->right_node, k);
        tree->right_node->parent = tree;
    }
    tree = balance(tree);
}



struct Node* search_node(Node* (&tree), int k)
{
    if (tree == nullptr)
    {
        return 0;
    }
    if (tree->value == k)
    {
        return tree;
    }
    if (tree->value < k)
    {
        return search_node(tree->right_node, k);
    }
    if (tree->value > k)
    {
        return search_node(tree->left_node, k);
    }

}




struct Node* search_node1(Node* (&tree), int k)
{
    if (tree == nullptr)
    {
        cout << "NO\n";
        return 0;
    }
    if (tree->value == k)
    {
        cout << "YES\n";
        return tree;
    }
    if (tree->value < k)
    {
        return search_node1(tree->right_node, k);
    }
    if (tree->value > k)
    {
        return search_node1(tree->left_node, k);
    }

}

struct Node* search_min(Node* (&tree))
{
    if (tree->left_node == nullptr)
    {
        return tree;
    }
    else
    {
        return search_min(tree->left_node);
    }
}

struct Node* search_max(Node* (&tree))
{
    if (tree->right_node == nullptr)
    {
        return tree;
    }
    else
    {
        return search_max(tree->right_node);
    }
}

void print_tree(Node* node)
{
    if (node != nullptr) {
        print_tree(node->left_node);
        cout << node->value << " ";
        print_tree(node->right_node);
    }
    return;
}

void printBT(const string& prefix, Node* (&tree), bool isLeft)
{
    if (tree)
    {
        cout << prefix;

        wcout << (isLeft ? L"├──" : L"└──");

        wcout << tree->value << endl;

        printBT(prefix + (isLeft ? "|   " : "    "), tree->left_node, true);
        printBT(prefix + (isLeft ? "|   " : "    "), tree->right_node, false);
    }
}

void Print_tree(Node* (&tree))
{
    printBT("", tree, false);
}




void delete_node(Node* (&tree), int k)
{
    struct Node* element = search_node(tree, k);
    if (element == tree)
    {
        if (tree->left_node == nullptr && tree->right_node == nullptr)
        {
            delete(tree);
            tree = nullptr;
        }
        else if (tree->left_node != nullptr && tree->right_node == nullptr)
        {
            tree = tree->left_node;
            tree = balance(tree);
        }
        else if (tree->left_node == nullptr && tree->right_node != nullptr)
        {
            tree = tree->right_node;
            tree = balance(tree);
        }
        else
        {
            struct Node* element_min = search_min(tree->right_node);
            int d = tree->value;
            tree->value = element_min->value;
            element_min->value = d;
            delete_node(element->right_node, d);
            tree = balance(tree);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (element->left_node == nullptr && element->right_node == nullptr)
    {

        if (element->parent->left_node != nullptr && element->parent->left_node->value == element->value)
        {
            element->parent->left_node = nullptr;
        }
        if (element->parent->right_node != nullptr && element->parent->right_node->value == element->value)
        {
            element->parent->right_node = nullptr;
        }
        tree = balance(tree);
        delete (element);

    }
    else if (element->left_node != nullptr && element->right_node == nullptr)
    {
        if (element->parent->left_node != nullptr && element->parent->left_node->value == element->value)
        {
            element->left_node->parent = element->parent;
            element->parent->left_node = element->left_node;
        }
        if (element->parent->right_node != nullptr && element->parent->right_node->value == element->value)
        {
            element->left_node->parent = element->parent;
            element->parent->right_node = element->left_node;
        }
        tree = balance(tree);
        delete(element);
    }
    else if (element->left_node == nullptr && element->right_node != nullptr)
    {
        if (element->parent->right_node != nullptr && element->value == element->parent->right_node->value)
        {
            element->right_node->parent = element->parent;
            element->parent->right_node = element->right_node;
        }
        else if (element->parent->left_node != nullptr && element->parent->left_node->value == element->value)
        {
            element->right_node->parent = element->parent;
            element->parent->left_node = element->right_node;
        }
        tree = balance(tree);
        delete(element);
    }
    else
    {
        struct Node* element_min = search_min(element->right_node);
        int d = element->value;
        element->value = element_min->value;
        element_min->value = d;
        delete_node(element->right_node, d);
        tree = balance(tree);
        return;
    }
}




int main()
{

    setlocale(LC_ALL, "");
    struct Node* root;
    root = nullptr;
    string choose;
    while (true)
    {
        cin >> choose;
        if (choose == "add")
        {
            int k;
            cin >> k;
            add_node(root, k);
        }
        else if (choose == "help")
        {
            cout << "Command:\nadd <key>\ndelete <key>\nprint\nmin\nmax\nsearch <key>\n";
        }
        else if (choose == "print")
        {
            Print_tree(root);
            cout << endl;
        }
        else if (choose == "delete")
        {
            int k;
            cin >> k;
            delete_node(root, k);
        }
        else if (choose == "min")
        {
            cout << search_min(root)->value;
            cout << endl;
        }
        else if (choose == "max")
        {
            cout << search_max(root)->value;
            cout << endl;
        }
        else if (choose == "search")
        {
            int k;
            cin >> k;
            search_node1(root, k);

        }
        else {
            break;
        }
    }
}


//add 8
//add 10
//add 9
//add 15
//add 13




//if (element->parent->right_node != nullptr && element->value == element->parent->right_node->value)
//{
//    element->parent->right_node = element_min;
//    element->left_node->parent = element_min;
//    element->right_node->parent = element_min;
//    element_min->left_node = element->left_node;
//    element_min->right_node = element->right_node;
//}
//else if (element->parent->left_node != nullptr && element->parent->left_node->value == element->value)
//{
//    element->parent->left_node = element_min;
//    element->left_node->parent = element_min;
//    element->right_node->parent = element_min;
//    element_min->left_node = element->left_node;
//    element_min->right_node = element->right_node;
//}
//delete(element);