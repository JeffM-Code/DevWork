public class PathManager
{
    private readonly string basePath;

    public PathManager()
    {
        basePath = AppDomain.CurrentDomain.BaseDirectory;
    }

    private string ConstructPath(string[] relativePathParts)
    {
        string fullPath = Path.GetFullPath(Path.Combine(basePath, Path.Combine(relativePathParts)));
        return fullPath;
    }

    public string GetSourcePath()
    {
        return ConstructPath(new[] { "..", "..", "..", "..", "..", "..", "data" });
    }

    public string GetProcessedDataPath()
    {
        return ConstructPath(new[] { "..", "..", "..", "..", "..", "..", "processed_data" });
    }

    public string GetDatabasePath()
    {
        return ConstructPath(new[] { "..", "..", "..", "..", "..", "..", "database" });
    }

    public string GetElpyPath()
    {
        var path = ConstructPath(new[] { "..", "..", "..", "..", "..", "..", "..", "Elpy", "build", "Release", "Elpy.exe" });
        Console.WriteLine($"Constructed Elpy Path: {path}");
        return path;
    }

    public string GetAgarpainPath()
    {
        var path = ConstructPath(new[] { "..", "..", "..", "..", "..", "..", "..", "Agarpain", "build", "Release", "Agarpain.exe" });
        Console.WriteLine($"Constructed Agarpain Path: {path}");
        return path;
    }

    public string GetWorkflowPath()
    {
        return ConstructPath(new[] { "..", "..", "..", "..", "..", "..", "..", "..", "workflow" });
    }
}
