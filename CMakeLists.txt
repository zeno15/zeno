cmake_minimum_required(VERSION 3.2)
project(zeno)

# Install to C:\MinGW64\mingw32\i686-w64-mingw32
#[[
Building glew with mingw

clone git repo: https://github.com/Perlmint/glew-cmake.git

cd into folder
then run the following
------------------------------------------------------------------------------------------------------------------------
mkdir lib

gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.o -c src/glew.c
gcc -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a    -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
ar cr lib/libglew32.a src/glew.o



gcc -DGLEW_NO_GLU -DGLEW_MX -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
gcc -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o lib/glew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
ar cr lib/libglew32mx.a src/glew.mx.o



gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -DGLEW_STATIC -o src/glew.o -c src/glew.c
ar cr lib/libglew32s.a src/glew.o
------------------------------------------------------------------------------------------------------------------------

all library files will be in lib folder
]]

#[[
To build cmake from git repo for wingw

clone from https://github.com/vinniefalco/FreeType.git

cd into FreeType

mingw32-make.exe
mingw32-make.exe

then in objs folder is freetype.a
need to rename to libfreetype.a
]]



# Comment out for visual studio, is c++11 by default
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -static")

# Default extension, -s for static, -d for debug
set(LIBRARY_EXTENSION "")

# Default build type
set(LIBRARY_BUILD_TYPE "STATIC")

set(BUILD_SSL TRUE)

message(STATUS "BUILD_SSL: " ${BUILD_SSL})

set(STB_LOCATION "${CMAKE_SOURCE_DIR}/extlibs")


# Set the generic include directory for the project
include_directories(${CMAKE_SOURCE_DIR}/include)

# TODO check if this should be removed, and have it be a cmake variable being the path to std and freetype etc
# Add the external libraries folder to the include directories
#include_directories(${CMAKE_SOURCE_DIR}/extlibs)
include_directories(${STB_LOCATION})



# My testing stuff
# Visual Studio 2013
#include_directories(C:/programminglibs/glew-1.12.0/include)
#link_directories(C:/programminglibs/glew-1.12.0/lib/Release/Win32)

#include_directories(C:/programminglibs/freetype/include)
#link_directories(C:/programminglibs/freetype/lib)



# Locations for GLEW include and lib
# include_directories(path/to/glew/include)
# link_directories(path/to/glew32s.lib)

# Locations for freetype include and lib
# include_directories(path/to/freetype/include)
# link_directories(path/to/freetype.lib)

# Locations for gflw include and lib
# include_directories(path/to/gflw/include)
# link_directories(path/to/gflw.lib)



#-----------------------------  Module Includes start ----------------------
set(MODULE_INCLUDES ${MODULE_INCLUDES}
		${CMAKE_SOURCE_DIR}/include/zeno/Game.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Utility.hpp
		#${CMAKE_SOURCE_DIR}/include/zeno/Audio.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/GUI.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Network.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/System.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Window.hpp
    )
#-----------------------------  Module Includes end   ----------------------

