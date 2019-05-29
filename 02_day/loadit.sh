#!/bin/sh

module=my_minor_num.ko
node=/dev/mydev
minor=0

echo loading $module
insmod $module

major=$(awk "\$2==\"mydev\" {print \$1}" /proc/devices)
echo major number is: $major
echo creating the device node at $node with minor number=0
mknod $node c $major $minor

