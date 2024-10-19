#include "List.h"
#include <iostream>
#include <string>
#include <cassert>

// 用于测试的简单类，包含移动语义
class TestObject {
    std::string data;
public:
    TestObject(const std::string& s = "") : data(s) {}
    TestObject(const TestObject& other) : data(other.data) {}
    TestObject(TestObject&& other) noexcept : data(std::move(other.data)) {}
    
    TestObject& operator=(const TestObject& other) {
        if (this != &other) data = other.data;
        return *this;
    }
    
    TestObject& operator=(TestObject&& other) noexcept {
        if (this != &other) data = std::move(other.data);
        return *this;
    }
    
    bool operator==(const TestObject& other) const {
        return data == other.data;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const TestObject& obj) {
        return os << obj.data;
    }
};

// 测试基本构造函数和析构函数
void testConstructorsAndDestructors() {
    std::cout << "Testing constructors and destructors..." << std::endl;
    
    // 测试默认构造函数
    List<int> list1;
    assert(list1.empty());
    assert(list1.size() == 0);
    
    // 测试初始化列表构造函数
    List<int> list2 = {1, 2, 3, 4, 5};
    assert(list2.size() == 5);
    assert(list2.front() == 1);
    assert(list2.back() == 5);
    
    // 测试拷贝构造函数
    List<int> list3(list2);
    assert(list3.size() == list2.size());
    
    // 测试移动构造函数
    List<int> list4(std::move(list3));
    assert(list4.size() == 5);
    assert(list3.empty());  // 移动后原对象应为空
    
    std::cout << "Constructors and destructors tests passed!" << std::endl;
}

// 测试迭代器功能
void testIterators() {
    std::cout << "Testing iterators..." << std::endl;
    
    List<int> list = {1, 2, 3, 4, 5};
    
    // 测试begin()和end()
    auto it = list.begin();
    assert(*it == 1);
    
    // 测试迭代器自增
    ++it;
    assert(*it == 2);
    it++;
    assert(*it == 3);
    
    // 测试const迭代器
    const List<int>& constList = list;
    auto constIt = constList.begin();
    assert(*constIt == 1);
    
    // 测试迭代器遍历
    int sum = 0;
    for (const auto& num : list) {
        sum += num;
    }
    assert(sum == 15);
    
    std::cout << "Iterator tests passed!" << std::endl;
}

// 测试插入和删除操作
void testInsertionAndDeletion() {
    std::cout << "Testing insertion and deletion..." << std::endl;
    
    List<TestObject> list;
    
    // 测试push_back
    list.push_back(TestObject("first"));
    assert(list.size() == 1);
    assert(list.back() == TestObject("first"));
    
    // 测试push_front
    list.push_front(TestObject("second"));
    assert(list.size() == 2);
    assert(list.front() == TestObject("second"));
    
    // 测试insert
    auto it = list.begin();
    ++it;
    list.insert(it, TestObject("third"));
    assert(list.size() == 3);
    
    // 测试移动插入
    list.push_back(TestObject("fourth"));
    assert(list.back() == TestObject("fourth"));
    
    // 测试pop_front和pop_back
    list.pop_front();
    list.pop_back();
    assert(list.size() == 2);
    
    // 测试erase
    it = list.begin();
    it = list.erase(it);
    assert(list.size() == 1);
    
    // 测试clear
    list.clear();
    assert(list.empty());
    
    std::cout << "Insertion and deletion tests passed!" << std::endl;
}

// 测试赋值操作
void testAssignment() {
    std::cout << "Testing assignment operations..." << std::endl;
    
    List<int> list1 = {1, 2, 3};
    List<int> list2;
    
    // 测试拷贝赋值
    list2 = list1;
    assert(list2.size() == list1.size());
    
    // 测试移动赋值
    List<int> list3;
    list3 = std::move(list1);
    assert(list3.size() == 3);
    assert(list1.empty());
    
    std::cout << "Assignment tests passed!" << std::endl;
}

// Bug测试：测试在空列表上调用front()和back()
void testBugEmptyAccess() {
    std::cout << "Testing bug: accessing empty list..." << std::endl;
    
    List<int> list;
    // 这里应该会导致未定义行为，因为我们在空列表上调用front()
    // 在实际应用中应该添加边界检查
    try {
        int front = list.front();
        std::cout << "Bug found: front() on empty list returned " << front << std::endl;
    } catch (...) {
        std::cout << "Exception caught as expected" << std::endl;
    }
}

void testDecrementOperator() {
    std::cout << "Testing decrement operators..." << std::endl;
    
    List<int> list = {1, 2, 3, 4, 5};
    
    // 测试前置--
    auto it = list.end();
    --it;
    assert(*it == 5);
    --it;
    assert(*it == 4);
    
    // 测试后置--
    auto it2 = list.end();
    auto it3 = it2--;
    assert(it3 == list.end());
    assert(*it2 == 5);
    
    // 测试const迭代器的--操作
    const List<int>& constList = list;
    auto constIt = constList.end();
    --constIt;
    assert(*constIt == 5);
    
    auto constIt2 = constIt--;
    assert(*constIt2 == 5);
    assert(*constIt == 4);
    
    std::cout << "Decrement operator tests passed!" << std::endl;
}

void testMoveAssignment() {
    std::cout << "Testing move assignment..." << std::endl;
    
    List<int> list1 = {1, 2, 3};
    List<int> list2;
    
    list2 = std::move(list1);
    assert(list2.size() == 3);
    assert(list1.empty());
    
    std::cout << "Move assignment test passed!" << std::endl;
}

void testClear() {
    std::cout << "Testing clear..." << std::endl;
    
    List<int> list = {1, 2, 3, 4, 5};
    list.clear();
    assert(list.empty());
    assert(list.size() == 0);
    
    std::cout << "Clear test passed!" << std::endl;
}

void testRangeErase() {
    std::cout << "Testing range erase..." << std::endl;
    
    List<int> list = {1, 2, 3, 4, 5};
    auto it1 = list.begin();
    ++it1;
    auto it2 = list.end();
    --it2;
    
    list.erase(it1, it2);
    assert(list.size() == 2);
    assert(list.front() == 1);
    assert(list.back() == 5);
    
    std::cout << "Range erase test passed!" << std::endl;
}

void testFrontBackNonEmpty() {
    std::cout << "Testing front() and back() on non-empty list..." << std::endl;
    
    List<int> list = {1, 2, 3};
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    std::cout << "Front and back on non-empty list test passed!" << std::endl;
}

int main() {
    std::cout << "Starting List tests..." << std::endl;
    
    testConstructorsAndDestructors();
    testIterators();
    testInsertionAndDeletion();
    testAssignment();
    testDecrementOperator();
    testBugEmptyAccess();
    testMoveAssignment();
    testClear();
    testRangeErase();
    testFrontBackNonEmpty();
    
    std::cout << "All tests completed successfully!" << std::endl;
    return 0;
}