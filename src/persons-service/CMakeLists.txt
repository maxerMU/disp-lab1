project( persons-service CXX )

add_subdirectory(unit_tests)

add_executable( ${PROJECT_NAME} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/persons.yaml ${CMAKE_CURRENT_BINARY_DIR}/persons.yaml)

target_sources( ${PROJECT_NAME} PRIVATE
    main.cpp

    dto/PersonDTO.h
    dto/PersonDTO.cpp
    dto/PersonPatchDTO.h
    dto/PersonPostDTO.h
    dto/PersonPostDTO.cpp

    gateway/PersonsServerHandler.h
    gateway/PersonsServerHandler.cpp
    gateway/PersonsGateway.h
    gateway/PersonsGateway.cpp

    bl/PersonsFacade.h
    bl/PersonsFacade.cpp

    da/IPersonsRepository.h
    da/PersonsDA.h
    da/PersonsDA.cpp
    da/PostgresPersonsRepository.h
    da/PostgresPersonsRepository.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        base
        NetLib
        jsoncpp_lib
        pqxx
)
