project(zeno)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extlibs)

# Cross platform code
set(HEADER_FILES ${HEADER_FILES} 
		# Graphics
		include/zeno/Graphics/Colour.hpp
		include/zeno/Graphics/Image.hpp
		include/zeno/Graphics/ImageLoader.hpp
		include/zeno/Graphics/Renderable.hpp
		include/zeno/Graphics/RenderData.hpp
		include/zeno/Graphics/Shader.hpp
		include/zeno/Graphics/ShaderManager.hpp
		include/zeno/Graphics/Sprite.hpp
		include/zeno/Graphics/Texture.hpp
		include/zeno/Graphics/Vertex.hpp
		include/zeno/Graphics/VertexArray.hpp
				
		# GUI
		include/zeno/GUI/GUIEvent.hpp
		include/zeno/GUI/GuiDesktop.hpp
		include/zeno/GUI/GuiBase.hpp
		include/zeno/GUI/GuiPane.hpp
		include/zeno/GUI/GuiButton.hpp
		
		# Network
		
		# System
		include/zeno/System/Clock.hpp
		include/zeno/System/Event.hpp
		include/zeno/System/Font.hpp
		include/zeno/System/FontAtlasImage.hpp
		include/zeno/System/FontLoader.hpp
		include/zeno/System/Glyph.hpp
		include/zeno/System/Keyboard.hpp
		include/zeno/System/Mat4x4.hpp
		include/zeno/System/Mouse.hpp
		include/zeno/System/Rect.hpp
		include/zeno/System/Time.hpp
		include/zeno/System/Transformable2D.hpp
		include/zeno/System/Vector2.hpp
		include/zeno/System/Vector3.hpp
		include/zeno/System/Vector4.hpp
		
		include/zeno/System/Rect.inl
		include/zeno/System/Vector2.inl
		include/zeno/System/Vector3.inl
		include/zeno/System/Vector4.inl
		
		# Window
		include/zeno/Window/ContextImplementation.hpp
		include/zeno/Window/VideoMode.hpp
		include/zeno/Window/Window.hpp
		include/zeno/Window/WindowHandle.hpp
		include/zeno/Window/WindowImplementation.hpp
		include/zeno/Window/WindowStyle.hpp
		)

set(SRC_FILES ${SRC_FILES}
		# Graphics
		src/zeno/Graphics/Colour.cpp
		src/zeno/Graphics/Image.cpp
		src/zeno/Graphics/ImageLoader.cpp
		src/zeno/Graphics/Shader.cpp
		src/zeno/Graphics/ShaderManager.cpp
		src/zeno/Graphics/Sprite.cpp
		src/zeno/Graphics/Texture.cpp
		src/zeno/Graphics/Vertex.cpp
		src/zeno/Graphics/VertexArray.cpp
	
		# GUI
		src/zeno/GUI/GuiDesktop.cpp
		src/zeno/GUI/GuiBase.cpp
		src/zeno/GUI/GuiPane.cpp
		src/zeno/GUI/GuiButton.cpp
	
		# Network
	
		# System
		src/zeno/System/Clock.cpp
		src/zeno/System/Font.cpp
		src/zeno/System/FontAtlasImage.cpp
		src/zeno/System/FontLoader.cpp
		src/zeno/System/Glyph.cpp
		src/zeno/System/Keyboard.cpp
		src/zeno/System/Mat4x4.cpp
		src/zeno/System/Mouse.cpp
		src/zeno/System/Time.cpp
		src/zeno/System/Transformable2D.cpp
		
		
		# Window
		src/zeno/Window/Window.cpp
		
		)
	
# Platform specific code
if(UNIX)
	set (HEADER_FILES ${HEADER_FILES}
			include/zeno/System/InputImplementationUnix.hpp
			
			include/zeno/Window/WindowImplementationUnix.hpp
			include/zeno/Window/ContextUnix.hpp
			)
	set (SRC_FILES ${SRC_FILES}
			src/zeno/System/InputImplementationUnix.cpp
			
			src/zeno/Window/WindowImplementationUnix.cpp
			src/zeno/Window/ContextUnix.cpp
			)
			
	
	set(LIBS ${LIBS} 
			xcb
			X11
			GL
			GLEW
			freetype
			)
			
elseif (WIN32)
	set (HEADER_FILES ${HEADER_FILES}
			include/zeno/System/InputImplementationWindows.hpp
			
			include/zeno/Window/WindowImplementationWin32.hpp
			include/zeno/Window/ContextWin32.hpp
			)
	set (SRC_FILES ${SRC_FILES}
			src/zeno/System/InputImplementationWindows.cpp
			
			src/zeno/Window/WindowImplementationWin32.cpp
			src/zeno/Window/ContextWin32.cpp
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

# Test code
set(TEST_FILES ${TEST_FILES} 
		test/main.cpp
		test/test.cpp
		test/catch.hpp
		test/toString.hpp
		)



set(LIBRARY_NAME ${LIBRARY_NAME} zeno)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${LIBRARY_NAME} ${LIBS})

add_executable(tests ${TEST_FILES})
target_link_libraries(tests LINK_PUBLIC ${LIBRARY_NAME})

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
			
