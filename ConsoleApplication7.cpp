#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <stdexcept>


class Stack {
private:
    std::array<int, 100> data; 
    int top;

public:
    Stack() : top(-1) {}

   
    void push(int value) {
        if (top >= 99) {
            throw std::overflow_error("stack !");
        }
        data[++top] = value;
    }

   
    int pop() {
        if (top == -1) {
            throw std::underflow_error("stack empty!");
        }
        return data[top--];
    }

  
    bool isEmpty() const {
        return top == -1;
    }
};


int evaluatePostfix(const std::string &expression) {
    Stack stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            stack.push(std::stoi(token));
        } else {
           
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            int result = 0;

            if (token == "+") {
                result = operand1 + operand2;
            } else if (token == "-") {
                result = operand1 - operand2;
            } else if (token == "*") {
                result = operand1 * operand2;
            } else if (token == "/") {
                if (operand2 == 0) {
                    throw std::runtime_error("division by zero error!");
                }
                result = operand1 / operand2;
            } else {
                throw std::runtime_error("Not operator!");
            }

           
            stack.push(result);
        }
    }

    
    if (stack.isEmpty()) {
        throw std::runtime_error("not valid!");
    }

    return stack.pop();
}

int main() {
    std::string expression;

    std::cout << "Enter the value (Example: 2 3 + 4 *): ";
    std::getline(std::cin, expression);

    try {
        int result = evaluatePostfix(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
