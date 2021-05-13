# Imog3n

## Build

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
