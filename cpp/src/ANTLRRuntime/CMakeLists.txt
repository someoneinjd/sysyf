file(GLOB antlrruntime_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/atn/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/dfa/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/misc/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/support/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/tree/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/tree/pattern/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/tree/xpath/*.cpp"
)

add_library(ANTLRRuntime ${antlrruntime_SRC})