#-----------------------------  Window start    ----------------------
set(WINDOW_HEADER_FILES ${WINDOW_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/Window/VideoMode.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/Window.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/WindowStyle.hpp
	)

set(WINDOW_SOURCE_FILES ${WINDOW_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/Window/Window.cpp
	)
#-----------------------------  Window end    ----------------------



#-----------------------------  System start    ----------------------
set(SYSTEM_HEADER_FILES ${SYSTEM_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/System/Clock.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Event.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Keyboard.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Mat4x4.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Mouse.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Rect.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Time.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Transformable2D.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Transformable3D.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector2.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector3.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector4.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/VectorMath.hpp

		${CMAKE_SOURCE_DIR}/include/zeno/System/Rect.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector2.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector3.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector4.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/VectorMath.inl
    )

set(SYSTEM_SOURCE_FILES ${SYSTEM_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/System/Clock.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Keyboard.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Mat4x4.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Mouse.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Time.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Transformable2D.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Transformable3D.cpp
	)
#-----------------------------  System end    ----------------------



#-----------------------------  Network start    ----------------------
set(NETWORK_HEADER_FILES ${NETWORK_HEADER_FILES}
        ${CMAKE_SOURCE_DIR}/include/zeno/Network/HTTPProtocol.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Network/Socket.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Network/SocketHandle.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Network/TCPListener.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Network/TCPSocket.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Network/UDPSocket.hpp
	)

set(NETWORK_SOURCE_FILES ${NETWORK_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/src/zeno/Network/HTTPProtocol.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Network/Socket.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Network/TCPListener.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Network/TCPSocket.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Network/UDPSocket.cpp
    )


if (BUILD_SSL STREQUAL "TRUE")
set(NETWORK_HEADER_FILES ${NETWORK_HEADER_FILES}
        ${CMAKE_SOURCE_DIR}/include/zeno/Network/SSLTCPSocket.hpp
)
set(NETWORK_SOURCE_FILES ${NETWORK_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/src/zeno/Network/SSLTCPSocket.cpp
)
endif (BUILD_SSL STREQUAL "TRUE")
#-----------------------------  Network end    ----------------------



#-----------------------------  Graphics start    ----------------------
set(GRAPHICS_HEADER_FILES ${GRAPHICS_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Circle.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Colour.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Font.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Glyph.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Image.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/ImageLoader.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Polygon.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Rectangle.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Renderable.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/RenderData.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Shader.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/ShaderManager.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Shape.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Sprite.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Text.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Texture.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Vertex.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/VertexArray.hpp
	)

set(GRAPHICS_SOURCE_FILES ${GRAPHICS_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Circle.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Colour.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Font.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Glyph.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Image.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/ImageLoader.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Polygon.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Rectangle.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Shader.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/ShaderManager.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Shape.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Sprite.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Text.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Texture.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Vertex.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/VertexArray.cpp
	)
#-----------------------------  Graphics end    ----------------------


#-----------------------------  GUI start    ----------------------
set(GUI_HEADER_FILES ${GUI_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GUIEvent.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/Desktop.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GuiBase.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/Pane.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/Button.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/Label.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/ProgressBar.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/Slider.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/TextBox.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/CheckBox.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/DropdownMenu.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/RadioButton.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/RadioButtonGroup.hpp



		${CMAKE_SOURCE_DIR}/include/zeno/GUI/Desktop.inl
	)

set(GUI_SOURCE_FILES ${GUI_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/Desktop.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/GuiBase.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/Pane.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/Button.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/Label.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/ProgressBar.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/Slider.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/TextBox.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/CheckBox.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/DropdownMenu.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/RadioButton.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/RadioButtonGroup.cpp
	)
#-----------------------------  GUI end    ----------------------

#-----------------------------  Audio start    ----------------------
set(AUDIO_HEADER_FILES ${AUDIO_HEADER_FILES}
    )

set(AUDIO_SOURCE_FILES ${AUDIO_SOURCE_FILES}
    )
#-----------------------------  Audio end    ----------------------

#-----------------------------  Utility start    ----------------------
set(UTILITY_HEADER_FILES ${UTILITY_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/Utility/Epub.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Utility/JSON.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Utility/JSON/JSONNode.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Utility/JSON/JSONValueNode.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Utility/JSON/JSONObjectNode.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Utility/StringMethods.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Utility/XML.hpp
        ${CMAKE_SOURCE_DIR}/include/zeno/Utility/Zip.hpp
	)

set(UTILITY_SOURCE_FILES ${UTILITY_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/Utility/Epub.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Utility/JSON.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Utility/JSON/JSONNode.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Utility/JSON/JSONValueNode.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Utility/JSON/JSONObjectNode.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Utility/StringMethods.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Utility/XML.cpp
        ${CMAKE_SOURCE_DIR}/src/zeno/Utility/Zip.cpp
	)
#-----------------------------  Utility end    ----------------------

#-----------------------------  Game start    ----------------------
set(GAME_HEADER_FILES ${GAME_HEADER_FILES}
        ${CMAKE_SOURCE_DIR}/include/zeno/Game/Game.hpp
		)

set(GAME_SOURCE_FILES ${GAME_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/src/zeno/Game/Game.cpp
		)
#-----------------------------  Game end    ----------------------



if (_WIN32 OR WIN32)
    # Add win32 files
    add_definitions(-DGLEW_STATIC)
    add_definitions(-D_WIN32)
    add_definitions(-DNOMINMAX)


    if (BUILD_SSL STREQUAL "TRUE")
        message(STATUS "BUILD_SSL == TRUE")
        set(LIBS  ${LIBS}
            ssl
            crypto
        )
    else (BUILD_SSL STREQUAL "TRUE")
        message(STATUS "BUILD_SSL != TRUE")
        add_definitions(-DNO_BUILD_SSL)
    endif (BUILD_SSL STREQUAL "TRUE")

    set(LIBS ${LIBS}
        glfw3
        glew32s
        opengl32
        freetype
        ws2_32
    )
else (_WIN32 OR WIN32)
    # Add non win32 files


    if (BUILD_SSL STREQUAL "TRUE")
        message(STATUS "BUILD_SSL == TRUE")
        set(LIBS ${LIBS}
            ssl
            crypto
        )
    else (BUILD_SSL STREQUAL "TRUE")
        message(STATUS "BUILD_SSL != TRUE")
        add_definitions(-DNO_BUILD_SSL)
    endif (BUILD_SSL STREQUAL "TRUE")

    set(LIBS ${LIBS}
        xcb
        X11
        GL
        GLEW
        freetype
        dl
    )

    # freetype is installed to a different location on ubuntu, this solves
    include_directories(/usr/local/include/freetype2/)
endif (_WIN32 OR WIN32)

message(STATUS "LIBS: " ${LIBS})

# Determine what type of library (Static/Shared) to build
if (NOT CMAKE_SHARED_LIBS)
    set(CMAKE_SHARED_LIBS OFF)
    set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}-s")

else(NOT CMAKE_SHARED_LIBS)
    set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}")
    set(LIBRARY_BUILD_TYPE "SHARED")

endif(NOT CMAKE_SHARED_LIBS)

# Determine what type of library (Debug/Release) to build
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Debug)
    set(LIBRARY_EXTENSION "${LIBRARY_EXTENSION}-d")

else(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE Release)

endif(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)


add_library(zeno-window${LIBRARY_EXTENSION}     ${LIBRARY_BUILD_TYPE}   ${WINDOW_SOURCE_FILES}      ${WINDOW_HEADER_FILES})
add_library(zeno-system${LIBRARY_EXTENSION}     ${LIBRARY_BUILD_TYPE}   ${SYSTEM_SOURCE_FILES}      ${SYSTEM_HEADER_FILES})
add_library(zeno-network${LIBRARY_EXTENSION}    ${LIBRARY_BUILD_TYPE}   ${NETWORK_SOURCE_FILES}     ${NETWORK_HEADER_FILES})
add_library(zeno-graphics${LIBRARY_EXTENSION}   ${LIBRARY_BUILD_TYPE}   ${GRAPHICS_SOURCE_FILES}    ${GRAPHICS_HEADER_FILES})
add_library(zeno-gui${LIBRARY_EXTENSION}        ${LIBRARY_BUILD_TYPE}   ${GUI_SOURCE_FILES}         ${GUI_HEADER_FILES})
#add_library(zeno-audio${LIBRARY_EXTENSION}      ${LIBRARY_BUILD_TYPE}   ${AUDIO_SOURCE_FILES}       ${AUDIO_HEADER_FILES})
add_library(zeno-utility${LIBRARY_EXTENSION}    ${LIBRARY_BUILD_TYPE}   ${UTILITY_SOURCE_FILES}     ${UTILITY_HEADER_FILES})
add_library(zeno-game${LIBRARY_EXTENSION}       ${LIBRARY_BUILD_TYPE}   ${GAME_SOURCE_FILES}        ${GAME_HEADER_FILES})

add_executable(testProgram test.cpp)
target_link_libraries(testProgram LINK_PUBLIC   zeno-window${LIBRARY_EXTENSION}
                                                zeno-network${LIBRARY_EXTENSION}
                                                zeno-gui${LIBRARY_EXTENSION}
                                                zeno-graphics${LIBRARY_EXTENSION}
                                                zeno-system${LIBRARY_EXTENSION}
                                                zeno-utility${LIBRARY_EXTENSION}
                                                zeno-game${LIBRARY_EXTENSION}
                                                ${LIBS})

