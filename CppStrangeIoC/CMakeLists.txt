cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(StrengeIOCcpp)				# Proj Name

set(CMAKE_SUPPRESS_REGENERATION true)

set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/)

# -------------------------------------------------------------------------------------
# StrengeIOCcpp
file(GLOB STRENGEIOCCPP_SOURCE "*.cpp")
file(GLOB STRENGEIOCCPP_HEADERS "*.h")
source_group( StrengeIOCcpp FILES ${STRENGEIOCCPP_SOURCE} ${STRENGEIOCCPP_HEADERS} )
include_directories(${CMAKE_CURRENT_BINARY_DIR} ./)

# -------------------------------------------------------------------------------------
# StrengeIOCcpp binding
file(GLOB BINDING_SOURCE "framework/binding/*.cpp")
file(GLOB BINDING_HEADERS "framework/binding/*.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR} framework/binding/)
source_group( StrengeIOCcpp\\binding FILES ${BINDING_SOURCE} ${BINDING_HEADERS} )


# -------------------------------------------------------------------------------------
# StrengeIOCcpp dispatcher
#file(GLOB DISPATCHER_SOURCE "framework/dispatcher/*.cpp")
#file(GLOB DISPATCHER_HEADERS "framework/dispatcher/*.h")
#include_directories(${CMAKE_CURRENT_BINARY_DIR} framework/dispatcher/)
#source_group( StrengeIOCcpp\\dispatcher FILES ${DISPATCHER_SOURCE} ${DISPATCHER_HEADERS} )


# -------------------------------------------------------------------------------------
add_executable(	${PROJECT_NAME} 
					${STRENGEIOCCPP_SOURCE} 
					${STRENGEIOCCPP_HEADERS} 
					${BINDING_SOURCE}
					${BINDING_HEADERS} 
					#${DISPATCHER_SOURCE}
					#${DISPATCHER_HEADERS} 
					)





