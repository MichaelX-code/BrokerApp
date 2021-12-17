cmake_minimum_required(VERSION 3.20)
project(BrokerApp)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
    include/investments/investment.cpp
    include/investments/stock.cpp
    include/investments/obligation.cpp
    include/investments/metal.cpp
    include/fund.cpp
    include/market.cpp
    include/utils/utils.cpp
    include/utils/date.cpp
    include/utils/csv_parser.cpp
    main.cpp)

include_directories(include)
add_executable(BrokerApp ${SOURCE_FILES})
