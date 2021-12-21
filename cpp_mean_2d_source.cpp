#include <iostream>
#include <vector>

std::vector<double> mean_2d_vector(std::vector<std::vector<double>> v, int axis = 0){
    // axis selects which index to average over
    
    if (axis==0){
        std::vector<double> sum(v[0].size(), 0.0);

        for (uint i=0; i < v.size(); i++){
            for (uint j=0; j < v[0].size(); j++){
                sum[j] += v[i][j]; 
            }
        }

        for (uint j=0; j < sum.size(); j++){
            sum[j] /= v.size(); 
        }

        return sum;
    }
    else if (axis==1){
        std::vector<double> sum(v.size(), 0.0);

        for (uint i=0; i < v.size(); i++){
            for (uint j=0; j < v[0].size(); j++){
                sum[i] += v[i][j]; 
            }
        }

        for (uint i=0; i < sum.size(); i++){
            sum[i] /= v[0].size(); 
        }

        return sum;
    }
    else{
        throw std::runtime_error("Axis must be either 0 or 1");
    }
}


void mean_2d_array0(double* array, double* avg_arr, uint len0, uint len1, int axis = 0){

    // I dont want to write this again, this is why I will use the vector method inside
    // this array method is only here to show how it should be wrapped using buffers

    std::vector<std::vector<double>> v;
    for (uint j=0; j<len0; j++){
        std::vector<double> l;
        for (uint i=0; i<len1; i++){
            l.push_back(array[i+len1*j]);
        }
        v.push_back(l);
    }

    std::vector<double> avg = mean_2d_vector(v , axis );

    for (uint i=0; i<avg.size(); i++){
        avg_arr[i] = avg[i];
    }


    return;
}

