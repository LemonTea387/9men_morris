enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

add_executable(
  savegame_test
  savegame_test.cpp
  ../src/SaveGame.hpp
  ../src/SaveGame.cpp
)
target_link_libraries(
  savegame_test 
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(savegame_test)

