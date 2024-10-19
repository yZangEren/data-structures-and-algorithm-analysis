#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class SingleLinkedList {
private:
    class Node {
    private:
        T data;
        Node* next = nullptr;
        Node(T _val) : data(_val) {}
        
        friend class SingleLinkedList<T>;
    };

    Node* head = nullptr;
    Node* currentPos = nullptr;
    int size = 0;
    
    void _emptyList();
    void _copy(const SingleLinkedList<T>& _l);
    
public:
    T getCurrentVal() const;
    void setCurrentVal(const T& _val);
    bool isEmpty() const;
    int getSize() const { return size; }
    void emptyList();
    SingleLinkedList() = default;
    SingleLinkedList(std::initializer_list<T> _l);
    ~SingleLinkedList();
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T>& _l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T>& _l);
    void insert(T _val);
    void remove();
    bool find(const T& _val);
};

template<typename T>
T SingleLinkedList<T>::getCurrentVal() const {
    if (currentPos == nullptr) {
        throw std::runtime_error("Empty current position! Can't get value!");
    }
    return currentPos->data;
}

template<typename T>
void SingleLinkedList<T>::setCurrentVal(const T& _val) {
    if (currentPos == nullptr) {
        throw std::runtime_error("Empty current position! Can't set value!");
    }
    currentPos->data = _val;
}

template<typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template<typename T>
void SingleLinkedList<T>::insert(T _val) {
    if (isEmpty()) {
        head = new Node(_val);
        currentPos = head;
        size = 1;
    } else {
        Node* newNode = new Node(_val);
        newNode->next = currentPos->next;
        currentPos->next = newNode;
        currentPos = newNode;
        size++;
    }
}

template<typename T>
void SingleLinkedList<T>::remove() {
    if (currentPos == nullptr) {
        return;
    }
    
    if (size == 1) {
        delete head;
        head = nullptr;
        currentPos = nullptr;
        size = 0;
    } else if (currentPos->next != nullptr) {
        Node* toDelete = currentPos->next;
        currentPos->next = toDelete->next;
        delete toDelete;
        size--;
    }
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l) {
    for (const auto& val : _l) {
        insert(val);
    }
}

template<typename T>
void SingleLinkedList<T>::_emptyList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    _emptyList();
}

template<typename T>
void SingleLinkedList<T>::printList() const {
    Node* p = head;
    while (p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T>& _l) {
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T>& _l) {
    Node* p = _l.head;
    while (p != nullptr) {
        insert(p->data);
        p = p->next;
    }
    currentPos = head;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T>& _l) {
    if (this != &_l) {
        _emptyList();
        _copy(_l);
    }
    return *this;
}

template<typename T>
bool SingleLinkedList<T>::find(const T& _val) {
    Node* p = head;
    while (p != nullptr) {
        if (p->data == _val) {
            currentPos = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

int main() {
    //SingleLinkedList<int> a;
	SingleLinkedList<int> a{1,2,3,4,5};
	int a_get = a.getCurrentVal();
	std::cout << a_get << std::endl; //测试【取值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
	//SingleLinkedList<char> b;
	SingleLinkedList<char> b{'a','c','e'};
	b.setCurrentVal('g');
	b.printList(); //测试【定义值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
	SingleLinkedList<char> e;
	std::cout << b.isEmpty() << " "
	<< e.isEmpty() << std::endl; //测试【空链表判断】操作是否正确，18分
	SingleLinkedList<double> c1;
	SingleLinkedList<double> c2{1.5,2.0,9.0,4.7};
	SingleLinkedList<double> c3;
	c3 = c2;
	c1.insert(3.0);
	c2.insert(8.8);
	bool f_c3 = c3.find(2.0);
	c3.insert(8.8);
	c1.printList();
	c2.printList();
	c3.printList(); //测试【插入】操作是否正确，每种情况6分
	e.remove();
	c1.remove();
	bool f = c2.find(9.0);
	c2.remove();
	e.printList();
	c1.printList();
	c2.printList(); //测试【删除】操作是否正确，每种情况6分
	return 0;
}
