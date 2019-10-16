#include <string>
#include <iostream>
#include <list>
#include <sstream>

std::string removeSpaces(const std::string& str) {
    std::string s(str);
    int j = 0;
    int N = s.size();

    for (int i = 0; i < N; ++i) {
        if (s[i] != ' ') {
            s[j] = s[i];
            j++;
        }
    }

    s.resize(j);
    return s;
}

int tokenize(const std::string& str, std::list<std::string>& tokens) {
    std::string num;
    int error = 0;
    int N = str.size();

    for (int i = 0; i < N; ++i) {
        char c = str[i];

        if (isdigit(c)) {
            num += c;
        } else if (isalpha(c)) {
            return 1;
        } else {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }

            std::string token;
            token += c;
            tokens.push_back(token);
        }
    }

    if (!num.empty()) {
        tokens.push_back(num);
        num.clear();
    }

    return 0;
}

class Calculator {
public:
    Calculator(const std::string& expression);

    void next();
    int exp();
    int term();
    int factor();
    int toInt(const std::string& s);
    int err = 0;

private:
    std::list<std::string> mTokens;
    std::string mCurrent;
};

Calculator::Calculator(const std::string& expression) {
    std::string s = removeSpaces(expression);
    err = tokenize(s, mTokens);
    mCurrent = mTokens.front();
}

void Calculator::next() {
    mTokens.pop_front();

    if (!mTokens.empty()) {
        mCurrent = mTokens.front();
    } else {
        mCurrent = std::string();
    }
}

int Calculator::exp() {
    int result = term();

    while (mCurrent == "+" || mCurrent == "-") {
        if (mCurrent == "+") {
            next();

            if (mCurrent.empty()) {
                err = 1;
                return 0;
            }

            result += term();
        }
        if (mCurrent == "-") {
            next();

            if (mCurrent.empty()) {
                err = 1;
                return 0;
            }

            result -= term();
        }
    }

    return result;
}

int Calculator::term() {
    int result = factor();

    while (mCurrent == "*" || mCurrent == "/") {
        if (mCurrent == "*") {
            next();

            if (mCurrent.empty()) {
                err = 1;
                return 0;
            }

            result *= factor();
        }
        if (mCurrent == "/") {
            next();

            if (mCurrent.empty()) {
                err = 1;
                return 0;
            }

            int denominator = factor();

            if (denominator != 0) {
                result /= denominator;
            } else {
                err = 1;
                return 0;
            }
        }
    }

    return result;
}

int Calculator::factor() {
    int result;

    if (mCurrent == "(") {
        next();
        result = exp();
        next();
    } else if (mCurrent == "-") {
        next();

        if (mCurrent.empty()) {
            err = 1;
            return 0;
        }

        result = -toInt(mCurrent);
        next();
    } else {
        result = toInt(mCurrent);
        next();
    }

    return result;
}

int Calculator::toInt(const std::string& s) {
    std::stringstream ss;
    ss << s;
    int x;
    ss >> x;
    return x;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "error";
        return 1;
    }

    std::string expression (argv[1]);
    Calculator calculator(expression);
    int exp = calculator.exp();

    if (calculator.err) {
        std::cout << "error";
        return 1;
    }

    std::cout << exp;

    return 0;
}
