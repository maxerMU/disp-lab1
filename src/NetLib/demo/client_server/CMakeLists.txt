project( net_lib_demo_client_server CXX )

add_executable( ${PROJECT_NAME} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )

target_sources( ${PROJECT_NAME} PRIVATE
  main.cpp
  inc/dummy_client_server_handler.h
  inc/DummyClientServerRoute.h
  src/dummy_client_server_handler.cpp
  src/DummyClientServerRoute.cpp
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