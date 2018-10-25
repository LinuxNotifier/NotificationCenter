set(TARGET test_NotificationCenter)

add_executable(${TARGET} test_main.cpp
    test_ncdatabase.cpp
    test_ncmessage.cpp
    test_notificationcenter.cpp
    test_messagemanager.cpp
    test_plugininterface.h
    test_plugininterface.cpp
    test_pluginmanager.cpp
    test_mainwindow.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_LIBRARY})
qt5_use_modules(${TARGET} ${QT})
