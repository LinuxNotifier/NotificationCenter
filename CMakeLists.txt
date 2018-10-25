cmake_minimum_required(VERSION 2.8)

project(NotificationCenter)
set(${PROJECT_NAME}_LIBRARY NC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -Wno-reorder")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(notdir $(abspath $<))\"'")

find_package(PkgConfig REQUIRED)
set(QT Core Gui Widgets Network DBus Sql X11Extras)
find_package(Qt5 REQUIRED ${QT})
find_package(Qt5LinguistTools)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_libraries(${X11_LIBRARIES})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "NotificationCenter/*.cpp")
file(GLOB_RECURSE HEADERS "NotificationCenter/*.h")
file(GLOB_RECURSE FORMS "NotificationCenter/*.ui")

include_directories(NotificationCenter/widgets)
add_subdirectory(NotificationCenter)
enable_testing()
# add_subdirectory(third_libraries)
include_directories(third_libraries)
include_directories(NotificationCenter)
add_subdirectory(test)

add_subdirectory(plugins)

# don't clean *.ts files when execute `make clean`
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM TRUE)
set(${PROJECT_NAME}_TS_FILES translations/NotificationCenter_zh_CN.ts
    translations/NotificationCenter_zh_TW.ts)
qt5_create_translation(${PROJECT_NAME}_QM_FILES ${HEADERS} ${SOURCES} ${FORMS} ${${PROJECT_NAME}_TS_FILES})
# qt5_add_translation(${PROJECT_NAME}_QM_FILES ${${PROJECT_NAME}_TS_FILES})
add_custom_target(translations DEPENDS ${${PROJECT_NAME}_QM_FILES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/languages")

file(COPY plugins DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/NotificationCenter)
file(COPY themes DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/NotificationCenter)
# file(COPY ${${PROJECT_NAME}_QM_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/NotificationCenter/languages)

install(DIRECTORY "plugins" DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY "themes" DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${${PROJECT_NAME}_QM_FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/languages")
install(DIRECTORY "docs" DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES "run.sh" DESTINATION ${CMAKE_INSTALL_PREFIX})
