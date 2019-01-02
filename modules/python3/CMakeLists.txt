cmake_minimum_required(VERSION 2.8)

set(TARGET pymodule)

# find_package(PythonLibrary)
# include(PythonMacros)
# find_package(SIP)
# include(SIPMacros)
# find_package(PyQt5)

# TODO: this allows this target to be automatically built, but it takes a long time
add_custom_target(${${PROJECT_NAME}_Py} ALL
# add_custom_target(${${PROJECT_NAME}_Py}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/configure.py ${CMAKE_CURRENT_SOURCE_DIR}/*.sip ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cp ${PROJECT_BINARY_DIR}/NotificationCenter/libNCCore.so ./
    COMMAND python3 configure.py ${PROJECT_SOURCE_DIR} ${qt_dir} ${sip_dir} ${pyqt_sip_dir}  
    COMMAND $(MAKE)
    COMMAND cp Py.so ${PROJECT_BINARY_DIR}/NotificationCenter/modules
    # TODO: rebuild if and only if those "*.sip" files changed
    DEPENDS "*.sip"
    )
add_dependencies(${${PROJECT_NAME}_Py} ${${PROJECT_NAME}_CORE})

add_library(${TARGET} SHARED python.json
    python.h
    python.cpp
    )
# target_link_libraries(${${PROJECT_NAME}_Py} ${${PROJECT_NAME}_CORE})
# qt5_use_modules(${${PROJECT_NAME}_Py} ${QT})
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE} ${PYTHON_LIBRARIES})
qt5_use_modules(${TARGET} ${QT})

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND cp $<TARGET_FILE:${TARGET}> "${PROJECT_BINARY_DIR}/NotificationCenter/plugins"
    )

install(TARGETS ${TARGET} DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Py.so" DESTINATION "${CMAKE_INSTALL_PREFIX}/modules")
