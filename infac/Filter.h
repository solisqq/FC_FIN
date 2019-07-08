template <class Type>
class Filter {
	Type *val;
	virtual void Config(Type *value, float param1=-1.0f, float param2=-1.0f) = 0;
	virtual void Update() = 0;
};