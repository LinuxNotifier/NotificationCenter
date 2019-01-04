cmake_minimum_required(VERSION 2.8)

project(NotificationCenter)
set(${PROJECT_NAME}_CORE NCCore)
set(${PROJECT_NAME}_Py Py)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -Wno-reorder -rdynamic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(notdir $(abspath $<))\"'")

macro(subdirlist result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

set(pyqt_sip_dir "/home/zhiping/Projects/boost_practice/PyQt5_gpl-5.11.3/sip")
set(sip_dir "/home/zhiping/Projects/boost_practice/hello-sip-pyqt5/sip_build")
set(qt_dir "/home/zhiping/Applications/Qt/5.10.1/gcc_64")
set(DCMAKE_PREFIX_PATH ${qt_dir})

foreach(subdir ${SUBDIRS})
    file(COPY ${subdir} DESTINATION ${PROJECT_BINARY_DIR}/NotificationCenter/plugins/python)
endforeach()

find_package(PkgConfig REQUIRED)
set(QT Core Gui Widgets Network DBus Sql X11Extras)
find_package(Qt5 REQUIRED ${QT})
find_package(Qt5LinguistTools)

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_libraries(${X11_LIBRARIES})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "NotificationCenter/*.cpp")
file(GLOB_RECURSE HEADERS "NotificationCenter/*.h")
file(GLOB_RECURSE FORMS "NotificationCenter/*.ui")

# NOTE: this need to be set before add_executable()
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/modules")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(NotificationCenter/widgets)
add_subdirectory(NotificationCenter)
enable_testing()
# add_subdirectory(third_libraries)
include_directories(third_libraries)
include_directories(NotificationCenter)

add_subdirectory(modules)
add_subdirectory(plugins)
add_subdirectory(translations)
add_subdirectory(themes)
add_subdirectory(docs)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(tests)
endif()
