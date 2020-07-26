cmake_minimum_required(VERSION 3.15)

project(instat
    VERSION 0.1
    DESCRIPTION "instat: instruction statistics of a PE"
    HOMEPAGE_URL "https://github.com/restruc/instat"
)

find_package(zydis)
find_package(zycore)

set(SOURCE_DIR "src")

file(GLOB_RECURSE SOURCE_FILES
    "${SOURCE_DIR}/*.cxx"
    "${SOURCE_DIR}/*.hxx"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    zycore
    zydis
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE
    ${zycore_LIB_DIR}
    ${zydis_LIB_DIR}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${SOURCE_DIR}
    ${zycore_INCLUDE_DIR}
    ${zydis_INCLUDE_DIR}
)
