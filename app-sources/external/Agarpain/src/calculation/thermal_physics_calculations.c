#include "thermal_physics_calculations.h"
#include <stdio.h>

void calculate_latent_heat(double mass, double latentHeatCapacity)
{
    double latentHeat = mass * latentHeatCapacity;
    printf("Latent Heat: %f Joules\n", latentHeat);
    fflush(stdout);
}

void calculate_sensible_heat(double mass, double specificHeatCapacity, double temperatureChange)
{
    double sensibleHeat = mass * specificHeatCapacity * temperatureChange;
    printf("Sensible Heat: %f Joules\n", sensibleHeat);
    fflush(stdout);
}