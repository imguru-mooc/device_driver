#!/bin/sh
module=my_minor_num.ko
node=/dev/mydev
minor=0

major=$(awk "\$2==\"mydev\" {print \$1}" /proc/devices)
echo major number is: $major

echo unloading $module
rmmod $module

echo removing the device node at $node with minor number=0

rm $node

