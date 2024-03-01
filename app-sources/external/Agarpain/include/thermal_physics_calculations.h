#ifndef THERMAL_PHYSICS_H
#define THERMAL_PHYSICS_H

void calculate_latent_heat(double mass, double latentHeatCapacity);
void calculate_sensible_heat(double mass, double specificHeatCapacity, double temperatureChange);

#endif // THERMAL_PHYSICS_H
