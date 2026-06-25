# Set minimum policy version to avoid errors about new CMake features
# This is mainly for vorbis.
set(CMAKE_POLICY_VERSION_MINIMUM 3.15)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:>${CMAKE_SOURCE_DIR}/../engine)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_definitions(-DXTHREADS)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-format-security -Wno-invalid-offsetof -fvisibility=hidden -fno-unsafe-math-optimizations -fno-strict-aliasing -fPIC")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fno-omit-frame-pointer -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -msse2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_definitions(-DXTHREADS)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-format-security -Wno-invalid-offsetof -fvisibility=hidden -fno-unsafe-math-optimizations -fno-strict-aliasing -fPIC")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fno-omit-frame-pointer -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -msse2")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)
	add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE)
	add_compile_definitions(WIN32)
	add_compile_definitions(_WIN32_WINNT=0x0601)
	add_compile_definitions(NTDDI_VERSION=0x06010000)

	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	    add_compile_definitions(_USE_32BIT_TIME_T)
	endif()

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	    add_compile_definitions(_64BUILD)
	endif()

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO /STACK:16777216,16777216 /LARGEADDRESSAWARE /MAP /DELAYLOAD:OpenAL32.dll /DELAYLOAD:SDL2d.dll /DELAYLOAD:SDL2.dll delayimp.lib")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} /ASSEMBLYDEBUG")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /OPT:REF /OPT:ICF")
	
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO /STACK:16777216,16777216 /LARGEADDRESSAWARE /MAP")
	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS} /ASSEMBLYDEBUG")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} /OPT:REF /OPT:ICF")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /GR /fp:fast /GS- /MP /W3")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /MDd /Od /Zi")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /O2 /GL")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MD /O2 /GL /Zi")

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

if(UNIX)
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()
