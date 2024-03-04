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
                string workingDirectory = AppDomain.CurrentDomain.BaseDirectory;

                Console.WriteLine($"Attempting to start *..**.* ELPY *.**..* at: {appPath}");
                Console.WriteLine($"Set working directory to: {workingDirectory}");

                using (Process process = new Process())
                {
                    process.StartInfo.FileName = appPath;
                    process.StartInfo.WorkingDirectory = workingDirectory;
                    process.StartInfo.UseShellExecute = false;
                    process.StartInfo.RedirectStandardOutput = true;
                    process.StartInfo.RedirectStandardError = true;

                    bool started = process.Start();
                    if (!started)
                    {
                        Console.WriteLine("Failed to start the external application. Please check the path and permissions.");
                        return;
                    }

                    Console.WriteLine("External application started successfully.");

                    string output = process.StandardOutput.ReadToEnd();
                    string errors = process.StandardError.ReadToEnd();

                    process.WaitForExit();

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
