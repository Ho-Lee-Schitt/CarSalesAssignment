//
// Created by Niall Hughes on 11/01/2021.
//

#ifndef CARSALESASSIGNMENT_CAR_HPP
#define CARSALESASSIGNMENT_CAR_HPP

#include <string>
#include <ctime>

class car
{
public:

    ~car(){}

    car(std::string car_make,
        int const & car_value);

    std::string get_car_make() const;
    int get_car_value() const;
    int get_commision() const;
    time_t get_sale_date() const;

private:
    std::string  car_make_;
    int  car_value_;
    int  commision_;
    time_t sale_date_;

    static int calculate_commision(int const car_value);
};


#endif //CARSALESASSIGNMENT_CAR_HPP
