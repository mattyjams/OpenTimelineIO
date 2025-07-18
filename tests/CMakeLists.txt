include_directories(${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/deps
    ${PROJECT_SOURCE_DIR}/src/deps/optional-lite/include
	${PROJECT_SOURCE_DIR}/src/tests)

list(APPEND tests_opentime test_opentime)
foreach(test ${tests_opentime})
	add_executable(${test} utils.h utils.cpp ${test}.cpp)
	target_link_libraries(${test} opentime)
	set_target_properties(${test} PROPERTIES FOLDER tests)
	add_test(NAME ${test} 
           COMMAND ${test}
           # Set the pwd to the source directory so we can load the samples
           # like the python tests do
           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

list(APPEND tests_opentimelineio test_clip test_serialization test_serializableCollection test_stack_algo test_timeline test_track test_editAlgorithm test_composition)
foreach(test ${tests_opentimelineio})
    add_executable(${test} utils.h utils.cpp ${test}.cpp)

    target_link_libraries(${test} opentimelineio)
    set_target_properties(${test} PROPERTIES FOLDER tests)
    add_test(NAME ${test} 
           COMMAND ${test}
           # Set the pwd to the source directory so we can load the samples
           # like the python tests do
           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
