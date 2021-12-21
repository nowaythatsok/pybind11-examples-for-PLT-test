import numpy as np
from cpp_mean_module_name import cpp_mean_array, cpp_mean_vector

def main():

    for i in range(100):

        length  = np.random.randint(low=10, high=100)
        arr     = np.random.rand(length)*2000-1000

        np_avg  = np.mean(arr)
        cpp_avg = cpp_mean_array(arr)

        if not np.isclose(np_avg, cpp_avg):
            print("(Array) These averages are not really close, test failed!")
            print("try", i+1)
            print("length", length)
            print("arr", list(arr))
            print("np_avg", np_avg)
            print("cpp_avg", cpp_avg)

            return 0

        cpp_avg = cpp_mean_vector(arr)

        if not np.isclose(np_avg, cpp_avg):
            print("(Vector) These averages are not really close, test failed!")
            print("try", i+1)
            print("length", length)
            print("arr", list(arr))
            print("np_avg", np_avg)
            print("cpp_avg", cpp_avg)

            return 0

    print("Test terminated successfully.")

if __name__=='__main__':
    main()
