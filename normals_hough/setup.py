# from distutils.core import setup
# from distutils.extension import Extension

from setuptools import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

setup(
    name = "Hough Normal Estimator",
    ext_modules = [
      Extension(
        "NormalEstimatorHough",
        sources=[
          "src/NormalEstimatorHough.pyx",
          "src/normEstHough.cxx"
        ],
        include_dirs=["third_party_includes/"],
        language="c++",
        extra_compile_args = ["-fopenmp", "-std=c++11"],
        extra_link_args=['-lgomp']
    )],
    cmdclass = {'build_ext': build_ext},
)