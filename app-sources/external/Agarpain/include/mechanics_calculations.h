#ifndef MECHANICS_CALCULATIONS_H
#define MECHANICS_CALCULATIONS_H

void calculate_weight(double mass, double gravity);

void calculate_velocity(double distance, double time);
void calculate_speed(double distance, double time);
void calculate_acceleration(double velocity, double time);
void calculate_final_velocity(double initial_velocity, double acceleration, double time);
void calculate_final_displacement(double initial_displacement, double initial_velocity, double acceleration, double time);
void calculate_final_velocity_squared(double initial_velocity, double acceleration, double final_displacement, double initial_displacement);
void calculate_average_velocity(double final_velocity, double initial_velocity);

void calculate_force(double mass, double acceleration);

#endif
