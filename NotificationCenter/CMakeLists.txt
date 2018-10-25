set(TARGET NotificationCenter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS mainwindow.h
    ncglobal.h
    ncdebug.h
    notificationcenter.h
    notificationcenter_p.h
    ncdatabase.h
    ncmessage.h
    ncmessage_p.h
    messagemanager.h
    pluginmanager.h
    plugininterface.h
    )
# set(${PROJECT_NAME}_SOURCES main.cpp
set(SOURCES mainwindow.cpp
    notificationcenter.cpp
    ncdatabase.cpp
    ncmessage.cpp
    messagemanager.cpp
    pluginmanager.cpp
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
