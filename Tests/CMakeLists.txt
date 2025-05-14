cmake_minimum_required(VERSION 3.27)

project(ManTest LANGUAGES CXX)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(GTest CONFIG REQUIRED)
#find_package(benchmark CONFIG REQUIRED)

set(${CMAKE_CURRENT_BINARY_DIR})

function(AddTestProgram TestFile Libraries)
    get_filename_component(FILE_NAME ${TestFile} NAME_WE)
    add_executable(${FILE_NAME} ${TestFile})
    
    get_filename_component(FilePath "${TestFile}" PATH)
    set_target_properties(${FILE_NAME}
            PROPERTIES
            FOLDER "Tests/${FilePath}")

    foreach (Lib ${Libraries})
        target_link_libraries(${FILE_NAME}
                PUBLIC ${Lib})
    endforeach ()
    
    set_target_properties(${FILE_NAME} 
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME_UPPERCASE}_BINARY_DIR})

    add_test(NAME "${FILE_NAME}Test"
            COMMAND ${FILE_NAME}
            WORKING_DIRECTORY ${${PROJECT_NAME_UPPERCASE}_BINARY_DIR})

endfunction(AddTestProgram)
