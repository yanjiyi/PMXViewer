cmake_minimum_required(VERSION 3.21)

project(MMDUtils)

FIND_PACKAGE(Qt5 COMPONENTS Widgets REQUIRED)

include_directories("MMD")

set(MMDUtils_Source
    MMD/Pmd.cpp
    MMD/Pmx.cpp
    HeaderWidget.cpp
    ShowWidget.cpp
    main.cpp
)

set(MMDUtils_Headers
    MMD/Pmd.h
    MMD/Pmx.h
    MMD/Vmd.h
    HeaderWidget.h
    ShowWidget.h
)

set(MMDUtils_Forms
    HeaderWidget.ui
)

set(MMDUtils_Resources

)


QT5_WRAP_CPP(MMDUtils_Headers_MOC ${MMDUtils_Headers})

QT5_WRAP_UI(MMDUtils_Forms_Headers ${MMDUtils_Forms})

QT5_ADD_RESOURCES(MMDUtils_Resources_RCC ${MMDUtils_Resources})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(MMDUtils 
        ${MMDUtils_Source}
        ${MMDUtils_Headers_MOC}
        ${MMDUtils_Forms_Headers}
        ${MMDUtils_Resources_RCC}
)

target_link_libraries(MMDUtils ${Qt5Widgets_LIBRARIES})
target_link_options(MMDUtils PRIVATE -mwindows)