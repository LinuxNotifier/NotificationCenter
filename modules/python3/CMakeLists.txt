cmake_minimum_required(VERSION 2.8)

set(TARGET pymodule)

# find_package(PythonLibrary)
# include(PythonMacros)
# find_package(SIP)
# include(SIPMacros)
# find_package(PyQt5)

add_custom_target(${${PROJECT_NAME}_Py} ALL
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/prepare.sh ${CMAKE_CURRENT_SOURCE_DIR}/configure.py ${CMAKE_CURRENT_SOURCE_DIR}/*.sip ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cp ${PROJECT_BINARY_DIR}/NotificationCenter/libNCCore.so ./
    COMMAND bash ./prepare.sh
    # COMMAND python3 configure.py
    COMMAND $(MAKE)
    COMMAND mkdir ${PROJECT_BINARY_DIR}/NotificationCenter/modules -p
    COMMAND cp PyNc.so ${PROJECT_BINARY_DIR}/NotificationCenter/modules
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
