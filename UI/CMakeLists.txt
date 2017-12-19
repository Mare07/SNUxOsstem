
cmake_minimum_required(VERSION 2.8)

project(ImageProcessing)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

if (ITKVtkGlue_LOADED)
	find_package(VTK REQUIRED)
	include(${VTK_USE_FILE})
endif()

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

set(OBJECTS ffillwhole.cpp shapematch.cpp)

add_executable(ui ui.cpp ${OBJECTS})

if( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(ui ITKReview ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} ${GTK3_LIBRARIES})
else( "${ITK_VERSION_MAJOR}" LESS 4 )
  target_link_libraries(ui ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} ${GTK3_LIBRARIES})
endif( "${ITK_VERSION_MAJOR}" LESS 4 )
