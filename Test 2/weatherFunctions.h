#ifndef WEATHERFUNCTIONS_H
#define WEATHERFUNCTIONS_H
// add function declarations/prototypes
double** add_cities_from_file(double**& map, size_t &days, size_t &cities, std::string filename);

void destroy_table(double**& map, size_t cities);

double get_average_rainfall_between_days_given_city(double** map, size_t cities, size_t days, size_t start_day, size_t end_day, size_t city);

double get_average_rainfall_between_days_all_cities(double** map, size_t cities, size_t days, size_t start_day, size_t end_day);

double get_max_rainfall_all_cities_given_day(double** map, size_t cities, size_t days, size_t day);

double get_max_rainfall_given_city(double** map, size_t cities, size_t days, size_t city);

#endif