#include <iostream>
#include <vector>

#include "cost_matrix/cost_matrix.h"
#include "help_functions/help_functions.h"


int main() {

    Ivec cost_matrix{
            {NAN, 10, 8, 19, 12},
            {10, NAN, 20, 6, 3},
            {8, 20, NAN, 4, 2},
            {19, 6, 4, NAN, 7},
            {12, 3, 2, 7, NAN}
    };

    std::vector<int> best_path = tsp(cost_matrix);
    print_path(best_path);

    return 0;
}

