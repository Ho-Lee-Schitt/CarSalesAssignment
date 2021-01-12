//
// Created by Niall Hughes on 11/01/2021.
//

#include "car_database.hpp"

car_database::car_database()
{
}

void car_database::add_car(const car & new_car)
{
    cars_.push_back(new_car);
}

std::vector<car> car_database::get_cars() const
{
    return cars_;
}
