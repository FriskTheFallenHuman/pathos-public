project(clientdll LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:>${CMAKE_SOURCE_DIR}/../engine/pathos/dlls)

add_library(${PROJECT_NAME} SHARED)

set(CLIENT_COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/common/cbitset.cpp
    ${CMAKE_SOURCE_DIR}/common/cbuffer.cpp
    ${CMAKE_SOURCE_DIR}/common/common.cpp
    ${CMAKE_SOURCE_DIR}/common/crc32.cpp
    ${CMAKE_SOURCE_DIR}/common/cstring.cpp
    ${CMAKE_SOURCE_DIR}/common/cstringpool.cpp
    ${CMAKE_SOURCE_DIR}/common/matrix.cpp
    ${CMAKE_SOURCE_DIR}/common/md5.cpp
    ${CMAKE_SOURCE_DIR}/common/r_common.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_COMMON_SOURCES})
source_group("Common" FILES ${CLIENT_COMMON_SOURCES})

set(CLIENT_COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/common/buttonbits.h
    ${CMAKE_SOURCE_DIR}/common/cache_model.h
    ${CMAKE_SOURCE_DIR}/common/carray.h
    ${CMAKE_SOURCE_DIR}/common/carray_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/cbitset.h
    ${CMAKE_SOURCE_DIR}/common/cbitset_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/cbuffer.h
    ${CMAKE_SOURCE_DIR}/common/cbuffer_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/clinkedlist.h
    ${CMAKE_SOURCE_DIR}/common/clinkedlist_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/common.h
    ${CMAKE_SOURCE_DIR}/common/common_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/com_math.h
    ${CMAKE_SOURCE_DIR}/common/com_math_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/constants.h
    ${CMAKE_SOURCE_DIR}/common/crc32.h
    ${CMAKE_SOURCE_DIR}/common/cstring.h
    ${CMAKE_SOURCE_DIR}/common/cstringpool.h
    ${CMAKE_SOURCE_DIR}/common/cstringpool_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/cstring_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/entitydata.h
    ${CMAKE_SOURCE_DIR}/common/hashlist.h
    ${CMAKE_SOURCE_DIR}/common/hashlist_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/matrix.h
    ${CMAKE_SOURCE_DIR}/common/md5.h
    ${CMAKE_SOURCE_DIR}/common/msgreader.h
    ${CMAKE_SOURCE_DIR}/common/msgreader_inline.hpp
    ${CMAKE_SOURCE_DIR}/common/r_common.h
    ${CMAKE_SOURCE_DIR}/common/TinyJSON.cpp
    ${CMAKE_SOURCE_DIR}/common/TinyJSON.h
    ${CMAKE_SOURCE_DIR}/common/vector.h
    ${CMAKE_SOURCE_DIR}/common/vector_inline.hpp)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_COMMON_HEADERS})
source_group("Common" FILES ${CLIENT_COMMON_HEADERS})

file(GLOB CLIENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_SOURCES})
source_group("Client" FILES ${CLIENT_SOURCES})

file(GLOB CLIENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_HEADERS})
source_group("Client" FILES ${CLIENT_HEADERS})

set(CLIENT_SHARED_SOURCES
    ${CMAKE_SOURCE_DIR}/shared/decallist.cpp
    ${CMAKE_SOURCE_DIR}/shared/playermove.cpp
    ${CMAKE_SOURCE_DIR}/shared/r_glextf.cpp
    ${CMAKE_SOURCE_DIR}/shared/r_glsl.cpp
    ${CMAKE_SOURCE_DIR}/shared/r_vbo.cpp
    ${CMAKE_SOURCE_DIR}/shared/stepsound.cpp
    ${CMAKE_SOURCE_DIR}/shared/uischema.cpp
    ${CMAKE_SOURCE_DIR}/shared/vbm_shared.cpp
    ${CMAKE_SOURCE_DIR}/shared/weapons_shared.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_SHARED_SOURCES})
source_group("Shared" FILES ${CLIENT_SHARED_SOURCES})

set(CLIENT_SHARED_HEADERS
    ${CMAKE_SOURCE_DIR}/shared/bike_shared.h
    ${CMAKE_SOURCE_DIR}/shared/blackhole_shared.h
    ${CMAKE_SOURCE_DIR}/shared/brushmodel_shared.h
    ${CMAKE_SOURCE_DIR}/shared/cldll_interface.h
    ${CMAKE_SOURCE_DIR}/shared/decallist.h
    ${CMAKE_SOURCE_DIR}/shared/entity_extrainfo.h
    ${CMAKE_SOURCE_DIR}/shared/flexmanager.h
    ${CMAKE_SOURCE_DIR}/shared/flex_shared.h
    ${CMAKE_SOURCE_DIR}/shared/ladder_shared.h
    ${CMAKE_SOURCE_DIR}/shared/mlight.h
    ${CMAKE_SOURCE_DIR}/shared/playermove.h
    ${CMAKE_SOURCE_DIR}/shared/efxapi.h
    ${CMAKE_SOURCE_DIR}/shared/r_glextf.h
    ${CMAKE_SOURCE_DIR}/shared/r_glsl.h
    ${CMAKE_SOURCE_DIR}/shared/r_glsl_inline.hpp
    ${CMAKE_SOURCE_DIR}/shared/r_interface.h
    ${CMAKE_SOURCE_DIR}/shared/r_vbo.h
    ${CMAKE_SOURCE_DIR}/shared/stepsound.h
    ${CMAKE_SOURCE_DIR}/shared/gameui_shared.h
    ${CMAKE_SOURCE_DIR}/shared/uischema.h
    ${CMAKE_SOURCE_DIR}/shared/vbm_shared.h
    ${CMAKE_SOURCE_DIR}/shared/vcontroller_shared.h
    ${CMAKE_SOURCE_DIR}/shared/weapons_shared.h)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_SHARED_HEADERS})
source_group("Shared" FILES ${CLIENT_SHARED_HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${PLATFORM_DEFINES} CLIENT CLIENT_EXPORTS)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/common ${CMAKE_SOURCE_DIR}/shared)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 OpenGL::GL)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "client_x64")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "client_x86")
endif()
