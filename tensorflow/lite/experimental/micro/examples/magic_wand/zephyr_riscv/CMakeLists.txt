cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(tf_lite_magic_wand)

set(TF_MICRO_DIR $ENV{TF_BASE}/tensorflow/lite/experimental/micro)
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
                src/accelerometer_handler.cc
                src/accelerometer_handler.h
                src/constants.cc
                ../output_handler.cc
                ../output_handler.h
                ../gesture_predictor.cc
                ../constants.h
                ../gesture_predictor.h
                ../main.cc
                ../main_functions.cc
                ../magic_wand_model_data.cc
                ../main_functions.h
                ../magic_wand_model_data.h
                ${MICRO_SOURCES}
                ${MICRO_KERNELS_SOURCES}
                ${MICRO_MEMORY_SOURCES}
                ${MICRO_HEADERS}
                ${MICRO_KERNEL_HEADERS}
                ${MICRO_MEMORY_HEADERS}
                $ENV{TF_BASE}/tensorflow/lite/c/c_api_internal.c
                $ENV{TF_BASE}/tensorflow/lite/core/api/error_reporter.cc
                $ENV{TF_BASE}/tensorflow/lite/core/api/flatbuffer_conversions.cc
                $ENV{TF_BASE}/tensorflow/lite/core/api/op_resolver.cc
                $ENV{TF_BASE}/tensorflow/lite/core/api/tensor_utils.cc
                $ENV{TF_BASE}/tensorflow/lite/kernels/internal/quantization_util.cc
                $ENV{TF_BASE}/tensorflow/lite/kernels/kernel_util.cc

                )

target_include_directories(app PRIVATE
                $ENV{TF_BASE}
                $ENV{TF_BASE}/tensorflow/lite/experimental/micro/tools/make/downloads/gemmlowp
                $ENV{TF_BASE}/tensorflow/lite/experimental/micro/tools/make/downloads/flatbuffers/include
                $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}
                $ENV{TOOLCHAIN_BASE}/include
                $ENV{TOOLCHAIN_BASE}/include/c++/$ENV{TOOLCHAIN_VERSION}/riscv32-zephyr-elf/rv32i/ilp32
                )

add_definitions(-DNDEBUG -DTF_LITE_STATIC_MEMORY)
