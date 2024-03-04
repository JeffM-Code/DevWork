using System;
using System.IO;

namespace PistyApp
{
    public class WorkflowManager
    {
        private readonly string baseWorkflowPath;

        public WorkflowManager(string basePath)
        {
            baseWorkflowPath = basePath;
            Console.WriteLine($"Initializing WorkflowManager with base path: {baseWorkflowPath}");
            EnsureWorkflowDirectory();
        }

        private void EnsureWorkflowDirectory()
        {
            if (!Directory.Exists(baseWorkflowPath))
            {
                Console.WriteLine($"Workflow directory does not exist. Creating: {baseWorkflowPath}");
                Directory.CreateDirectory(baseWorkflowPath);
            }
            else
            {
                Console.WriteLine($"Workflow directory already exists: {baseWorkflowPath}");
            }

            EnsureSubdirectory("Physics\\Mechanics");
            EnsureSubdirectory("Physics\\ThermalPhysics");
        }

        private void EnsureSubdirectory(string subPath)
        {
            string fullPath = Path.Combine(baseWorkflowPath, subPath);
            if (!Directory.Exists(fullPath))
            {
                Console.WriteLine($"Subdirectory does not exist. Creating: {fullPath}");
                Directory.CreateDirectory(fullPath);
            }
            else
            {
                Console.WriteLine($"Subdirectory already exists: {fullPath}");
            }
        }

        public string GetProcessingTypePath(string processingType)
        {
            string path = Path.Combine(baseWorkflowPath, processingType);
            Console.WriteLine($"Processing type path: {path}");
            return path;
        }
    }
}
