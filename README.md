# SaberTask

## Linux
```
git clone https://github.com/YuryAlkevich/SaberTask
cd SaberTask
mkdir build && cd build
cmake ..
make
ctest --verbose
```

## Windows

```
git clone https://github.com/YuryAlkevich/SaberTask
cd SaberTask
mkdir build
cd build
cmake ..
cmake --build . --config Release
ctest --verbose