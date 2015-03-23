project(zeno)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extlibs)

set(LIB_TYPE SHARED)

if(BUILD_SHARED_LIBS MATCHES OFF)
    set(BUILD_TYPE_EXTENSION ${BUILD_TYPE_EXTENSION}-s)
	set(LIB_TYPE STATIC)
endif(BUILD_SHARED_LIBS MATCHES OFF)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(BUILD_TYPE_EXTENSION ${BUILD_TYPE_EXTENSION}-d)
endif(CMAKE_BUILD_TYPE MATCHES Debug)


# Cross platform code
set(GRAPHICS_HEADER_FILES ${GRAPHICS_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Colour.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Image.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/ImageLoader.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Renderable.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/RenderData.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Shader.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/ShaderManager.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Sprite.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Texture.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/Vertex.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Graphics/VertexArray.hpp
	)
			
set(GUI_HEADER_FILES ${GUI_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GUIEvent.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GuiDesktop.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GuiBase.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GuiPane.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/GUI/GuiButton.hpp
	)
	
set(NETWORK_HEADER_FILES ${NETWORK_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/Network/Socket.hpp
	)
		
set(SYSTEM_HEADER_FILES ${SYSTEM_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/System/Clock.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Event.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Font.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/FontAtlasImage.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/FontLoader.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Glyph.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Keyboard.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Mat4x4.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Mouse.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Rect.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Time.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Transformable2D.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector2.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector3.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector4.hpp
		
		${CMAKE_SOURCE_DIR}/include/zeno/System/Rect.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector2.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector3.inl
		${CMAKE_SOURCE_DIR}/include/zeno/System/Vector4.inl
	)
		
set(WINDOW_HEADER_FILES ${WINDOW_HEADER_FILES}
		${CMAKE_SOURCE_DIR}/include/zeno/Window/ContextImplementation.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/VideoMode.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/Window.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/WindowHandle.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/WindowImplementation.hpp
		${CMAKE_SOURCE_DIR}/include/zeno/Window/WindowStyle.hpp
	)

set(GRAPHICS_SOURCE_FILES ${GRAPHICS_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Colour.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Image.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/ImageLoader.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Shader.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/ShaderManager.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Sprite.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Texture.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/Vertex.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/Graphics/VertexArray.cpp
	)
	
set(GUI_SOURCE_FILES ${GUI_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/GuiDesktop.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/GuiBase.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/GuiPane.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/GUI/GuiButton.cpp
	)
	
set(NETWORK_SOURCE_FILES ${NETWORK_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/Network/Socket.cpp
	)
	
set(SYSTEM_SOURCE_FILES ${SYSTEM_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/System/Clock.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Font.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/FontAtlasImage.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/FontLoader.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Glyph.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Keyboard.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Mat4x4.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Mouse.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Time.cpp
		${CMAKE_SOURCE_DIR}/src/zeno/System/Transformable2D.cpp
	)
		
set(WINDOW_SOURCE_FILES ${WINDOW_SOURCE_FILES}
		${CMAKE_SOURCE_DIR}/src/zeno/Window/Window.cpp
	)
	
# Platform specific code
if(UNIX)
	set (SYSTEM_HEADER_FILES ${SYSTEM_HEADER_FILES}
			${CMAKE_SOURCE_DIR}/include/zeno/System/InputImplementationUnix.hpp
		)			

	set (WINDOW_HEADER_FILES ${WINDOW_HEADER_FILES}
			${CMAKE_SOURCE_DIR}/include/zeno/Window/WindowImplementationUnix.hpp
			${CMAKE_SOURCE_DIR}/include/zeno/Window/ContextUnix.hpp
		)
			
	set (SYSTEM_SOURCE_FILES ${SYSTEM_SOURCE_FILES}
			${CMAKE_SOURCE_DIR}/src/zeno/System/InputImplementationUnix.cpp
		)
		
	set (WINDOW_SOURCE_FILES ${WINDOW_SOURCE_FILES}
			${CMAKE_SOURCE_DIR}/src/zeno/Window/WindowImplementationUnix.cpp
			${CMAKE_SOURCE_DIR}/src/zeno/Window/ContextUnix.cpp
		)
			
	set(LIBS ${LIBS} 
			xcb
			X11
			GL
			GLEW
			freetype
			)
			
elseif (WIN32)
	set (SYSTEM_HEADER_FILES ${SYSTEM_HEADER_FILES}
			${CMAKE_SOURCE_DIR}/include/zeno/System/InputImplementationWindows.hpp
		)
	set (WINDOW_HEADER_FILES ${WINDOW_HEADER_FILES}
			${CMAKE_SOURCE_DIR}/include/zeno/Window/WindowImplementationWin32.hpp
			${CMAKE_SOURCE_DIR}/include/zeno/Window/ContextWin32.hpp
		)
		
	set (SYSTEM_SOURCE_FILES ${SYSTEM_SOURCE_FILES}
			${CMAKE_SOURCE_DIR}/src/zeno/System/InputImplementationWindows.cpp
		)
	
	set (WINDOW_SOURCE_FILES ${WINDOW_SOURCE_FILES}
			${CMAKE_SOURCE_DIR}/src/zeno/Window/WindowImplementationWin32.cpp
			${CMAKE_SOURCE_DIR}/src/zeno/Window/ContextWin32.cpp
		)	
	
	set (LIBS ${LIBS}
			glew32s
			opengl32
			freetype
			)
			
endif(UNIX)

include_directories(${CMAKE_SOURCE_DIR}/extlibs/glew/include)
include_directories(${CMAKE_SOURCE_DIR}/extlibs/freetype/include)

link_directories(${CMAKE_SOURCE_DIR}/extlibs/glew/lib)
link_directories(${CMAKE_SOURCE_DIR}/extlibs/freetype/lib)
link_directories(${CMAKE_SOURCE_DIR}/build)

# Test code
set(TEST_FILES ${TEST_FILES} 
		test/main.cpp
		test/test.cpp
		test/catch.hpp
		test/toString.hpp
		)


set(ALL_SOURCE_FILES ${ALL_SOURCE_FILES}
		${GRAPHICS_HEADER_FILES}
		${GUI_HEADER_FILES}
		${NETWORK_HEADER_FILES}
		${SYSTEM_HEADER_FILES}
		${WINDOW_HEADER_FILES}
	)
	
set(ALL_HEADER_FILES ${ALL_HEADER_FILES}
		${GRAPHICS_SOURCE_FILES}
		${GUI_SOURCE_FILES}
		${NETWORK_SOURCE_FILES}
		${SYSTEM_SOURCE_FILES}
		${WINDOW_SOURCE_FILES}
	)
	
set(MODULE_NAMES ${MODULE_NAMES}
		${CMAKE_PROJECT_NAME}-graphics${BUILD_TYPE_EXTENSION}
		${CMAKE_PROJECT_NAME}-gui${BUILD_TYPE_EXTENSION}
		${CMAKE_PROJECT_NAME}-network${BUILD_TYPE_EXTENSION}
		${CMAKE_PROJECT_NAME}-system${BUILD_TYPE_EXTENSION}
		${CMAKE_PROJECT_NAME}-window${BUILD_TYPE_EXTENSION}
	)
	

add_library(${CMAKE_PROJECT_NAME}-graphics${BUILD_TYPE_EXTENSION} 	${LIB_TYPE} ${GRAPHICS_SOURCE_FILES}	${GRAPHICS_HEADER_FILES})
add_library(${CMAKE_PROJECT_NAME}-gui${BUILD_TYPE_EXTENSION} 		${LIB_TYPE} ${GUI_SOURCE_FILES}			${GUI_HEADER_FILES})
add_library(${CMAKE_PROJECT_NAME}-network${BUILD_TYPE_EXTENSION} 	${LIB_TYPE} ${NETWORK_SOURCE_FILES}		${NETWORK_HEADER_FILES})
add_library(${CMAKE_PROJECT_NAME}-system${BUILD_TYPE_EXTENSION} 	${LIB_TYPE} ${SYSTEM_SOURCE_FILES}		${SYSTEM_HEADER_FILES})
add_library(${CMAKE_PROJECT_NAME}-window${BUILD_TYPE_EXTENSION} 	${LIB_TYPE} ${WINDOW_SOURCE_FILES}		${WINDOW_HEADER_FILES})	
	


add_executable(tests ${TEST_FILES})
target_link_libraries(tests LINK_PUBLIC ${MODULE_NAMES} ${LIBS})

install(TARGETS ${CMAKE_PROJECT_NAME}-graphics${BUILD_TYPE_EXTENSION}	DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/lib)
install(TARGETS ${CMAKE_PROJECT_NAME}-gui${BUILD_TYPE_EXTENSION}		DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/lib)
install(TARGETS ${CMAKE_PROJECT_NAME}-network${BUILD_TYPE_EXTENSION}	DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/lib)
install(TARGETS ${CMAKE_PROJECT_NAME}-system${BUILD_TYPE_EXTENSION}		DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/lib)
install(TARGETS ${CMAKE_PROJECT_NAME}-window${BUILD_TYPE_EXTENSION}		DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/lib)

# Install Graphics header files
foreach(FILENAME ${GRAPHICS_HEADER_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/include/zeno/Graphics)
endforeach()
# Install GUI header files
foreach(FILENAME ${GUI_HEADER_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/include/zeno/GUI)
endforeach()
# Install Network header files
foreach(FILENAME ${NETWORK_HEADER_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/include/zeno/Network)
endforeach()
# Install System header files
foreach(FILENAME ${SYSTEM_HEADER_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/include/zeno/System)
endforeach()
# Install Window header files
foreach(FILENAME ${WINDOW_HEADER_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/include/zeno/Window)
endforeach()

# Install Graphics source files
foreach(FILENAME ${GRAPHICS_SOURCE_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/src/zeno/Graphics)
endforeach()
# Install GUI source files
foreach(FILENAME ${GUI_SOURCE_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/src/zeno/GUI)
endforeach()
# Install Network source files
foreach(FILENAME ${NETWORK_SOURCE_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/src/zeno/Network)
endforeach()
# Install System source files
foreach(FILENAME ${SYSTEM_SOURCE_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/src/zeno/System)
endforeach()
# Install Window source files
foreach(FILENAME ${WINDOW_SOURCE_FILES})
	install(FILES ${FILENAME} DESTINATION C:/programminglibs/${CMAKE_PROJECT_NAME}/src/zeno/Window)
endforeach()


if(UNIX)
	add_definitions(-std=c++11
					-Werror
					-Wall
					)
elseif (WIN32)
	# Gets rid of warnings from fopen in stb header
	add_definitions(-D_CRT_SECURE_NO_WARNINGS
					-DGLEW_STATIC
					)
	
	# Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif(UNIX)			
			
