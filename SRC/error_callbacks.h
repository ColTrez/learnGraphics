#pragma once
#include <cstdio>

static void error_callback(int error, const char* description){

    fprintf(stderr, "Error:%s\n", description);

    throw("glfw error");
}
