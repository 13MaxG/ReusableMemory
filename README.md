```
conda env create -f environment.yml
```
```
conda env update -f environment.yml
```
```
conda env export --from-history > environment.yml
```


Create settings
``` 
{
    "cmake.configureArgs": [
        "-DCMAKE_PREFIX_PATH=/opt/homebrew/Caskroom/miniconda/base/envs/Reusable"
    ]
}
```