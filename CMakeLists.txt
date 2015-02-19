project(zeno)
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/test)

set(HEADER_FILES ${HEADER_FILES} 
		include/Colour.hpp
		include/Window.hpp
		)
set(SRC_FILES ${SRC_FILES}
		src/Colour.cpp
		src/Window.cpp
		)

set(TEST_FILES ${TEST_FILES} 
		test/test.cpp
		test/catch.hpp
		)

set(LIBS ${LIBS} X11)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

set(LIBRARY_NAME ${LIBRARY_NAME} zeno)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${LIBRARY_NAME} ${LIBS})

add_executable(tests ${TEST_FILES})
target_link_libraries(tests LINK_PUBLIC ${LIBRARY_NAME})

#add_custom_command(G tests POST_BUILD ./tests)
