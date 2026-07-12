include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(LOBTests
  OrderTest.cpp
  LobTest.cpp
)

target_link_libraries(LOBTests
  PRIVATE
    lob
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(LOBTests)
