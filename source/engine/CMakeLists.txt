project(pathos_engine LANGUAGES CXX C)

add_executable(${PROJECT_NAME})

file(GLOB ENGINE_COMMON_CSOURCES ${CMAKE_SOURCE_DIR}/common/*.c)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_COMMON_CSOURCES})
source_group("Engine\\Common" FILES ${ENGINE_COMMON_CSOURCES})

file(GLOB ENGINE_COMMON_SOURCES ${CMAKE_SOURCE_DIR}/common/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_COMMON_SOURCES})
source_group("Engine\\Common" FILES ${ENGINE_COMMON_SOURCES})

file(GLOB ENGINE_COMMON_HEADERS ${CMAKE_SOURCE_DIR}/common/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_COMMON_HEADERS})
source_group("Engine\\Common" FILES ${ENGINE_COMMON_HEADERS})

if(WIN32)
file(GLOB RES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resource/*.rc ${CMAKE_CURRENT_SOURCE_DIR}/resource/*.ico ${CMAKE_CURRENT_SOURCE_DIR}/resource/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${RES_SOURCES})
source_group("Engine\\RC" FILES ${RES_SOURCES})
endif()

file(GLOB RYG_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/rygsdxtc/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${RYG_SOURCES})
source_group("Engine\\RYGSDXTc" FILES ${RYG_SOURCES})

file(GLOB RYG_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/rygsdxtc/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${RYG_HEADERS})
source_group("Engine\\RYGSDXTc" FILES ${RYG_HEADERS})

file(GLOB WINDOW_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/windows/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${WINDOW_SOURCES})
source_group("Engine\\Windows" FILES ${WINDOW_SOURCES})

file(GLOB WINDOW_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/windows/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${WINDOW_HEADERS})
source_group("Engine\\Windows" FILES ${WINDOW_HEADERS})

file(GLOB UI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${UI_SOURCES})
source_group("Engine\\UI" FILES ${UI_SOURCES})

file(GLOB UI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${UI_HEADERS})
source_group("Engine\\UI" FILES ${UI_HEADERS})

file(GLOB RENDER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/renderer/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${RENDER_SOURCES})
source_group("Engine\\Renderer" FILES ${RENDER_SOURCES})

if(WIN32)
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/r_water.cpp
        ${CMAKE_SOURCE_DIR}/shared/r_vbo.cpp
        PROPERTIES COMPILE_OPTIONS "$<$<AND:$<CONFIG:Release>,$<EQUAL:8,${CMAKE_SIZEOF_VOID_P}>>:/O2>")
endif()

file(GLOB RENDER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/renderer/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${RENDER_HEADERS})
source_group("Engine\\Renderer" FILES ${RENDER_HEADERS})

file(GLOB SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SERVER_SOURCES})
source_group("Engine\\Server" FILES ${SERVER_SOURCES})

file(GLOB SERVER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/server/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${SERVER_HEADERS})
source_group("Engine\\Server" FILES ${SERVER_HEADERS})


file(GLOB BSP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/bsp/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${BSP_SOURCES})
source_group("Engine\\BSP" FILES ${BSP_SOURCES})

file(GLOB BSP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/bsp/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${BSP_HEADERS})
source_group("Engine\\BSP" FILES ${BSP_HEADERS})

file(GLOB CLIENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/client/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_SOURCES})
source_group("Engine\\Client" FILES ${CLIENT_SOURCES})

file(GLOB CLIENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/client/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${CLIENT_HEADERS})
source_group("Engine\\Client" FILES ${CLIENT_HEADERS})

file(GLOB ENGINE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_SOURCES})
source_group("Engine" FILES ${ENGINE_SOURCES})

file(GLOB ENGINE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_HEADERS})
source_group("Engine" FILES ${ENGINE_HEADERS})

file(GLOB ENGINE_SHARED_SOURCES ${CMAKE_SOURCE_DIR}/shared/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_SHARED_SOURCES})
source_group("Engine\\Shared" FILES ${ENGINE_SHARED_SOURCES})

file(GLOB ENGINE_SHARED_HEADERS ${CMAKE_SOURCE_DIR}/shared/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_SHARED_HEADERS})
source_group("Engine\\Shared" FILES ${ENGINE_SHARED_HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${PLATFORM_DEFINES} $<$<CONFIG:Debug>:_CONSOLE;NETWORKING;DONT_USE_VAO>)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/shared
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp
    ${CMAKE_CURRENT_SOURCE_DIR}/client
    ${CMAKE_CURRENT_SOURCE_DIR}/server
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/windows
    ${CMAKE_CURRENT_SOURCE_DIR}/rygsdxtc)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    OpenAL::OpenAL
    ENet::enet
    ${OPENGL_LIBRARIES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE Detours::detours)
    target_link_libraries(${PROJECT_NAME} PRIVATE user32 gdi32 shell32 glu32 winmm ws2_32 gdiplus comctl32)

    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE" LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl OpenGL::GL)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "pathos_x64")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "pathos_x86")
endif()
