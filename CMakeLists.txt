project(CSP2SAT)

cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# C++14
set(CMAKE_CXX_STANDARD 14)

# set-up ANTLR
add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/deps/antlr/antlr-4.8-complete.jar)
set(ANTLR4_ZIP_REPOSITORY ${PROJECT_SOURCE_DIR}/deps/antlr/antlr4-master.zip)
include(ExternalAntlr4Cpp)
include_directories(${ANTLR4_INCLUDE_DIRS})

# generate ANTLR files
find_package(ANTLR REQUIRED)
antlr_target(
        CSP2SAT
        ${CMAKE_CURRENT_SOURCE_DIR}/src/CSP2SAT.g4
        PACKAGE CSP2SAT
        VISITOR
)

antlr_target(
        JSON
        ${CMAKE_CURRENT_SOURCE_DIR}/src/JSON.g4
        PACKAGE CSP2SAT
        VISITOR
)

include_directories(${ANTLR_CSP2SAT_OUTPUT_DIR})
include_directories(${ANTLR_JSON_OUTPUT_DIR})


# build CSP2SAT
file(GLOB CSP2SAT_SRC "src/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/src/api/smtapi/src)
include_directories(${PROJECT_SOURCE_DIR}/cmake-build-debug/antlr4cpp_generated_src)
include_directories(${PROJECT_SOURCE_DIR}/deps/antlr)

add_executable(
            CSP2SAT
            src/main.cpp
            ${ANTLR_CSP2SAT_CXX_OUTPUTS}
            ${ANTLR_JSON_CXX_OUTPUTS}
            src/api/smtapi/src/smtformula.cpp
            src/api/smtapi/src/smtapi.cpp
            src/api/smtapi/src/MDD/mddbuilder.cpp
            src/api/smtapi/src/MDD/amopbbddbuilder.cpp
            src/api/smtapi/src/MDD/amopbmddbuilder.cpp
            src/api/smtapi/src/MDD/mdd.cpp
            src/api/smtapi/src/util/util.cpp
        )
target_link_libraries(CSP2SAT antlr4_static)

