# CMakeLists.txt
# Used for building the example code on any CMake supported system.
# This software is licensed under the MIT license. Please refer to
# LICENSE.txt for more information.

#IF(BIICODE)
#   INCLUDE("biicode.cmake")
#   RETURN()
#ENDIF()

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (PhantomBot)

# If we're on GCC, set the c++11 compilation flag.
IF (CMAKE_COMPILER_IS_GNUCXX)
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -std=c++11")
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

SET (EX_BUILDLOCATION "PhantomBot")

INCLUDE_DIRECTORIES ("Lib/" "Network/" "TwitchCommands/" "TwitchIRC/" "CustomCommands/")
FILE(GLOB_RECURSE LIB_SOURCES "Lib/*.cpp")
FILE(GLOB_RECURSE NETWORK_SOURCES "Network/*.cpp")
FILE(GLOB_RECURSE TCOMMANDS_SOURCES "TwitchCommands/*.cpp")
FILE(GLOB_RECURSE TIRC_SOURCES "TwitchIRC/*.cpp")
FILE(GLOB_RECURSE CCMDS_SOURCES "CustomCommands/*.cpp")

ADD_EXECUTABLE (${EX_BUILDLOCATION} "PhantomBot.cpp" ${LIB_SOURCES}
 ${NETWORK_SOURCES} ${TCOMMANDS_SOURCES} ${TIRC_SOURCES} ${CCMDS_SOURCES})

