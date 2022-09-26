cmake_minimum_required(VERSION 3.23)
project(QtCpp2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(QtCpp2048
        main.cpp
        ui/MainWindow.h
        ui/MainWindow.cpp
        ui/MainWindow.ui
        core/Block.h
        core/Block.cpp
        )

target_link_libraries(QtCpp2048
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )