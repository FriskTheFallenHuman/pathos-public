project(game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:>${CMAKE_SOURCE_DIR}/../engine/pathos/dlls)

add_library(${PROJECT_NAME} SHARED)

set(GAME_COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/common/cbitset.cpp
    ${CMAKE_SOURCE_DIR}/common/common.cpp
    ${CMAKE_SOURCE_DIR}/common/crc32.cpp
    ${CMAKE_SOURCE_DIR}/common/cstring.cpp
    ${CMAKE_SOURCE_DIR}/common/cstringpool.cpp
    ${CMAKE_SOURCE_DIR}/common/logfile.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${GAME_COMMON_SOURCES})
source_group("Common" FILES ${GAME_COMMON_SOURCES})

set(GAME_COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/common/animevent.h
    ${CMAKE_SOURCE_DIR}/common/cache_model.h
    ${CMAKE_SOURCE_DIR}/common/carray.h
    ${CMAKE_SOURCE_DIR}/common/carray_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/cbitset.h
    ${CMAKE_SOURCE_DIR}/common/cbitset_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/clinkedlist.h
    ${CMAKE_SOURCE_DIR}/common/clinkedlist_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/common.h
    ${CMAKE_SOURCE_DIR}/common/common_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/com_math.h
    ${CMAKE_SOURCE_DIR}/common/com_math_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/constants.h
    ${CMAKE_SOURCE_DIR}/common/contents.h
    ${CMAKE_SOURCE_DIR}/common/crc32.h
    ${CMAKE_SOURCE_DIR}/common/cstring.h
    ${CMAKE_SOURCE_DIR}/common/cstringpool.h
    ${CMAKE_SOURCE_DIR}/common/cstringpool_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/cstring_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/logfile.h
    ${CMAKE_SOURCE_DIR}/common/vector.h
    ${CMAKE_SOURCE_DIR}/common/vector_inline.hpp)
target_sources(${PROJECT_NAME} PRIVATE ${GAME_COMMON_HEADERS})
source_group("Common" FILES ${GAME_COMMON_HEADERS})

file(GLOB GAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${GAME_SOURCES})
source_group("Game" FILES ${GAME_SOURCES})

file(GLOB GAME_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${GAME_HEADERS})
source_group("Game" FILES ${GAME_HEADERS})

set(GAME_SHARED_SOURCES
    ${CMAKE_SOURCE_DIR}/shared/activitymappings.cpp
    ${CMAKE_SOURCE_DIR}/shared/decallist.cpp
    ${CMAKE_SOURCE_DIR}/shared/flexmanager.cpp
    ${CMAKE_SOURCE_DIR}/shared/playermove.cpp
    ${CMAKE_SOURCE_DIR}/shared/sentencesfile.cpp
    ${CMAKE_SOURCE_DIR}/shared/stepsound.cpp
    ${CMAKE_SOURCE_DIR}/shared/vbm_shared.cpp
    ${CMAKE_SOURCE_DIR}/shared/weapons_shared.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${GAME_SHARED_SOURCES})
source_group("Shared" FILES ${GAME_SHARED_SOURCES})

set(GAME_SHARED_HEADERS
    ${CMAKE_SOURCE_DIR}/shared/activity.h
    ${CMAKE_SOURCE_DIR}/shared/blackhole_shared.h
    ${CMAKE_SOURCE_DIR}/shared/brushmodel_shared.h
    ${CMAKE_SOURCE_DIR}/shared/gdll_interface.h
    ${CMAKE_SOURCE_DIR}/shared/globalstate_shared.h
    ${CMAKE_SOURCE_DIR}/shared/net_shared.h
    ${CMAKE_SOURCE_DIR}/shared/playermove.h
    ${CMAKE_SOURCE_DIR}/shared/portal_shared.h
    ${CMAKE_SOURCE_DIR}/shared/sentencesfile.h
    ${CMAKE_SOURCE_DIR}/shared/stepsound.h
    ${CMAKE_SOURCE_DIR}/shared/trace.h
    ${CMAKE_SOURCE_DIR}/shared/weapons_shared.h)
target_sources(${PROJECT_NAME} PRIVATE ${GAME_SHARED_HEADERS})
source_group("Shared" FILES ${GAME_SHARED_HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${PLATFORM_DEFINES} GAMEDLL GAMEDLL_EXPORTS)
target_include_directories(${PROJECT_NAME} PRIVATE {CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/common ${CMAKE_SOURCE_DIR}/shared)
target_link_libraries(${PROJECT_NAME} PRIVATE libs SDL2::SDL2)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "game_x64")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "game_x86")
endif()
