#pragma once

typedef enum { OK, UNKNOWN } vm_result_type;

typedef struct {
  vm_result_type res;
  char *msg;
} vm_result;

void on_error(vm_result *res) {}
