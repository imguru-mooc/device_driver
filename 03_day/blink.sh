#!/bin/sh

echo 16 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio16/direction

while true
do
	echo 1 > /sys/class/gpio/gpio16/value
	sleep 1
	echo 0 > /sys/class/gpio/gpio16/value
	sleep 1
done
