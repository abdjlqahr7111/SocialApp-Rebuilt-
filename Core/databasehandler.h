set(CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/databasehandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camerahandler.cpp
)

set(CORE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/databasehandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camerahandler.h
)

add_library(SocialAppCore STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(SocialAppCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SocialAppCore PUBLIC
    Qt6::Core
    Qt6::Sql
)
