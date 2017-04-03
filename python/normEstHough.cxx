#include "normEstHough.h"

NormEstHough::NormEstHough(){
        n_planes=700;
        n_rot=5;
        n_phi=15;
        tol_angle_rad=0.79;
        neighborhood_size = 200;
        use_density = false;
        k_density = 5;
}


NormEstHough::~NormEstHough(){}

int NormEstHough::size(){
    return pts.rows();
}

int NormEstHough::size_normals(){
    return nls.rows();
}



void NormEstHough::get_points(double* array, int m, int n) {

    int i, j ;
    int index = 0 ;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            array[index] = pts(i,j);
            index ++ ;
            }
        }
    return ;
}

void NormEstHough::get_normals(double* array, int m, int n) {

    int i, j ;
    int index = 0 ;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            array[index] = nls(i,j);
            index ++ ;
            }
        }
    return ;
}

void NormEstHough::set_points(double* array, int m, int n){
    // resize the point cloud
    pts.resize(m,3);

    // fill the point cloud
    int i, j ;
    int index = 0 ;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            pts(i,j) = array[index];
            index ++ ;
        }
    }
    return ;
}

void NormEstHough::set_normals(double* array, int m, int n){
    // resize the point cloud
    nls.resize(m,3);

    // fill the point cloud
    int i, j ;
    int index = 0 ;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            nls(i,j) = array[index];
            index ++ ;
        }
    }
    return ;
}
