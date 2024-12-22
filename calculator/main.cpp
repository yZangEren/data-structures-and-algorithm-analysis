#include "expression_evaluator.h"
#include <iomanip>
#include <vector>
struct TestCase
{
    std::string expression;
    bool expectSuccess;
    double expectedResult;
};
void runTests()
{
    std::vector<TestCase> testCases = {
        // 基本四则运算测试
        {"1+1", true, 2.0},
        {"2-1", true, 1.0},
        {"2*3", true, 6.0},
        {"6/2", true, 3.0},

        // 括号测试
        {"(1+1)*2", true, 4.0},
        {"((1+1)*2)", true, 4.0},
        {"(1+(2*3))", true, 7.0},

        // 小数测试
        {"1.5+2.5", true, 4.0},
        {"3.14*2", true, 6.28},

        // 负数测试
        {"-1+2", true, 1.0},
        {"1+-2", true, -1.0},
        {"1+(-2)", true, -1.0},

        // 科学计数法测试
        {"1e2+1", true, 101.0},
        {"-1e-2+1", true, 0.99},
        {"1.5e2*2", true, 300.0},

        // 复杂表达式测试
        {"1+2*3+4", true, 11.0},
        {"(1+2)*(3+4)", true, 21.0},
        {"-1.5e2+2.5e1*(3-1)", true, -100.0},

        // 非法表达式测试
        {"1++1", false, 0.0},
        {"1+(2", false, 0.0},
        {"1+2)", false, 0.0},
        {"1+2+", false, 0.0},
        {"+1+2", false, 0.0},
        {"1/0", false, 0.0},
        {"1+()", false, 0.0},
        {"1+2**3", false, 0.0},
        {"1e2e3", false, 0.0}};
    Calculator calc;
    int passedTests = 0;
    int totalTests = testCases.size();
    std::cout << "开始运行测试用例：" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    for (size_t i = 0; i < testCases.size(); i++)
    {
        const auto &test = testCases[i];
        std::cout << "\n测试 #" << (i + 1) << ": " << test.expression << std::endl;

        try
        {
            double result = calc.evaluate(test.expression);

            if (!test.expectSuccess)
            {
                std::cout << "❌ 失败：期望非法表达式，但得到结果: " << result << std::endl;
                continue;
            }

            if (std::abs(result - test.expectedResult) < 1e-10)
            {
                std::cout << "✅ 通过：结果 = " << result << std::endl;
                passedTests++;
            }
            else
            {
                std::cout << "❌ 失败：期望 " << test.expectedResult
                          << "，但得到 " << result << std::endl;
            }
        }
        catch (const std::runtime_error &e)
        {
            if (test.expectSuccess)
            {
                std::cout << "❌ 失败：期望合法表达式，但抛出异常: " << e.what() << std::endl;
            }
            else
            {
                std::cout << "✅ 通过：正确识别非法表达式" << std::endl;
                passedTests++;
            }
        }
    }
    std::cout << "\n测试总结：" << std::endl;
    std::cout << "总测试数: " << totalTests << std::endl;
    std::cout << "通过测试: " << passedTests << std::endl;
    std::cout << "通过率: " << (passedTests * 100.0 / totalTests) << "%" << std::endl;
}

int main()
{
    runTests();

    // 交互式测试
    std::cout << "\n现在进入交互式测试模式。输入表达式（输入'q'退出）：" << std::endl;

    Calculator calc;
    std::string expr;
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, expr);

        if (expr == "q")
            break;

        try
        {
            double result = calc.evaluate(expr);
            std::cout << result << std::endl;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << "ILLEGAL" << std::endl;
        }
    }

    return 0;
}