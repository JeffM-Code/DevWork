#include "calculations_controller.h"
#include "mechanics_calculation_controller.h"
#include "thermal_physics_calculation_controller.h"
#include <stdio.h>
#include <string.h>

void process_calculations()
{
    char calculationType[100];

    while (scanf_s("%s", calculationType, (unsigned int)(sizeof(calculationType) / sizeof(calculationType[0]) - 1)) != EOF)
    {
        if (strstr(calculationType, "calc_type_weight") != NULL
        || strstr(calculationType, "calc_type_velocity") != NULL
        || strstr(calculationType, "calc_type_speed") != NULL
        || strstr(calculationType, "calc_type_acceleration") != NULL
        || strstr(calculationType, "calc_type_final_velocity") != NULL
        || strstr(calculationType, "calc_type_final_displacement") != NULL
        || strstr(calculationType, "calc_type_final_velocity_squared") != NULL
        || strstr(calculationType, "calc_type_average_velocity") != NULL
        || strstr(calculationType, "calc_type_force") != NULL)
        {
            process_mechanics_calculations(calculationType);
        }
        else if (strstr(calculationType, "calc_type_latent_heat") != NULL
        || strstr(calculationType, "sensible_heat") != NULL)
        {
            process_thermal_physics_calculations(calculationType);
        }
        else
        {
            fprintf(stderr, "Unknown calculation domain.\n");
        }
    }
}
