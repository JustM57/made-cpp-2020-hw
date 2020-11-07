#include <functional>
#include <iostream>

typedef std::function<int(int)> Op;

Op compose(size_t n, Op ops[]) {
  Op res = [](int x) -> int { return x; };
  for (ssize_t i = n - 1; i >= 0; --i) {
    Op foo = ops[i];
    Op compose_two = [res, foo](int x) { return foo(res(x)); };
    res = compose_two;
  }
  return res;
}

int main() {
  /// Simple tests:

  Op op1 = [](int x) -> int { return x + 1; };

  auto op2 = [](int p) -> Op { return [p](int x) { return p * x; }; };

  {
    Op ops[0] = {};
    if (compose(0, ops)(2) != 2) {
      std::cout << "FAILED AT TEST 0" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 0" << std::endl;
  }

  {
    Op ops[2] = {op1, op1};
    if (compose(2, ops)(2) != 4) {
      std::cout << "FAILED AT TEST 0.1" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 0.1" << std::endl;
  }

  {
    Op ops[3] = {op1, op1, op1};
    if (compose(3, ops)(2) != 5) {
      std::cout << "FAILED AT TEST 0.2" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 0.2" << std::endl;
  }

  {
    Op ops[2] = {
        op1,
        op2(2),
    };
    if (compose(2, ops)(2) != 5) {
      std::cout << "FAILED AT TEST 0.3" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 0.3" << std::endl;
  }

  {
    Op ops[4] = {op1, op2(2), op1, op2(2)};
    if (compose(4, ops)(2) != 11) {
      std::cout << "FAILED AT TEST 1" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 1" << std::endl;
  }

  {
    Op ops[8] = {op1, op2(2), op1, op1, op1, op2(2), op2(2), op1};
    if (compose(8, ops)(5) != 55) {
      std::cout << "FAILED AT TEST 2" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 2" << std::endl;
  }

  {
    Op ops[1] = {op1};
    if (compose(1, ops)(3) != 4) {
      std::cout << "FAILED AT TEST 3" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 3" << std::endl;
  }

  {
    Op ops[0] = {};
    if (compose(0, ops)(4) != 4) {
      std::cout << "FAILED AT TEST 4" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 4" << std::endl;
  }

  {
    Op ops[4] = {op2(2), op2(3), op2(4), op2(5)};
    if (compose(4, ops)(1) != 120) {
      std::cout << "FAILED AT TEST 5" << std::endl;
      return 0;
    } else
      std::cout << "PASSED TEST 5" << std::endl;
  }
}