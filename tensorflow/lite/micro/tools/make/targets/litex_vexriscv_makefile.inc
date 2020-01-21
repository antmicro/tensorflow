ifeq ($(TARGET), zephyr_vexriscv)
  export ZEPHYR_SDK_INSTALL_DIR?=/opt/zephyr-sdk
  export PATH := $(ZEPHYR_SDK_INSTALL_DIR)/riscv32-zephyr-elf/bin/:$(PATH)
  TARGET_TOOLCHAIN_PREFIX=riscv32-zephyr-elf-
  TOOLCHAIN_VERSION=8.3.0

  $(eval $(call add_third_party_download,$(ZEPHYR_URL),$(ZEPHYR_MD5), zephyr, setup_zephyr,))

  PLATFORM_FLAGS = \
    -D__ZEPHYR__ \
    -DNDEBUG \
    -DTF_LITE_STATIC_MEMORY \
    -fno-threadsafe-statics

  CXXFLAGS += $(PLATFORM_FLAGS)
  CCFLAGS += $(PLATFORM_FLAGS)
endif