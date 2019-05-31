#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd29ace7d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x871bbb3f, __VMLINUX_SYMBOL_STR(kernel_kobj) },
	{ 0xe259fa6e, __VMLINUX_SYMBOL_STR(kset_unregister) },
	{ 0xebb18e89, __VMLINUX_SYMBOL_STR(kset_create_and_add) },
	{ 0xfd6d346, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd94c17ba, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0x5c547620, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xb41a4d7c, __VMLINUX_SYMBOL_STR(kobject_init_and_add) },
	{ 0xf6f5580, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x373db350, __VMLINUX_SYMBOL_STR(kstrtoint) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FD4E1CF75F01E1CA67DDCEB");
