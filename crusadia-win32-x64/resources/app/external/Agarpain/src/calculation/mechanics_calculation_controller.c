#include "mechanics_calculation_controller.h"
#include "mechanics_calculations.h"
#include <stdio.h>
#include <string.h>

// Adjusted to accept and use calculationType
void process_mechanics_calculations(char *calculationType)
{
    double mass, acceleration, gravity, distance, time, initial_velocity, final_velocity,
        initial_displacement, final_displacement;

    if (strcmp(calculationType, "calc_type_weight") == 0)
    {
        scanf_s("%lf %lf", &mass, &gravity);
        calculate_weight(mass, gravity);
    }
    else if (strcmp(calculationType, "calc_type_velocity") == 0)
    {
        scanf_s("%lf %lf", &distance, &time);
        calculate_velocity(distance, time);
    }
    else if (strcmp(calculationType, "calc_type_speed") == 0)
    {
        scanf_s("%lf %lf", &distance, &time);
        calculate_speed(distance, time);
    }
    else if (strcmp(calculationType, "calc_type_acceleration") == 0)
    {
        scanf_s("%lf %lf", &distance, &time);
        calculate_acceleration(distance, time);
    }
    else if (strcmp(calculationType, "calc_type_final_velocity") == 0)
    {
        scanf_s("%lf %lf %lf", &initial_velocity, &acceleration, &time);
        calculate_final_velocity(initial_velocity, acceleration, time);
    }
    else if (strcmp(calculationType, "calc_type_final_displacement") == 0)
    {
        scanf_s("%lf %lf %lf %lf", &initial_displacement, &initial_velocity, &acceleration, &time);
        calculate_final_displacement(initial_displacement, initial_velocity, acceleration, time);
    }
    else if (strcmp(calculationType, "calc_type_final_velocity_squared") == 0)
    {
        scanf_s("%lf %lf %lf %lf", &initial_velocity, &acceleration, &final_displacement, &initial_displacement);
        calculate_final_velocity_squared(initial_velocity, acceleration, final_displacement, initial_displacement);
    }
    else if (strcmp(calculationType, "calc_type_average_velocity") == 0)
    {
        scanf_s("%lf %lf", &final_velocity, &initial_velocity);
        calculate_average_velocity(final_velocity, initial_velocity);
    }
    else if (strcmp(calculationType, "calc_type_force") == 0)
    {
        scanf_s("%lf %lf", &mass, &acceleration);
        calculate_force(mass, acceleration);
    }
    else
    {
        fprintf(stderr, "Unknown mechanics calculation type\n");
    }
}
