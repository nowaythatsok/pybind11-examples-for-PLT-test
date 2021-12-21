#include <iostream>
#include <pybind11/pybind11.h>
// these 2 make the list <--> vector conversions!
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
// this is to be able to use buffers and return numpy objects for example for the convolution
#include <pybind11/numpy.h>


namespace py = pybind11;


// Averaging 1D structures, returning a single number

double mean_array0(double* array, uint length){
    // binding this directly does not work, because pybind would expect array to be a pointer to a single value
    // to let it know that this is not so, we need to use buffers
    double sum = 0;
    for (uint i=0; i<length; i++){
        sum += array[i]; 
    }
    return sum / length;
}

double mean_array_wrapper(py::array_t<double> input){
    // this is here to fix the previous pointer issue, and this requires the numpy.h
    // https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html#arrays
    py::buffer_info buf = input.request();

    if (buf.ndim != 1)
        throw std::runtime_error("Number of dimensions must be one");

    uint length = buf.size;
    double *ptr = static_cast<double *>(buf.ptr);

    return mean_array0(ptr, length);
}


double mean_vector(std::vector<double> v){
    // this works out of the box, no wrapper needed
    double sum = 0;
    for(uint i=0; i < v.size(); i++){
        sum += v[i]; 
    }
    return sum / v.size();
}

// Averaging a 2D structure along rows or columns
// I will separate these functions in a different cpp file just to decrease the clutter here
#include "cpp_mean_2d_source.cpp"

// make a wrapper for the array function
py::array_t<double> mean_2d_array_wrapper(py::array_t<double> input, int axis = 0){

    // do conversion input
    py::buffer_info input_buf   = input.request();
    uint len0                   = input_buf.shape[0];
    uint len1                   = input_buf.shape[1];
    double *array               = static_cast<double *>(input_buf.ptr);

    // make a wrapped array for the output
    uint avg_arr_size;
    if (axis==0){
        avg_arr_size = len1;
    }
    else if (axis==1){
        avg_arr_size = len0;
    }
    else throw std::runtime_error("Axis must be either 0 or 1");

    auto result                 = py::array_t<double>(avg_arr_size);
    py::buffer_info result_buf  = result.request();
    double *result_ptr          = static_cast<double *>(result_buf.ptr);
    

    // run function
    mean_2d_array0( array, result_ptr, len0, len1, axis);

    return result;
}


PYBIND11_MODULE(cpp_mean_module_name, handle){
    handle.doc() = "Test module.";
    
    handle.def("cpp_mean_array0", &mean_array0, "Very simple average computation using a C array in C++.");
    handle.def("cpp_mean_array",  &mean_array_wrapper, "Very simple average computation using a C array in C++ wrapped.");
    handle.def("cpp_mean_vector", &mean_vector, "Very simple average computation using a C++ vector.");
    
    handle.def("cpp_mean_2d_array0", &mean_2d_array0);
    handle.def("cpp_mean_2d_array", &mean_2d_array_wrapper);
    handle.def("cpp_mean_2d_vector", &mean_2d_vector);
}