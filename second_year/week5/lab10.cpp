#include <iostream>
#include <memory>
#include <vector>

template <class T>
class TreeInLinkedList {
  public:
    TreeInLinkedList() {
        nodeList = std::make_shared<std::vector<std::shared_ptr<TreeNode>>>();
    }

    void addElement(T data) {
        int k = nodeList->size();

        if (data == 1) {
            nodeList->clear();
            nodeList = std::make_shared<std::vector<std::shared_ptr<TreeNode>>>();
            std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>(data, nullptr);
            nodeList->push_back(newNode);
        } else {
            for (int j{0}; j < k; j++) {
                if (data % (*nodeList)[j]->data == 0) {
                    std::shared_ptr<TreeNode> newNode = std::make_shared<TreeNode>(data, (*nodeList)[j]);
                    nodeList->push_back(newNode);
                }
            }
        }
    }

    void displayPreorder() {
        // Implementation here
    }

    void displayPostorder() {
        // Implementation here
    }

  private:
    class TreeNode {
      public:
        TreeNode(T d, std::shared_ptr<TreeNode> p) : data(d), parent(p) {}
        std::shared_ptr<TreeNode> parent;
        T data;
    };

    std::shared_ptr<std::vector<std::shared_ptr<TreeNode>>> nodeList;
};

int main(void) {
    std::unique_ptr<TreeInLinkedList<int>> tree = std::make_unique<TreeInLinkedList<int>>();

    int n;
    std::cin >> n;

    for (int j{1}; j <= n; j++) {
        tree->addElement(j);
    }

    tree->displayPreorder();
    std::cout << std::endl;

    tree->displayPostorder();
    std::cout << std::endl;
}
