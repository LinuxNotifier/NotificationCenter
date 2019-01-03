set(TARGET test_NotificationCenter)

add_executable(${TARGET} test_main.cpp
    test_database.cpp
    test_notification.cpp
    test_notificationcenter.cpp
    test_notificationmanager.cpp
    test_extensioninterface.h
    test_extensioninterface.cpp
    test_extensionmanager.cpp
    test_widget.cpp
    test_mainwindow.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE} ${PYTHON_LIBRARIES})
qt5_use_modules(${TARGET} ${QT})
