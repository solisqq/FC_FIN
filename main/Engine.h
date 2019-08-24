#include "esp32-hal-ledc.h"
int channelPinAvailable = 2;

#include "Settings.h"
#include "../infac/AllowPrint.h"
class Engine : public AllowPrint {
public:
	int pinID, speed=Settings::Engines::minimum;
	int myChannel;
	Engine() {}
	void Init(int pin) {
		pinID = pin;
		myChannel = channelPinAvailable;
		ledcSetup(myChannel, 400, 11);
		ledcAttachPin(pin, myChannel);
		channelPinAvailable++;
		SetSpeed(Settings::Engines::minimum);
	}
	void SetSpeed(int newSpeed) {
		if(newSpeed<Settings::Engines::minimum) 
			speed = Settings::Engines::minimum;
		else if(newSpeed>Settings::Engines::maximum)
			speed = Settings::Engines::maximum;
		else
			speed=newSpeed;
			
		ledcWrite(myChannel,speed);
	}
	void Stop() {
		SetSpeed(Settings::Engines::minimum);
	}
	virtual String toString() {
		return static_cast<String>(speed);
	}
};