#include "thermal_physics_calculation_controller.h"
#include "thermal_physics_calculations.h"
#include <stdio.h>
#include <string.h>

void process_thermal_physics_calculations(char *calculationType)
{
    double mass, latentHeatCapacity;

    if (strcmp(calculationType, "calc_type_latent_heat") == 0)
    {
        scanf("%lf %lf", &mass, &latentHeatCapacity);
        calculate_latent_heat(mass, latentHeatCapacity);
    }

    else if (strcmp(calculationType, "calc_type_sensible_heat") == 0)
    {
        double specificHeatCapacity, temperatureChange;
        scanf("%lf %lf %lf", &mass, &specificHeatCapacity, &temperatureChange);
        calculate_sensible_heat(mass, specificHeatCapacity, temperatureChange);
    }

    else
    {
        fprintf(stderr, "Unknown thermal physics calculation type.\n");
    }
}
