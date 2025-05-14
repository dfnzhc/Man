file(GLOB_RECURSE ROOT_FILES ./*.hpp ./*.cpp)
file(GLOB_RECURSE CORE_FILES ./Core/*.hpp ./Core/*.cpp)
file(GLOB_RECURSE DETAIL_FILES ./Detail/*.hpp ./Detail/*.cpp)
file(GLOB_RECURSE OPERATION_FILES ./Operation/*.hpp ./Operation/*.cpp)

source_group("Root Files" FILES ${ROOT_FILES})
source_group("Core Files" FILES ${CORE_FILES})
source_group("Detail Files" FILES ${DETAIL_FILES})
source_group("Operation Files" FILES ${OPERATION_FILES})

add_library(ManHeaderOnly INTERFACE)
add_library(Man::ManHeaderOnly ALIAS ManHeaderOnly)

target_include_directories(ManHeaderOnly INTERFACE
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (MAN_BUILD_LIBRARY)
    add_library(Man
            ${ROOT_FILES} ${CORE_FILES} ${DETAIL_FILES} ${OPERATION_FILES}
    )
    add_library(Man::Man ALIAS Man)
    target_link_libraries(Man PUBLIC ManHeaderOnly)
else ()
    add_library(Man INTERFACE)
    add_library(Man::Man ALIAS Man)
    target_link_libraries(Man INTERFACE ManHeaderOnly)
endif ()

target_compile_features(Man
        PUBLIC cxx_std_23
        PRIVATE cxx_std_23
)

if(MSVC)
	target_compile_options(Man INTERFACE /INCLUDE:mi_version)
endif()

set_target_properties(Man PROPERTIES LINKER_LANGUAGE CXX)
