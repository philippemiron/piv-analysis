cmake_minimum_required(VERSION 3.3)
project(piv)

# Make sure to compile and link with g++-5/6
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-6")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fopenmp -lblas -llapack -std=c++11")

include_directories(lib/tecio/tecsrc)
include_directories(src)

set(SOURCE_FILES
        src/include.hpp
        src/diffint.cpp
        src/diffint.hpp
        src/matrix.cpp
        src/matrix.hpp
        src/stats.cpp
        src/stats.hpp
        src/tecplotio.cpp
        src/tecplotio.hpp
        src/windows.cpp
        src/windows.hpp
        )

add_executable(avg average.cpp ${SOURCE_FILES})
add_executable(avgs average_stereo.cpp ${SOURCE_FILES})
add_executable(phaavg phase_average.cpp ${SOURCE_FILES})
add_executable(phaavgs phase_average_stereo.cpp ${SOURCE_FILES})
add_executable(q q.cpp ${SOURCE_FILES})
add_executable(f2p field2points.cpp ${SOURCE_FILES})
add_executable(p2f points2field.cpp ${SOURCE_FILES})
add_executable(fft fft.cpp ${SOURCE_FILES})
add_executable(fftplan fftplan.cpp ${SOURCE_FILES})

if (UNIX AND NOT APPLE)
    target_link_libraries(avg ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(avgs ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(phaavg ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(phaavgs ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(q ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(f2p ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(p2f ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(fft ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
    target_link_libraries(fftplan ${CMAKE_SOURCE_DIR}/lib/libtecio_linux.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_linux.a)
elseif (WIN32)
    # Not tested on Windows so you're on your own
elseif (APPLE)
    target_link_libraries(avg ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(avgs ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(phaavg ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(phaavgs ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(q ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(f2p ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(p2f ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(fft ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
    target_link_libraries(fftplan ${CMAKE_SOURCE_DIR}/lib/libtecio_osx.a ${CMAKE_SOURCE_DIR}/lib/libfftw3_macos.a)
endif (UNIX AND NOT APPLE)