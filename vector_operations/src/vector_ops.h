#pragma once
#include <vector>
#include <iostream>
#include <algorithm>


namespace task {

    std::vector<int>& operator | (const std::vector<int>& first, const std::vector<int>& second) {
        std::vector<int> res;
        for (size_t i = 0; i < min(first.size(), second.size()); ++i) {
            res.push_back(first[i] | second[i]);
        }
        if (first.size() < second.size()) {
            std::swap(first, second);
        }
        for (size_t i = second.size(); i < first.size(); ++i) {
            res.push_back(first[i]);
        }
    }


}  // namespace task
