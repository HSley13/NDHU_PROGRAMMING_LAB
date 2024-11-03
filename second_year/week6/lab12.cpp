#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class ExpressionTree {
  private:
    struct Node {
        std::string value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const std::string &val) : value(val), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;

  public:
    ExpressionTree(const std::string &expression) {
        // Here you would implement your logic to build the tree from the expression
    }

    void printInFixOrder() {
        // Implement your infix printing logic
    }

    void printPreFixOrder() {
        // Implement your prefix printing logic
    }

    void printPostFixOrder() {
        // Implement your postfix printing logic
    }

    int eval() {
        return evaluate(root.get());
    }

  private:
    int evaluate(Node *node) {
        if (!node) {
            throw std::runtime_error("Invalid expression tree");
        }

        // Implement your evaluation logic here
        return 0;
    }
};

int main(void) {
    std::cout << "Enter infix expression: ";

    std::string infix;
    std::getline(std::cin, infix);
    ExpressionTree exprTree(infix);

    std::cout << "InFixOrder: ";
    exprTree.printInFixOrder();

    std::cout << "PreFixOrder: ";
    exprTree.printPreFixOrder();

    std::cout << "PostFixOrder: ";
    exprTree.printPostFixOrder();

    std::cout << "Evaluated result: " << exprTree.eval() << std::endl;
}
