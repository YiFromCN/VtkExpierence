cmake_minimum_required(VERSION 2.8)

PROJECT(polydataConnect )

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(polydataConnect  MACOSX_BUNDLE polydataConnect.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(polydataConnect  ${VTK_LIBRARIES})
else()
  target_link_libraries(polydataConnect  vtkHybrid vtkWidgets)
endif()
