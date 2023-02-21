cmake_minimum_required( VERSION 3.24 )
project( AverageReadings )

set( CMAKE_CXX_STANDARD 14 )

include_directories( . )

add_executable( AverageReadings
		AverageReadings.ino
		PrivateInfo.h )

set_target_properties( AverageReadings PROPERTIES LINKER_LANGUAGE CXX )
