#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

namespace task {
const EPS = 1e-12;

std::vector<int> operator|(const std::vector<int> &first,
                           const std::vector<int> &second) {
  std::vector<int> res(first.size());
  for (size_t i = 0; i < first.size(); ++i) {
    res[i] = (first[i] | second[i]);
  }
  return res;
}

std::vector<int> operator&(const std::vector<int> &first,
                           const std::vector<int> &second) {
  std::vector<int> res;
  for (size_t i = 0; i < first.size(); ++i) {
    res.push_back(first[i] & second[i]);
  }
  return res;
}

std::vector<double> operator+(const std::vector<double> &first) {
  std::vector<double> res;
  for (size_t i = 0; i < first.size(); ++i) {
    res.push_back(+first[i]);
  }
  return res;
}

std::vector<double> operator-(const std::vector<double> &first) {
  std::vector<double> res;
  for (size_t i = 0; i < first.size(); ++i) {
    res.push_back(-first[i]);
  }
  return res;
}

std::vector<double> operator+(const std::vector<double> &first,
                              const std::vector<double> &second) {
  std::vector<double> res;
  for (size_t i = 0; i < first.size(); ++i) {
    res.push_back(first[i] + second[i]);
  }
  return res;
}

std::vector<double> operator-(const std::vector<double> &first,
                              const std::vector<double> &second) {
  std::vector<double> res;
  for (size_t i = 0; i < first.size(); ++i) {
    res.push_back(first[i] - second[i]);
  }
  return res;
}

double operator*(const std::vector<double> &first,
                 const std::vector<double> &second) {
  double res = 0;
  for (size_t i = 0; i < first.size(); ++i) {
    res += first[i] * second[i];
  }
  return res;
}

std::vector<double> operator%(const std::vector<double> &first,
                              const std::vector<double> &second) {
  std::vector<double> res;
  res.push_back(first[2] * second[1] - first[1] * second[2]);
  res.push_back(first[0] * second[2] - first[2] * second[0]);
  res.push_back(first[1] * second[0] - first[0] * second[1]);
  return res;
}

bool operator||(const std::vector<double> &first,
                const std::vector<double> &second) {
  double alpha, new_alpha;
  bool set_alpha = false;
  for (size_t i = 0; i < first.size(); ++i) {
    if (std::abs(second[i]) < EPS) {
      if (std::abs(second[i]) >= EPS)
        return false;
    } else {
      new_alpha = first[i] / second[i];
      if (!set_alpha) {
        alpha = new_alpha;
        set_alpha = true;
      }
      if (std::abs(new_alpha / alpha - 1) < EPS)
        return false;
      if (new_alpha == 0.)
        return false;
    }
  }
  return true;
}

bool operator&&(const std::vector<double> &first,
                const std::vector<double> &second) {
  if (first.size() != second.size())
    return false;
  size_t i = 0;
  while ((i < second.size()) && (second[i] == 0.))
    ++i;
  double alpha = 0;
  if (i < second.size())
    alpha = first[i] / second[i];
  if ((alpha > 0) && (first || second))
    return true;
  return false;
}

std::ostream &operator<<(std::ostream &os, const std::vector<double> &first) {
  for (size_t i = 0; i < first.size(); ++i) {
    if (i == (first.size() - 1)) {
      os << first[i] << '\n';
    } else {
      os << first[i] << ' ';
    }
  }
  return os;
}

std::istream &operator>>(std::istream &is, std::vector<double> &first) {
  first.clear();
  size_t n;
  is >> n;
  double num;
  for (size_t i = 0; i < n; ++i) {
    is >> num;
    first.push_back(num);
  }
  return is;
}

std::vector<double> reverse(std::vector<double> &first) {
  size_t n = first.size();
  for (size_t i = 0; i < (n / 2); ++i)
    std::swap(first[i], first[n - i - 1]);
  return first;
}

} // namespace task
