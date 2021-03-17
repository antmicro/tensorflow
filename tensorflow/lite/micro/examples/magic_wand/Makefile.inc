EXAMPLE_NAME:=magic_wand

ifeq ($(TARGET), sparkfun_edge)
  INCLUDES += \
    -I$(APOLLO3_SDK)/$(SF_BSPS_DEST)/common/third_party/lis2dh12/

  THIRD_PARTY_CC_SRCS += \
    $(APOLLO3_SDK)/$(SF_BSPS_DEST)/common/third_party/lis2dh12/lis2dh12_platform_apollo3.c \
    $(APOLLO3_SDK)/boards_sfe/common/third_party/lis2dh12/lis2dh12_reg.c

  THIRD_PARTY_CC_HDRS += \
    $(APOLLO3_SDK)/boards_sfe/common/third_party/lis2dh12/lis2dh12_platform_apollo3.h \
    $(APOLLO3_SDK)/boards_sfe/common/third_party/lis2dh12/lis2dh12_reg.h
endif

ACCELEROMETER_HANDLER_TEST_SRCS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/accelerometer_handler.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/accelerometer_handler_test.cc

ACCELEROMETER_HANDLER_TEST_HDRS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/accelerometer_handler.h

OUTPUT_HANDLER_TEST_SRCS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler_test.cc

OUTPUT_HANDLER_TEST_HDRS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.h

GESTURE_PREDICTOR_TEST_SRCS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/gesture_predictor.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/gesture_predictor_test.cc

GESTURE_PREDICTOR_TEST_HDRS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/constants.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/gesture_predictor.h \

magic_wand_TEST_SRCS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/$(EXAMPLE_NAME)_test.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/$(EXAMPLE_NAME)_model_data.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/slope_micro_features_data.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/ring_micro_features_data.cc

magic_wand_TEST_HDRS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/$(EXAMPLE_NAME)_model_data.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/slope_micro_features_data.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/ring_micro_features_data.h

magic_wand_SRCS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/main.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/main_functions.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/$(EXAMPLE_NAME)_model_data.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/accelerometer_handler.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/gesture_predictor.cc \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.cc

magic_wand_HDRS := \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/main_functions.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/constants.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/$(EXAMPLE_NAME)_model_data.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/accelerometer_handler.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/gesture_predictor.h \
tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/output_handler.h

#Find any platform - specific rules for this example.
include $(wildcard tensorflow/lite/micro/examples/$(EXAMPLE_NAME)/*/Makefile.inc)

# Tests the accelerometer handler
$(eval $(call microlite_test,gesture_accelerometer_handler_test,\
$(ACCELEROMETER_HANDLER_TEST_SRCS),$(ACCELEROMETER_HANDLER_TEST_HDRS)))

# Tests the output handler
$(eval $(call microlite_test,gesture_output_handler_test,\
$(OUTPUT_HANDLER_TEST_SRCS),$(OUTPUT_HANDLER_TEST_HDRS)))

# Tests the gesture predictor
$(eval $(call microlite_test,gesture_predictor_test,\
$(GESTURE_PREDICTOR_TEST_SRCS),$(GESTURE_PREDICTOR_TEST_HDRS)))

# Tests loading and running the gesture recognition model
$(eval $(call microlite_test,$(EXAMPLE_NAME)_test,\
$($(EXAMPLE_NAME)_TEST_SRCS),$($(EXAMPLE_NAME)_TEST_HDRS)))

# Builds a standalone binary
$(eval $(call microlite_test,$(EXAMPLE_NAME),\
$($(EXAMPLE_NAME)_SRCS),$($(EXAMPLE_NAME)_HDRS)))

list_$(EXAMPLE_NAME)_example_sources:
	@echo $(magic_wand_SRCS)

list_$(EXAMPLE_NAME)_example_headers:
	@echo $(magic_wand_HDRS)
