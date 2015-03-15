project(zeno)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extlibs)

# Cross platform code
set(HEADER_FILES ${HEADER_FILES} 
		include/Colour.hpp
		include/ContextImplementation.hpp
		include/Clock.hpp
		include/Event.hpp
		include/FontAtlasImage.hpp
		include/FontLoader.hpp
		include/Glyph.hpp
		include/Image.hpp
		include/ImageLoader.hpp
		include/Keyboard.hpp
		include/Mat4x4.hpp
		include/Mouse.hpp
		include/Rect.hpp
		include/Shader.hpp
		include/ShaderManager.hpp
		include/Time.hpp
		include/Vector2.hpp
		include/Vector3.hpp
		include/Vector4.hpp
		include/VideoMode.hpp
		include/Window.hpp
		include/WindowHandle.hpp
		include/WindowImplementation.hpp
		include/WindowStyle.hpp
		
		include/GUIEvent.hpp
		include/GuiDesktop.hpp
		include/GuiBase.hpp
		include/GuiPane.hpp
		include/GuiButton.hpp
		)
set(INLINE_FILES ${INLINE_FILES}
		include/Rect.inl
		include/Vector2.inl
		include/Vector3.inl
		include/Vector4.inl
		)
set(SRC_FILES ${SRC_FILES}
		src/Colour.cpp
		src/Clock.cpp
		src/FontAtlasImage.cpp
		src/FontLoader.cpp
		src/Glyph.cpp
		src/Image.cpp
		src/ImageLoader.cpp
		src/Keyboard.cpp
		src/Mat4x4.cpp
		src/Mouse.cpp
		src/Shader.cpp
		src/ShaderManager.cpp
		src/Time.cpp
		src/VideoMode.cpp
		src/Window.cpp
		
		src/GuiDesktop.cpp
		src/GuiBase.cpp
		src/GuiPane.cpp
		src/GuiButton.cpp
		)


include_directories(${CMAKE_SOURCE_DIR}/extlibs/glew/include)
include_directories(${CMAKE_SOURCE_DIR}/extlibs/freetype/include)

link_directories(${CMAKE_SOURCE_DIR}/extlibs/glew/lib)
link_directories(${CMAKE_SOURCE_DIR}/extlibs/freetype/lib)
		
# Platform specific code
if(UNIX)
	set (HEADER_FILES ${HEADER_FILES}
			include/InputImplementationUnix.hpp
			include/WindowImplementationUnix.hpp
			include/ContextUnix.hpp
			)
	set (SRC_FILES ${SRC_FILES}
			src/InputImplementationUnix.cpp
			src/WindowImplementationUnix.cpp
			src/ContextUnix.cpp
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
			include/InputImplementationWindows.hpp
			include/WindowImplementationWin32.hpp
			include/ContextWin32.hpp
			)
	set (SRC_FILES ${SRC_FILES}
			src/InputImplementationWindows.cpp
			src/WindowImplementationWin32.cpp
			src/ContextWin32.cpp
			)	
	
	set (LIBS ${LIBS}
			glew32s
			opengl32
			freetype
			)
			
endif(UNIX)

# Test code
set(TEST_FILES ${TEST_FILES} 
		test/main.cpp
		test/test.cpp
		test/catch.hpp
		test/toString.hpp
		)



set(LIBRARY_NAME ${LIBRARY_NAME} zeno)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES} ${HEADER_FILES} ${INLINE_FILES})
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
			
