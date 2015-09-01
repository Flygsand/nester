find_package(Boost 1.54.0 REQUIRED
             COMPONENTS log program_options)
find_package(Threads)

add_executable(nester nester.cpp nst/database.cpp)
add_definitions(-DBOOST_LOG_DYN_LINK)
target_link_libraries(nester ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})