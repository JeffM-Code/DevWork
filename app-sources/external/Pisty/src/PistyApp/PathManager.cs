namespace PistyApp
{
    class PathManager
    {
        private readonly string documentsFolderPath;
        private readonly string pistyBasePath;
        private readonly string elpyBasePath;
        private readonly string agarpainBasePath;
        private readonly string workflowBasePath;

        public PathManager()
        {
            documentsFolderPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            
            pistyBasePath = Path.Combine(documentsFolderPath, "release-builds", "crusadia-win32-x64", "resources", "app", "external", "Pisty");
            elpyBasePath = Path.Combine(documentsFolderPath, "release-builds", "crusadia-win32-x64", "resources", "app", "external", "Elpy", "build", "Release");
            agarpainBasePath = Path.Combine(documentsFolderPath, "release-builds", "crusadia-win32-x64", "resources", "app", "external", "Agarpain", "build", "Release");
            workflowBasePath = Path.Combine(documentsFolderPath, "release-builds", "crusadia-win32-x64", "resources", "app", "workflow");
        }

        public string GetSourcePath() => Path.Combine(pistyBasePath, "data");

        public string GetTargetPath() => Path.Combine(pistyBasePath, "processed_data");

        public string GetElpyAppPath() => Path.Combine(elpyBasePath, "Elpy.exe");

        public string GetAgarpainPath() => Path.Combine(agarpainBasePath, "Agarpain.exe");

        public string GetDatabasePath() => Path.Combine(pistyBasePath, "database");

        public string GetWorkflowPath() => workflowBasePath;
    }
}
