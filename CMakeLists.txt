cmake_minimum_required(VERSION 3.27)
project(Stop-Motion)



# Ensure C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I/opt/homebrew/opt/llvm/include/c++/v1")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/llvm/lib -lc++")

# Find wxWidgets
set(wxWidgets_ROOT_DIR </Users/bartek/wxWidgets-3.2.4/buildOSX>)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# Include directories
include_directories(include)

# Find FreeImage
find_library(FREEIMAGE_LIBRARY FreeImage PATHS /path/to/freeimage/lib)

# Find X11 if using CImg for display (on macOS, make sure XQuartz is installed)
find_package(X11 REQUIRED)

# Collect all .cpp and .h files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} MyApp.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${FREEIMAGE_LIBRARY} ${X11_LIBRARIES})
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})


