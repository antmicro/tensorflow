ifeq ($(TARGET), zephyr_vexriscv)
	export ZEPHYR_TOOLCHAIN_VARIANT?=zephyr
	export TOOLCHAIN_BASE=${ZEPHYR_SDK_INSTALL_DIR}/riscv32-zephyr-elf/riscv32-zephyr-elf
	export TOOLCHAIN_VERSION=8.3.0
hello_world_bin: third_party_downloads
	( \
	  . ${ZEPHYR_BASE}/venv-zephyr/bin/activate; \
	  cmake -B${GENDIR}hello_world/CMake -DBOARD="litex_vexriscv" -Htensorflow/lite/micro/examples/hello_world/zephyr_riscv -DPython_ROOT_DIR=${ZEPHYR_BASE}/venv-zephyr/bin/; \
	  make -C ${GENDIR}hello_world/CMake; \
	)
endif
