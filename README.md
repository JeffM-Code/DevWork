# DevWork 
Main app in: release-builds/crusadia-win32-x64/crusadia.exe, for demonstration of concepts ive been studying.
To run app, place the release-builds directory into Documents as the app will look for relevant files from ~/Documents/release-builds/crusadia-win32-x64/... (working on better path management so this doesnt have to be the case), and will also need Microsoft Visual C++ Redistributable x64: https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170 as well to run app. The code for the app is in: app-sources/ so if the executable in release builds doesnt work, its possible to build the electron app with that code.
Working on cleaning up code and other aspects of app for release such as ensuring better dynamic file path handling (works regardless of Document folder placement), and working on including other full stack applications to repo.
