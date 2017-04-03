

# If the pyx file is a C++ file, we should specify that here.
set_source_files_properties(
 ${CMAKE_SOURCE_DIR}/python/NormalEstimatorHough.pyx
 PROPERTIES CYTHON_IS_CXX TRUE )



# Multi-file cython modules do not appear to be working at the moment.
cython_add_module( NormalEstimatorHough
   NormalEstimatorHough.pyx
   normEstHough.cxx
   )
target_link_libraries(NormalEstimatorHough ${EXTRA_LIBS} ${Boost_LIBRARIES} ${PCL_LIBRARIES} ${PROJECT_LINK_LIB} )
