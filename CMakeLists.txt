cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME sfml_enemies)				 # имя проекта		 
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_definitions(-DSFML_STATIC)		 # дефайны

include_directories("ext/SFML/include/")	# добавляем директории
include_directories("inc/")
link_directories("ext/SFML/lib/")	

add_executable("${PROJECT_NAME}" main.cpp inc/game.hpp inc/ship.hpp inc/bullet.hpp inc/Enemies.hpp inc/Enemy1.hpp  inc/Enemy2.hpp inc/Enemy3.hpp inc/asteroid.hpp inc/menu.hpp
src/game.cpp src/ship.cpp src/bullet.cpp src/Enemies.cpp src/Enemy1.cpp  src/Enemy2.cpp src/Enemy3.cpp src/asteroid.cpp src/menu.cpp)
											
target_link_libraries("${PROJECT_NAME}" 
						  sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)
						  
file(COPY "assets" DESTINATION "/")
file(COPY "openal32.dll" DESTINATION "/")