#pragma once

#include <ibvm/error.h>
#include <stdint.h>

// Type to be used as value type (stack)
typedef struct {
  union {
    uint32_t u;
    int32_t i;
    float f;
  };
} vm_val_type;

// Type to be used as reference type (heap)
typedef struct {
  uint8_t header;
  vm_val_type data;
} vm_ref_type;

vm_val_type convert_uint_to_float(vm_val_type v) {
  v.f = (float)v.u;
  return v;
}

vm_val_type convert_int_to_float(vm_val_type v) {
  v.f = (float)v.i;
  return v;
}

vm_val_type convert_float_to_uint(vm_val_type v) {
  v.u = (uint32_t)v.f;
  return v;
}

vm_val_type convert_float_to_int(vm_val_type v) {
  v.i = (int32_t)v.f;
  return v;
}
