cmake_minimum_required(VERSION 3.27)
project(Stop-Motion)

set(CMAKE_ENBALE_COMPILATION_COMMANDS = true) 

# Ensure C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Find wxWidgets
set(wxWidgets_ROOT_DIR </Users/bartek/wxWidgets-3.2.4/buildOSX>)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# Include directories
include_directories(include)

# Collect all .cpp and .h files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} MyApp.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} )
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})


