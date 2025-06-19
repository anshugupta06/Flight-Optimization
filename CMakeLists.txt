cmake_minimum_required(VERSION 3.16)

project(AirportsProject VERSION 0.1 LANGUAGES CXX)

# Enable Qt's automatic processing for UI, moc, and resources
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 Widgets or fallback to Qt5
find_package(Qt6 COMPONENTS Widgets QUIET)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    set(QT_LIB_PREFIX Qt6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets)
    set(QT_VERSION_MAJOR 5)
    set(QT_LIB_PREFIX Qt5)
endif()

# Source and header files (flat structure)
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    Backend.cpp
    cleaning.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    Backend.h
    cleaning.h
)

set(PROJECT_FORMS
    mainwindow.ui
)

# Define executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AirportsProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_FORMS}
    )
else()
    add_executable(AirportsProject
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_FORMS}
    )
endif()

# Link Qt libraries
target_link_libraries(AirportsProject PRIVATE
    ${QT_LIB_PREFIX}::Widgets
)

# Add Qt resources (optional)
qt_add_resources(AirportsProject RESOURCES resources.qrc)

# Install rules (optional)
install(TARGETS AirportsProject
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize Qt 6 executable
if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(AirportsProject)
endif()
