file(GLOB ir_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(IR ${ir_SRC})

