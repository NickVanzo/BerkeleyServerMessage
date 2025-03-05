project(exercise7Chapter4)
set(SOURCES OutputMemoryBitStream.cpp main.cpp ../cmake-build-debug/exercise8Chapter4/main.cpp ../ex8Chapter4/main.cpp ../ex8Chapter4/UnorderedMapConverted.cpp ../ex8Chapter4/UnorderedMapConverted.h)
add_executable(exercise7 ${SOURCES})
target_link_libraries(exercise7)