struct my_keys_button {
	unsigned int code;
	int gpio;
	int active_low;
};

struct my_keys_platform_data {
	struct my_keys_button *buttons;
	int nbuttons;
};
