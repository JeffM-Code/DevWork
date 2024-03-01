using Microsoft.Data.Sqlite;

public class DatabaseManager
{
    private string sourceDirectory;
    private string databaseDirectory;

    public DatabaseManager(string sourceDir, string dbDir)
    {
        sourceDirectory = sourceDir;
        databaseDirectory = dbDir;

        // Ensure database directory exists
        if (!Directory.Exists(databaseDirectory))
        {
            Directory.CreateDirectory(databaseDirectory);
        }
    }

    public void CreateDatabasesFromTextFiles()
    {
        // Get all text files from source directory
        string[] files = Directory.GetFiles(sourceDirectory, "*.txt");
        foreach (var file in files)
        {
            string baseFileName = Path.GetFileNameWithoutExtension(file);
            string dbFilePath = Path.Combine(databaseDirectory, $"{baseFileName}.db");

            // Create and populate the database
            bool result = CreateAndPopulateDatabase(file, dbFilePath);
            if (result)
            {
                Console.WriteLine($"Database created successfully at: {dbFilePath}");
            }
            else
            {
                Console.WriteLine($"Failed to create database for: {file}. See error messages above for details.");
            }
        }
    }

    private bool CreateAndPopulateDatabase(string textFilePath, string dbFilePath)
    {
        try
        {
            using (var connection = new SqliteConnection($"Data Source={dbFilePath}"))
            {
                connection.Open();
                var command = connection.CreateCommand();
                command.CommandText = "CREATE TABLE IF NOT EXISTS data (value REAL)";
                command.ExecuteNonQuery();

                var lines = File.ReadAllLines(textFilePath);
                foreach (var line in lines)
                {
                    if (double.TryParse(line, out double value))
                    {
                        command.Parameters.Clear();
                        command.CommandText = "INSERT INTO data (value) VALUES ($value)";
                        command.Parameters.AddWithValue("$value", value);
                        command.ExecuteNonQuery();
                    }
                    else
                    {
                        Console.WriteLine($"Skipping invalid or non-numeric line: '{line}' in {textFilePath}");
                    }
                }
                return true;
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error creating or populating database from {textFilePath}: {ex.Message}");
            return false;
        }
    }
}
