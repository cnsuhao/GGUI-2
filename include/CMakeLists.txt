#include_directories(${DERP_SOURCE_DIR}/code)
# add_sources(main.cpp)

# file( GLOB SRCS *.c *.h *.cpp *.hpp ../src/*.c ../src/*.h ../src/*.cpp ../src/*.hpp) 
# ile( GLOB HEADERS *.c *.h *.cpp *.hpp) 
file( GLOB SRCS *.c *.h *.cpp *.hpp ../src/*.c ../src/*.h ../src/*.cpp ../src/*.hpp) 

add_executable( ${ExeName} ${SRCS} )

if (MSVC)
 #   target_link_libraries(${ExeName} ${LIBDIR}/opengl32.lib ${LIBDIR}/glew32.lib ${LIBDIR}/SDL2.lib ${LIBDIR}/SDL2main.lib)    
    set(LIBDIR "C:/Dependencies/lib")
    find_library(SDL_LIBRARY SDL2 HINTS ${LIBDIR}/)
    find_library(SDLmain_LIBRARY SDL2main HINTS ${LIBDIR}/)
    find_library(GLEW_LIBRARY glew32 HINTS ${LIBDIR}/)
    target_link_libraries(${ExeName} PUBLIC opengl32.lib ${SDL_LIBRARY} ${SDLmain_LIBRARY} ${GLEW_LIBRARY})
endif (MSVC)
