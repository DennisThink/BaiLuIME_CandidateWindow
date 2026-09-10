cmake_minimum_required(VERSION 3.0)
project(BaiLuIME_CandidateWindow)
SET(TEST1_SOURCE_FILE ./WinMain.cpp)
SET(COMMON_FILE ./CandidateWindow.cpp
./CandidateWindow.h
./ListCandidateView.cpp
./ListCandidateView.h
)
SET(TEST2_SOURCE_FILE ./TestCore.h ./TestCore.cpp ./TestWindow.h TestWindow.cpp ./main.cpp)
include_directories(.)
add_compile_definitions(UNICODE _UNICODE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") 
add_executable(windowTest1 ${TEST1_SOURCE_FILE} ${COMMON_FILE})
add_executable(windowTest2 ${TEST2_SOURCE_FILE} ${COMMON_FILE})