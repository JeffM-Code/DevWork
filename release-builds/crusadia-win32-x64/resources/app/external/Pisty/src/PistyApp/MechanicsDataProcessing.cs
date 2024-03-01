namespace PistyApp
{
    public class MechanicsDataProcessing
    {
        private readonly PhysicsDataProcessing physicsDataProcessing;

        public MechanicsDataProcessing(PhysicsDataProcessing physicsProcessor)
        {
            this.physicsDataProcessing = physicsProcessor;
        }

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
        public double CalculateWeight(double mass, double gravity)
        {
            // Use the existing field instead of creating a new instance
            string input = $"calc_type_weight\n{mass} {gravity}\n";
            return physicsDataProcessing.PerformCalculation(input);
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
        public double CalculateVelocity(double distance, double time)
        {
            string input = $"calc_type_velocity\n{distance} {time}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }

        /*
        Speed:

        Eq. i: v = s / t

        v - Speed
        s - Distance
        t - Time

        */
        // Eq. i
        public double CalculateSpeed(double distance, double time)
        {
            string input = $"calc_type_speed\n{distance} {time}\n";
            return physicsDataProcessing.PerformCalculation(input);
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
        public double CalculateAcceleration(double velocity, double time)
        {
            string input = $"calc_type_acceleration\n{velocity} {time}\n";
            return physicsDataProcessing.PerformCalculation(input);
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
        public double CalculateFinalVelocity(double initialVelocity, double acceleration, double time)
        {
            string input = $"calc_type_final_velocity\n{initialVelocity} {acceleration} {time}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }

        // Eq. ii
        public double CalculateFinalDisplacement(double initialDisplacement, double initialVelocity, double acceleration, double time)
        {
            string input = $"calc_type_final_displacement\n{initialDisplacement} {initialVelocity} {acceleration} {time}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }

        // Eq. iii
        public double CalculateFinalVelocitySquared(double initialVelocity, double acceleration, double finalDisplacement, double initialDisplacement)
        {
            string input = $"calc_type_final_velocity_squared\n{initialVelocity} {acceleration} {finalDisplacement} {initialDisplacement}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }

        // Eq. iv
        public double CalculateAverageVelocity(double finalVelocity, double initialVelocity)
        {
            string input = $"calc_type_average_velocity\n{finalVelocity} {initialVelocity}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }

        /*
        * Interaction
        */

        /*
        Force:

        Eq. i: F = m * a

        F - Force
        m - Mass
        a - Acceleration

        Eq. ii: Sigma_vector_F = m * vector_a

        */
        public double CalculateForce(double mass, double acceleration)
        {
            string input = $"calc_type_force\n{mass} {acceleration}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }
    }
}
