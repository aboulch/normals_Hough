from libcpp.string cimport string
import numpy as np
cimport numpy as np

cdef extern from "normEstHough.h":
    cdef cppclass NormEstHough:

        NormEstHough()

        void loadXYZ(string)
        void saveXYZ(string)

        void get_points(double*, int,int)
        void set_points(double*, int, int)
        void get_normals(double*, int,int)
        void set_normals(double*, int, int)

        void estimate_normals()

        int size()
        int size_normals()

        int get_T()
        void set_T(int)

        int get_n_phi()
        void set_n_phi(int)

        int get_n_rot()
        void set_n_rot(int)

        int get_K()
        void set_K(int)

        int get_density_sensitive()
        void set_density_sensitive(bool)

        double get_tol_angle_rad()
        void set_tol_angle_rad(float)

        int get_K_density()
        void set_K_density(int)
