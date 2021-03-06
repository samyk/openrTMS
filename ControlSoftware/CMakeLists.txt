cmake_minimum_required(VERSION 2.8)

project(Open-rTMS_Control_Software)

find_package(wxWidgets COMPONENTS gl core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

add_subdirectory(src)

if(MINGW)

	add_executable(openrtmscontrol.exe src/Open-rTMS.cpp)

	target_link_libraries(openrtmscontrol.exe
		3D
		gui
		hardware
		${wxWidgets_LIBRARIES}
		opengl32
		glu32
	)

elseif(APPLE)

	find_package(OpenGL REQUIRED)
	add_executable(openrtmscontrol src/Open-rTMS.cpp)

	target_link_libraries(openrtmscontrol
		3D
		gui
		hardware
		${wxWidgets_LIBRARIES}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
	)

else()

	add_executable(openrtmscontrol src/Open-rTMS.cpp)

	target_link_libraries(openrtmscontrol
		3D
		gui
		hardware
		${wxWidgets_LIBRARIES}
		GL
		GLU
	)
	
endif()	

file(COPY i18n DESTINATION ${CMAKE_BINARY_DIR})
file(COPY firmware DESTINATION ${CMAKE_BINARY_DIR})
	
