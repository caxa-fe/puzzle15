cmake_minimum_required(VERSION 3.16)

project(Qml_15Game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR "C:/Qt7/6.7.1/msvc2019_64/lib/cmake/Qt6")
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
#find_package(Qt6 6.5 REQUIRED )

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appQml_15Game
    main.cpp
)

qt_add_qml_module(appQml_15Game
    URI Qml_15Game
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES Tile.qml
        QML_FILES GameBoard.qml
        QML_FILES
        SOURCES gameboard.h gameboard.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQml_15Game PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQml_15Game
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQml_15Game
    PRIVATE Qt6::Quick
)

message("CMAKE_INSTALL_LIBDIR : ${CMAKE_INSTALL_LIBDIR}")
message("CMAKE_INSTALL_BINDIR : ${CMAKE_INSTALL_BINDIR}")

include(GNUInstallDirs)
install(TARGETS appQml_15Game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
