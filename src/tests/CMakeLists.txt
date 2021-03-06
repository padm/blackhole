CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(PROJECT blackhole-tests)

# The next line enforces google testing framework to use own tuple implementation.
ADD_DEFINITIONS(-DGTEST_USE_OWN_TR1_TUPLE=1)
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/foreign/gmock ${CMAKE_BINARY_DIR}/gmock)

ENABLE_TESTING()

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

file(GLOB_RECURSE BLACKHOLE_HEADERS . ../blackhole/*.hpp)

SET(HEADERS
    ${BLACKHOLE_HEADERS}
    global.hpp
    mocks.hpp
    mocks/files.hpp
    mocks/logger.hpp
    mocks/socket.hpp
    mocks/syslog.hpp
    datetime/common.hpp
    # Temporary
    extra/balancing.hpp
    extra/client.hpp
    extra/log.hpp
    extra/pool.hpp
    extra/settings.hpp
    extra/transport.hpp
    extra/queue.hpp
)

SET(SOURCES
    main
    datetime/test_DayOfYear
    datetime/test_DayOfMonth
    datetime/test_DayOfWeek
    datetime/test_Month
    datetime/test_Other
    datetime/test_Time
    datetime/test_Year
    datetime/test_Week
    extra/ElasticsearchSink
    test_AttachableStream
    test_Attribute
    test_Config
    test_ConfigJsonInitialization
    test_ExceptionTrap
    test_FactoryInitialization
    test_FileRotation
    test_FileRotationNaming
    test_FileBackend
    test_FileRotationSizeWatcher
    test_FileRotationDateTimeWatcher
    test_FileSink
    test_Filter
    test_Functional
    test_JsonFormatter
    test_Keyword
    test_Logger
    test_LoggerSynchronized
    test_Macro
    test_Manual
    test_MsgpackFormatter
    test_NullSink
    test_StreamSink
    test_StringFormatter
    test_StringPatternParser
    test_SyslogSink
    test_Traits
    test_UdpSink
    test_Utils
    test_VerboseLogger
    utils/test_GenericStringFormatter
)

SET(Boost_USE_MULTITHREADED ON)

SET(BOOST_COMPONENTS
    system
    filesystem
    thread
)

PROJECT(${PROJECT})

INCLUDE_DIRECTORIES(
    ../
    ${CMAKE_SOURCE_DIR}/foreign/rapidjson/include
    SYSTEM ${CMAKE_SOURCE_DIR}/foreign/gmock/include
    SYSTEM ${CMAKE_SOURCE_DIR}/foreign/gtest/include
)

LINK_DIRECTORIES(
    ${CMAKE_BINARY_DIR}/gmock/gtest
    ${CMAKE_BINARY_DIR}/gmock
)

FIND_PACKAGE(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

ADD_EXECUTABLE(${PROJECT} ${HEADERS} ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    gmock
    gtest
    msgpack
)

ADD_TEST(NAME blackhole-tests COMMAND blackhole-tests)

ADD_DEFINITIONS(-std=c++0x)

