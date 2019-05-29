#include <wiringPi.h>
#include <stdio.h>

#define SW  4       /* GPIO23 */
#define LED 27      /* GPIO16 */

int switchControl()
{

	pinMode(SW,  INPUT);
	pinMode(LED, OUTPUT);

	while (1) {
		if(digitalRead(SW) == LOW) {
			digitalWrite(LED, HIGH);
			delay(1000);
			digitalWrite(LED, LOW);
			delay(1000);
		}
	};
	return 0 ;
}

int main(int argc, char** argv)
{
	wiringPiSetup();

	switchControl();

	return 0 ;
}

