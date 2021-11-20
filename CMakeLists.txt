cmake_minimum_required(VERSION 3.12)

project(substd VERSION 1.0)

set(CXX_STANDARD C++20)
set(CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GNUInstallDirs)

install(TARGETS substd LIBRARY)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME} TYPE INCLUDE)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake 
    VERSION ${CMAKE_PROJECT_VERSION} 
    COMPATABLILTY SameMajorVersion)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake 
    DESTINATION ${LIB_INSTALL_DIR)/${CMAKE_PROJECT_NAME}/cmake)