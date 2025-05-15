file(GLOB_RECURSE ROOT_FILES ./*.hpp ./*.cpp)
file(GLOB_RECURSE CORE_FILES ./Core/*.hpp ./Core/*.cpp)
file(GLOB_RECURSE DETAIL_FILES ./Detail/*.hpp ./Detail/*.cpp)

source_group("Root Files" FILES ${ROOT_FILES})
source_group("Core Files" FILES ${CORE_FILES})
source_group("Detail Files" FILES ${DETAIL_FILES})

add_library(ManHeaderOnly INTERFACE)
add_library(Man::ManHeaderOnly ALIAS ManHeaderOnly)

target_include_directories(ManHeaderOnly INTERFACE
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (MAN_BUILD_LIBRARY)
    add_library(Man
            ${ROOT_FILES} ${CORE_FILES} ${DETAIL_FILES}
    )
    add_library(Man::Man ALIAS Man)
    target_link_libraries(Man PUBLIC ManHeaderOnly)
else ()
    add_library(Man INTERFACE)
    add_library(Man::Man ALIAS Man)
    target_link_libraries(Man INTERFACE ManHeaderOnly)
endif ()

target_compile_features(Man PUBLIC cxx_std_20)
set_property(TARGET Man PROPERTY CXX_STANDARD 20)

target_compile_definitions(Man
            PUBLIC
            $<$<CONFIG:Release>:NDEBUG>
            $<$<CONFIG:Debug>:_DEBUG>
            # Windows
            $<$<PLATFORM_ID:Windows>:NOMINMAX>
            $<$<PLATFORM_ID:Windows>:UNICODE>
            # MSVC C++ 
            $<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES>
            $<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>
            $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
            $<$<CXX_COMPILER_ID:MSVC>:_ENABLE_EXTENDED_ALIGNED_STORAGE>
            $<$<CXX_COMPILER_ID:MSVC>:_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING>
            # Clang.
            $<$<CXX_COMPILER_ID:Clang>:_MSC_EXTENSIONS> # enable MS extensions
)
    
if (MAN_USE_DOUBLE_PRECISION)
target_compile_definitions(Man
            PUBLIC
            MAN_DOUBLE_PRECISION
)
endif()

set_target_properties(Man PROPERTIES LINKER_LANGUAGE CXX)
