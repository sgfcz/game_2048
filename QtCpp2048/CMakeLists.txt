cmake_minimum_required(VERSION 3.23)
project(QtCpp2048)

if(APPLE)
    set(CMAKE_PREFIX_PATH "/Volumes/KnowBoat/Qt5.11.3/5.11.3/clang_64/lib/cmake")
    set(CMAKE_OSX_ARCHITECTURES x86_64)
endif()

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