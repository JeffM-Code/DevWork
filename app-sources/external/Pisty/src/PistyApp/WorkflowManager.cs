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
            EnsureWorkflowDirectory();
        }

        private void EnsureWorkflowDirectory()
        {
            if (!Directory.Exists(baseWorkflowPath))
            {
                Directory.CreateDirectory(baseWorkflowPath);
            }

            EnsureSubdirectory("Physics\\Mechanics");
            EnsureSubdirectory("Physics\\ThermalPhysics");
        }

        private void EnsureSubdirectory(string subPath)
        {
            string fullPath = Path.Combine(baseWorkflowPath, subPath);
            if (!Directory.Exists(fullPath))
            {
                Directory.CreateDirectory(fullPath);
            }
        }

        public string GetProcessingTypePath(string processingType)
        {
            return Path.Combine(baseWorkflowPath, processingType);
        }
    }
}
