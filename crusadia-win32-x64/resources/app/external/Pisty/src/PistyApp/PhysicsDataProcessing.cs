using System.Diagnostics;
using System.Text.RegularExpressions;

namespace PistyApp
{
    public class PhysicsDataProcessing
    {
        private readonly string pathToAgarpain;

        public PhysicsDataProcessing()
        {
            PathManager pathManager = new PathManager();
            string agarpainPath = pathManager.GetAgarpainPath();
            pathToAgarpain = agarpainPath;
        }

        public double PerformCalculation(string input)
        {
            Console.WriteLine("*.*.*..*.*.** AGARPAIN *.*.*..*.*.**\n");
            Console.WriteLine($"Sending to *..**.* AGARPAIN *.**..*: [{input}]");

            try
            {
                ProcessStartInfo startInfo = new ProcessStartInfo
                {
                    FileName = pathToAgarpain,
                    UseShellExecute = false,
                    RedirectStandardInput = true,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                };

                using (Process? process = Process.Start(startInfo))
                {
                    if (process == null)
                    {
                        throw new InvalidOperationException("Failed to start physics calculation process.");
                    }

                    using (StreamWriter sw = process.StandardInput)
                    {
                        if (sw.BaseStream.CanWrite)
                        {
                            sw.WriteLine(input);
                        }
                    }

                    string result = process.StandardOutput.ReadToEnd();
                    process.WaitForExit();

                    Console.WriteLine($"Received from *..**.* AGARPAIN *.**..*: [{result}]");

                    // Extract the numeric part of the result
                    var match = Regex.Match(result, @"\d+(\.\d+)?");

                    if (match.Success && double.TryParse(match.Value, out double calculationResult))
                    {
                        return calculationResult;
                    }
                    else
                    {
                        Console.WriteLine("Failed to parse calculation result.");
                        return double.NaN; // Consider appropriate error handling
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred while performing physics calculation: {ex.Message}");
                return double.NaN; // Consider appropriate error handling
            }
        }
    }
}
