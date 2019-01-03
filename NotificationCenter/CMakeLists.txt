set(TARGET NotificationCenter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS mainwindow.h
    global.h
    debug.h
    notificationcenter.h
    notificationcenter_p.h
    database.h
    notification.h
    notification_p.h
    notificationmanager.h
    extensionmanager.h
    extensioninterface.h
    notificationlistener.h
    )
# set(${PROJECT_NAME}_SOURCES main.cpp
set(SOURCES mainwindow.cpp
    # blur.cpp
    notificationcenter.cpp
    database.cpp
    notification.cpp
    notificationmanager.cpp
    extensionmanager.cpp
    extensioninterface.cpp
    notificationlistener.cpp
    )
set(FORMS mainwindow.ui
    )
set(RESOURCES resources.qrc
    )
file(GLOB WIDGETS "widgets/*")

# add_library(${${PROJECT_NAME}_CORE} STATIC ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES} ${WIDGETS})
add_library(${${PROJECT_NAME}_CORE} SHARED ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES} ${WIDGETS})
target_link_libraries(${${PROJECT_NAME}_CORE})
# don't link against ${Qt} directly!
qt5_use_modules(${${PROJECT_NAME}_CORE} ${QT})

add_executable(${TARGET} main.cpp ${RESOURCES})
# target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE})
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE})

# to auto-generate *.qm files
# add_dependencies(${TARGET} translations)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS ${${PROJECT_NAME}_CORE} DESTINATION "${CMAKE_INSTALL_PREFIX}/modules")
