set(TARGET test_NotificationCenter)
find_package(PkgConfig REQUIRED)
set(QT Core Gui Widgets Network DBus Sql X11Extras)
find_package(Qt5 REQUIRED ${QT})
find_package(X11 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(notdir $(abspath $<))\"'")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${TARGET} test_main.cpp
    test_ncdatabase.cpp
    test_ncmessage.cpp
    test_notificationcenter.cpp
    test_messagemanager.cpp
    test_mainwindow.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_LIBRARY})
qt5_use_modules(${TARGET} ${QT})
