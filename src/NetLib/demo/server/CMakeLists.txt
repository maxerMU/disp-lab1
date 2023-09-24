project( net_lib_demo_server CXX )

add_executable( ${PROJECT_NAME} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )

target_sources( ${PROJECT_NAME} PRIVATE
  main.cpp
  inc/dummy_server_handler.h
  inc/dummy_server_handler_creator.h
  src/dummy_server_handler.cpp
  src/dummy_server_handler_creator.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc/
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        base
        NetLib
)
