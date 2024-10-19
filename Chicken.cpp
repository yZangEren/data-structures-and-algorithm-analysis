#include <iostream>
#include <cstring>

class Chicken
{
private:
    int age = 24;
    char* name = nullptr;
public:
    Chicken() {};
    Chicken(int _age) : age(_age) {};
    Chicken(int _age, const char* _name) : age(_age)
    {
        int len = strlen(_name) + 1;
        name = new char[len];
        for (int i = 0; i < len; i++)
            name[i] = _name[i];
    };
    Chicken(const Chicken& other) : age(other.age), name(nullptr) {
        if (other.name != nullptr) {
            int len = strlen(other.name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = other.name[i];
        }
    }
    ~Chicken()
    {
        if (name != nullptr)
            delete[] name;
    };
    void setAge(int _age)
    {
        age = _age;
    };
    void setName(const char* _name)
    {
        if (name != nullptr) {
            delete[] name;
        }
        int len = strlen(_name) + 1;
        name = new char[len];
        for (int i = 0; i < len; i++)
            name[i] = _name[i];
    };
    void makeEmpty()
    {
        age = 0;
        if (name != nullptr)
            delete[] name;
        name = nullptr;
    };
    Chicken& operator=(const Chicken & _l)
    {
        if (this == &_l)
            return *this;
        makeEmpty();
        age = _l.age;
        int len = strlen(_l.name) + 1;
        name = new char[len];
        for (int i = 0; i < len; i++)
            name[i] = _l.name[i];
        return *this;
    };

    const char* getName() const
    {
        return name;
    };

    const int& getAge() const
    {
        return age;
    };
};

int main() {
    auto print = [](const Chicken& c) {
        std::cout << "Hi, everyone! My name is " << c.getName()
            << ", I am " << c.getAge() << " years old." << std::endl;
        };

    Chicken c(24, "Kunkun");
    print(c);

    Chicken d;
    d = c;
    print(d); // 测试赋值运算符是否正确

    Chicken a = c;
    print(a); // 测试赋值构造函数是否正确

    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d); // 测试是否为深度复制

    Chicken b;
    b = d = c;
    print(b);
    print(d); // 测试连续赋值功能

    return 0;
}
