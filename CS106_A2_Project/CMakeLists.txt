cmake_minimum_required(VERSION 3.5)

project(CS106_A2_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    resource.qrc
        main.cpp

        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        userlogin.cpp
        userlogin.h
        userlogin.ui
        adminlogin.cpp
        adminlogin.h
        adminlogin.ui
        userdashboard.cpp
        userdashboard.h
        userdashboard.ui
        admindashboard.cpp
        admindashboard.h
        admindashboard.ui
        usersignin.cpp
        usersignin.h
        usersignin.ui
        welcomescreenuser.cpp
        welcomescreenuser.h
        welcomescreenuser.ui
        adminuserinformation.cpp
        adminuserinformation.h
        adminuserinformation.ui
        userreportissue.cpp
        userreportissue.h
        userreportissue.ui
        covidpositiveresult.cpp
        covidpositiveresult.h
        covidpositiveresult.ui
        covidnegativeresult.cpp
        covidnegativeresult.h
        covidnegativeresult.ui
        databaseheader.h
        admincovidtestreport.cpp
        admincovidtestreport.h
        admincovidtestreport.ui
        adminmodifyuserinformation.cpp
        adminmodifyuserinformation.h
        adminmodifyuserinformation.ui
        usercovidlist.cpp
        usercovidlist.h
        usercovidlist.ui
        uservaccinationrecord.cpp
        uservaccinationrecord.h
        uservaccinationrecord.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CS106_A2_Project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CS106_A2_Project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CS106_A2_Project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CS106_A2_Project
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CS106_A2_Project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(CS106_A2_Project PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CS106_A2_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CS106_A2_Project)
endif()
