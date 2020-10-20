cmake_minimum_required(VERSION 3.17)

#set(SFML_DIR ./sfml)
set(CMAKE_PREFIX_PATH ./sfml)
set(SFML_INCLUDE_DIR "./sfml/include")
set(SFML_LIBRARY_DIR "./sfml/build/lib")

include_directories(SFML_INCLUDE_DIR)
link_directories(SFML_LIBRARY_DIR)

#find_package(SFML COMPONENTS system window graphics network audio)

#find_package(SFML)

add_subdirectory(sfml)