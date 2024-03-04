# DevWork 
Main app is an electron app "db-electron" for demonstration of concepts ive been studying. To run it, you'll need Microsoft Visual C++ Redistributable x64: https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170. It reads from files in: ~\external\Pisty\data in a specific format (one value per line) and does some calculations or "processing" using them by making a database of these values to process, so more can be added to the data files or new ones can be created to better test robustness of application, but will try to keep improving it. Generally its simply a way to understand the way the data is changing throughout the app, where processing occurs in many steps, with great detail at each. app-sources is for the source code for the all applications for db-electron and the packaged app is in release-builds in: ~release-builds\db-electron-win32-x64\db-electron.exe.
