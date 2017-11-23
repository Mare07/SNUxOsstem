
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MedicalDemo4)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MedicalDemo4 MACOSX_BUNDLE MedicalDemo4.cxx )
 
target_link_libraries(MedicalDemo4 ${VTK_LIBRARIES})
