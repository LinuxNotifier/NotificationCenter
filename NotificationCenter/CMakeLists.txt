set(TARGET NotificationCenter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set(OpenCV_DIR "/home/zhiping/Projects/opencv/test_install/share/OpenCV")
# find_package( OpenCV REQUIRED )
# include_directories( ${OpenCV_INCLUDE_DIRS} )
# # add_executable( DisplayImage DisplayImage.cpp )
# # target_link_libraries( DisplayImage ${OpenCV_LIBS} )

set(HEADERS mainwindow.h
    ncglobal.h
    ncdebug.h
    # converter.h
    notificationcenter.h
    notificationcenter_p.h
    ncdatabase.h
    ncmessage.h
    ncmessage_p.h
    messagemanager.h
    extensionsmanager.h
    extensioninterface.h
    )
# set(${PROJECT_NAME}_SOURCES main.cpp
set(SOURCES mainwindow.cpp
    # blur.cpp
    notificationcenter.cpp
    ncdatabase.cpp
    ncmessage.cpp
    messagemanager.cpp
    extensionsmanager.cpp
    extensioninterface.cpp
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
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE} ${OpenCV_LIBS})

# to auto-generate *.qm files
# add_dependencies(${TARGET} translations)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_PREFIX})
