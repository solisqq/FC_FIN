#include "esp32-hal-ledc.h"
int channelPinAvailable = 2;

#include "Settings.h"

class Engine {
public:
	int pinID, speed=Settings::Engines::minimum;
	int myChannel;
	//Servo engine;
	Engine() {}
	void Init(int pin) {
		pinID = pin;
		//engine.attach(pinID);
		myChannel = channelPinAvailable;
		ledcSetup(myChannel, 4000, 11);
		ledcAttachPin(pin, myChannel);
		channelPinAvailable++;
		SetSpeed(Settings::Engines::minimum);
	}
	void SetSpeed(int newSpeed) {
		if(newSpeed<Settings::Engines::minimum || newSpeed>Settings::Engines::maximum) return;
		speed=newSpeed;
		ledcWrite(myChannel,speed);
	}
	void Stop() {
		SetSpeed(Settings::Engines::minimum);
	}
};