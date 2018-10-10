cmake_minimum_required(VERSION 3.0.0)

project(befrank)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(VERSION "1.0.1-beta.2")

include_directories(include src external "${CMAKE_CURRENT_BINARY_DIR}/version")  

if(APPLE)
    include_directories(SYSTEM /usr/include/malloc)
    if(POLICY CMP0042)
        cmake_policy(SET CMP0042 NEW)
    endif()
    enable_language(ASM)
endif()

if(MSVC)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows)
elseif(APPLE)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OSX)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Posix)
elseif(LINUX)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Linux)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Posix)
endif()

add_subdirectory(external)

# Final setup for miniupnpc
if(STATIC OR IOS)
  add_definitions("-DUPNP_STATIC")
else()
  add_definitions("-DUPNP_DYNAMIC")
  include_directories(${UPNP_INCLUDE})
endif()

if(MSVC)
  add_definitions("/bigobj /MP /W3 /GS- /D_CRT_SECURE_NO_WARNINGS /wd4996 /wd4345 /D_WIN32_WINNT=0x0600 /DWIN32_LEAN_AND_MEAN /DGTEST_HAS_TR1_TUPLE=0 /D_VARIADIC_MAX=8 /D__SSE4_1__")
  #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Dinline=__inline")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10485760")
  include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/msc)
else()
  include(TestCXXAcceptsFlag)
  set(WARNINGS "-Wall -Wextra -Wpointer-arith -Wundef -Wvla -Wwrite-strings -Werror\
    -Wno-error=delete-non-virtual-dtor\
    -Wno-error=extra\
    -Wno-error=unused-function\
    -Wno-error=unused-private-field\
    -Wno-error=deprecated-declarations\
    -Wno-error=sign-compare\
    -Wno-error=strict-aliasing\
    -Wno-error=type-limits\
    -Wno-unused-parameter\
    -Wno-error=unused-variable\
    -Wno-error=undef\
    -Wno-error=uninitialized\
    -Wno-error=unused-result -Wno-unused-lambda-capture")
endif()


set(C_WARNINGS "-Waggregate-return -Wnested-externs -Wold-style-definition -Wstrict-prototypes")
set(CXX_WARNINGS "-Wno-reorder -Wno-missing-field-initializers")

# With GCC 6.1.1 the compiled binary malfunctions due to aliasing. Until that
# is fixed in the code (Issue #847), force compiler to be conservative.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -D_GNU_SOURCE  ${WARNINGS} ${C_WARNINGS} ${ARCH_FLAG} ${PIC_FLAG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_GNU_SOURCE ${WARNINGS} ${CXX_WARNINGS} ${ARCH_FLAG} ${PIC_FLAG}")

option(NO_AES "Explicitly disable AES support" ${NO_AES})

if(NOT NO_AES AND NOT ARM AND NOT PPC64LE)
    message(STATUS "AES support enabled")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes")
endif()

find_package(Boost 1.58 QUIET REQUIRED COMPONENTS system filesystem thread date_time chrono regex serialization program_options coroutine context atomic)

set(CMAKE_FIND_LIBRARY_SUFFIXES ${OLD_LIB_SUFFIXES})
if(NOT Boost_FOUND)
  die("Could not find Boost libraries, please make sure you have installed Boost or libboost-all-dev (1.58) or the equivalent")
elseif(Boost_FOUND)
  message(STATUS "Found Boost Version: ${Boost_VERSION}")
endif()

if(APPLE OR OPENBSD OR ANDROID)
  set(Boost_LIBRARIES "${Boost_LIBRARIES}")
elseif(NOT MSVC)
  set(Boost_LIBRARIES "${Boost_LIBRARIES};rt")
endif()

if(WIN32)
  include_directories(SYSTEM ../boost)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    link_directories(SYSTEM ../boost/stage/lib) # must be before add_executable, add_library
  else()
    link_directories(SYSTEM ../boost/stage32/lib) # must be before add_executable, add_library
  endif()
endif()


include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include("${CMAKE_CURRENT_SOURCE_DIR}/src/version.cmake")

add_subdirectory(src)

set(COMMIT_ID_IN_VERSION ON CACHE BOOL "Include commit ID in version")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/version")
if (NOT COMMIT_ID_IN_VERSION)
  set(VERSION "${VERSION}-unknown")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version/version.h")
  add_custom_target(version ALL)
elseif(DEFINED COMMIT)
  string(REPLACE "." "\\." VERSION_RE "${VERSION}")
  if(NOT REFS MATCHES "(\\(|, )tag: v${VERSION_RE}(\\)|, )")
    set(VERSION "${VERSION}-g${COMMIT}")
  endif()
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version/version.h")
  add_custom_target(version ALL)
else()
  find_package(Git QUIET)
  if(Git_FOUND OR GIT_FOUND)
    message(STATUS "Found Git: ${GIT_EXECUTABLE}")
    add_custom_target(version ALL "${CMAKE_COMMAND}" "-D" "VERSION=${VERSION}" "-D" "GIT=${GIT_EXECUTABLE}" "-D" "TO=${CMAKE_CURRENT_BINARY_DIR}/version/version.h" "-P" "${CMAKE_CURRENT_SOURCE_DIR}/src/version.cmake" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
  else()
    message(STATUS "WARNING: Git was not found!")
    set(VERSION "${VERSION}-unknown")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version/version.h")
    add_custom_target(version ALL)
  endif()
endif()