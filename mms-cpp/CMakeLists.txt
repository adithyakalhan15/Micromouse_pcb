cmake_minimum_required(VERSION 3.28.0)

project(mmc)

# Add the executable
add_executable(main Main.cpp API.cpp)


# include_directories(API.h)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
# set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)


# If you have additional .cpp files, list them here
# add_executable(YourExecutableName your_source_file.cpp additional_file.cpp)

# If you have additional header files, list their directories here
# include_directories(include)

# If you have additional libraries, link them here
# target_link_libraries(YourExecutableName YourLibraryName)
