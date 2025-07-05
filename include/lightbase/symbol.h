#pragma once

#include <stdio.h>

#include "lightbase.h"

#ifdef __cplusplus
extern "C" {
#endif

int lb_load_symbols_symdb(const char *in_filename);
int lb_load_symbols(const char *in_filename);
LBAPI char lb_sym_avail();
LBAPI void *lb_sym_find(const char *in_sym);
void lb_sym_free();

#ifdef __cplusplus
}
#endif

#define SCALL(sym, func_proto, ...) \
	((func_proto)lb_sym_find(sym))(__VA_ARGS__)

#define ACALL(addr, func_proto, ...) \
	((func_proto)addr)(__VA_ARGS__)
