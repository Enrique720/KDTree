cmake_minimum_required(VERSION 3.17)
project(kdtree)


set(CMAKE_CXX_STANDARD 14)
set(EIGEN3_INCLUDE_DIR "/usr/include/eigen3")
set(YOU_NEED_X11 1)
set(YOU_NEED_PNG 1)
set(YOU_NEED_JPG 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

    message(STATUS "This project requires the CGAL library, and will not be compiled.")
    return()

endif()

add_executable(kdtree main.cpp CImg.h)

target_link_libraries(kdtree Threads::Threads)
target_link_libraries(kdtree X11)

if(${YOU_NEED_X11} EQUAL 1)
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(kdtree ${X11_LIBRARIES})
else()
    target_compile_definitions(kdtree PRIVATE cimg_display=0)
endif()

if(${YOU_NEED_JPG} EQUAL 1)
    message(STATUS "Looking for libjpg...")
    find_package(JPEG REQUIRED)
    include_directories(${JPEG_INCLUDE_DIR})
    target_link_libraries (kdtree ${JPEG_LIBRARY})
    target_compile_definitions(kdtree PRIVATE cimg_use_jpeg=1)
endif()

if(${YOU_NEED_PNG} EQUAL 1)
    message(STATUS "Looking for libpng...")
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    target_link_libraries (kdtree ${PNG_LIBRARY})
    target_compile_definitions(kdtree PRIVATE cimg_use_png=1)
endif()