#ifndef TSP_HELP_FUNCTIONS_H
#define TSP_HELP_FUNCTIONS_H


void print_matrix(TSP_cost_matrix matrix);

double find_minimum(ivec vec);

std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);

void print_path(std::vector<int> path);


#endif //TSP_HELP_FUNCTIONS_H
