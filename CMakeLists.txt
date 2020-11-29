cmake_minimum_required(VERSION 3.17)
project(5_lab LANGUAGES C VERSION 0.1.0 DESCRIPTION "laboratory work on course OS")

set(CMAKE_C_STANDARD 99)


add_executable(statMain src/statMain.c)
add_executable(dynMain src/dynMain.c)


add_library(calc_integral1 SHARED
        src/calc_integral/realization1.c
        )

add_library(calc_integral2 SHARED
        src/calc_integral/realization2.c
)


set_target_properties(calc_integral1 PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER src/calc_integral/realization.h
)

set_target_properties(calc_integral2 PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER src/calc_integral/realization.h
)

target_link_libraries(calc_integral1 m)
target_link_libraries(calc_integral2 m)


add_library(
        translate_number1 SHARED
        src/translate_number/realization1.c
)

set_target_properties(translate_number1 PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER src/translate_number/realization1.h
)

add_library(
        translate_number2 SHARED
        src/translate_number/realization2.c
)

set_target_properties(translate_number2 PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER src/translate_number/realization1.h
)


target_include_directories(calc_integral1 PRIVATE src/calc_integral)
target_include_directories(calc_integral2 PRIVATE src/calc_integral)

target_include_directories(translate_number1 PRIVATE src/translate_number)
target_include_directories(translate_number2 PRIVATE src/translate_number)

set(custom_targets)

list(APPEND custom_targets calc_integral1)
list(APPEND custom_targets calc_integral2)


if(NOT lab_link_type)
    set(lab_link_type calc_integral1)
endif()

function(invalid_target)
    message("Unknown target selected")
    message("All available targets:")
    foreach(target IN ITEMS ${custom_targets})
        message("    ${target}")
    endforeach()
endfunction()


if (${lab_link_type} IN_LIST custom_targets)
else()
    invalid_target()
    message( FATAL_ERROR "Invalid target selected" )
endif()

message("Link library for statMain will be now " ${lab_link_type})

target_link_libraries(statMain ${lab_link_type})
target_link_libraries(dynMain ${CMAKE_DL_LIBS})
add_dependencies(dynMain translate_number1 translate_number2 calc_integral1 calc_integral2)
