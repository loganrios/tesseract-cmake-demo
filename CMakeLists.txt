cmake_minimum_required(VERSION 3.25)

project(TessDemo)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

include(FetchContent)

FetchContent_Declare(
  zlib
  GIT_REPOSITORY https://github.com/madler/zlib.git
  GIT_TAG v1.3.1
)

FetchContent_Declare(
  libpng
  GIT_REPOSITORY https://github.com/glennrp/libpng.git
  GIT_TAG v1.6.43
)

FetchContent_Declare(
  icu
  GIT_REPOSITORY https://github.com/unicode-org/icu.git
  GIT_TAG release-75-1
)

FetchContent_Declare(
  leptonica
  GIT_REPOSITORY https://github.com/DanBloomberg/leptonica.git
  GIT_TAG 1.84.1
)

FetchContent_Declare(
  tesseract
  GIT_REPOSITORY https://github.com/tesseract-ocr/tesseract.git
  GIT_TAG 5.4.0
)

# Technically not necessary;
# we could just hard-download `eng.traineddata` from the URL,
# but this keeps us more flexible.
FetchContent_Declare(
  tessdata
  GIT_REPOSITORY https://github.com/tesseract-ocr/tessdata.git
  GIT_TAG 4.1.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/tessdata
)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(OPENCV_FORCE_3RDPARTY_BUILD ON)
set(BUILD_ZLIB OFF CACHE BOOL "")
set(WITH_OBSENSOR OFF CACHE BOOL "")
set(BUILD_opencv_videoio OFF CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(BUILD_EXAMPLES OFF CACHE BOOL "")
set(BUILD_TESTS OFF CACHE BOOL "")
set(BUILD_PERF_TESTS OFF CACHE BOOL "")
set(BUILD_opencv_apps OFF CACHE BOOL "")
set(WITH_IPP OFF CACHE BOOL "")
set(WITH_CUDA OFF CACHE BOOL "")
set(WITH_OPENCL OFF CACHE BOOL "")
set(WITH_ORBBEC OFF CACHE BOOL "" FORCE)
set(BUILD_LIST "core,imgproc,imgcodecs,highgui" CACHE STRING "" FORCE)

FetchContent_Declare(
  opencv
  GIT_REPOSITORY https://github.com/opencv/opencv.git
  GIT_TAG 4.10.0
)

FetchContent_MakeAvailable(zlib)

set(PNG_SHARED OFF CACHE BOOL "")
set(PNG_STATIC ON CACHE BOOL "")
set(PNG_TESTS OFF CACHE BOOL "")
FetchContent_MakeAvailable(libpng)

set(ICU_ROOT ${CMAKE_CURRENT_BINARY_DIR}/_deps/icu-src/icu4c)
set(ICU_BUILD_SHARED OFF)
set(ICU_BUILD_STATIC ON)
FetchContent_MakeAvailable(icu)

set(BUILD_PROG OFF CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
FetchContent_MakeAvailable(leptonica)

set(BUILD_TRAINING_TOOLS OFF CACHE BOOL "")
set(DISABLE_PKGCONFIG ON CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(DISABLED_LEGACY_ENGINE ON CACHE BOOL "")
set(DISABLE_ARCHIVE ON CACHE BOOL "")
set(DISABLE_CURL ON CACHE BOOL "")
set(DISABLE_OPENCL ON CACHE BOOL "")
FetchContent_MakeAvailable(tesseract)

add_dependencies(tesseract leptonica)

FetchContent_MakeAvailable(tessdata)

add_custom_target(tessdata)

target_include_directories(libtesseract
  PRIVATE
    ${leptonica_SOURCE_DIR}/src
    ${ICU_ROOT}/source/common
    ${ICU_ROOT}/source/i18n
)

FetchContent_MakeAvailable(opencv)

add_executable(tess-demo simple.cpp)

add_dependencies(tess-demo tessdata)

target_link_libraries(tess-demo
  PRIVATE
  libtesseract
  leptonica
  opencv_core
  opencv_imgproc
  opencv_highgui
)

target_include_directories(tess-demo
  PRIVATE
  ${tesseract_SOURCE_DIR}/include
  ${tesseract_BINARY_DIR}/include
  ${leptonica_SOURCE_DIR}/src
  ${leptonica_BINARY_DIR}/src
  ${opencv_SOURCE_DIR}/include
  ${opencv_BINARY_DIR}
  ${opencv_BINARY_DIR}/opencv2
)
