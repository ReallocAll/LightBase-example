#pragma once

#include "lightbase.h"

#ifdef __cplusplus
extern "C" {
#endif

LBAPI void *lb_ahook_install(void *in_target, void *in_hook, void **out_call, char in_priority);
LBAPI void *lb_shook_install(const char *in_sym, void *in_hook, void **out_call, char in_priority);
LBAPI void *lb_ohook_install(const char *in_fmt, int in_offset, void *in_hook, void **out_call, char in_priority);
LBAPI void lb_hook_uninstall(const char *in_sym, void *in_target, void *in_call);
void lb_hook_uninstall_all();
int lb_hook_install_all();

#ifdef __cplusplus
}
#endif

struct lb_hook {
	void *addr;
	void *(*install)();
	void *(*installex)(char in_priority);
	void (*uninstall)();
	void *call;
	void *hook;
};

#define AHOOK(name, ret_type, i_addr, ...)                                                        \
	void *lb_hook_##name##_install();                                                             \
	void *lb_hook_##name##_installex(unsigned char in_priority);                                  \
	void lb_hook_##name##_uninstall();                                                            \
	ret_type lb_hook_##name##_hook(__VA_ARGS__);                                                  \
                                                                                                  \
	struct lb_hook_##name {                                                                       \
		void *addr;                                                                               \
		void *(*install)();                                                                       \
		void *(*installex)(unsigned char in_priority);                                            \
		void (*uninstall)();                                                                      \
		ret_type (*call)(__VA_ARGS__);                                                            \
		ret_type (*hook)(__VA_ARGS__);                                                            \
	} name = { NULL,                                                                              \
			   lb_hook_##name##_install,                                                          \
			   lb_hook_##name##_installex,                                                        \
			   lb_hook_##name##_uninstall,                                                        \
			   (ret_type(*)(__VA_ARGS__))NULL,                                                    \
			   lb_hook_##name##_hook };                                                           \
                                                                                                  \
	void *lb_hook_##name##_install()                                                              \
	{                                                                                             \
		return name.addr = lb_ahook_install(i_addr, name.hook, (void **)&name.call, 127);         \
	}                                                                                             \
	void *lb_hook_##name##_installex(unsigned char in_priority)                                   \
	{                                                                                             \
		return name.addr = lb_ahook_install(i_addr, name.hook, (void **)&name.call, in_priority); \
	}                                                                                             \
	void lb_hook_##name##_uninstall()                                                             \
	{                                                                                             \
		lb_hook_uninstall(#i_addr, name.addr, (void *)name.call);                                 \
	}                                                                                             \
	ret_type lb_hook_##name##_hook(__VA_ARGS__)

#define SHOOK(name, ret_type, sym, ...)                                                        \
	void *lb_hook_##name##_install();                                                          \
	void *lb_hook_##name##_installex(unsigned char in_priority);                               \
	void lb_hook_##name##_uninstall();                                                         \
	ret_type lb_hook_##name##_hook(__VA_ARGS__);                                               \
                                                                                               \
	struct lb_hook_##name {                                                                    \
		void *addr;                                                                            \
		void *(*install)();                                                                    \
		void *(*installex)(unsigned char in_priority);                                         \
		void (*uninstall)();                                                                   \
		ret_type (*call)(__VA_ARGS__);                                                         \
		ret_type (*hook)(__VA_ARGS__);                                                         \
	} name = { NULL,                                                                           \
			   lb_hook_##name##_install,                                                       \
			   lb_hook_##name##_installex,                                                     \
			   lb_hook_##name##_uninstall,                                                     \
			   (ret_type(*)(__VA_ARGS__))NULL,                                                 \
			   lb_hook_##name##_hook };                                                        \
                                                                                               \
	void *lb_hook_##name##_install()                                                           \
	{                                                                                          \
		return name.addr = lb_shook_install(sym, name.hook, (void **)&name.call, 127);         \
	}                                                                                          \
	void *lb_hook_##name##_installex(unsigned char in_priority)                                \
	{                                                                                          \
		return name.addr = lb_shook_install(sym, name.hook, (void **)&name.call, in_priority); \
	}                                                                                          \
	void lb_hook_##name##_uninstall()                                                          \
	{                                                                                          \
		lb_hook_uninstall(sym, name.addr, (void *)name.call);                                  \
	}                                                                                          \
	ret_type lb_hook_##name##_hook(__VA_ARGS__)

#define OHOOK(name, ret_type, fmt, offset, ...)                                                        \
	void *lb_hook_##name##_install();                                                                  \
	void *lb_hook_##name##_installex(unsigned char in_priority);                                       \
	void lb_hook_##name##_uninstall();                                                                 \
	ret_type lb_hook_##name##_hook(__VA_ARGS__);                                                       \
                                                                                                       \
	struct lb_hook_##name {                                                                            \
		void *addr;                                                                                    \
		void *(*install)();                                                                            \
		void *(*installex)(unsigned char in_priority);                                                 \
		void (*uninstall)();                                                                           \
		ret_type (*call)(__VA_ARGS__);                                                                 \
		ret_type (*hook)(__VA_ARGS__);                                                                 \
	} name = { NULL,                                                                                   \
			   lb_hook_##name##_install,                                                               \
			   lb_hook_##name##_installex,                                                             \
			   lb_hook_##name##_uninstall,                                                             \
			   (ret_type(*)(__VA_ARGS__))NULL,                                                         \
			   lb_hook_##name##_hook };                                                                \
                                                                                                       \
	void *lb_hook_##name##_install()                                                                   \
	{                                                                                                  \
		return name.addr = lb_ohook_install(fmt, offset, name.hook, (void **)&name.call, 127);         \
	}                                                                                                  \
	void *lb_hook_##name##_installex(unsigned char in_priority)                                        \
	{                                                                                                  \
		return name.addr = lb_ohook_install(fmt, offset, name.hook, (void **)&name.call, in_priority); \
	}                                                                                                  \
	void lb_hook_##name##_uninstall()                                                                  \
	{                                                                                                  \
		lb_hook_uninstall(fmt, name.addr, (void *)name.call);                                          \
	}                                                                                                  \
	ret_type lb_hook_##name##_hook(__VA_ARGS__)

#define SCALL(sym, func_proto, ...) \
	((func_proto)lb_sym_find(sym))(__VA_ARGS__)

#define ACALL(addr, func_proto, ...) \
	((func_proto)addr)(__VA_ARGS__)

#define OFIND(name, opt_code, offset) \
	name = lb_opt_search(opt_code, offset);

#define ODFIND(name, opt_code) \
	OFIND(name, opt_code, 0)

// #define VCALL(lb_hook, ...) (lb_hook.call_status->is_called ? (void)0 : lb_hook.call(__VA_ARGS__), lb_hook.call_status->is_called = 1)
// #define DCALL(lb_hook, ...) (lb_hook.call_status->is_called ? lb_hook.call_status->ret_value : (lb_hook.call_status->is_called = 1, lb_hook.call_status->ret_value = (void *)(unsigned long long)lb_hook.call(__VA_ARGS__)))
