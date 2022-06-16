target_sources(LearnOpenGL
	PRIVATE
	"main.cpp"
)

add_subdirectory("Application")
add_subdirectory("EventSystem")
#add_subdirectory("GameObject")
add_subdirectory("Mesh")
add_subdirectory("Rendering")
add_subdirectory("ResourceManager")
#add_subdirectory("Scene")
add_subdirectory("Utilities")