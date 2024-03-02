namespace PistyApp
{
    class PathManager
    {
        private readonly string basePath;
        private readonly string pistyBasePath;
        private readonly string elpyBasePath;
        private readonly string agarpainBasePath;
        private readonly string workflowBasePath;

        public PathManager()
        {
            basePath = AppDomain.CurrentDomain.BaseDirectory;

            pistyBasePath = Path.Combine(basePath, "external", "Pisty");
            elpyBasePath = Path.Combine(basePath, "external", "Elpy", "build", "Release");
            agarpainBasePath = Path.Combine(basePath, "external", "Agarpain", "build", "Release");
            workflowBasePath = Path.Combine(basePath, "workflow");
        }

        public string GetSourcePath() => Path.Combine(pistyBasePath, "data");

        public string GetTargetPath() => Path.Combine(pistyBasePath, "processed_data");

        public string GetElpyAppPath() => Path.Combine(elpyBasePath, "Elpy.exe");

        public string GetAgarpainPath() => Path.Combine(agarpainBasePath, "Agarpain.exe");

        public string GetDatabasePath() => Path.Combine(pistyBasePath, "database");

        public string GetWorkflowPath() => workflowBasePath;
    }
}
