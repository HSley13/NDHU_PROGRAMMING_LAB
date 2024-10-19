#include <iostream>
#include <vector>

template <class T>
class TreeInLinkedList {
  public:
    TreeInLinkedList() {
        nodeList = new std::vector<TreeNode *>();
    }

    void addElement(T data) {
        int k = nodeList->size();
        if (data == 1) {
            nodeList->clear();

            nodeList = new std::vector<TreeNode *>();
            TreeNode *newNode = new TreeNode(data, nullptr);

            nodeList->push_back(newNode);
        } else {
            for (int j{0}; j < k; j++) {
                if (data % (*nodeList)[j]->data == 0) {
                    TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                    nodeList->push_back(newNode);
                }
            }
        }
    }

    void displayPreorder() {
    }

    void displayPostorder() {
    }

  private:
    class TreeNode {
      private:
      public:
        TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
        TreeNode *parent;
        T data;
    };

    std::vector<TreeNode *> *nodeList;
};

int main(void) {
    TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();

    int n;
    std::cin >> n;

    for (int j{1}; j <= n; j++)
        tree->addElement(j);

    tree->displayPreorder();
    std::cout << std::endl;

    tree->displayPostorder();
    std::cout << std::endl;
}
