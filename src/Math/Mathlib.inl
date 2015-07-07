
inline f32 engine::Math::ToDeg(f32 radian){
	return radian * (180.f / Math::Pi);
}

inline f32 engine::Math::ToRad(f32 degree){
	return degree * (Math::Pi / 180.f);
}

inline f32 engine::Math::Sin(f32 value){
	// clamp -PI..PI
	if(value < -Math::Pi)
		value += 6.28318531f;
	else if(value > Math::Pi)
		value -= 6.28318531f;
	
	f32 sin;
			
	// approximation de sin par une parabole (4/PI * x - 4/PI² * x²)	(abs(x) pour le signe)
	sin = 1.27323954f * value - 0.405284735f * value * std::abs(value);
	
	//extra precison grace a la squared parabola
	sin = 0.225f * ( sin * std::abs(sin) - sin) + sin;
	
	return sin; 
}

inline f32 engine::Math::Cos(f32 value){ 
	// cos(x) = sin(x + PI/2)
	value += Math::HalfPi;
	// clamp -PI..PI
	if(value < -Math::Pi)
		value += 6.28318531f;
	else if(value > Math::Pi)
		value -= 6.28318531f;
	
	f32 cos;
			
	// approximation de sin par une parabole (4/PI * x - 4/PI² * x²)	(abs(x) pour le signe)
	cos = 1.27323954f * value - 0.405284735f * value * std::abs(value);
	
	//extra precison grace a la squared parabola
	cos = 0.225f * ( cos * std::abs(cos) - cos) + cos;
	
	return cos; 
}

inline f32 engine::Math::Tan(f32 value){ 
	return (f32)std::tan(value);
}

// Valeur entre 0..1
inline f32 engine::Math::ACos(f32 value){ 
	f32 root = Math::Sqrt(Math::Abs((1.f)-value));
    f32 ret = -0.0012624911f;
    ret *= value;
    ret += 0.0066700901f;
    ret *= value;
    ret -= 0.0170881256f;
    ret *= value;
    ret += 0.0308918810f;
    ret *= value;
    ret -= 0.0501743046f;
    ret *= value;
    ret += 0.0889789874f;
    ret *= value;
    ret -= 0.2145988016f;
    ret *= value;
    ret += 1.5707963050f;
    ret *= root;
    return ret;
}

// Valeur entre 0..1
inline f32 engine::Math::ASin(f32 value){
	f32 root = Math::Sqrt(Math::Abs((1.f)-value));
    f32 ret = -0.0012624911f;
    ret *= value;
    ret += 0.0066700901f;
    ret *= value;
    ret -= 0.0170881256f;
    ret *= value;
    ret += 0.0308918810f;
    ret *= value;
    ret -= 0.0501743046f;
    ret *= value;
    ret += 0.0889789874f;
    ret *= value;
    ret -= 0.2145988016f;
    ret *= value;
    ret += 1.5707963050f;
    ret = 1.570796325f - root*ret;
    return ret;
}

// Valeur entre -1..1
inline f32 engine::Math::ATan(f32 value){
	f32 sqr = value*value;
    f32 ret = 0.0028662257f;
    ret *= sqr;
    ret -= 0.0161657367f;
    ret *= sqr;
    ret += 0.0429096138f;
    ret *= sqr;
    ret -= 0.0752896400f;
    ret *= sqr;
    ret += 0.1065626393f;
    ret *= sqr;
    ret -= 0.1420889944f;
    ret *= sqr;
    ret += 0.1999355085f;
    ret *= sqr;
    ret -= 0.3333314528f;
    ret *= sqr;
    ret += 1.f;
    ret *= value;
    return ret;
}

inline f32 engine::Math::ATan2(f32 Y, f32 X){ 
	return (f32)std::atan2(Y,X);
}
		
inline f32 engine::Math::Sqrt(f32 value){ 
	return value * Math::InvSqrt(value);
}

inline f32 engine::Math::InvSqrt(f32 x){ 
	// Chris Lomont's InvSqrt
	f32 xhalf = 0.5f * x;
	int i = *(int*)&x;					//get bits for f32ing value
	i = 0x5f375a86 - (i>>1);	//initial guess
	x = *(f32*)&i;						//back to f32
	x = x * (1.5f - xhalf * x * x);	//Newton step, repeat increases accuracy
	x = x * (1.5f - xhalf * x * x);	//Newton step, repeat increases accuracy
	x = x * (1.5f - xhalf * x * x);	//Newton step, repeat increases accuracy
	return x;
}
		
inline f32 engine::Math::Ceil(f32 value){ 
	return (f32)std::ceil(value);
}

inline f32 engine::Math::Floor(f32 value){ 
	return (f32)std::floor(value);
}
		
inline f32 engine::Math::Abs(f32 value){ 
	return (f32)std::fabs((f32)value);	
}
		
inline f32 engine::Math::Pow(f32 value, u32 exp){ 
	return (f32)std::pow(value, (int)exp);
}

inline f32 engine::Math::Exp(f32 value){ 
	return (f32)std::exp(value);
}
		
inline int engine::Math::Sign(int value){ 
	if(value > 0)
		return 1;
	if(value < 0)
		return -1;
	return 0;
}

inline int engine::Math::Sign(f32 value){ 
	if(value > 0.f)
		return 1;
	if(value < 0.f)
		return -1;
	return 0;
}

template<typename T>
inline T engine::Math::Max(T a, T b){
	return (a > b) ? a : b;
}
		
template<typename T>
inline T engine::Math::Min(T a, T b){
	return (a < b) ? a : b;
}

inline f32 engine::Math::Rand(u32 min, u32 max, u32 seed){ 
	if(seed > 0)
		srand(seed);

	f32 ratio = ((f32)rand()) / ((f32)RAND_MAX);
	return min + (max - min) * ratio;
}

inline bool engine::Math::IsNaN(double x){
	return x != x;
}

inline bool engine::Math::IsPowOf2(u32 value){
	return (value > 0) && ((value & (value - 1)) == 0);
}

inline bool engine::Math::IsEqual(f32 x, f32 y){
	return std::fabs(x - y) < std::numeric_limits<f32>::epsilon();
}

inline f32 engine::Math::Clamp(f32 val, f32 min, f32 max){
	val = (val > max ? max : val);
	val = (val < min ? min : val);

	return val;
}
