set(TARGET test_NotificationCenter)

add_executable(${TARGET} test_main.cpp
    test_ncdatabase.cpp
    test_ncmessage.cpp
    test_notificationcenter.cpp
    test_messagemanager.cpp
    test_extensioninterface.h
    test_extensioninterface.cpp
    test_extensionmanager.cpp
    test_ncwidget.cpp
    test_mainwindow.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE} ${PYTHON_LIBRARIES})
qt5_use_modules(${TARGET} ${QT})
