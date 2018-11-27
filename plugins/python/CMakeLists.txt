# subdirlist(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
#
# foreach(subdir ${SUBDIRS})
#     file(COPY ${subdir} DESTINATION ${PROJECT_BINARY_DIR}/NotificationCenter/plugins/python)
# endforeach()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION "${PROJECT_BINARY_DIR}/NotificationCenter/plugins")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")
