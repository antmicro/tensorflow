export ZEPHYR_BASE?=${HOME}/zephyr
export ZEPHYR_TOOLCHAIN_VARIANT?=zephyr
export ZEPHYR_SDK_INSTALL_DIR?=/opt/zephyr-sdk
export TF_BASE=$(realpath ../../../../../../..)
export TOOLCHAIN_BASE=${ZEPHYR_SDK_INSTALL_DIR}/riscv32-zephyr-elf/riscv32-zephyr-elf
export TOOLCHAIN_VERSION=8.3.0

prepare_zephyr_litex:
	echo ${TF_BASE}
	cmake -B build -DBOARD="litex_vexriscv" .

build_zephyr_litex: prepare_zephyr_litex
	make -C build

clean_zephyr_litex:
	rm -rf build

