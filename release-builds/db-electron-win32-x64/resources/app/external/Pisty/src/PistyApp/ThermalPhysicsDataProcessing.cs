namespace PistyApp
{
    public class ThermalPhysicsDataProcessing
    {
        private readonly PhysicsDataProcessing physicsDataProcessing;

        public ThermalPhysicsDataProcessing(PhysicsDataProcessing physicsProcessor)
        {
            this.physicsDataProcessing = physicsProcessor;
        }

        public double CalculateLatentHeat(double mass, double latentHeatCapacity)
        {
            if (mass <= 0 || latentHeatCapacity <= 0)
            {
                throw new ArgumentException("Mass and latent heat capacity must be greater than zero.");
            }

            string input = $"calc_type_latent_heat\n{mass} {latentHeatCapacity}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }

        public double CalculateSensibleHeat(double mass, double specificHeatCapacity, double changeInTemperature)
        {
            if (mass <= 0 || specificHeatCapacity <= 0 || changeInTemperature <= 0)
            {
                throw new ArgumentException("Mass, specific heat capacity, and change in temperature must be greater than zero.");
            }

            string input = $"calc_type_sensible_heat\n{mass} {specificHeatCapacity} {changeInTemperature}\n";
            return physicsDataProcessing.PerformCalculation(input);
        }
    }
}
