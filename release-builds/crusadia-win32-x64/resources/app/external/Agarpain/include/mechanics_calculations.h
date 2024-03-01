#ifndef MECHANICS_CALCULATIONS_H
#define MECHANICS_CALCULATIONS_H

/*
* Existence
*/
void calculate_weight(double mass, double gravity);

/*
* Motion
*/
void calculate_velocity(double distance, double time);
void calculate_speed(double distance, double time);
void calculate_acceleration(double velocity, double time);
void calculate_final_velocity(double initial_velocity, double acceleration, double time);
void calculate_final_displacement(double initial_displacement, double initial_velocity, double acceleration, double time);
void calculate_final_velocity_squared(double initial_velocity, double acceleration, double final_displacement, double initial_displacement);
void calculate_average_velocity(double final_velocity, double initial_velocity);

/*
* Interaction
*/
void calculate_force(double mass, double acceleration);

#endif // MECHANICS_CALCULATIONS_H
