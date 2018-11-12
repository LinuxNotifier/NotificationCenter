subdirlist(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${SUBDIRS})
    file(COPY ${subdir} DESTINATION ${PROJECT_BINARY_DIR}/NotificationCenter/plugins/python)
endforeach()
