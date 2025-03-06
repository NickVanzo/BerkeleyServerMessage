project(exercise7Chapter4)
set(SOURCES OutputMemoryBitStream.cpp main.cpp ../cmake-build-debug/exercise8Chapter4/main.cpp ../ex8Chapter4/main.cpp ../ex8Chapter4/OutputMemoryBitStream.cpp ../ex8Chapter4/OutputMemoryBitStream.h)
add_executable(exercise7 ${SOURCES})
target_link_libraries(exercise7)