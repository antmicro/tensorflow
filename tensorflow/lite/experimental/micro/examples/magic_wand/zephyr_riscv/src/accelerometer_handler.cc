/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/experimental/micro/examples/magic_wand/accelerometer_handler.h"
#include <stdio.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>

int begin_index = 0;
struct device *sensor = NULL;
int current_index = 0;
static float x_val[200];
static float y_val[200];
static float z_val[200];

TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter) {
  sensor = device_get_binding("accel-0");
  if(sensor == NULL) {
    error_reporter->Report("Failed to get accelerometer\n");
  }
  error_reporter->Report("Got accelerometer\n");
  return kTfLiteOk;
}

bool ReadAccelerometer(tflite::ErrorReporter* error_reporter, float* input,
                       int length, bool reset_buffer) {
  int rc = sensor_sample_fetch(sensor);
  struct sensor_value accel[3];
  if(rc)
    return false;
  rc = sensor_channel_get(sensor,
                          SENSOR_CHAN_ACCEL_XYZ,
                          accel);
  if (rc < 0) {
    error_reporter->Report("ERROR: Update failed: %d\n", rc);
    return false;
  }
  x_val[current_index] = sensor_value_to_double(&accel[0]);
  y_val[current_index] = sensor_value_to_double(&accel[1]);
  z_val[current_index] = sensor_value_to_double(&accel[2]);

  current_index ++;
  begin_index ++;
  // Reset begin_index to simulate behavior of loop buffer
  if (current_index >= 128) current_index = 0;
  // Only return true after the function was called 100 times, simulating the
  // desired behavior of a real implementation (which does not return data until
  // a sufficient amount is available)
  if (begin_index > 100) {
    int sample = 0;
    for (int i = 0; i < length; i+=3) {
      input[i] = x_val[sample];
      input[i+1] = y_val[sample];
      input[i+2] = z_val[sample];
      sample++;
    }
    return true;
  } else { return false; }
}
