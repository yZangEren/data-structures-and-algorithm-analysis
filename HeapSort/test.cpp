#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "HeapSort.h"

using namespace std;
using namespace std::chrono;

// 检查排序结果是否正确
template <typename Comparable>
bool check(const vector<Comparable> &arr)
{
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

// 生成测试数据
vector<int> generateRandom(int size)
{
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = dis(gen);
    }
    return arr;
}

vector<int> generateSorted(int size)
{
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }
    return arr;
}

vector<int> generateReversed(int size)
{
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = size - i;
    }
    return arr;
}

vector<int> generatePartiallyRepeated(int size)
{
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, size / 10); // 只使用size/10范围内的数，确保重复
    for (int i = 0; i < size; i++)
    {
        arr[i] = dis(gen);
    }
    return arr;
}

// 测试函数
void runTest(const string &testName, vector<int> &arr)
{
    cout << "\n测试 " << testName << " (大小: " << arr.size() << ")" << endl;

    // 为std::sort_heap准备副本
    vector<int> arr_std = arr;
    vector<int> arr_custom = arr;

    // 测试自定义堆排序
    auto start = high_resolution_clock::now();
    heapsort(arr_custom);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "自定义堆排序用时: " << duration.count() << " 毫秒" << endl;
    cout << "排序结果是否正确: " << (check(arr_custom) ? "是" : "否") << endl;

    // 测试标准库sort_heap
    start = high_resolution_clock::now();
    make_heap(arr_std.begin(), arr_std.end());
    sort_heap(arr_std.begin(), arr_std.end());
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "标准库sort_heap用时: " << duration.count() << " 毫秒" << endl;
    cout << "排序结果正确: " << (check(arr_std) ? "是" : "否") << endl;
}

int main()
{
    const int SIZE = 1000000;

    // 测试随机序列
    vector<int> randomArr = generateRandom(SIZE);
    runTest("随机序列", randomArr);

    // 测试有序序列
    vector<int> sortedArr = generateSorted(SIZE);
    runTest("有序序列", sortedArr);

    // 测试逆序序列
    vector<int> reversedArr = generateReversed(SIZE);
    runTest("逆序序列", reversedArr);

    // 测试部分重复序列
    vector<int> repeatedArr = generatePartiallyRepeated(SIZE);
    runTest("部分重复序列", repeatedArr);

    return 0;
}