cmake_minimum_required(VERSION 3.5)

project(file_modifier_shaina VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        creator.cpp
        creator.h
        manager.cpp
        manager.h
        graphics.cpp
        graphics.h
        dialog.h
        dialog.cpp
        directory_group.h
        directory_group.cpp
        current_settings.h
        current_settings.cpp
        alert_dialog.h
        alert_dialog.cpp
        modificator.h
        modificator.cpp
)


qt_add_executable(file_modifier_shaina
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(file_modifier_shaina PRIVATE Qt::Widgets)
target_link_libraries(file_modifier_shaina PRIVATE Qt::Core)
target_link_libraries(file_modifier_shaina PRIVATE Qt::Gui)

set_target_properties(file_modifier_shaina PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS file_modifier_shaina
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(file_modifier_shaina)
endif()
