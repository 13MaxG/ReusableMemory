```
conda env create -f environment.yml
```
```
conda env update -f environment.yml
```
```
conda env export --from-history > environment.yml
```
```
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/Caskroom/miniconda/base/envs/Reusable  -DCMAKE_INSTALL_RPATH=/opt/homebrew/Caskroom/miniconda/base/envs/Reusable/lib
make 
ctest
```
Create settings
``` 
{
     "cmake.configureArgs": [
        "-DCMAKE_PREFIX_PATH=/opt/homebrew/Caskroom/miniconda/base/envs/Reusable", 
        "-DCMAKE_INSTALL_RPATH=/opt/homebrew/Caskroom/miniconda/base/envs/Reusable/lib"
    ],
}
```