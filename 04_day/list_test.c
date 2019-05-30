#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct input_dev
{
	char name[20];
	struct list_head node;
};

void display( struct list_head *head )
{
	struct list_head *temp;
	struct input_dev *p;
	system("clear");
	printf("[head]");
	for(temp=head->next; temp!=head; temp = temp->next )
	{
		p = list_entry( temp, struct input_dev, node);
		printf("<->[%s]", p->name);
	}
	printf("<->[head]\n");
	getchar();
}

static LIST_HEAD(input_dev_list);

int main()
{
	int i;
	struct input_dev input[4]
		= {{"keyboard"},{"touchscreen"},{"mouse"},{"switch"}};


	display( &input_dev_list );
	for(i=0; i<4; i++)
	{
		list_add_tail( &input[i].node,  &input_dev_list);
		display( &input_dev_list );
	}
	return 0;
}



