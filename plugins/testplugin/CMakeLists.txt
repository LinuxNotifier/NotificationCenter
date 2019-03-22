set(TARGET testplugin)

add_library(${TARGET} SHARED test.json
    testplugin.h
    testplugin.cpp
    notifyme.h
    notifyme.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE})
qt5_use_modules(${TARGET} ${QT})

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND cp $<TARGET_FILE:${TARGET}> "${PROJECT_BINARY_DIR}/NotificationCenter/plugins"
    )
install(TARGETS ${TARGET} DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")
