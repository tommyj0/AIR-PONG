cmake_minimum_required(VERSION 3.15)

project(PONG LANGUAGES C)

# set(CMAKE_C_COMPILER "riscv64-unknown-elf-gcc")
# set(CMAKE_ASM_COMPILER "riscv64-unknown-elf-gcc")

# --------------------------------------------------------------------
# Configuration
# --------------------------------------------------------------------
set(CMAKE_C_STANDARD 99)

# Build type: Debug / Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# --------------------------------------------------------------------
# Directories
# --------------------------------------------------------------------
# Source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)
set(CSFML_DIR ${CMAKE_SOURCE_DIR}/ext/CSFML)

# Collect all .c or .cpp files automatically
file(GLOB_RECURSE SOURCES 
    # ${CMAKE_SOURCE_DIR}/utils/crt0.s
    ${SRC_DIR}/*.c 
    )

include_directories(
    ${INCLUDE_DIR}
    ${CSFML_DIR}/include
    )

# --------------------------------------------------------------------
# Linker Flags
# --------------------------------------------------------------------
# Add custom linker flags if needed

## set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lcsfml-graphics")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lcsfml-window")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lcsfml-system")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lcsfml-audio")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L .")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L ${CSFML_DIR}/build/lib")
  

# --------------------------------------------------------------------
# External Libraries
# --------------------------------------------------------------------
link_directories(${CSFML_DIR}/build/lib)

# Example manual linking:
set(CMAKE_PREFIX_PATH "${CSFML_DIR}/build")
set(LIBS m csfml-graphics csfml-window csfml-system csfml-audio)

# --------------------------------------------------------------------
# Targets
# --------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries (add or remove as needed)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${LIBS}
)

# Optional: set compile options per target
target_compile_options(${PROJECT_NAME}
    PRIVATE
      -g 
      #-DNORMALUNIX -DLINUX # -DUSEASM 
)

# Optional: specify include directories per target
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    BUILD_RPATH "${CSFML_DIR}/build/lib"
    INSTALL_RPATH "${CSFML_DIR}/build/lib"
)

# --------------------------------------------------------------------
# Installation (optional)
# --------------------------------------------------------------------
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
# install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION include)