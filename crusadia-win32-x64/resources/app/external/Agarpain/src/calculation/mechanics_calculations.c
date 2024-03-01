#include "mechanics_calculations.h"
#include <stdio.h>

/*
********************************************************************

Mechanics

********************************************************************
*/

/*

* Existence

*/
/*
Weight:

Eq. i: W = m * g

W - Weight
m - Mass
g - Gravity

*/
// Eq. i
void calculate_weight(double mass, double gravity)
{
    double weight = mass * gravity;
    printf("Weight: %f Newtons\n", weight);
    fflush(stdout);
}

/*

* Motion

*/

/*
Velocity:

Eq. i: v = s / t

v - Velocity
s - Displacement
t - Time

Eq. ii: avg_v = delta_s / delta_t

avg_v - Average velocity
delta_s - Change in distance
delta_t - Change in time

Eq. iii: vector_v = dvector_s / dt

vector_v - Velocity vector
dvector_s - Change in distance vector
dt - Change in time

*/
// Eq. i
void calculate_velocity(double distance, double time)
{
    if (time == 0)
    {
        printf("Error: Time cannot be zero.\n");
        fflush(stdout);
        return;
    }
    double velocity = distance / time;
    printf("Velocity: %f meters/second\n", velocity);
    fflush(stdout); // Ensuring the output is flushed immediately
}

/*
Speed:

Eq. i: v = s / t

v - Speed
s - Distance
t - Time

*/
// Eq. i
void calculate_speed(double distance, double time)
{
    if (time == 0)
    {
        printf("Error: Time cannot be zero.\n");
        fflush(stdout);
        return;
    }
    double speed = distance / time;
    printf("Speed: %f meters/second\n", speed);
    fflush(stdout);
}

/*
Acceleration:

Eq. i: a = v / t

a - Acceleration
v - Velocity
t - Time

Eq. ii: avg_vector_a = delta_vector_v / delta_t

avg_vector_a - Average acceleration vector
delta_vector_v - Change in velocity vector
delta_t - Change in time

Eq. iii: vector_a = dvector_v / dt

vector_a - Acceleration vector
dvector_v - Change in velocity vector
dt - Change in time

*/
// Eq. i
void calculate_acceleration(double velocity, double time)
{
    if (time == 0)
    {
        printf("Error: Time cannot be zero.\n");
        fflush(stdout);
        return;
    }
    double acceleration = velocity / time;
    printf("Acceleration: %f meters/second^2\n", acceleration);
    fflush(stdout);
}

/*
Equations of motion:

Eq. i: v = v0 + a * t

v - Final velocity
v0 - Initial velocity
a - Acceleration
t - Time

Eq. ii: s = s0 + v0 * t + 0.5 * a * t^2

s - Final displacement
s0 - Initial displacement
v0 - Initial velocity
a - Acceleration
t - Time

Eq. iii: v^2 = v0^2 + 2 * a * (s - s0)

v - Final velocity
v0 - Initial velocity
a - Acceleration
s - Final displacement
s0 - Initial displacement

Eq. iv: avg_v = 0.5 * (v + v0)

avg_v - Average velocity
v - Final velocity
v0 - Initial velocity

*/
// Eq. i
void calculate_final_velocity(double initial_velocity, double acceleration, double time)
{
    double final_velocity = initial_velocity + acceleration * time;
    printf("Final velocity: %f meters/second\n", final_velocity);
    fflush(stdout);
}

// Eq. ii
void calculate_final_displacement(double initial_displacement, double initial_velocity, double acceleration, double time)
{
    double final_displacement = initial_displacement + initial_velocity * time + 0.5 * acceleration * time * time;
    printf("Final displacement: %f meters\n", final_displacement);
    fflush(stdout);
}

// Eq. iii
void calculate_final_velocity_squared(double initial_velocity, double acceleration, double final_displacement, double initial_displacement)
{
    double final_velocity_squared = initial_velocity * initial_velocity + 2 * acceleration * (final_displacement - initial_displacement);
    printf("Final velocity squared: %f meters/second\n", final_velocity_squared);
    fflush(stdout);
}

// Eq. iv
void calculate_average_velocity(double final_velocity, double initial_velocity)
{
    double average_velocity = 0.5 * (final_velocity + initial_velocity);
    printf("Average velocity: %f meters/second\n", average_velocity);
    fflush(stdout);
}

/*

* Interactions

*/

/*
Force:

Eq. i: F = m * a

F - Force
m - Mass
a - Acceleration

*/
void calculate_force(double mass, double acceleration)
{
    double force = mass * acceleration;
    printf("Force: %f Newtons\n", force);
    fflush(stdout);
}
