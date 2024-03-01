using Microsoft.Data.Sqlite;

namespace PistyApp
{
    public class DataProcessor
    {
        private readonly string sourceDirectory;
        private readonly string targetDirectory;
        private readonly string databaseDirectory;

        public DataProcessor(string sourceDir, string targetDir, string dbDir)
        {
            sourceDirectory = sourceDir;
            targetDirectory = targetDir;
            databaseDirectory = dbDir;
        }

        public List<double?> ReadDataFromFile(string filePath)
        {
            List<double?> validData = new List<double?>();
            try
            {
                var lines = File.ReadAllLines(filePath);
                foreach (var line in lines.Select(l => l.Trim()))
                {
                    if (string.IsNullOrWhiteSpace(line))
                    {
                        Console.WriteLine($"Warning: Ignored whitespace/empty line in file {filePath}");
                        validData.Add(null);
                        continue;
                    }

                    if (double.TryParse(line, out double value))
                    {
                        validData.Add(value);
                    }
                    else
                    {
                        Console.WriteLine($"Warning: Ignored invalid value '{line}' in file {filePath}");
                        validData.Add(null);
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error reading file {filePath}: {ex.Message}");
            }

            return validData;
        }

        public List<double?> ReadDataFromDatabase(string baseFileName)
        {
            List<double?> data = new List<double?>();
            string dbFilePath = Path.Combine(databaseDirectory, $"{baseFileName}.db");

            if (!File.Exists(dbFilePath))
            {
                Console.WriteLine($"Database file not found: {dbFilePath}");
                return data;
            }

            using (var connection = new SqliteConnection($"Data Source={dbFilePath}"))
            {
                connection.Open();
                string query = "SELECT Value FROM data";
                using (var command = new SqliteCommand(query, connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            if (double.TryParse(reader["Value"].ToString(), out double value))
                            {
                                data.Add(value);
                            }
                            else
                            {
                                data.Add(null);
                            }
                        }
                    }
                }
                connection.Close();
            }

            return data;
        }

        /*
        // For testing
        public List<double?> ReadData(string baseFileName, bool preferDatabase = true)
        {
            // For testing, force to always read from the text file
            var data = ReadDataFromFile(Path.Combine(sourceDirectory, $"{baseFileName}.txt"));

            // Convert List<double> to List<double?> for compatibility
            return data.Select(x => (double?)x).ToList();
        }
        */

        public List<double?> ReadData(string baseFileName, bool preferDatabase = true)
        {
            List<double?> data = new List<double?>();
            string dbFilePath = Path.Combine(databaseDirectory, $"{baseFileName}.db");
            string textFilePath = Path.Combine(sourceDirectory, $"{baseFileName}.txt");

            if (preferDatabase && File.Exists(dbFilePath))
            {
                Console.WriteLine($"Reading from database: {dbFilePath}");
                data = ReadDataFromDatabase(baseFileName);
                if (data.Any())
                {
                    return data;
                }
                Console.WriteLine($"No data found in database: {dbFilePath}. Attempting to read from text file.");
            }

            if (File.Exists(textFilePath))
            {
                Console.WriteLine($"Reading from text file: {textFilePath}");
                data = ReadDataFromFile(textFilePath);
            }
            else
            {
                Console.WriteLine($"No data source found for {baseFileName}. Checked {dbFilePath} and {textFilePath}.");
            }

            return data;
        }

        public void WriteResultsToFile(string fullPath, List<string> results)
        {
            try
            {
                File.WriteAllLines(fullPath, results);
                Console.WriteLine($"Successfully written to: {fullPath}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error writing to {fullPath}: {ex.Message}");
            }
        }

    }
}
