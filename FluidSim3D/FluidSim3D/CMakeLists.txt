cmake_minimum_required(VERSION 3.15)
project(FluidSim3D CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")

# pkg_search_module(GLFW REQUIRED glfw3)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
set(
        SOURCE_FILES
        "classicSolver.cpp"
        "FluidRenderer3d.cpp"
        "FluidSim3dMain.cpp"
        "FluidSolver3d.cpp"
        "MarchingCubes.cpp"
        "RenderUtil.cpp"
        "SimUtil.cpp"
)
add_executable(main ${SOURCE_FILES})
link_libraries(${GLFW_LIBRARY_DIRS})

target_link_libraries(main ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} )
# ################################################################################
# # Source groups
# ################################################################################
# set(no_group_source_files
#     "basicShader.fs"
#     "basicShader.vs"
#     "normalShader.fs"
#     "normalShader.vs"
# )
# source_group("" FILES ${no_group_source_files})
#
# set(Header_Files
#     "classicSolver.h"
#     "FluidRenderer3d.h"
#     "FluidSolver3d.h"
#     "MarchingCubes.h"
#     "RenderUtil.h"
#     "resource.h"
#     "SimUtil.h"
# )
# source_group("Header Files" FILES ${Header_Files})
#
# set(Shaders
#     "frag.glsl"
#     "vert.glsl"
# )
# source_group("Shaders" FILES ${Shaders})
#
# set(Source_Files
#     "classicSolver.cpp"
#     "FluidRenderer3d.cpp"
#     "FluidSim3dMain.cpp"
#     "FluidSolver3d.cpp"
#     "MarchingCubes.cpp"
#     "RenderUtil.cpp"
#     "SimUtil.cpp"
# )
# source_group("Source Files" FILES ${Source_Files})
#
# set(ALL_FILES
#     ${no_group_source_files}
#     ${Header_Files}
#     ${Shaders}
#     ${Source_Files}
# )
#
# ################################################################################
# # Target
# ################################################################################
# add_executable(${PROJECT_NAME} ${ALL_FILES})
#
# # use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
# set(ROOT_NAMESPACE FluidSim3D)
#
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     VS_GLOBAL_KEYWORD "Win32Proj"
# )
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     set_target_properties(${PROJECT_NAME} PROPERTIES
#         INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#     set_target_properties(${PROJECT_NAME} PROPERTIES
#         INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
#     )
# endif()
# ################################################################################
# # Include directories
# ################################################################################
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     target_include_directories(${PROJECT_NAME} PUBLIC
#         "$<$<CONFIG:Debug>:"
#             "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.0/include"
#         ">"
#         "${CMAKE_CURRENT_SOURCE_DIR}/include"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#     target_include_directories(${PROJECT_NAME} PUBLIC
#         "${CMAKE_CURRENT_SOURCE_DIR}/include;"
#         "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.0/include"
#     )
# endif()
#
# ################################################################################
# # Compile definitions
# ################################################################################
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE
#         "$<$<CONFIG:Debug>:"
#             "_DEBUG"
#         ">"
#         "$<$<CONFIG:Release>:"
#             "NDEBUG"
#         ">"
#         "_CONSOLE;"
#         "UNICODE;"
#         "_UNICODE"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE
#         "$<$<CONFIG:Debug>:"
#             "_DEBUG"
#         ">"
#         "$<$<CONFIG:Release>:"
#             "NDEBUG"
#         ">"
#         "WIN32;"
#         "_CONSOLE;"
#         "UNICODE;"
#         "_UNICODE"
#     )
# endif()
#
# ################################################################################
# # Compile and link options
# ################################################################################
# if(MSVC)
#     if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#         target_compile_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /Od;
#                 ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
#             >
#             $<$<CONFIG:Release>:
#                 /O2;
#                 /Oi;
#                 ${DEFAULT_CXX_RUNTIME_LIBRARY};
#                 /Gy
#             >
#             /W3;
#             ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
#             ${DEFAULT_CXX_EXCEPTION_HANDLING};
#             /Y-
#         )
#     elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#         target_compile_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /Od;
#                 ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
#             >
#             $<$<CONFIG:Release>:
#                 /O2;
#                 /Oi;
#                 ${DEFAULT_CXX_RUNTIME_LIBRARY};
#                 /Gy
#             >
#             /W3;
#             ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
#             ${DEFAULT_CXX_EXCEPTION_HANDLING};
#             /Y-
#         )
#     endif()
#     if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#         target_link_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /INCREMENTAL
#             >
#             $<$<CONFIG:Release>:
#                 /OPT:REF;
#                 /OPT:ICF;
#                 /INCREMENTAL:NO
#             >
#             /DEBUG;
#             /SUBSYSTEM:CONSOLE
#         )
#     elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#         target_link_options(${PROJECT_NAME} PRIVATE
#             $<$<CONFIG:Debug>:
#                 /INCREMENTAL
#             >
#             $<$<CONFIG:Release>:
#                 /OPT:REF;
#                 /OPT:ICF;
#                 /INCREMENTAL:NO
#             >
#             /DEBUG;
#             /SUBSYSTEM:CONSOLE
#         )
#     endif()
# endif()
#
# ################################################################################
# # Dependencies
# ################################################################################
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     set(ADDITIONAL_LIBRARY_DEPENDENCIES
#         "$<$<CONFIG:Debug>:"
#             "OpenCL"
#         ">"
#         "glew32;"
#         "glew32s;"
#         "SDL2;"
#         "SDL2main;"
#         "SDL2test;"
#         "OpenGL32"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#     set(ADDITIONAL_LIBRARY_DEPENDENCIES
#         "OpenCL;"
#         "glew32;"
#         "glew32s;"
#         "SDL2;"
#         "SDL2main;"
#         "SDL2test;"
#         "OpenGL32;"
#         "AntTweakBar64"
#     )
# endif()
# target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
#
# if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
#     target_link_directories(${PROJECT_NAME} PUBLIC
#         "$<$<CONFIG:Debug>:"
#             "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.0/lib/x64"
#         ">"
#         "${CMAKE_CURRENT_SOURCE_DIR}/./lib"
#     )
# elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
#     target_link_directories(${PROJECT_NAME} PUBLIC
#         "${CMAKE_CURRENT_SOURCE_DIR}/./lib;"
#         "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v9.0/lib/x64"
#     )
# endif()
#
# # use_package(${PROJECT_NAME} nupengl.core.redist 0.1.0.1)
# # use_package(${PROJECT_NAME} nupengl.core 0.1.0.1)
# # use_package(${PROJECT_NAME} glm 0.9.7.1)
