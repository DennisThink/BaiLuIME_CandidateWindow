cmake_minimum_required(VERSION 3.0)
project(BaiLuIME_CandidateWindow_Test)
include_directories(../../external/BaiLuIME_Common/include/)
SET(TEST1_SOURCE_FILE ./test1/WinMain.cpp)
SET(SOURCE_FOLDER ../source)
SET(COMMON_FILE ${SOURCE_FOLDER}/CandidateWindow.cpp
${SOURCE_FOLDER}/CandidateWindow.h
${SOURCE_FOLDER}/ListCandidateView.cpp
${SOURCE_FOLDER}/ListCandidateView.h
${SOURCE_FOLDER}/PreeditWindow.cpp
${SOURCE_FOLDER}/PreeditWindow.h
${SOURCE_FOLDER}/WindowBase.cpp
../../external/BaiLuIME_Common/src/core/CommonFunction.cpp
)
SET(TEST2_SOURCE_FILE ./test2/TestCore.h 
./test2/TestCore.cpp 
./test2/TestWindow.h 
./test2/TestWindow.cpp 
./test2/main.cpp)
include_directories(${SOURCE_FOLDER})
#add_compile_definitions(UNICODE _UNICODE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") 
add_executable(windowTest1 ${TEST1_SOURCE_FILE} ${COMMON_FILE})
add_executable(windowTest2 ${TEST2_SOURCE_FILE} ${COMMON_FILE})