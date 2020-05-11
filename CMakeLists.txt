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


# build CSP2SATCompiler
file(GLOB CSP2SAT_SRC "src/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/src/api/)
include_directories(${PROJECT_SOURCE_DIR}/cmake-build-debug/antlr4cpp_generated_src)
include_directories(${PROJECT_SOURCE_DIR}/deps/antlr)

add_executable(
        CSP2SAT
        src/main.cpp
        ${ANTLR_CSP2SAT_CXX_OUTPUTS}
        ${ANTLR_JSON_CXX_OUTPUTS}
        src/api/smtformula.cpp
        src/api/smtapi.cpp
        src/api/encoding.cpp
        src/api/MDD/mddbuilder.cpp
        src/api/MDD/amopbbddbuilder.cpp
        src/api/MDD/amopbmddbuilder.cpp
        src/api/MDD/mdd.cpp
        src/api/controllers/basiccontroller.cpp
        src/api/controllers/solvingarguments.cpp
        src/api/controllers/arguments.cpp
        src/api/optimizers/buoptimizer.cpp
        src/api/optimizers/singlecheck.cpp
        src/api/optimizers/uboptimizer.cpp
        src/api/optimizers/dicooptimizer.cpp
        src/api/optimizers/nativeoptimizer.cpp
        src/api/optimizers/optimizer.cpp
        src/api/encoders/fileencoder.cpp
        src/api/encoders/encoder.cpp
        src/api/encoders/apiencoder.cpp
        src/api/encoders/smtlib2fileencoder.cpp
        src/api/encoders/dimacsfileencoder.cpp
        src/api/encoders/glucoseapiencoder.cpp
        src/api/encoders/minisatapiencoder.cpp
        src/api/solvers/glucose/simp/SimpSolver.cc
        src/api/solvers/glucose/core/Solver.cc
        src/api/solvers/minisat/simp/SimpSolver.cc
        src/api/solvers/minisat/core/Solver.cc
        src/api/util/util.cpp
        src/api/util/errors.cpp
        src/Errors/CSP2SATInputExceptionsRepository.h
        src/Visitors/Output/CSP2SATOutputVisitor.h
        src/Symtab/Symbol/StringSymbol.h)
target_link_libraries(CSP2SAT antlr4_static)

