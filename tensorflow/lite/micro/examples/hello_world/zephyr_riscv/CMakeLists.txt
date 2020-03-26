cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(tf_lite_helloworld)

set(TF_MICRO_DIR ${PROJECT_SOURCE_DIR}/../../../)
file(GLOB MICRO_SOURCES ${TF_MICRO_DIR}/*cc)
file(GLOB MICRO_HEADERS ${TF_MICRO_DIR}/*.h)
file(GLOB MICRO_TESTS_SOURCES ${TF_MICRO_DIR}/*test.cc)
file(GLOB MICRO_KERNELS_SOURCES ${TF_MICRO_DIR}/kernels/*cc)
file(GLOB MICRO_KERNELS_HEADERS ${TF_MICRO_DIR}/kernels/*.h)
file(GLOB MICRO_TESTS_KERNELS_SOURCES ${TF_MICRO_DIR}/kernels/*test.cc)
file(GLOB MICRO_MEMORY_SOURCES ${TF_MICRO_DIR}/memory_planner/*cc)
file(GLOB MICRO_MEMORY_HEADERS ${TF_MICRO_DIR}/memory_planner/*.h)
file(GLOB MICRO_TESTS_MEMORY_SOURCES ${TF_MICRO_DIR}/memory_planner/*test.cc)

# remove test sources from app sources
list(REMOVE_ITEM MICRO_SOURCES ${MICRO_TESTS_SOURCES})
list(REMOVE_ITEM MICRO_KERNELS_SOURCES ${MICRO_TESTS_KERNELS_SOURCES})
list(REMOVE_ITEM MICRO_MEMORY_SOURCES ${MICRO_TESTS_MEMORY_SOURCES})

# -fno-threadsafe-statics -- disables the mutex around initialization of local static variables
target_compile_options(app PRIVATE "-fno-threadsafe-statics")

target_sources(app PRIVATE
                src/assert.cc
                ../main.cc
                ../main_functions.cc
                ../sine_model_data.cc
                ../output_handler.cc
                ../constants.cc
                ${MICRO_SOURCES}
                ${MICRO_KERNELS_SOURCES}
                ${MICRO_MEMORY_SOURCES}
                ${MICRO_HEADERS}
                ${MICRO_KERNEL_HEADERS}
                ${MICRO_MEMORY_HEADERS}
                ${TF_MICRO_DIR}/../c/common.c
                ${TF_MICRO_DIR}/../core/api/error_reporter.cc
                ${TF_MICRO_DIR}/../core/api/flatbuffer_conversions.cc
                ${TF_MICRO_DIR}/../core/api/op_resolver.cc
                ${TF_MICRO_DIR}/../core/api/tensor_utils.cc
                ${TF_MICRO_DIR}/../kernels/internal/quantization_util.cc
                ${TF_MICRO_DIR}/../kernels/kernel_util.cc
                )

target_include_directories(app PRIVATE
                ${TF_MICRO_DIR}/../../../
                ${TF_MICRO_DIR}/tools/make/downloads/gemmlowp
                ${TF_MICRO_DIR}/tools/make/downloads/flatbuffers/include
                $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}
                $ENV{TOOLCHAIN_BASE}/include
                $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}/riscv32-zephyr-elf/rv32i/ilp32
                )

add_definitions(-DNDEBUG -DTF_LITE_STATIC_MEMORY)
