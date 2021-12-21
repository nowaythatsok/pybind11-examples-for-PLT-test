# Averaging function Pybind11 examples

There are 1D and 2D examples, with arrays and vectors. 
Vectors are 1100% easier to use. 

## First get the pybind sources you ll need to include in your code
```sh
git clone https://github.com/pybind/pybind11.git
```

## Build shared object
```sh
mkdir build 
cd build
make ..
make
mv cpp_mean_module_name.* ..
cd ..
rm -rf build
```

## test in terminal
```sh
python3 
```
```py
from cpp_mean_module_name import *
import numpy as np
cpp_mean_array0.__doc__ # see? expect a single float instead of an array!
cpp_mean_array.__doc__
cpp_mean_array([0,1,2])
cpp_mean_array(np.array([0,1,2]))
cpp_mean_vector.__doc__
cpp_mean_vector([0,1,2])
cpp_mean_vector(np.array([0,1,2]))
```

Run the test code
```sh
python3 test_cpp_avg.py
```