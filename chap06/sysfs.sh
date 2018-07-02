#!/bin/bash

PIN=$1
echo $PIN > /sys/class/gpio/export
sleep 1
echo out > /sys/class/gpio/gpio$PIN/direction
sleep 1

echo gpio:$PIN
for i in `seq 1 10`;
do
	echo LED ON
	echo 1 > /sys/class/gpio/gpio$PIN/value
	sleep 0.5
	echo LED OFF
	echo 0 > /sys/class/gpio/gpio$PIN/value
	sleep 0.5
done

echo $PIN > /sys/class/gpio/unexport

