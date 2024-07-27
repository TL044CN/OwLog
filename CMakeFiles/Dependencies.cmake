include(FetchContent)
include(CheckIncludeFileCXX)

set(${PROJECT_NAME}_LIBRARIES "" CACHE INTERNAL "")

function(addExternalDependency)
    set(options "")
    set(oneValueArgs NAME TAG URL)
    set(multiValueArgs MODULES)

    cmake_parse_arguments(PREFIX "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    FetchContent_Declare(
        ${PREFIX_NAME}
        GIT_REPOSITORY ${PREFIX_URL}
        GIT_TAG ${PREFIX_TAG}
    )
    FetchContent_MakeAvailable(${PREFIX_NAME})

    if(NOT "${PREFIX_MODULES}" STREQUAL "")
        foreach(module IN LISTS PREFIX_MODULES)
            list(APPEND ${PROJECT_NAME}_LIBRARIES ${module})
        endforeach()
    else()
        list(APPEND ${PROJECT_NAME}_LIBRARIES ${PREFIX_NAME})
    endif()

    # To make changes visible outside this function
    set(${PROJECT_NAME}_LIBRARIES "${${PROJECT_NAME}_LIBRARIES}" CACHE INTERNAL "")
endfunction()


check_include_file_cxx("format" HAVE_FORMAT)
if("${HAVE_FORMAT}" STREQUAL "")
    addExternalDependency(
        NAME fmt
        URL https://github.com/fmtlib/fmt
        TAG 11.0.2
        MODULES fmt::fmt
    )
endif()

if(NOT ${PROJECT_NAME}_LIBRARIES STREQUAL "")
    message(STATUS "==========|${PROJECT_NAME}|=======>>")
    message(STATUS "External Libraries:")
    foreach(lib IN LISTS ${PROJECT_NAME}_LIBRARIES)
        message(STATUS "  - ${lib}")
    endforeach()
    message(STATUS "<<========|${PROJECT_NAME}|=========")
endif()