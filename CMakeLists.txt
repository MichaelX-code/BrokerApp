cmake_minimum_required(VERSION 3.20)
project(BrokerApp)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
    include/fund.cpp
    include/investment.cpp
    include/utils/utils.cpp
    include/utils/date.cpp
    main.cpp)

include_directories(include)
add_executable(BrokerApp ${SOURCE_FILES})
