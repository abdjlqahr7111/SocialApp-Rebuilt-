set(APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(APP_QML_RESOURCES
    ${CMAKE_SOURCE_DIR}/ui/qml.qrc
)

qt_add_executable(SocialApp
    ${APP_SOURCES}
    ${APP_QML_RESOURCES}
)

target_link_libraries(SocialApp PRIVATE
    SocialAppCore
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

if(ANDROID)
    set_target_properties(SocialApp PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android"
        QT_ANDROID_ABIS "arm64-v8a;armeabi-v7a"
    )
endif()
