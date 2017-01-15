cmake_minimum_required(VERSION 3.2)
project(Taxi)

#set(core_sockets src/sockets/Socket.cpp src/sockets/Udp.cpp src/sockets/Tcp.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})
#add_library(sockets ${core_sockets})


set(core_sockets src/Point.cpp src/Point.h
        src/Grid.h src/Grid.cpp src/BFS.h src/BFS.cpp src/ISearchable.h src/ISearchable.cpp
        src/Parser.h src/Parser.cpp src/State.h src/State.cpp src/Trip.h src/Trip.cpp
        src/Driver.cpp src/Driver.h src/ITaxiCab.h src/ITaxiCab.cpp src/Waze.cpp src/Waze.h
        src/LuxuryCab.cpp src/LuxuryCab.h src/Map.cpp src/Map.h src/Passenger.cpp src/Passenger.h
        src/StandardCab.cpp src/StandardCab.h src/TaxiCenter.cpp src/TaxiCenter.h
        src/Menu.cpp src/Menu.h src/sockets/Udp.cpp src/sockets/Udp.h
        src/sockets/Socket.cpp src/sockets/Socket.h)


add_executable(Main ${core_sockets} Main.cpp)
add_executable(Client ${core_sockets} Client.cpp)

target_link_libraries(Main   ${Boost_LIBRARIES})
target_link_libraries(Client  ${Boost_LIBRARIES})

#endif()
