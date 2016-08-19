# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0.2)
project (GGUIProject)


#if (CMAKE_SYSTEM_NAME STREQUAL Darwin)
	
#endif (CMAKE_SYSTEM_NAME STREQUAL Darwin)

set(ExeName GGUI)
# set(VulkanProject_BINARY_DIR build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)


if (MSVC)
    include_directories(${CMAKE_BINARY_DIR}/../include "C:\\Dependencies\\include")
endif (MSVC)
if (UNIX)
	# SET(MACOSX_DEPLOYMENT_TARGET ${DARWIN_MAJOR_SDK_VERSION}.${DARWIN_MINOR_SDK_VERSION})
	# SET(CMAKE_CXX_FLAGS "--sysroot ${CMAKE_OSX_SYSROOT} ${CMAKE_CXX_FLAGS}")
	# MESSAGE("Setting MACOSX_DEPLOYMENT_TARGET to '${MACOSX_DEPLOYMENT_TARGET}'.")
	# append_cxx_compiler_flags("-std=c++11 -DNDEBUG" "CLANG" CMAKE_CXX_FLAGS)
    # append_cxx_compiler_flags("-stdlib=libc++" "CLANG" CMAKE_CXX_FLAGS)
    include_directories(${CMAKE_BINARY_DIR}/../include)
endif (UNIX)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (src)
add_subdirectory (include)

if (UNIX)
	# target_link_libraries(${ExeName} lGL lGLEW lSDL2 lSDL2main)	
	#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lGL -lGLEW -lSDL2 -lSDL2main" )	

find_package (SDL2 REQUIRED)
	if (SDL2_FOUND)
	  MESSAGE("Include: ${SDL2_INCLUDE_DIRS}.")
	  MESSAGE("Libraries: ${SDL2_LIBRARIES}.")
	  include_directories(${SDL2_INCLUDE_DIRS})
	  target_link_libraries(${ExeName} ${SDL2_LIBRARIES})
	endif (SDL2_FOUND)
endif (UNIX)
if (MSVC)
	set(LIBDIR "C:/Dependencies/lib")
    target_link_libraries(${ExeName} ${LIBDIR}/opengl32.lib ${LIBDIR}/glew32.lib ${LIBDIR}/SDL2.lib ${LIBDIR}/SDL2main.lib)
endif (MSVC)


# add_executable (Build/Derp main.cpp)



