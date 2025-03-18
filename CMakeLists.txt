cmake_minimum_required(VERSION 3.18)
project(QtCpp2048)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#苹果系统编译环境
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
endif ()

#自动生成ui头文件和moc头文件
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#添加ui头文件寻找
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "ui")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FILE(GLOB_RECURSE ui "ui/MainWindow.ui")
FILE(GLOB_RECURSE SRCS
        "core/Block.cpp"
        "core/MainWindow.cpp")
FILE(GLOB_RECURSE INCLUDES
        "include/Block.h" ,
        "include/MainWindow.h")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(QtCpp2048
        main.cpp
        ${UI}
        ${SRCS}
        ${INCLUDES}
)

target_link_libraries(QtCpp2048
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
