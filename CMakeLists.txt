cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules/"  "/usr/share/SFML/cmake/Modules/")

project(TheLastSurvivor)

add_subdirectory(Tweeny)
add_subdirectory(Common)
add_subdirectory(Game)
add_subdirectory(ResourceManager)
add_subdirectory(Bullet)

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
endif()

set(SOURCE main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE
                                      Tweeny
                                      Common
                                      Game
                                      Bullet
                                      ResourceManager)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-audio sfml-window)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

