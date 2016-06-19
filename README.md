# normals_Hough

Normal Estimation in Unstructured Point Clouds with Hough transform

# Paper

Please acknowledge our the reference paper :

"Deep Learning for Robust Normal Estimation in Unstructured Point Clouds " by Alexandre Boulch and Renaud Marlet, Symposium of Geometry Processing 2016, Computer Graphics Forum


# Dependencies

Eigen and nanoflann (assumed to be in the source folder)

PCL: ply read only (main.cpp)

Boost: argument parsing (main.cpp)

# Usage

HoughCNN_Exec [options] -i input_file.ply -o output_file.ply
