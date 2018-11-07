set(TARGET testplugin)

add_library(${TARGET} SHARED test.json
    testplugin.h
    testplugin.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE})
qt5_use_modules(${TARGET} ${QT})
