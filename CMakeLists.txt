############################################################################
# Copyright (c) 2017, Sylvain Corlay, Johan Mabille Wolf Vollprecht and    #
# Martin Renou                                                             #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

cmake_minimum_required(VERSION 3.8)
project(xwebrtc)

message(STATUS "Forcing tests build type to Release")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

set(XWEBRTC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XWEBRTC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(XWEBRTC_SHARE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/share)

# Configuration
# =============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XWEBRTC_INSTALL_LIBRARY_DIR "\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"")

configure_file (
    "${XWEBRTC_INCLUDE_DIR}/xwebrtc/xwebrtc_config_cling.hpp.in"
    "${XWEBRTC_INCLUDE_DIR}/xwebrtc/xwebrtc_config_cling.hpp"
)

# Versionning
# ===========

file(STRINGS "${XWEBRTC_INCLUDE_DIR}/xwebrtc/xwebrtc_config.hpp" xwebrtc_version_defines
     REGEX "#define XWEBRTC_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xwebrtc_version_defines})
    if(ver MATCHES "#define XWEBRTC_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XWEBRTC_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XWEBRTC_VERSION
    ${XWEBRTC_VERSION_MAJOR}.${XWEBRTC_VERSION_MINOR}.${XWEBRTC_VERSION_PATCH})
message(STATUS "xwebrtc version: v${XWEBRTC_VERSION}")

# Binary version
# See the following URL for explanations about the binary versionning
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html#Updating-version-info
file(STRINGS "${XWEBRTC_INCLUDE_DIR}/xwebrtc/xwebrtc_config.hpp" xwebrtc_version_defines
    REGEX "#define XWEBRTC_BINARY_(CURRENT|REVISION|AGE)")
foreach(ver ${xwebrtc_version_defines})
    if(ver MATCHES "#define XWEBRTC_BINARY_(CURRENT|REVISION|AGE) +([^ ]+)$")
        set(XWEBRTC_BINARY_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XWEBRTC_BINARY_VERSION
    ${XWEBRTC_BINARY_CURRENT}.${XWEBRTC_BINARY_REVISION}.${XWEBRTC_BINARY_AGE})
message(STATUS "xwebrtc binary version: v${XWEBRTC_BINARY_VERSION}")

# Dependencies
# ============

find_package(cppzmq 4.2.3 REQUIRED)
find_package(xtl 0.4 REQUIRED)
find_package(xeus 0.12.0 REQUIRED)
find_package(xwidgets 0.10.0 REQUIRED)

# Source files
# ============

set(XWEBRTC_HEADERS
    ${XWEBRTC_INCLUDE_DIR}/xwebrtc/xmedia_stream.hpp
)

set(XWEBRTC_SOURCES
    # ${XWEBRTC_SOURCE_DIR}/xcircle_marker.cpp
)

# Output
# ======

add_library(xwebrtc SHARED ${XWEBRTC_SOURCES} ${XWEBRTC_HEADERS})
target_include_directories(xwebrtc PUBLIC $<BUILD_INTERFACE:${XWEBRTC_INCLUDE_DIR}>
                                           $<INSTALL_INTERFACE:include>)

target_link_libraries(xwebrtc
    PUBLIC xtl
    PUBLIC xeus
    PUBLIC xwidgets)

set_target_properties(xwebrtc PROPERTIES
                      PUBLIC_HEADER "${XWEBRTC_HEADERS}"
                      COMPILE_DEFINITIONS "XWEBRTC_EXPORTS"
                      PREFIX ""
                      VERSION ${XWEBRTC_BINARY_VERSION}
                      SOVERSION ${XWEBRTC_BINARY_CURRENT}
                      OUTPUT_NAME "libxwebrtc")

# Compilation flags
# =================

include(CheckCXXCompilerFlag)
string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)
OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

set_target_properties(xwebrtc PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED 14)

target_compile_features(xwebrtc PRIVATE cxx_std_14)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(xwebrtc PUBLIC -Wunused-parameter -Wextra -Wreorder)
    if (DISABLE_ARCH_NATIVE)
        target_compile_options(xwebrtc PUBLIC -mtune=generic)
    else()
        target_compile_options(xwebrtc PUBLIC -march=native)
    endif()

    # Enable link time optimization and set the default symbol
    # visibility to hidden (very important to obtain small binaries)
    if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        # Check for Link Time Optimization support
        # (GCC/Clang)
        CHECK_CXX_COMPILER_FLAG("-flto" HAS_LTO_FLAG)
        if (HAS_LTO_FLAG)
            target_compile_options(xwebrtc PUBLIC -flto)
        endif()

        # Intel equivalent to LTO is called IPO
        if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
            CHECK_CXX_COMPILER_FLAG("-ipo" HAS_IPO_FLAG)
            if (HAS_IPO_FLAG)
                target_compile_options(xwebrtc PUBLIC -ipo)
            endif()
        endif()
    endif()
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

# if(MSVC)
#     target_compile_definitions(xwebrtc PUBLIC -DNOMINMAX)
#     target_compile_options(xwebrtc PUBLIC /DGUID_WINDOWS /MP /bigobj)
#     target_compile_options(xwebrtc PUBLIC /wd4251 /wd 4996)
#     # Allows to compile in debug without requiring each dependencies to
#     # be compiled in debug
#     if(${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
#         set(CMAKE_CXX_FLAGS_DEBUG "/DNDEBUG /MD /Zi /Ob0 /Od /RTC1")
#         message(STATUS "Overriding CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
#     endif()
# endif()

# Tests
# =====

OPTION(BUILD_TESTS "xwebrtc test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

# Installation
# ============

install(DIRECTORY "${XWEBRTC_SHARE_DIR}/xwebrtc"
        DESTINATION "share")

set(XWEBRTC_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for xwebrtcConfig.cmake")

install(TARGETS xwebrtc
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xwebrtc)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XWEBRTC_CMAKECONFIG_INSTALL_DIR})
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${XWEBRTC_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
              DESTINATION ${XWEBRTC_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
DESTINATION ${XWEBRTC_CMAKECONFIG_INSTALL_DIR})
