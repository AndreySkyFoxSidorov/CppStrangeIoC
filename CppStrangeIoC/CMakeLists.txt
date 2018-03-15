cmake_minimum_required(VERSION 2.8) 
project(StrengeIOCcpp)				# Proj Name

set(SOURCE_EXE main.cpp)			# Main

# binding
include_directories(framework/binding)			# pattern binding Include
add_subdirectory(framework/binding)				# pattern binding Source

# command
include_directories(framework/command)			# pattern command Include
add_subdirectory(framework/command)				# pattern command Source

# context
include_directories(framework/context)			# pattern context Include
add_subdirectory(framework/context)				# pattern context Source

# dispatcher
include_directories(framework/dispatcher)			# pattern dispatcher Include
add_subdirectory(framework/dispatcher)				# pattern dispatcher Source

# injector
include_directories(framework/injector)			# pattern injector Include
add_subdirectory(framework/injector)				# pattern injector Source

# mediation
include_directories(framework/mediation)			# pattern mediation Include
add_subdirectory(framework/mediation)				# pattern mediation Source

# pool
include_directories(framework/pool)			# pattern pool Include
add_subdirectory(framework/pool)				# pattern pool Source

# reflector
include_directories(framework/reflector)			# pattern reflector Include
add_subdirectory(framework/reflector)				# pattern reflector Source

# sequencer
include_directories(framework/sequencer)			# pattern sequencer Include
add_subdirectory(framework/sequencer)				# pattern sequencer Source

# signal
include_directories(framework/signal)			# pattern signal Include
add_subdirectory(framework/signal)				# pattern signal Source

add_executable(main ${SOURCE_EXE})	# add executable

target_link_libraries(main framework/binding)		# pattern binding Link Libraries
target_link_libraries(main framework/command)		# pattern command Link Libraries
target_link_libraries(main framework/context)		# pattern context Link Libraries
target_link_libraries(main framework/dispatcher)	# pattern dispatcher Link Libraries
target_link_libraries(main framework/injector)		# pattern injector Link Libraries
target_link_libraries(main framework/mediation)		# pattern mediation Link Libraries
target_link_libraries(main framework/pool)			# pattern pool Link Libraries
target_link_libraries(main framework/reflector)		# pattern reflector Link Libraries
target_link_libraries(main framework/sequencer)		# pattern sequencer Link Libraries
target_link_libraries(main framework/signal)		# pattern signal Link Libraries



