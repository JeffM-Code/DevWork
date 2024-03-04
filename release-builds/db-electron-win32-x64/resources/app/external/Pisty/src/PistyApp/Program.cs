namespace PistyApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("*.*.*..*.*.** PISTY *.*.*..*.*.**\n");

            PathManager pathManager = new PathManager();

            string sourceDirectory = pathManager.GetSourcePath();
            string targetDirectory = pathManager.GetProcessedDataPath();
            string databaseDirectory = pathManager.GetDatabasePath();
            string workflowDirectory = pathManager.GetWorkflowPath();
            string elpyAppPath = pathManager.GetElpyPath();
            string agarpainPath = pathManager.GetAgarpainPath();

            WorkflowManager workflowManager = new WorkflowManager(workflowDirectory);
            DatabaseManager databaseManager = new DatabaseManager(sourceDirectory, databaseDirectory);
            databaseManager.CreateDatabasesFromTextFiles();

            DataProcessor dataProcessor = new DataProcessor(sourceDirectory, targetDirectory, databaseDirectory);

            PhysicsDataProcessing physicsDataProcessing = new PhysicsDataProcessing(agarpainPath);

            MechanicsDataProcessing mechanicsDataProcessing = new MechanicsDataProcessing(physicsDataProcessing);
            ThermalPhysicsDataProcessing thermalPhysicsDataProcessing = new ThermalPhysicsDataProcessing(physicsDataProcessing);

            MechanicsDataProcessor mechanicsDataProcessor = new MechanicsDataProcessor(mechanicsDataProcessing, dataProcessor, sourceDirectory, targetDirectory, workflowManager);
            ThermalPhysicsDataProcessor thermalPhysicsDataProcessor = new ThermalPhysicsDataProcessor(thermalPhysicsDataProcessing, dataProcessor, sourceDirectory, targetDirectory, workflowManager);

            PerformPhysicsCalculations(mechanicsDataProcessor, thermalPhysicsDataProcessor);

            ProgramRunner.RunExternalApp(elpyAppPath);
        }

        static void PerformPhysicsCalculations(MechanicsDataProcessor mechanicsDataProcessor, ThermalPhysicsDataProcessor thermalPhysicsDataProcessor)
        {
            Console.WriteLine("\n* Processing Mechanics Data...\n");
            mechanicsDataProcessor.ProcessWeight();
            mechanicsDataProcessor.ProcessVelocity();
            mechanicsDataProcessor.ProcessSpeed();
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
