# normals_Hough

Normal Estimation in Unstructured Point Clouds with Hough transform

# Paper

Please acknowledge our reference paper :

"Fast and robust normal estimation for point clouds with sharp features" by Alexandre Boulch and Renaud Marlet, Symposium on Geometry Processing 2012 (SGP 2012) and Computer Graphics Forum



# Code

The code for normal estimation is C++ hearder only. Three version are proposed, previous version are located in ```archives/cgal/``` and ```archives/pcl/``` relies on CGAL and PCL libriaries.
The current version Normals.h relies on Eigen and nanoflann (we provide them in the ```third_party_includes``` folder).

# Parameters

* `neighborhood_size (default 200)` the neighborhood size for computing the normals.
* `n_planes (default 700)` the number of random sample to be picked to estimate the distribution.
* `n_rot (default 5)` the number of random rotations of the accumulator.
* `n_phi (default 15)` the discretization of the sphere accumulator.
* `tol_angle_rad (default 0.79)` the maximal angle used for normal cluster (final normal decision).
* `k_density (defautl 5)` the neighborhood size for density computation.

# Examples and tests

## Python

Using the library with Python requires building the wrapper.
All python code has been built and tested under Unbuntu 18.04 and Anaconda.

### Building the wrapper
```
pip install -ve /path/to/notmals_Hough/
```

### Python test
From the root directory:
```
python example.py
```
The script creates a point cloud on a cube and estimate the normals.
It produces a ```.xyz``` containing both points and normals, it can be displayed using Meshlab or CloudCompare.

## C++

In the folder ```test_cpp```, the executable can be generated using CMake.

### Usage

Hough_Exec [options] -i input_file.xyz -o output_file.xyz

# Author webpage

[Alexandre Boulch](www.boulch.eu)

# License

The code is released under a GPLv3 license. For commercial purposes contact the authors.
The detailed licence is [here](LICENSE.md).

# Previous versions

Previous version of the code are located in folders ```archives/cgal/``` and ```archives/pcl/```
