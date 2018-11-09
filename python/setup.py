from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext


ext_modules = [Extension(
       "NormalEstimatorHough",
       sources=["NormalEstimatorHough.pyx", "normEstHough.cxx"],
       include_dirs=["third_party_includes/", "../include"],
       language="c++",             # generate C++ code
       extra_compile_args = ["-fopenmp", "-std=c++11"]
  )]

setup(
    name = "Hough Normal Estimator",
    ext_modules = ext_modules,
    cmdclass = {'build_ext': build_ext},
)