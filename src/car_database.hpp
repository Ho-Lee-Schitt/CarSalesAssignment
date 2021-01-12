//
// Created by Niall Hughes on 11/01/2021.
//

#ifndef CARSALESASSIGNMENT_CAR_DATABASE_HPP
#define CARSALESASSIGNMENT_CAR_DATABASE_HPP

#include <vector>

#include "car.hpp"

class car_database
{
public:
    car_database();

    void add_car(car const & new_car);

    std::vector<car> get_cars() const;

private:
    std::vector<car> cars_;
};


#endif //CARSALESASSIGNMENT_CAR_DATABASE_HPP
