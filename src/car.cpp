//
// Created by Niall Hughes on 11/01/2021.
//

#include "car.hpp"

#include <utility>

car::car(std::string  car_make,
         const int & car_value)
    :
        car_make_(std::move(car_make)),
        car_value_(car_value),
        commision_(calculate_commision(car_value_)),
        sale_date_(time(0))
{
}

int car::calculate_commision(const int car_value)
{
    double commision = 0;
    if(car_value < 10000)
    {
        commision = car_value * 0.0015;
    }
    else if (car_value >= 10000 && car_value <= 20000)
    {
        commision = car_value * 0.0025;
    }
    else if (car_value >= 20001 && car_value <= 40000)
    {
        commision = car_value * 0.005;
    }
    else if (car_value > 40000)
    {
        commision = car_value * 0.007;
    }

    return (int)commision;
}

std::string car::get_car_make() const
{
    return car_make_;
}

int car::get_car_value() const
{
    return car_value_;
}

int car::get_commision() const
{
    return commision_;
}

time_t car::get_sale_date() const
{
    return sale_date_;
}
