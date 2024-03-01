namespace PistyApp
{
    public class MechanicsDataProcessor
    {
        private readonly MechanicsDataProcessing mechanicsDataProcessing;
        private readonly DataProcessor dataProcessor;
        private readonly string sourceDirectory;
        private readonly string targetDirectory;
        private readonly WorkflowManager workflowManager;

        public MechanicsDataProcessor(MechanicsDataProcessing mechanicsProcessing, DataProcessor dataProcessor, string sourceDir, string targetDir, WorkflowManager workflowManager)
        {
            this.mechanicsDataProcessing = mechanicsProcessing;
            this.dataProcessor = dataProcessor;
            this.sourceDirectory = sourceDir;
            this.targetDirectory = targetDir;
            this.workflowManager = workflowManager; // Store the WorkflowManager instance
        }

        private List<double> ReadData(string baseFileName)
        {
            // Attempt to read from the database first, then fallback to file if necessary
            var dataNullable = dataProcessor.ReadData(baseFileName.Replace(".txt", ""), true);
            // Filter out nulls and ensure list has only valid (non-null) data
            return dataNullable.Where(x => x.HasValue).Select(x => x!.Value).ToList();
        }

        /*
        
        Existence

        */

        public void ProcessWeight()
        {
            // Assume ReadData is a method that reads data and returns a List<double>
            var massData = ReadData("mass_data"); // Placeholder for actual data reading logic
            var gravityData = ReadData("gravity_data"); // Placeholder for actual data reading logic

            List<string> results = new List<string>();

            // Assuming massData and gravityData are lists of doubles and have the same count
            int count = Math.Min(massData.Count, gravityData.Count);
            for (int i = 0; i < count; i++)
            {
                // Calculate weight using the formula: weight = mass * gravity
                double weight = mechanicsDataProcessing.CalculateWeight(massData[i], gravityData[i]);
                results.Add($"{weight} N"); // Assuming the result is in Newtons
            }

            // Define the filename for saving results
            string fileName = "processed_weight_data.txt";

            // Save results to the original processed_data directory
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            // Save results to the new workflow directory
            // Note: "Physics\\Mechanics" is the subpath for mechanics data within the workflow directory.
            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Weight calculations completed successfully and saved to both directories.");
        }


        /*

        Motion

        */

        public void ProcessVelocity()
        {
            // Assuming ReadData method exists and reads data from the source, returning a list of double
            var distanceData = ReadData("distance_data");
            var timeData = ReadData("time_data");

            List<string> results = new List<string>();

            int count = Math.Min(distanceData.Count, timeData.Count);
            for (int i = 0; i < count; i++)
            {
                if (timeData[i] == 0) // Check to avoid division by zero
                {
                    Console.WriteLine($"Skipping velocity calculation for entry {i + 1} due to zero time value.");
                    continue;
                }

                double velocity = distanceData[i] / timeData[i]; // Calculate velocity
                results.Add($"{velocity} m/s");
            }

            // Define the filename for processed data
            string fileName = "processed_velocity_data.txt";

            // Save results to the original processed_data directory
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            // Save results to the new workflow directory
            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Velocity calculations completed successfully and saved to both directories.");
        }


        public void ProcessSpeed()
        {
            // Assuming ReadData method exists and reads data from the source, returning a list of double
            var distanceData = ReadData("distance_data");
            var timeData = ReadData("time_data");

            List<string> results = new List<string>();

            int count = Math.Min(distanceData.Count, timeData.Count);
            for (int i = 0; i < count; i++)
            {
                if (timeData[i] == 0) // Check to avoid division by zero
                {
                    Console.WriteLine($"Skipping speed calculation for entry {i + 1} due to zero time value.");
                    continue;
                }

                double speed = distanceData[i] / timeData[i]; // Calculate speed
                results.Add($"{speed} m/s");
            }

            // Define the filename for processed data
            string fileName = "processed_speed_data.txt";

            // Save results to the original processed_data directory
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            // Additionally, save results to the workflow directory
            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Speed calculations completed successfully and saved to both directories.");
        }


        public void ProcessAcceleration()
        {
            var velocityData = ReadData("velocity_data");
            var timeData = ReadData("time_data");

            List<string> results = new List<string>();

            int count = Math.Min(velocityData.Count, timeData.Count);
            for (int i = 0; i < count; i++)
            {
                if (timeData[i] == 0)
                {
                    Console.WriteLine($"Skipping acceleration calculation for entry {i + 1} due to zero time value.");
                    continue;
                }

                double acceleration = mechanicsDataProcessing.CalculateAcceleration(velocityData[i], timeData[i]);
                results.Add($"{acceleration} m/s^2");
            }

            dataProcessor.WriteResultsToFile("processed_acceleration_data.txt", results);
        }

        public void ProcessFinalVelocity()
        {
            var initialVelocityData = ReadData("initial_velocity_data");
            var accelerationData = ReadData("acceleration_data");
            var timeData = ReadData("time_data");

            List<string> results = new List<string>();

            int count = Math.Min(initialVelocityData.Count, Math.Min(accelerationData.Count, timeData.Count));
            for (int i = 0; i < count; i++)
            {
                double finalVelocity = initialVelocityData[i] + accelerationData[i] * timeData[i]; // Calculate final velocity
                results.Add($"{finalVelocity} m/s");
            }

            string fileName = "processed_final_velocity_data.txt";
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Final Velocity calculations completed successfully and saved to both directories.");
        }

        public void ProcessFinalDisplacement()
        {
            var initialDisplacementData = ReadData("initial_displacement_data");
            var initialVelocityData = ReadData("initial_velocity_data");
            var accelerationData = ReadData("acceleration_data");
            var timeData = ReadData("time_data");

            List<string> results = new List<string>();

            int count = Math.Min(Math.Min(initialDisplacementData.Count, initialVelocityData.Count), Math.Min(accelerationData.Count, timeData.Count));
            for (int i = 0; i < count; i++)
            {
                double finalDisplacement = initialDisplacementData[i] + initialVelocityData[i] * timeData[i] + 0.5 * accelerationData[i] * Math.Pow(timeData[i], 2); // Calculate final displacement
                results.Add($"{finalDisplacement} m");
            }

            string fileName = "processed_final_displacement_data.txt";
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Final Displacement calculations completed successfully and saved to both directories.");
        }

        public void ProcessAverageVelocity()
        {
            var initialVelocityData = ReadData("initial_velocity_data");
            var finalVelocityData = ReadData("final_velocity_data");

            List<string> results = new List<string>();

            int count = Math.Min(initialVelocityData.Count, finalVelocityData.Count);
            for (int i = 0; i < count; i++)
            {
                double averageVelocity = (initialVelocityData[i] + finalVelocityData[i]) / 2; // Calculate average velocity
                results.Add($"{averageVelocity} m/s");
            }

            string fileName = "processed_average_velocity_data.txt";
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Average Velocity calculations completed successfully and saved to both directories.");
        }

        /*

        Interaction

        */

        public void ProcessForce()
        {
            var massData = ReadData("mass_data");
            var accelerationData = ReadData("acceleration_data");

            List<string> results = new List<string>();

            int count = Math.Min(massData.Count, accelerationData.Count);
            for (int i = 0; i < count; i++)
            {
                double force = massData[i] * accelerationData[i]; // Calculate force using F = ma
                results.Add($"{force} N"); // Newtons
            }

            string fileName = "processed_force_data.txt";
            string processedFilePath = Path.Combine(targetDirectory, fileName);
            dataProcessor.WriteResultsToFile(processedFilePath, results);

            string workflowFilePath = Path.Combine(workflowManager.GetProcessingTypePath("Physics\\Mechanics"), fileName);
            dataProcessor.WriteResultsToFile(workflowFilePath, results);

            Console.WriteLine("Processed Force calculations completed successfully and saved to both directories.");
        }
    }
}
