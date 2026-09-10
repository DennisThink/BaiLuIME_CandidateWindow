cmake_minimum_required(VERSION 3.0)
project(BaiLuIME_CandidateWindow)
SET(SOURCE_FILE ./WinMain.cpp
./CandidateWindow.cpp
./CandidateWindow.h
./ListCandidateView.cpp
./ListCandidateView.h
)
include_directories(.)
add_compile_definitions(UNICODE _UNICODE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS") 
add_executable(windowTest ${SOURCE_FILE})