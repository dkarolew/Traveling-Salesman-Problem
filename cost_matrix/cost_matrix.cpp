#include "cost_matrix.h"
#include "../help_functions/help_functions.h"


void TSP_cost_matrix::reduce_row(uint row) {
    double min = find_minimum(_cost_matrix[row]);
    for(auto &elem : _cost_matrix[row]) {
        elem -= min;
    }
    _low_bound += min;
}

void TSP_cost_matrix::reduce_col(uint col) {
    ivec column;
    for(uint i = 0; i != _cost_matrix.size(); i++) {
        column.push_back(_cost_matrix[i][col]);
    }
    double min = find_minimum(column);
    for (uint i = 0; i != _cost_matrix.size(); ++i) {
        _cost_matrix[i][col] -= min;
    }
    _low_bound += min;
}

void TSP_cost_matrix::reduce_all_cols() {
    for(uint i = 0; i != _cost_matrix.size(); i++) {
        reduce_col(i);
    }
}

void TSP_cost_matrix::reduce_all_rows() {
    for(uint i = 0; i != _cost_matrix.size(); i++) {
        reduce_row(i);
    }
}

void TSP_cost_matrix::find_next_path() {
    double min_row_elem, min_col_elem;
    Ivec data;
    ivec cross_line;
    ivec is_zero;
    double current_max = -1;
    std::pair<int, int> peak;
    if (uint(_solution.size()) == _cost_matrix.size() - 2) {
        for (uint i = 0; i != _cost_matrix.size(); i++) {
            for (uint j = 0; j != _cost_matrix.size(); j++) {
                if (_cost_matrix[i][j] == 0) {
                    for (uint k = 0; k != _cost_matrix.size(); k++) {
                        if (_cost_matrix[i][k] == 0 and k != j) {
                            is_zero.push_back(0);
                        }
                        if (_cost_matrix[k][j] == 0 and k != i) {
                            is_zero.push_back(0);
                        }
                    }
                    if (is_zero.size() != 2) {
                        peak = std::make_pair(i + 1, j + 1);
                        _solution.push_back(peak);
                    }
                    is_zero.clear();
                }
            }
        }
    }
    else {
        for (uint i = 0; i != _cost_matrix.size(); i++) {
            for (uint j = 0; j != _cost_matrix.size(); j++) {
                if (_cost_matrix[i][j] == 0) {
                    for (uint k = 0; k != _cost_matrix.size(); k++) {
                        if (k != j) {
                            cross_line.push_back(_cost_matrix[i][k]);
                        }
                    }
                    min_row_elem = find_minimum(cross_line);
                    cross_line.clear();
                    for (uint k = 0; k != _cost_matrix.size(); k++) {
                        if (k != i) {
                            cross_line.push_back(_cost_matrix[k][j]);
                        }
                    }
                    min_col_elem = find_minimum(cross_line);
                    cross_line.clear();
                    data.push_back({double(i), double(j), min_col_elem + min_row_elem});
                }
            }
        }
        for (auto &part : data) {
            if (part[2] > current_max) {
                current_max = part[2];
                peak = std::make_pair(part[0] + 1, part[1] + 1);
            }
        }
        _solution.push_back(peak);
        for (auto &cell_row_index : _cost_matrix[peak.first - 1]) {
            cell_row_index = INF;
        }
        for (uint i = 0; i != _cost_matrix.size(); i++) {
            _cost_matrix[i][peak.second - 1] = INF;
        }
        _cost_matrix[peak.second - 1][peak.first - 1] = INF;
    }
}

bool TSP_cost_matrix::check_zeroes_for_rows() {
    ivec counter;
    for (auto row : _cost_matrix) {
        for (auto elem : row) {
            if (std::isnan(elem)) {
                counter.push_back(1);
            }
            if (counter.size() == _cost_matrix.size()) {
                counter.clear();
                break;
            }
        }
        counter.clear();
        if (!(std::find(row.begin(), row.end(), 0) != row.end())) {
            return false;
        }
    }
    return true;
}

bool TSP_cost_matrix::check_zeroes_for_cols() {
    ivec counter;
    ivec zeroes (_cost_matrix.size(), 0);
    Ivec transposed_matrix (_cost_matrix.size(), zeroes);
    for(uint i = 0; i != _cost_matrix.size(); i++) {
        for(uint j = 0; j != _cost_matrix.size(); j++) {
            transposed_matrix[i][j] = _cost_matrix[j][i];
        }
    }
    for(auto col : transposed_matrix) {
        for(auto elem : col) {
            if(std::isnan(elem)) {
                counter.push_back(1);
            }
            if(counter.size() == _cost_matrix.size()) {
                counter.clear();
                break;
            }
        }
        counter.clear();
        if(!(std::find(col.begin(), col.end(), 0) != col.end())) {
            return false;
        }
    }
    return true;
}







