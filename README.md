# Hawk FC
## ESP32 Flight Controller

### Features
- 8kHz gyro loop, 1kHz PID loop
- Written in OOP standard
- Easy in use filter interface
- Flexible debugger
- Complementary filter with auto-adjustable gains
- Compatible with OneShot125 ESCs
- Command system based on trie data structure

### Compatible with:
- ESP32 Sparkfun Thing
- MPU9250/MPU6050 (GY-91/GY-521)
- PWM/OneShot125 ESCs
- CPPM-type RX modules (like FrSky D4R-II) 

### How to
##### 1. Filtering/Signal processing:
If you want to process value which is being continuously updated you have to initialize it as template FilterableValue:

`FilterableValue<float> gyroscope;`

and add any filter to its list:

`gyroscope.addFilter(new SimpleIR<float>(filter_dump_strength));`

then when you want to update gyroscope by new value:

`gyroscope.update(newValue);`

Notice that update method will process new value by all enlisted filters. Order of adding is very important. Filters will run one after another passing processed values beetwen each other so:
```cpp
gyroscope.addFilter(new ButterworthLP<float>(data_rate_freq, cut_off_freq));
gyroscope.addFilter(new SimpleIR<float>(filter_dump_strength));
```
this example will run Butterworth low pass filter on new value and pass processed value to SimpleIR filter so it can processed it further. 

##### 2. Add debug command
Keeping eye on data processing is very important. Debug system allows you to observe values of almost any utility and sensor. 

If you want to show your object data in debug system it need to inherit from DebugInfo interface.  DebugInfo interface has one virtual method which returns a String. This string is going to be showed when object will be debugged. 

Use `cmd.setDebugOnCMD(debugger, ur_object, "command_text");` to add command "command_text". Sending "command_text\n" by serial port will now continuously show String from ur_object getDebug() method. 


##FUN!

![](https://raw.githubusercontent.com/solisqq/FC_FIN/master/img/drone.jpg)