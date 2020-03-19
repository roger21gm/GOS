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
        LISTENER
)
include_directories(${ANTLR_CSP2SAT_OUTPUT_DIR})


# build CSP2SAT
file(GLOB CSP2SAT_SRC "src/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/cmake-build-debug)
include_directories(${PROJECT_SOURCE_DIR}/deps/antlr)
add_executable(CSP2SAT ${CSP2SAT_SRC} ${ANTLR_CSP2SAT_CXX_OUTPUTS} src/main.cpp src/CSP2SATCustomVisitor.cpp src/CSP2SATCustomVisitor.h src/Symtab/SymtbolTable.h src/Symtab/Symbol/Symbol.h src/Symtab/Type.h src/Symtab/Scope/Scope.h src/Symtab/Scope/BaseScope.h src/Symtab/Scope/GlobalScope.h src/Symtab/Scope/LocalScope.h src/Symtab/Symbol/VariableSymbol.h src/Symtab/Symbol/BuildInTypeSymbol.h src/Symtab/Symbol/ScopedSymbol.h src/Symtab/Symbol/StructSymbol.h)
target_link_libraries(CSP2SAT antlr4_static)

