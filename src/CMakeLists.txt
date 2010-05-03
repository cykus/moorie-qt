set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/")

find_package(Boost COMPONENTS regex REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(mcrypt REQUIRED)
find_package(mhash REQUIRED)
find_package(Qt4 REQUIRED )

add_subdirectory (cli)
add_subdirectory (lib)
if(ENABLE_GUI)
	add_subdirectory (gui)
endif(ENABLE_GUI)


