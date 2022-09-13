#include <iostream>
#include <fstream>
#include <string>
#include "weatherFunctions.h"

using std::cin;
using std::cout;
using std::endl;
//using std::string;
using std::ifstream;
using std::invalid_argument;

double** add_cities_from_file(double**& map, size_t& num_cities, size_t& num_days, std::string file_name) {
  ifstream ifs(file_name);

  if (!ifs.is_open()) {
    throw std::invalid_argument("invalid argument");
  }
  size_t extra_cities{};
  size_t days{};

  ifs >> extra_cities;

  ifs >> days;

  unsigned int old_num_cities = num_cities;

  unsigned int old_num_days = num_days;

  if (map == nullptr) {
    num_cities = extra_cities;
    num_days = days;
    map = new double* [num_cities];
    for (size_t i = 0; i < num_cities; i++) {
      map[i] = new double[num_days];
    }

    for (size_t i = 0; i < num_cities; i++) {
      for (size_t j = 0; j < num_days; j++) {
        ifs >> map[i][j];
      }
    }
    ifs.close();
    return map;
  }
  else {
    num_cities += extra_cities;
    num_days = old_num_days;
    if (num_days != days) {
      throw invalid_argument("days in file don't match existing map");
    }
    double** temp = new double* [num_cities];
    for (size_t i = 0; i < num_cities; i++) {
      temp[i] = new double[num_days];
    }

    for (size_t i = 0; i < old_num_cities; i++) {
      for (size_t j = 0; j < num_days; j++) {
        temp[i][j] = map[i][j];
      }
    }

    for (size_t i = 0; i < old_num_cities; i++) {
      delete[] map[i];
    }
    delete[] map;

    for (size_t i = old_num_cities; i < num_cities; i++) {
      for (size_t j = 0; j < num_days; j++) {
        ifs >> temp[i][j];
      }
    }
    ifs.close();
    map = temp;
    return map;
  }

  return nullptr;

}

double get_average_rainfall_between_days_given_city(double** map, size_t num_cities, size_t num_days, size_t start_day, size_t end_day, size_t city_index) {
  double avg_rainfall{};
  int counter{};
  if (city_index >= size_t(num_cities)) {
    throw invalid_argument("index of city cannot be greater than or equal to the number of cities");
  }
  if (map == nullptr) {
    throw invalid_argument("There is no map");
  }
  if ((end_day >= size_t(num_days)) || (end_day < start_day)) {
    throw invalid_argument("The end day cannot be greater than or equal to the total number of days or less than the starting day");
  }
  if (start_day >= size_t(num_days)) {
    throw invalid_argument("start day cannot be greater than or equal to the total number of days");
  }

  for (size_t i = start_day; i < (end_day + 1); i++) {
    avg_rainfall += map[city_index][i];
    counter += 1;
  }
  avg_rainfall /= counter;
  return avg_rainfall;

}

double get_average_rainfall_between_days_all_cities(double** map, size_t num_cities, size_t num_days, size_t start_day, size_t end_day) {
  double all_avg_rainfall{};
  int counter{};
  if (map == nullptr) {
    throw invalid_argument("There is no map");
  }
  if (start_day >= size_t(num_days)) {
    throw invalid_argument("start day cannot be greater than the total number of days");
  }
  if ((end_day >= size_t(num_days)) || (end_day < start_day)) {
    throw invalid_argument("end day cannot be greater than or equal to the total number of days or less than the start day");
  }
  for (size_t i = 0; i < num_cities; i++) {
    for (size_t j = start_day; j < (end_day + 1); j++) {
      all_avg_rainfall += map[i][j];
      counter += 1;
    }
  }
  all_avg_rainfall /= counter;
  return all_avg_rainfall;

}

double get_max_rainfall_all_cities_given_day(double** map, size_t num_cities, size_t num_days, size_t index_max_rainfall_day) {
  if (map == nullptr) {
    throw invalid_argument("There is no map");
  }
  if (num_cities <= 0) {
    throw invalid_argument("The number of cities cannot be less than or equal to 0");
  }
  if (index_max_rainfall_day >= size_t(num_days)) {
    throw invalid_argument("The chosen day cannot be greater than or equal to the total number of days");
  }
  double max_rainfall = map[0][index_max_rainfall_day];
  for (size_t i = 1; i < num_cities; i++) {
    if (max_rainfall < map[i][index_max_rainfall_day]) {
      max_rainfall = map[i][index_max_rainfall_day];
    }
  }
  return max_rainfall;
}

double get_max_rainfall_given_city(double** map, size_t num_cities, size_t num_days, size_t index_max_rainfall_city) {
  if (map == nullptr) {
    throw invalid_argument("There is no map");
  }
  if (num_days <= 0) {
    throw invalid_argument("The number of days cannot be less than or equal to 0");
  }
  if (index_max_rainfall_city >= size_t(num_cities)) {
    throw invalid_argument("The city cannot be greater than or equal to the total number of cities");
  }
  double max_rainfall = map[index_max_rainfall_city][0];
  for (size_t i = 1; i < num_days; i++) {
    if (max_rainfall < map[index_max_rainfall_city][i]) {
      max_rainfall = map[index_max_rainfall_city][i];
    }
  }
  return max_rainfall;
}


void destroy_table(double**& map, size_t num_cities) {
  if (num_cities == 0) {
    throw std::invalid_argument("The number of cities cannot be 0");
  }
  for (size_t i = 0; i < num_cities; i++) {
    delete[] map[i];
  }
  delete[] map;
}