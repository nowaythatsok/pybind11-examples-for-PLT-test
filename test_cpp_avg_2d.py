import numpy as np
from cpp_mean_module_name import cpp_mean_2d_array, cpp_mean_2d_vector



def main():

    for i in range(100):

        n  = np.random.randint(low=3, high=10)
        m  = np.random.randint(low=3, high=10)
        arr= np.random.rand(n,m)*2000-1000

        axis = int(np.round(np.random.rand()))

        np_avg  = np.mean(arr, axis=axis)
        cpp_avg = cpp_mean_2d_array(arr, axis) # , axis=axis) does not work

        if not np.allclose(np_avg, cpp_avg):
            print("(Array) These averages are not really close, test failed!")
            print("try", i+1)
            print("dims", n, m)
            print("axis", axis)
            print("np_avg", np_avg)
            print("cpp_avg", cpp_avg)

            return 0

        cpp_avg = cpp_mean_2d_vector(arr, axis)

        if not np.allclose(np_avg, cpp_avg):
            print("(Vector) These averages are not really close, test failed!")
            print("try", i+1)
            print("dims", n, m)
            print("axis", axis)
            print("np_avg", np_avg)
            print("cpp_avg", cpp_avg)

            return 0

    print("Test terminated successfully.")

if __name__=='__main__':
    main()