#pragma once
#include <vector>
#include <iostream>


namespace task {

    std::vector<int> operator| (const std::vector<int>& first, const std::vector<int>& second) {
        std::vector<int> res;
        for (size_t i = 0; i < first.size(); ++i) {
            res.push_back(first[i] | second[i]);
        }
        return res;
    }


    std::vector<int> operator& (const std::vector<int>& first, const std::vector<int>& second) {
        std::vector<int> res;
        for (size_t i = 0; i < first.size(); ++i) {
            res.push_back(first[i] & second[i]);
        }
        return res;
    }


    std::vector<double> operator+ (const std::vector<double>& first)  {
        std::vector<double> res;
        for (size_t i = 0; i < first.size(); ++i) {
            res.push_back(+first[i]);
        }
        return res;
    }


    std::vector<double> operator- (const std::vector<double>& first) {
        std::vector<double> res;
        for (size_t i = 0; i < first.size(); ++i) {
            res.push_back(-first[i]);
        }
        return res;
    }


    std::vector<double> operator+ (const std::vector<double>& first, const std::vector<double>& second) {
        std::vector<double> res;
        for (size_t i = 0; i < first.size(); ++i) {
            res.push_back(first[i] + second[i]);
        }
        return res;
    }


    std::vector<double> operator- (const std::vector<double>& first, const std::vector<double>& second) {
        std::vector<double> res;
        for (size_t i = 0; i < first.size(); ++i) {
            res.push_back(first[i] - second[i]);
        }
        return res;
    }


    double operator* (const std::vector<double>& first, const std::vector<double>& second) {
        double res = 0;
        for (size_t i = 0; i < first.size(); ++i) {
            res += first[i] * second[i];
        }
        return res;
    }


    std::vector<double> operator% (const std::vector<double>& first, const std::vector<double>& second) {
        std::vector<double> res;
        res.push_back(first[2] * second[1] - first[1] * second[2]);
        res.push_back(first[0] * second[2] - first[2] * second[0]);
        res.push_back(first[1] * second[0] - first[0] * second[1]);
        return res;
    }


    std::vector<double> operator|| (const std::vector<double>& first, const std::vector<double>& second) {
        std::vector<double> res;
        res.push_back(first[2] * second[1] - first[1] * second[2]);
        res.push_back(first[0] * second[2] - first[2] * second[0]);
        res.push_back(first[1] * second[0] - first[0] * second[1]);
        return res;
    }

}  // namespace task
