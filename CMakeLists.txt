CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
SET(CMAKE_CXX_STANDARD 11)
PROJECT(Cm)

SET(IncludeDir ${CMAKE_SOURCE_DIR}/include)
SET(SrcDir ${CMAKE_SOURCE_DIR}/src)
SET(ResDir ${CMAKE_SOURCE_DIR}/res)
SET(BuildDir ${CMAKE_SOURCE_DIR}/build)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${BuildDir}/parser.cpp)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BisonOutput}
      COMMAND ${BISON_EXECUTABLE}
              --defines=${BuildDir}/parser.hpp
              --output=${BisonOutput}
              -v
              ${ResDir}/parser.y
      COMMENT "Generating parser.cpp"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${BuildDir}/scanner.cpp)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
              --header-file=scanner.hpp
              --outfile=${FlexOutput}
              ${ResDir}/scanner.l
      COMMENT "Generating scanner.cpp"
    )
ENDIF()

SET(IncludeFiles ${IncludeDir}/AST.hpp ${IncludeDir}/context.hpp ${IncludeDir}/errors.hpp)
SET(SrcFiles ${BisonOutput} ${FlexOutput} ${SrcDir}/AST.cpp ${SrcDir}/context.cpp)
ADD_LIBRARY(CmLib ${IncludeFiles} ${SrcFiles})

ADD_EXECUTABLE(Cm ${SrcDir}/main.cpp)
TARGET_LINK_LIBRARIES(Cm CmLib)

ENABLE_TESTING()
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/test)