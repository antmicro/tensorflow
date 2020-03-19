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

#include "tensorflow/lite/micro/examples/magic_wand/accelerometer_handler.h"
#include <stdio.h>
#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <drivers/sensor.h>

#define BUFLEN 300
int begin_index = 0;
struct device *sensor = NULL;
int current_index = 0;

float bufx[BUFLEN] = {0.0f};
float bufy[BUFLEN] = {0.0f};
float bufz[BUFLEN] = {0.0f};

bool initial = true;

TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter) {
  /*sensor = device_get_binding(DT_INST_0_ADI_ADXL345_LABEL);
  if(sensor == NULL) {
    error_reporter->Report("Failed to get accelerometer, label: %s\n", DT_INST_0_ADI_ADXL345_LABEL);
  } else {
    error_reporter->Report("Got accelerometer, label: %s\n", DT_INST_0_ADI_ADXL345_LABEL);
  }*/
  return kTfLiteOk;
}

bool ReadAccelerometer(tflite::ErrorReporter* error_reporter, float* input,
                       int length) {
  int rc;
  struct sensor_value accel[3];
  int samples_count;

  //if(reset_buffer) {
  //  memset(bufx, 0, BUFLEN*sizeof(float));
  //  memset(bufy, 0, BUFLEN*sizeof(float));
  //  memset(bufz, 0, BUFLEN*sizeof(float));
  //  begin_index = 0;
  //  initial = true;
  //}

  //rc = sensor_sample_fetch(sensor);
  //if(rc < 0) {
  //  error_reporter -> Report("Fetch failed\n");
  //  return false;
  //}
  // skip if there is no data
  //if(!rc) {
  //  return false;
  //}

  //samples_count = rc;
  samples_count = 32;
  error_reporter->Report("Samples count: %d\n", samples_count);
  for(int i = 0; i < samples_count; i++) {
    //rc = sensor_channel_get(sensor,
    //                        SENSOR_CHAN_ACCEL_XYZ,
    //                        accel);
    //if (rc < 0) {
    //  error_reporter->Report("ERROR: Update failed: %d\n", rc);
    //  return false;
    //}
    accel[0].val1 = 255;
    accel[0].val2 = 0;
    accel[1].val1 = 255;
    accel[1].val2 = 0;
    accel[2].val1 = 255;
    accel[2].val2 = 0;
    error_reporter->Report("x: %d y: %d z: %d, index: %d", accel[0].val1, accel[1].val1, accel[2].val1, current_index);
    bufx[begin_index] = (float)sensor_value_to_double(&accel[0]);
    bufy[begin_index] = (float)sensor_value_to_double(&accel[1]);
    bufz[begin_index] = (float)sensor_value_to_double(&accel[2]);
    begin_index++;
    if (begin_index >= BUFLEN) begin_index = 0;

  }

  if(initial && begin_index >= 100) {
    initial = false;
  }

  if (initial) {
    return false;
  }

  int sample = 0;
  for (int i = 0; i < (length - 3); i+=3) {
    int ring_index = begin_index + sample - length/3;
    if(ring_index < 0) {
      ring_index += BUFLEN;
    }
    input[i] =   bufx[ring_index];
    input[i+1] = bufy[ring_index];
    input[i+2] = bufz[ring_index];
    sample++;
  }
  return true;
}
