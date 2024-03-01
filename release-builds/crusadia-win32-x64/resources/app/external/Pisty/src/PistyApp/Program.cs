using System;

namespace PistyApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("*.*.*..*.*.** PISTY *.*.*..*.*.**\n");

            // Initialize path management
            PathManager pathManager = new PathManager();
            string sourceDirectory = pathManager.GetSourcePath();
            string targetDirectory = pathManager.GetTargetPath();
            string databaseDirectory = pathManager.GetDatabasePath(); // Ensure this method returns the database directory path
            string workflowDirectory = pathManager.GetWorkflowPath(); // Assuming GetWorkflowPath() is implemented in PathManager
            string elpyAppPath = pathManager.GetElpyAppPath();

            // Initialize WorkflowManager with the workflow directory path
            WorkflowManager workflowManager = new WorkflowManager(workflowDirectory);

            // Initialize DatabaseManager to create databases from text files
            DatabaseManager databaseManager = new DatabaseManager(sourceDirectory, databaseDirectory);
            databaseManager.CreateDatabasesFromTextFiles(); // Populate databases from text files

            // Initialize core data processing utilities
            DataProcessor dataProcessor = new DataProcessor(sourceDirectory, targetDirectory, databaseDirectory);

            PhysicsDataProcessing physicsDataProcessing = new PhysicsDataProcessing();

            // Initialize domain-specific data processing
            MechanicsDataProcessing mechanicsDataProcessing = new MechanicsDataProcessing(physicsDataProcessing);
            ThermalPhysicsDataProcessing thermalPhysicsDataProcessing = new ThermalPhysicsDataProcessing(physicsDataProcessing);

            // Initialize domain-specific data processors with WorkflowManager
            MechanicsDataProcessor mechanicsDataProcessor = new MechanicsDataProcessor(mechanicsDataProcessing, dataProcessor, sourceDirectory, targetDirectory, workflowManager);
            ThermalPhysicsDataProcessor thermalPhysicsDataProcessor = new ThermalPhysicsDataProcessor(thermalPhysicsDataProcessing, dataProcessor, sourceDirectory, targetDirectory, workflowManager);

            // Execute processing tasks
            PerformPhysicsCalculations(mechanicsDataProcessor, thermalPhysicsDataProcessor);

            // Once all processing is complete, run the external C++ application
            ProgramRunner.RunExternalApp(elpyAppPath);
        }

        static void PerformPhysicsCalculations(MechanicsDataProcessor mechanicsDataProcessor, ThermalPhysicsDataProcessor thermalPhysicsDataProcessor)
        {
            Console.WriteLine("\n* Processing Mechanics Data...\n");
            mechanicsDataProcessor.ProcessWeight();
            mechanicsDataProcessor.ProcessVelocity();
            mechanicsDataProcessor.ProcessAcceleration();
            mechanicsDataProcessor.ProcessFinalVelocity();
            mechanicsDataProcessor.ProcessFinalDisplacement();
            mechanicsDataProcessor.ProcessAverageVelocity();
            mechanicsDataProcessor.ProcessForce();

            Console.WriteLine("\n\n* Processing Thermal Physics Data...\n");
            thermalPhysicsDataProcessor.ProcessLatentHeat();
            thermalPhysicsDataProcessor.ProcessSensibleHeat();

            Console.WriteLine("\n\n* All processing complete\n\n");
        }
    }
}
