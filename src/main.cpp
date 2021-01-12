#include <algorithm>
#include <iostream>
#include <string>

#include "car.hpp"
#include "car_database.hpp"

int get_valid_int_retry(std::string const & int_name, std::string const & message)
{
    do
    {
        std::cout << message << std::endl;
        int option = 0;
        std::string option_str = "";
        std::cin >> option_str;

        try
        {
            option = std::stoi(option_str);
        }
        catch (std::invalid_argument const &)
        {
            std::cout << "Error: " << int_name << " \"" << option_str << "\" is not a number!" << std::endl;
            continue;
        }
        catch (std::out_of_range const &)
        {
            std::cout << "Error: " << int_name << " \"" << option_str << "\" is too large!" << std::endl;
            continue;
        }

        return option;
    } while (true);
}

int get_main_menu_option()
{
    int option_num = 1;
    std::string const print_format = "%-10i%-10s\n";

    printf("\nCar Sales control system\n");
    printf("%-10s%-10s\n", "Option", "Action");
    printf(print_format.c_str(), option_num++, "Record a car sale");
    printf(print_format.c_str(), option_num++, "Display all car sales in date order");
    printf(print_format.c_str(), option_num++, "Display all car sales greater than a specified amount");
    printf(print_format.c_str(), option_num++, "Display all commissions in date order");
    printf(print_format.c_str(), option_num++, "Display the maximum car sale");
    printf(print_format.c_str(), option_num++, "Display the total commission earned so far");
    printf(print_format.c_str(), option_num++, "Display all car sales for a particular make");
    printf(print_format.c_str(), option_num++, "Exit");

    int option = get_valid_int_retry("Option", "Your choice:>>");

    if (option < 1 || option > 8)
    {
        throw std::runtime_error("Error: Option is invalid!");
    }

    return option;
}

void record_car(car_database & car_db)
{
    int car_value = get_valid_int_retry("Car Value", "Please enter the value of the car sale (a whole number of \x9Cs):");
    std::string car_make = "";

    std::cout << "Please enter a make: [Ford, Mazda, Lada, Nissan]:" << std::endl;
    std:: cin >> car_make;

    car new_car(car_make, car_value);

    car_db.add_car(new_car);
}

struct date_comp
{
    inline bool operator() (const car& a, const car& b)
    {
        return std::difftime(a.get_sale_date(), b.get_sale_date()) > 0;
    }
};

void list_car_sales(car_database & car_db)
{
    std::cout << "List of all car sales in date order" << std::endl;
    auto cars = car_db.get_cars();

    std::sort(cars.begin(), cars.end(), date_comp());

    for (auto car : cars)
    {
        std::cout << car.get_car_make() << ": \x9C" << car.get_car_value() << std::endl;
    }
}

void list_car_sales_over_value(car_database & car_db)
{
    int car_value = get_valid_int_retry("Car Value", "Please enter a threshold value (a whole number of \x9Cs)");
    std::cout << "List of all car sales over \x9C" << car_value << std::endl;
    auto cars = car_db.get_cars();

    std::sort(cars.begin(), cars.end(), date_comp());

    for (auto car : cars)
    {
        if (car.get_car_value() > car_value)
        {
            std::cout << car.get_car_make() << ": \x9C" << car.get_car_value() << std::endl;
        }
    }
}

void list_commision_sales(car_database & car_db)
{
    std::cout << "List of commissions earned to date:" << std::endl;
    auto cars = car_db.get_cars();

    std::sort(cars.begin(), cars.end(), date_comp());
    int i = 1;
    for (auto car : cars)
    {
        std::cout << "Commission " << i++ << " has value of \x9C" << car.get_commision() << std::endl;
    }
}

struct car_value_comp
{
    inline bool operator() (const car& a, const car& b)
    {
        return a.get_car_value() < b.get_car_value();
    }
};

void get_max_car(car_database & car_db)
{
    auto cars = car_db.get_cars();

    auto const max_car = std::max_element(cars.begin(), cars.end(), car_value_comp());

    std::cout << "The maximum car sale to date is \x9C" << max_car->get_car_value() << std::endl;
}


void get_total_commision(car_database & car_db)
{
    auto cars = car_db.get_cars();
    int total_commision = 0;
    for (auto car : cars)
    {
        total_commision += car.get_commision();
    }

    std::cout << "The total commission earned to date is \x9C" << total_commision << std::endl;
}

void get_car_makes(car_database & car_db)
{
    std::cout << "Please enter a make: [Ford, Mazda, Lada, Nissan]:" << std::endl;
    std::string car_make = "";
    std::cin >> car_make;
    auto cars = car_db.get_cars();

    std::sort(cars.begin(), cars.end(), date_comp());

    std::cout << "A list of all " << car_make << " sales:" << std::endl;

    for (auto car : cars)
    {
        if (car.get_car_make() == car_make)
        {
            std::cout << "\x9C" << car.get_car_value() << std::endl;
        }
    }
}

int main()
{
    std::cout << "DEMO APP FOR EXAMPLE PURPOSES. THERE MAY BE BUGS." << std::endl;
    auto * cars_db = new car_database;

    int option = 0;
    while (option != 8)
    {
        try
        {
            option = get_main_menu_option();
        }
        catch (std::runtime_error const & e)
        {
            std::cout << e.what() << std::endl;
            continue;
        }

        switch (option)
        {
            case 1:
            {
                record_car(*cars_db);
                break;
            }
            case 2:
            {
                list_car_sales(*cars_db);
                break;
            }
            case 3:
            {
                list_car_sales_over_value(*cars_db);
                break;
            }
            case 4:
            {
                list_commision_sales(*cars_db);
                break;
            }
            case 5:
            {
                get_max_car(*cars_db);
                break;
            }
            case 6:
            {
                get_total_commision(*cars_db);
                break;
            }
            case 7:
            {
                get_car_makes(*cars_db);
                break;
            }
        }
    }
    return 0;
}
