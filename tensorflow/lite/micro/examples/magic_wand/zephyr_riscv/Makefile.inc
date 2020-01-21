ifeq ($(TARGET), zephyr_vexriscv)
	export ZEPHYR_BASE?=${GENDIR}../downloads/zephyr
	export ZEPHYR_SDK_INSTALL_DIR?=/opt/zephyr-sdk
	export ZEPHYR_TOOLCHAIN_VARIANT?=zephyr
	export TOOLCHAIN_BASE=${ZEPHYR_SDK_INSTALL_DIR}/riscv32-zephyr-elf/riscv32-zephyr-elf
	export TOOLCHAIN_VERSION=8.3.0
magic_wand_bin:
	echo ${TF_BASE}
	cmake -B${GENDIR}CMake -DBOARD="litex_vexriscv" -Htensorflow/lite/micro/examples/magic_wand/zephyr_riscv
	make -C ${GENDIR}CMake
endif