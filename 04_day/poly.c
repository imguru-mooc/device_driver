#include <stdio.h>
class driver
{
	public:
		virtual void probe()
		{
			printf("driver::probe()\n");
		}
};
class platform_driver : public driver
{
	public:
		virtual void probe()
		{
			printf("platform_driver::probe()\n");
		}
};
class usb_driver : public driver
{
	public:
		virtual void probe()
		{
			printf("usb_driver::probe()\n");
		}
};
int main()
{
	driver *my_driver[2];
	my_driver[0] = new platform_driver; 
	my_driver[1] = new usb_driver; 
	for(int i=0; i<2; i++ )
		my_driver[i]->probe();
	return 0;
}
