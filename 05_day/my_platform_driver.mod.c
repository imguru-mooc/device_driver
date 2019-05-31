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
	{ 0x530d79a8, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xf9422afd, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x137c3884, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0xf95913f2, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x1dc6d519, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x64b35483, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0x459a97d6, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0x519468b1, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa0fcd3fc, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xcf08282d, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0x3d9835a6, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cmy-keys");
MODULE_ALIAS("of:N*T*Cmy-keysC*");

MODULE_INFO(srcversion, "47DB3C1C01627C26E89EEDB");
