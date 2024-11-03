#include <iostream>
#include <string>
#include "BinarySearchTree.h"

// 辅助函数：打印分隔线
void printDivider(const std::string &message)
{
    std::cout << "\n=== " << message << " ===" << std::endl;
}

// 辅助函数：打印树的内容并验证是否为空
void printAndVerify(const BinarySearchTree<int> &tree)
{
    std::cout << "树的内容：" << std::endl;
    tree.printTree();
    std::cout << "是否为空：" << (tree.isEmpty() ? "是" : "否") << std::endl;
}

int main()
{
    BinarySearchTree<int> bst;

    // 测试1：删除空树中的节点
    printDivider("测试1：删除空树中的节点");
    bst.remove(10);
    printAndVerify(bst);

    // 测试2：构建一个基本的树
    printDivider("测试2：插入节点构建树");
    bst.insert(50); // 根节点
    bst.insert(30); // 左子树
    bst.insert(70); // 右子树
    bst.insert(20); // 左左子树
    bst.insert(40); // 左右子树
    bst.insert(60); // 右左子树
    bst.insert(80); // 右右子树
    printAndVerify(bst);

    // 测试3：删除叶子节点
    printDivider("测试3：删除叶子节点(20)");
    bst.remove(20);
    printAndVerify(bst);

    // 测试4：删除只有一个子节点的节点
    printDivider("测试4：删除只有一个子节点的节点(30)");
    bst.remove(30);
    printAndVerify(bst);

    // 测试5：删除有两个子节点的节点
    printDivider("测试5：删除有两个子节点的节点(50)");
    bst.remove(50);
    printAndVerify(bst);

    // 测试6：删除不存在的节点
    printDivider("测试6：删除不存在的节点(100)");
    bst.remove(100);
    printAndVerify(bst);

    // 测试7：删除所有节点
    printDivider("测试7：删除所有剩余节点");
    bst.remove(40);
    bst.remove(60);
    bst.remove(70);
    bst.remove(80);
    printAndVerify(bst);

    // 测试8：特殊情况测试 - 连续右子树
    printDivider("测试8：特殊情况 - 连续右子树");
    bst.insert(10);
    bst.insert(20);
    bst.insert(30);
    printAndVerify(bst);
    bst.remove(10);
    printDivider("删除根节点(10)后");
    printAndVerify(bst);

    // 测试9：特殊情况测试 - 连续左子树
    printDivider("测试9：特殊情况 - 连续左子树");
    bst.makeEmpty();
    bst.insert(30);
    bst.insert(20);
    bst.insert(10);
    printAndVerify(bst);
    bst.remove(30);
    printDivider("删除根节点(30)后");
    printAndVerify(bst);

    std::cout << "\n所有测试完成！" << std::endl;
    return 0;
}