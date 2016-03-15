cmake_minimum_required(VERSION 2.8.4) # Avoid moaning about cygwin
project(ailab-week7)

# cmakew .. -G "Visual Studio 14 2015 Win64"

function(check_env var)
if (NOT DEFINED ${var})
  if (DEFINED ENV{${var}})
    set(${var} $ENV{${var}} CACHE PATH "Location of ${var}")
  else()
    message(SEND_ERROR "${var} is NOT defined")
    set(${var} ""           CACHE PATH "Location of ${var}")
  endif()
endif()
endfunction(check_env)

if (MSVC)
  if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(SEND_ERROR "Please build for 64-bit MSVS.")
  endif ()

  check_env(OPENCV_ROOT)
  include_directories(${OPENCV_ROOT}/include)
  link_directories(${OPENCV_ROOT}/x64/vc14/lib)
  set(OpenCV_LIBS opencv_world310.lib)
else ()
  find_package(OpenCV REQUIRED)
endif (MSVC)

foreach(n 1_capture_show_image 2_capture_show_video 3_capture_show_record_video 4_filter)
  add_executable(${n} src/${n}.cpp)
  target_link_libraries(${n} ${OpenCV_LIBS})
endforeach(n)

#include_directories(./face/include)
#add_definitions(-D__OPENCV_BUILD=1)
#set(n facerec_eigenfaces)
#add_executable(${n} ./face/samples/${n}.cpp ./face/src/facerec.cpp)
##add_executable(${n} ${n}.cpp)
#target_link_libraries(${n} ${OpenCV_LIBS})
