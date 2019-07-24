
Accel::Accel() {}
String Accel::getClassName() { return "Accel"; }
String Accel::getDebugMsg(bool raw) { return Sensor3D::toString(); }

Vector<float> Accel::getEulers(Point3D<float> backup)
{
	Vector<float> currAccel;
	currAccel.x = (atan2(-values.y.value, values.z.value) * 180.0) / Settings::Math::constPI;
	currAccel.y = (atan2(values.x.value, sqrt(values.y.value * values.y.value + values.z.value * values.z.value)) * 180.0) / M_PI;
	currAccel.z = values.z.value;
	currAccel *= (-1.0);
	if (currAccel.x != currAccel.x)
		currAccel.x = backup.x.value;
	if (currAccel.y != currAccel.y)
		currAccel.y = backup.y.value;
	return currAccel;
}
void Accel::updateByMPU(MPU9250 *mpu)
{
	Vector<int16_t> accelData;
	mpu->readRawAccel(&accelData);
	Sensor3D::update(accelData);
}
