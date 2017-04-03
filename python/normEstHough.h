#ifndef NORMALS_HOUGH_PYTHON_HEADER
#define NORMALS_HOUGH_PYTHON_HEADER

#include "Normals.h"

class NormEstHough:public Eigen_Normal_Estimator{

public:
    NormEstHough();
    ~NormEstHough();

    int size();
    int size_normals();

    void get_points(double* array, int m, int n);
    void get_normals(double* array, int m, int n);
    void set_points(double* array, int m, int n);
    void set_normals(double* array, int m, int n);


};


#endif
