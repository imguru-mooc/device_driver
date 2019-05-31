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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x8c675af8, __VMLINUX_SYMBOL_STR(mod_delayed_work_on) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0xfd6d346, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0x2f1f8f20, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x9138e27f, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xd61eeee, __VMLINUX_SYMBOL_STR(__bitmap_subset) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1b015d25, __VMLINUX_SYMBOL_STR(bitmap_parselist) },
	{ 0xf6f5580, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xfa5bcf35, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x7f02188f, __VMLINUX_SYMBOL_STR(__msecs_to_jiffies) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x149259a, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0x3e9d3734, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0xc5844d6f, __VMLINUX_SYMBOL_STR(of_property_read_variable_u32_array) },
	{ 0x75e391b6, __VMLINUX_SYMBOL_STR(irq_of_parse_and_map) },
	{ 0xc2a42f9b, __VMLINUX_SYMBOL_STR(of_property_read_string) },
	{ 0xc9656096, __VMLINUX_SYMBOL_STR(of_get_property) },
	{ 0x204488e8, __VMLINUX_SYMBOL_STR(of_get_next_available_child) },
	{ 0x64b35483, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0xfc33de0a, __VMLINUX_SYMBOL_STR(gpiod_set_debounce) },
	{ 0xf95913f2, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x19d3b7d8, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x1996b644, __VMLINUX_SYMBOL_STR(devm_request_any_context_irq) },
	{ 0x247c2a6c, __VMLINUX_SYMBOL_STR(devm_add_action) },
	{ 0x45a9aec7, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x8fdf772a, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x3d9835a6, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x39821e70, __VMLINUX_SYMBOL_STR(devm_gpio_request_one) },
	{ 0xf090eadf, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xb299cc9b, __VMLINUX_SYMBOL_STR(devm_input_allocate_device) },
	{ 0x40c57909, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0x9a18d7ff, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xa0fcd3fc, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xdcd5774d, __VMLINUX_SYMBOL_STR(gpiod_get_value_cansleep) },
	{ 0x3f5c6471, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xa0744ea9, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0xb1ea493e, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cgpio-keys");
MODULE_ALIAS("of:N*T*Cgpio-keysC*");

MODULE_INFO(srcversion, "26B72C3C036C43937357AF3");
