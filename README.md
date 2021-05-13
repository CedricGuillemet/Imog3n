# Imog3n

MacOs : [![Build Status](https://cedricguillemet.visualstudio.com/Imog3n/_apis/build/status/CedricGuillemet.Imog3n?branchName=main&jobName=macOS)](https://cedricguillemet.visualstudio.com/Imog3n/_build/latest?definitionId=3&branchName=main)
Linux : [![Build Status](https://cedricguillemet.visualstudio.com/Imog3n/_apis/build/status/CedricGuillemet.Imog3n?branchName=main&jobName=Ubuntu_Clang)](https://cedricguillemet.visualstudio.com/Imog3n/_build/latest?definitionId=3&branchName=main)
Windows : [![Build Status](https://cedricguillemet.visualstudio.com/Imog3n/_apis/build/status/CedricGuillemet.Imog3n?branchName=main&jobName=win32_x64)](https://cedricguillemet.visualstudio.com/Imog3n/_build/latest?definitionId=3&branchName=main)

## Build

Binary output directory is `bin/`

### Clone repo
```
git clone git clone https://github.com/CedricGuillemet/Imog3n.git
cd Imog3n
git submodule update --init --recursive
```

### Windows
```
mkdir build
cd build
cmake ..
```
And open .sln with Visual Studio

### Mac
```
mkdir build
cd build
cmake .. -G Xcode
```

And open project with Xcode

### Linux
```
mkdir build
cd build
cmake .. -G Ninja
ninja
```

### Web

Clone and activate emsdk https://github.com/emscripten-core/emsdk
Install your favorite build tool supported by cmake (ninja, make, ...)
```
mkdir build
cd build
emcmake cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
```
