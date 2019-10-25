#include "../cost_matrix/cost_matrix.h"


void print_matrix(TSP_cost_matrix matrix) {
    for(uint i = 0; i != matrix.get_num_of_summits(); i++) {
        for(uint j = 0; j != matrix.get_num_of_summits(); j++) {
            std::cout << matrix.get_elem(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

double find_minimum(ivec vec) {
    ivec correct;
    for (auto &elem : vec) {
        if (!std::isnan(elem)) {
            correct.push_back(elem);
        }
    }
    if(std::min_element(correct.begin(), correct.end()) != correct.end()){
        return *std::min_element(correct.begin(), correct.end());
    }
    return NAN;
}

std::vector<int> tsp(Ivec cost_matrix) {
    TSP_cost_matrix Cost_matrix(cost_matrix);
    std::vector<int> Solution;
    for (uint i = 0; i != Cost_matrix.get_num_of_summits() - 1; i++) {
        if(!Cost_matrix.check_zeroes_for_rows()) {
            Cost_matrix.reduce_all_rows();
        }
        if (!Cost_matrix.check_zeroes_for_cols()) {
            Cost_matrix.reduce_all_cols();
        }
        Cost_matrix.find_next_path();
    }
    for (uint i = 0; i != Cost_matrix.get_num_of_summits(); i++) {
        if (uint(Solution.size()) == 0) {
            Solution.push_back(Cost_matrix.get_solution()[0].first);
        }
        for (auto &part : Cost_matrix.get_solution()) {
            if (part.first == Solution.back())
            {
                Solution.push_back(part.second);
                break;
            }
        }
    }
    return Solution;
}

void print_path(std::vector<int> path) {
    for(auto elem : path) {
        std::cout << elem  << " ";
    }
}