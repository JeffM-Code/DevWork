const { app, BrowserWindow, ipcMain, Menu } = require('electron');
const fs = require('fs');
const fsp = require('fs').promises;
const path = require('path');
const { spawn } = require('child_process');
const os = require('os');
const sqlite3 = require('sqlite3').verbose();

const outputPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'output', 'workflowOutput.txt');
const resetLogPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'output', 'resetLog.txt');

let mainWindow;

/*
require('electron-reload')(__dirname, {
    electron: path.join(__dirname, 'node_modules', '.bin', 'electron')
});
*/

function createWindow() {
    const preloadPath = path.join(__dirname, '..', 'preload', 'preload.js');
    const indexPath = path.join(__dirname, '..', 'renderer', 'index.html');

    mainWindow = new BrowserWindow({
        width: 1400,
        height: 750,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            enableRemoteModule: false,
            preload: preloadPath
        }
    });

    mainWindow.loadFile(indexPath);

    watchDataFiles();
}

function watchDataFiles() {
    const processedDataPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'processed_data_streamlining');

    fs.watch(processedDataPath, (eventType, filename) => {
        if (filename) {
            getProcessedDataFiles();
        } else {
            console.log('Filename not provided');
        }
    });
}

async function getProcessedDataFiles() {
    const processedDataPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'processed_data_streamlining');
    
    try {
        const files = await fs.promises.readdir(processedDataPath);
        const filteredFiles = files.filter(file => file.startsWith('processed_force_data') || file.startsWith('processed_speed_data') || file.startsWith('processed_weight_data') || file.startsWith('processed_latent_heat_data'));
        mainWindow.webContents.send('processedDataFilesResponse', filteredFiles);
    } catch (error) {
        console.error('Error reading processed data directory:', error);
        mainWindow.webContents.send('processedDataFilesResponse', []);
    }
}

function resetDatabase() {
    const dbDirectory = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'external', 'Pisty', 'database');

    fs.readdir(dbDirectory, (err, files) => {
        if (err) {
            console.error('Could not list the directory.', err);
            return;
        }

        files.forEach((file) => {
            if (file.endsWith('.db')) {
                const dbPath = path.join(dbDirectory, file);

                let db = new sqlite3.Database(dbPath, sqlite3.OPEN_READWRITE, (err) => {
                    if (err) {
                        console.error(`Could not open database file ${file}`, err);
                        return;
                    }
                });

                const query = `SELECT name FROM sqlite_master WHERE type='table'`;

                db.all(query, [], (err, tables) => {
                    if (err) {
                        console.error('Error fetching tables', err);
                        return;
                    }

                    tables.forEach((table) => {
                        if (table.name) {
                            db.run(`DELETE FROM ${table.name}`, (deleteErr) => {
                                if (deleteErr) {
                                    console.error(`Error deleting contents of table ${table.name}`, deleteErr);
                                }
                            });
                        }
                    });
                });

                db.close((err) => {
                    if (err) {
                        console.error('Error closing the database', err);
                    }
                });
            }
        });
    });

    console.log('All database files have been reset.');
}

async function searchDirectory(dirPath, query) {
    let results = [];
    let searchedPaths = [];
    let directoryNotFound = false;

    try {
        const files = await fsp.readdir(dirPath, { withFileTypes: true });
        searchedPaths.push(dirPath);

        for (const file of files) {
            const filePath = path.join(dirPath, file.name);
            
            if (file.isDirectory()) {
                const subSearch = await searchDirectory(filePath, query);
                results = results.concat(subSearch.results);
                searchedPaths = searchedPaths.concat(subSearch.searchedPaths);
            } else if (file.isFile() && path.extname(file.name) === '.txt') {
                const content = await fsp.readFile(filePath, 'utf8');
                const lines = content.split(/\r?\n/);

                const regex = new RegExp(`\\b${query}\\b`, 'i');

                lines.forEach((line, index) => {
                    if (regex.test(line)) {
                        results.push({ path: filePath, line, lineNumber: index + 1 });
                    }
                });
            }
        }
    } catch (error) {
        console.error(`Error searching directory ${dirPath}:`, error);
        if (error.code === 'ENOENT') {
            directoryNotFound = true;
        }
    }

    return { results, searchedPaths, directoryNotFound };
}

