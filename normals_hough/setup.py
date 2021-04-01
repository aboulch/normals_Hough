# from distutils.core import setup
# from distutils.extension import Extension

from setuptools import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy
import platform

if platform.system() == 'Windows':
  COMPILE_ARGS = ["/openmp", "/std:c11"]
else:
  COMPILE_ARGS = ["-fopenmp", "-std=c++11"]

VERSION = "0.1.0"

setup(
    name = "Hough Normal Estimator",
    ext_modules = [
      Extension(
        "NormalEstimatorHough",
        sources=[
          "src/NormalEstimatorHough.pyx",
          "src/normEstHough.cxx"
        ],
        include_dirs=["third_party_includes/", numpy.get_include()],
        language="c++",
        extra_compile_args = COMPILE_ARGS,
        extra_link_args=['-lgomp']
    )],
    cmdclass = {'build_ext': build_ext},
    version=VERSION
)