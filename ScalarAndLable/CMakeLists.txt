cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(MotionBlur)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkIOPLY
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkCommonDataModel
  vtkIOGeometry
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkRenderingLabel
  QUIET
)

if (NOT VTK_FOUND)
  message("Skipping MotionBlur: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(MotionBlur MACOSX_BUNDLE MotionBlur.cxx )
  target_link_libraries(MotionBlur PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(MotionBlur MACOSX_BUNDLE MotionBlur.cxx )
  target_link_libraries(MotionBlur PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS MotionBlur
    MODULES ${VTK_LIBRARIES}
    )
endif ()