ipcMain.on('getProcessedDataFiles', getProcessedDataFiles);

ipcMain.on('readFileContent', async (event, filePath) => {
    const processedDataPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'processed_data_streamlining', filePath);

    try {
        const content = await fsp.readFile(processedDataPath, 'utf8');
        event.reply('fileContentResponse', content);
    } catch (error) {
        console.error('Error reading file:', error);
        event.reply('fileContentResponse', `Error reading file: ${error}`);
    }
});

ipcMain.on('resetProcessedDataFiles', async () => {
    fs.writeFileSync(resetLogPath, 'Reset Workflow Initiated\n');

    const processedDataPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'processed_data_streamlining');

    try {
        const files = await fs.promises.readdir(processedDataPath);
        files.forEach(file => {
            const filePath = path.join(processedDataPath, file);
            fs.writeFileSync(filePath, '');

            fs.appendFileSync(resetLogPath, `File reset: ${file}\n`);
        });

        console.log('All processed data files have been reset.');
        fs.appendFileSync(resetLogPath, 'All processed data files have been reset.\n');

        fs.readFile(resetLogPath, 'utf8', (err, data) => {
            if (err) {
                console.error('Error reading reset log file:', err);
                return;
            }
            mainWindow.webContents.send('updateOutputArea', data);
        });

    } catch (error) {
        console.error('Error during reset process:', error);
        fs.appendFileSync(resetLogPath, `Error during reset process: ${error}\n`);

        fs.readFile(resetLogPath, 'utf8', (err, data) => {
            if (err) {
                console.error('Error reading reset log file:', err);
                return;
            }
            mainWindow.webContents.send('updateOutputArea', data);
        });
    }

    resetDatabase();
});

ipcMain.on('openApplication', (event, arg) => {
    console.log('Received openApplication message. Attempting to open PISTY');

    const appPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'external', 'Pisty', 'src', 'PistyApp', 'bin', 'Release', 'net8.0', 'win-x64', 'PistyApp.exe');

    fs.writeFileSync(outputPath, '', (err) => {
        if (err) throw err;
    });

    const child = spawn(appPath, [], { shell: true });

    child.stdout.on('data', (data) => {
        fs.appendFileSync(outputPath, data.toString(), (err) => {
            if (err) throw err;
        });
    });

    child.stderr.on('data', (data) => {
        fs.appendFileSync(outputPath, data.toString(), (err) => {
            if (err) throw err;
        });
    });

    child.on('error', (err) => {
        console.error('Failed to start PISTY:', err);
    });

    child.on('exit', (code, signal) => {
        console.log(`The PISTY app exited with code ${code} and signal ${signal}`);
        watcher.close();
    });

    const watcher = fs.watch(outputPath, (eventType, filename) => {
        if (eventType === 'change') {
            fs.readFile(outputPath, 'utf8', (err, data) => {
                if (err) {
                    console.error('Error reading the output file:', err);
                    return;
                }

                mainWindow.webContents.send('updateOutputArea', data);
            });
        }
    });
});

ipcMain.on('readWorkflowOutput', (event) => {
    fs.readFile(outputPath, 'utf8', (err, data) => {
        if (err) {
            console.error('Error reading workflow output file:', err);
            mainWindow.webContents.send('fileContentResponse', 'Error reading workflow output file.');
            return;
        }
        mainWindow.webContents.send('fileContentResponse', data);
    });
});

ipcMain.on('readResetLog', () => {
    const resetLogContent = fs.readFileSync(resetLogPath, 'utf8');
    mainWindow.webContents.send('updateOutputArea', resetLogContent);
});

ipcMain.on('searchWorkflowContent', async (event, searchQuery) => {
    const workflowPath = path.join(os.homedir(), 'Documents', 'release-builds', 'crusadia-win32-x64', 'resources', 'app', 'workflow');

    const { results, searchedPaths, directoryNotFound } = await searchDirectory(workflowPath, searchQuery);
    event.reply('searchResults', { results, searchedPaths, directoryNotFound, searchQuery });
});

app.on('ready', () => {
    createWindow();
    Menu.setApplicationMenu(null);

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) createWindow();
    });
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});
