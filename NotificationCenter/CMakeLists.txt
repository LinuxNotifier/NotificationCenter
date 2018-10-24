set(TARGET NotificationCenter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(notdir $(abspath $<))\"'")

find_package(PkgConfig REQUIRED)
set(QT Core Gui Widgets Network DBus Sql X11Extras)
find_package(Qt5 REQUIRED ${QT})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_libraries(${X11_LIBRARIES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(HEADERS mainwindow.h
    ncglobal.h
    ncdebug.h
    notificationcenter.h
    notificationcenter_p.h
    ncdatabase.h
    ncmessage.h
    ncmessage_p.h
    ncsettings.h
    ncsettings_p.h
    messagemanager.h
    )
# set(${PROJECT_NAME}_SOURCES main.cpp
set(SOURCES mainwindow.cpp
    notificationcenter.cpp
    ncdatabase.cpp
    ncmessage.cpp
    ncsettings.cpp
    messagemanager.cpp
    )
set(FORMS mainwindow.ui
    )
set(RESOURCES resources.qrc
    )

add_library(${${PROJECT_NAME}_LIBRARY} STATIC ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_link_libraries(${${PROJECT_NAME}_LIBRARY} ${Qt})
qt5_use_modules(${${PROJECT_NAME}_LIBRARY} ${QT})

add_executable(${TARGET} main.cpp ${RESOURCES})
target_link_libraries(${TARGET} ${${PROJECT_NAME}_LIBRARY})
# to auto-generate *.qm files
# add_dependencies(${TARGET} translations)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_PREFIX})
