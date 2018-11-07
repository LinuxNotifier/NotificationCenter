set(TARGET colortester)

qt5_wrap_ui(UI_HEADERS colortester.ui)

add_library(${TARGET} SHARED colortester.json
# add_executable(${TARGET} colortester.json
    colortester.ui
    ${UI_HEADERS}
    ui_colortester.h
    ctwidget.h
    ctwidget.cpp
    colortester.h
    colortester.cpp)
target_link_libraries(${TARGET} ${${PROJECT_NAME}_CORE})
qt5_use_modules(${TARGET} ${QT})
