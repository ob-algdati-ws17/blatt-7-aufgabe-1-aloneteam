file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testAVL ${SRCS} ../avl/AVL.h)

target_link_libraries(testAVL
        gtest
        gmock
)

include_directories("..")

install(TARGETS testAVL DESTINATION bin)
