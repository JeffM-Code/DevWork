namespace PistyApp
{
    public class ThermalPhysicsDataProcessor
    {
        private readonly ThermalPhysicsDataProcessing thermalPhysicsDataProcessing;
        private readonly DataProcessor dataProcessor;
        private readonly string sourceDirectory;
        private readonly string targetDirectory;
        private readonly WorkflowManager workflowManager;

        public ThermalPhysicsDataProcessor(ThermalPhysicsDataProcessing thermalPhysicsProcessing, DataProcessor dataProcessor, string sourceDir, string targetDir, WorkflowManager workflowManager)
        {
            this.thermalPhysicsDataProcessing = thermalPhysicsProcessing;
            this.dataProcessor = dataProcessor;
            this.sourceDirectory = sourceDir;
            this.targetDirectory = targetDir;
            this.workflowManager = workflowManager;
        }

        private List<double> ReadData(string baseFileName)
        {
            var dataNullable = dataProcessor.ReadData(baseFileName.Replace(".txt", ""), true);
            return dataNullable.Where(x => x.HasValue).Select(x => x!.Value).ToList();
        }

        public void ProcessLatentHeat()
        {
            var massData = ReadData("mass_data");
            var latentHeatCapacityData = ReadData("latent_heat_capacity_data");

            List<string> results = new List<string>();

            int count = Math.Min(massData.Count, latentHeatCapacityData.Count);
            for (int i = 0; i < count; i++)
            {
                double latentHeat = thermalPhysicsDataProcessing.CalculateLatentHeat(massData[i], latentHeatCapacityData[i]);
                results.Add($"{latentHeat} J");
            }

            string processedFilePath = Path.Combine(targetDirectory, "processed_latent_heat_data.txt");
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\ThermalPhysics"), "processed_latent_heat_data.txt");
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Latent Heat calculations completed successfully.");
        }

        public void ProcessSensibleHeat()
        {
            var massData = ReadData("mass_data");
            var specificHeatCapacityData = ReadData("specific_heat_capacity_data");
            var temperatureChangeData = ReadData("temperature_change_data");

            List<string> results = new List<string>();

            int count = Math.Min(massData.Count, Math.Min(specificHeatCapacityData.Count, temperatureChangeData.Count));
            for (int i = 0; i < count; i++)
            {
                double sensibleHeat = thermalPhysicsDataProcessing.CalculateSensibleHeat(massData[i], specificHeatCapacityData[i], temperatureChangeData[i]);
                results.Add($"{sensibleHeat} J");
            }

            string processedFilePath = Path.Combine(targetDirectory, "processed_sensible_heat_data.txt");
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\ThermalPhysics"), "processed_sensible_heat_data.txt");
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Sensible Heat calculations completed successfully.");
        }
    }
}
