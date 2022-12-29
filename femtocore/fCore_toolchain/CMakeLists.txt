cmake_minimum_required(VERSION 3.15)
project(fCore_toolchain)

include(GNUInstallDirs)

option(BUILD_TESTS "Build test programs" OFF)
option(INCLUDE_EMULATOR "Include the emulator in the build" OFF)
option(INCLUDE_COVERAGE "Build with support for code coverage" OFF)
option(INCLUDE_DEVTOOLS "Include compiler development tools in the build" OFF)

set(ANTLR_VERSION 4.10.1)
SET(ANTLR_JAR antlr-${ANTLR_VERSION}-complete.jar)
set(ANTLR_CLASSPATH ${CMAKE_CURRENT_BINARY_DIR}/antlr_jar/${ANTLR_JAR})
set(ANTLR_OPTIONS -Dlanguage=Cpp -visitor -listener  -encoding iso-8859-1)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/antlr_runtime/dist/usr/local/include/antlr4-runtime)
include_directories(includes)

# setup xilinx fp model c library
include_directories(third_party/fp_ip_cmodel/includes)
link_directories(third_party/fp_ip_cmodel/lib)

install (FILES third_party/fp_ip_cmodel/lib/libgmp.so.11 DESTINATION /usr/lib/x86_64-linux-gnu)
install (FILES third_party/fp_ip_cmodel/lib/libmpfr.so.4 DESTINATION /usr/lib/x86_64-linux-gnu)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=undefined -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DSCHEMAS_FOLDER="${CMAKE_SOURCE_DIR}/schemas")
else()
    add_definitions(-DSCHEMAS_FOLDER="/usr/local/etc/fcore_toolchain")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG        v3.11.2
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
        json_schema
        GIT_REPOSITORY https://github.com/pboettch/json-schema-validator
        GIT_TAG       2.1.0
)
FetchContent_MakeAvailable(json_schema)

FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG        v2.3.0
)
FetchContent_MakeAvailable(cli11)

FetchContent_Declare(
        antlr_jar
        URL https://github.com/antlr/website-antlr4/blob/gh-pages/download/${ANTLR_JAR}?raw=true
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/antlr_jar
        DOWNLOAD_NAME ${ANTLR_JAR}
        DOWNLOAD_NO_EXTRACT ON
)
FetchContent_MakeAvailable(antlr_jar)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(googletest)





FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        76fb40d95455f249bd70824ecfcae7a8f0930fa3 # v1.10.0
)
FetchContent_MakeAvailable(spdlog)

if(${INCLUDE_COVERAGE})
    add_compile_options(-Wno-attributes -fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif(${INCLUDE_COVERAGE})

message(STATUS "C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")

add_subdirectory(includes/asm_parser)
add_subdirectory(includes/C_parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/antlr_runtime_src-src/runtime/Cpp/runtime/src)


if(${INCLUDE_DEVTOOLS})
    find_package(cpprestsdk REQUIRED)

endif(${INCLUDE_DEVTOOLS})

add_subdirectory(src)

if(${BUILD_TESTS})
    enable_testing()
    add_subdirectory(test)
endif(${BUILD_TESTS})

unset(BUILD_TESTS CACHE)

include(ExternalProject)

add_custom_target(parsers)
add_dependencies(parsers c_parser_gen asm_parser_gen)

FetchContent_Declare(
        antlr_runtime_src
        GIT_REPOSITORY https://github.com/antlr/antlr4.git
        SOURCE_SUBDIR runtime/Cpp
        GIT_TAG ${ANTLR_VERSION}
)
# Check if population has already been performed
FetchContent_GetProperties(antlr_runtime_src)
if(NOT antlr_runtime_src_POPULATED)
    # Fetch the content using previously declared details
    FetchContent_Populate(antlr_runtime_src)

    # Bring the populated content into the build
    add_subdirectory(${antlr_runtime_src_SOURCE_DIR}/runtime/Cpp ${antlr_runtime_src_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
