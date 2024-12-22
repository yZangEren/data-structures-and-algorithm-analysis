#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <sstream>
class Calculator
{
private:
    // 判断是否为运算符
    bool isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // 获取运算符优先级
    int getPriority(char op)
    {
        if (op == '*' || op == '/')
            return 2;
        if (op == '+' || op == '-')
            return 1;
        return 0;
    }

    // 执行运算
    double calculate(double a, double b, char op)
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Division by zero");
            return a / b;
        default:
            throw std::runtime_error("Invalid operator");
        }
    }

public:
    double evaluate(const std::string &expr)
    {
        std::stack<double> nums;
        std::stack<char> ops;
        std::string number;
        bool expectNumber = true;
        for (size_t i = 0; i < expr.length(); i++)
        {
            char c = expr[i];
            if (c == ' ')
                continue;
            // 处理数字（包括科学计数法和负数）
            if (isdigit(c) || c == '.' ||
                (c == '-' && expectNumber && i + 1 < expr.length() &&
                 (isdigit(expr[i + 1]) || expr[i + 1] == '.')))
            {
                number = "";
                if (c == '-')
                {
                    number += c;
                    i++;
                }

                bool hasE = false;
                bool hasDecimal = false;

                while (i < expr.length())
                {
                    c = expr[i];
                    if (isdigit(c))
                    {
                        number += c;
                    }
                    else if (c == '.' && !hasDecimal && !hasE)
                    {
                        number += c;
                        hasDecimal = true;
                    }
                    else if ((c == 'e' || c == 'E') && !hasE)
                    {
                        number += c;
                        hasE = true;
                        // 检查科学计数法的符号
                        if (i + 1 < expr.length() && (expr[i + 1] == '+' || expr[i + 1] == '-'))
                        {
                            number += expr[i + 1];
                            i++;
                        }
                    }
                    else
                    {
                        i--;
                        break;
                    }
                    i++;
                }
                try
                {
                    nums.push(std::stod(number));
                }
                catch (...)
                {
                    throw std::runtime_error("Invalid number format");
                }
                expectNumber = false;
                continue;
            }
            // 处理左括号
            if (c == '(')
            {
                if (!expectNumber && !ops.empty() && ops.top() != '(')
                {
                    throw std::runtime_error("Invalid expression");
                }
                ops.push(c);
                expectNumber = true;
                continue;
            }
            // 处理右括号
            if (c == ')')
            {
                if (expectNumber || nums.empty())
                {
                    throw std::runtime_error("Invalid expression");
                }

                while (!ops.empty() && ops.top() != '(')
                {
                    if (nums.size() < 2)
                    {
                        throw std::runtime_error("Invalid expression");
                    }
                    double b = nums.top();
                    nums.pop();
                    double a = nums.top();
                    nums.pop();
                    nums.push(calculate(a, b, ops.top()));
                    ops.pop();
                }

                if (ops.empty() || ops.top() != '(')
                {
                    throw std::runtime_error("Mismatched parentheses");
                }
                ops.pop();
                continue;
            }
            // 处理运算符
            if (isOperator(c))
            {
                if (expectNumber && c != '-')
                {
                    throw std::runtime_error("Invalid expression");
                }

                if (expectNumber && c == '-')
                {
                    nums.push(0); // 处理开头的负号
                }
                while (!ops.empty() && ops.top() != '(' &&
                       getPriority(ops.top()) >= getPriority(c))
                {
                    if (nums.size() < 2)
                    {
                        throw std::runtime_error("Invalid expression");
                    }
                    double b = nums.top();
                    nums.pop();
                    double a = nums.top();
                    nums.pop();
                    nums.push(calculate(a, b, ops.top()));
                    ops.pop();
                }
                ops.push(c);
                expectNumber = true;
                continue;
            }
            throw std::runtime_error("Invalid character");
        }
        if (expectNumber)
        {
            throw std::runtime_error("Invalid expression");
        }
        while (!ops.empty())
        {
            if (ops.top() == '(')
            {
                throw std::runtime_error("Mismatched parentheses");
            }
            if (nums.size() < 2)
            {
                throw std::runtime_error("Invalid expression");
            }
            double b = nums.top();
            nums.pop();
            double a = nums.top();
            nums.pop();
            nums.push(calculate(a, b, ops.top()));
            ops.pop();
        }
        if (nums.size() != 1)
        {
            throw std::runtime_error("Invalid expression");
        }
        return nums.top();
    }
};