using System.Diagnostics;

namespace PistyApp
{
    public static class ProgramRunner
    {
        private static readonly string documentsFolderPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

        public static void RunExternalApp(string appPath)
        {
            try
            {
                // Log the intended path and working directory for verification
                Console.WriteLine($"Attempting to start *..**.* ELPY *.**..* at: {appPath}");
                
                string workingDirectory = Path.Combine(documentsFolderPath, "release-builds", "crusadia-win32-x64", "resources", "app");
                
                Console.WriteLine($"Set working directory to: {workingDirectory}");

                using (Process process = new Process())
                {
                    process.StartInfo.FileName = appPath;
                    process.StartInfo.UseShellExecute = false; // Required to redirect standard output/error
                    process.StartInfo.RedirectStandardOutput = true;
                    process.StartInfo.RedirectStandardError = true;
                    process.StartInfo.WorkingDirectory = workingDirectory; // Set the working directory

                    // Start the external application
                    bool started = process.Start();
                    if (!started)
                    {
                        Console.WriteLine("Failed to start the external application. Please check the path and permissions.");
                        return;
                    }

                    Console.WriteLine("External application started successfully.");

                    // Asynchronously read the standard output and standard error
                    string output = process.StandardOutput.ReadToEnd();
                    string errors = process.StandardError.ReadToEnd();

                    // Wait for the application to exit
                    process.WaitForExit();

                    // Display the output and errors (if any)
                    if (!string.IsNullOrWhiteSpace(output))
                    {
                        Console.WriteLine($"Output from *..**.* ELPY *.**..*:\n{output}");
                    }

                    if (!string.IsNullOrWhiteSpace(errors))
                    {
                        Console.WriteLine($"Errors from ELPY:\n{errors}");
                    }

                    Console.WriteLine($"*..**.* ELPY *.**..* exited with code {process.ExitCode}.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An exception occurred while trying to run ELPY: {ex.Message}");
            }
        }
    }
}
