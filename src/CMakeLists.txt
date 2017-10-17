# Copyright 2016 Jonathan Eyolfson
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License version 3 as published by the Free
# Software Foundation.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.1.3)

project(EYL_DESKTOP C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_SERVER REQUIRED wayland-server)
pkg_check_modules(WESTON REQUIRED libweston-3)
pkg_check_modules(WESTON_DESKTOP REQUIRED libweston-desktop-3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wpedantic)
add_compile_options(-Wall)
add_compile_options(-Wextra)

include_directories(
	${WAYLAND_SERVER_INCLUDE_DIRS}
	${WESTON_INCLUDE_DIRS}
	${WESTON_DESKTOP_INCLUDE_DIRS}
)
link_directories(
	${WAYLAND_SERVER_LIBRARY_DIRS}
	${WESTON_LIBRARY_DIRS}
	${WESTON_DESKTOP_LIBRARY_DIRS}
)

add_executable(eyl-desktop
	main.c
)
target_link_libraries(eyl-desktop
	${WAYLAND_SERVER_LIBRARIES}
	${WESTON_LIBRARIES}
	${WESTON_DESKTOP_LIBRARIES}
)
