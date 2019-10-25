#ifndef TSP_COST_MATRIX_H
#define TSP_COST_MATRIX_H

#include <vector>
#include <cmath>
#include <functional>
#include <iostream>
#include <algorithm>

#define INF (NAN)

using uint = unsigned int;
using ulong = unsigned long;
using ivec = std::vector<double>;
using Ivec = std::vector<std::vector<double>>;
using ivecpair = std::vector<std::pair<int, int>>;


class TSP_cost_matrix {
public:
    explicit TSP_cost_matrix(const Ivec& cost_matrix) : _cost_matrix(cost_matrix), _num_of_summits(cost_matrix.size()), _low_bound(0) {}

    ulong get_num_of_summits() { return _num_of_summits; }
    double get_elem(int i, int j) { return _cost_matrix[i][j]; }
    ivecpair get_solution() { return _solution; }

    void reduce_col(uint col);
    void reduce_row(uint row);
    void reduce_all_cols();
    void reduce_all_rows();

    bool check_zeroes_for_rows();
    bool check_zeroes_for_cols();
    void find_next_path();
private:
    ulong _num_of_summits;
    double _low_bound;
    Ivec _cost_matrix;
    ivecpair _solution;
};


#endif //TSP_COST_MATRIX_H
