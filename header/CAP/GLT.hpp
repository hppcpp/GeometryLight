/**/
#include<limits.h>
#include<math.h>
#include<string.h>

#include<iostream>

//No double check here
#ifndef CAP_GLT_h
#define CAP_GLT_h
namespace CAP
{
template<typename>
class Vector2;
template<typename>
class Vector3;
template<typename>
class Vector4;

typedef Vector2<double> Point2d;
typedef Vector2<float> Point2f;
typedef Vector2<int> Point2i;
typedef Vector2<unsigned int> Point2ui;
typedef Vector2<long long> Point2ll;
typedef Vector2<unsigned long long> Point2ull;
typedef Vector3<unsigned char> RGBub;
typedef Vector3<double> Point3d;
typedef Vector3<double> RGBd;
typedef Vector3<float> Point3f;
typedef Vector3<float> RGBf;
typedef Vector3<int> Point3i;
typedef Vector3<unsigned int> Point3ui;
typedef Vector3<long long> Point3ll;
typedef Vector3<unsigned long long> Point3ull;
typedef Vector4<unsigned char> RGBAub;
typedef Vector4<double> RGBAd;
typedef Vector4<float> RGBAf;

//polar(rho,theta)
template<typename TN>
class Vector2
{
	private:
		TN vector2[2];
	public:
		Vector2();
		explicit Vector2(TN,TN);
		explicit Vector2(const TN* const);
		
		inline double norm()const;
		void deg_rad();
		inline void normalize();
		void rad_deg();
		void set(TN,TN);
		void set(const TN* const);
		
		bool operator==(const Vector2&)const;
		TN operator*(const Vector2&)const;
		TN& operator[](int);
		const TN& operator[](int)const;
		Vector2& operator*=(double);
		Vector2& operator+=(const Vector2&);
		Vector2& operator-=(const Vector2&);
		
		void setRho(TN value){vector2[0]=value;}
		void setTheta(TN value){vector2[1]=value;}
		void setx(TN value){vector2[0]=value;}
		void sety(TN value){vector2[1]=value;}
		TN getRho()const{return vector2[0];}
		TN getTheta()const{return vector2[1];}
		TN getx()const{return vector2[0];}
		TN gety()const{return vector2[1];}
		const TN* get()const{return vector2;}
		TN* set(){return vector2;}
};
//spherical(rho,theta,phi)
template<typename TN>
class Vector3
{
	private:
		TN vector3[3];
	public:
		Vector3();
		explicit Vector3(TN,TN,TN);
		explicit Vector3(const TN* const);
		
		inline double norm()const;
		void deg_rad();
		inline void normalize();
		void rad_deg();
		void set(TN,TN,TN);
		void set(const TN* const);
		
		bool operator==(const Vector3&)const;
		TN operator*(const Vector3&)const;
		TN& operator[](int);
		const TN& operator[](int)const;
		Vector3& operator*=(double);
		Vector3& operator+=(const Vector3&);
		Vector3& operator-=(const Vector3&);
		
		void setB(TN value){vector3[2]=value;}
		void setG(TN value){vector3[1]=value;}
		void setPhi(TN value){vector3[2]=value;}
		void setR(TN value){vector3[0]=value;}
		void setRho(TN value){vector3[0]=value;}
		void setTheta(TN value){vector3[1]=value;}
		void setx(TN value){vector3[0]=value;}
		void sety(TN value){vector3[1]=value;}
		void setz(TN value){vector3[2]=value;}
		TN getB()const{return vector3[2];}
		TN getG()const{return vector3[1];}
		TN getPhi()const{return vector3[2];}
		TN getR()const{return vector3[0];}
		TN getRho()const{return vector3[0];}
		TN getTheta()const{return vector3[1];}
		TN getx()const{return vector3[0];}
		TN gety()const{return vector3[1];}
		TN getz()const{return vector3[2];}
		const TN* get()const{return vector3;}
		TN* set(){return vector3;}
};
template<typename TN>
class Vector4
{
	private:
		TN vector4[4];
	public:
		Vector4();
		explicit Vector4(TN,TN,TN,TN);
		explicit Vector4(const TN* const);
		
		inline double norm()const;
		inline void normalize();
		void set(TN,TN,TN,TN);
		void set(const TN* const);
		
		bool operator==(const Vector4&)const;
		TN operator*(const Vector4&)const;
		TN& operator[](int);
		const TN& operator[](int)const;
		Vector4& operator*=(double);
		Vector4& operator+=(const Vector4&);
		Vector4& operator-=(const Vector4&);
		
		void setA(TN value){vector4[3]=value;}
		void setB(TN value){vector4[2]=value;}
		void setG(TN value){vector4[1]=value;}
		void setR(TN value){vector4[0]=value;}
		TN getA()const{return vector4[3];}
		TN getB()const{return vector4[2];}
		TN getG()const{return vector4[1];}
		TN getR()const{return vector4[0];}
		const TN* get()const{return vector4;}
		TN* set(){return vector4;}
};


//extern value
extern const double PI;
extern const int BYTE_BIT,PERIGON,RA,SA;

template<int dimension,typename TN>
inline const TN* vecZeroPtr()
{
	static const TN value[dimension]={0};
	return value;
}


template<typename TN>
bool vectorBetweenEqual(int,const TN* const,const TN* const,const TN* const);
template<typename TN>
bool vectorEqual(int,const TN* const,const TN* const);

//(if (>= double LLONG_MAX) LLONG_MIN)
inline int highestBit(long long integer){return integer>>BYTE_BIT*sizeof(long long)-1&1;}
template<typename TN>
int inTriangle2D(const TN* const,const TN* const,const TN* const,const TN* const);
inline int minusPower(long long exponential){return exponential%2?-1:1;}
template<typename TN>
int outTriangle2D(const TN* const,const TN* const,const TN* const,const TN* const);
template<typename TN>
inline int xorSign(TN,TN);

inline double deg_rad(double degree){return degree/SA*PI;}
double plusRemainder(double,double);
inline double rad_deg(double radian){return radian/PI*SA;}
template<typename TN>
double vectorNorm(int,const TN* const);

unsigned long long arrangementA(int,int);
unsigned long long combinationC(int,int);
inline long long roundd(double doubleFloat){return static_cast<long long>(doubleFloat+0.5);}

template<typename TN>
void complexMultiply(const TN* const,const TN* const,TN* const);
template<typename TN>
void matrixAdd(int,int,double,const TN* const,const TN* const,TN* const);
template<typename TN>
void matrixAddAssign(int,int,double,TN* const,const TN* const);
template<typename TN>
void matrixC(int,int,double,TN* const);
template<typename TN>
void matrixMultiply(int,int,int,const TN* const,const TN* const,TN* const);
template<typename TN>
void matrixTranspose(int,int,const TN* const,TN* const);
template<typename TN>
void polar_rectangular(const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void polar_rectangular_normalized(const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void quaternionMultiply(const TN* const,const TN* const,TN* const);
template<typename TN>
void rectangular_polar(const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void rectangular_spherical(const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void spherical_rectangular(const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void spherical_rectangular_normalized(const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector2Global(double,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector2Local(double,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector2Rotate(double,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector2RotateMatrix2(double,TN* const, bool isRadian=false);
template<typename TN>
void vector2Rotate_pivot(double,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector2Vertical(const TN* const,TN* const);
template<typename TN>
void vector3Cross(const TN* const,const TN* const,TN* const);
template<typename TN>
void vector3GlobalSpherical(const TN* const,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3LocalSpherical(const TN* const,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateAxis(double,int,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateAxisMatrix3(double,int,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateAxis_pivot(double,int,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateQuaternion(double,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateQuaternion_pivot(double,const TN* const,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateRectangular(double,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateRectangular_pivot(double,const TN* const,const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateSpherical(const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vector3RotateSpherical_pivot(const TN* const,const TN* const,const TN* const,TN* const, bool isRadian=false,bool reverse=false);
template<typename TN>
void vector3RotateSpherical_reverse(const TN* const,const TN* const,TN* const, bool isRadian=false);
template<typename TN>
void vectorAdd(int,double,const TN* const,const TN* const,TN* const);
template<typename TN>
void vectorAddAssign(int,double,TN* const,const TN* const);
template<typename TN>
void vectorC(int,double,TN* const);
template<typename TN>
void vectorMM(int,const TN* const,const TN* const,TN* const,TN* const);
template<typename TN>
void vectorNormalize(int,TN* const);
template<typename TN>
void vectorScale(int,double,const TN* const,TN* const);
template<typename TN>
void vectorScale_pivot(int,double,const TN* const,const TN* const,TN* const);

template<typename TN>
TN cofactor(int,int,int,const TN* const,TN* const);
template<typename TN>
TN determinant(int,const TN* const);
template<typename TN>
TN sigmaN(int,const TN* const);
template<typename TN>
inline TN vector2_pSide(const TN* const,const TN* const,const TN* const);
template<typename TN>
TN vectorDot(int,const TN* const,const TN* const);
template<typename TN>
TN vectorMax(int,const TN* const);
template<typename TN>
TN vectorMin(int,const TN* const);



//class
//Vector2
template<typename TN>
Vector2<TN>::Vector2():
	vector2{0,0}
{}
template<typename TN>
Vector2<TN>::Vector2(TN v0,TN v1):
	vector2{v0,v1}
{}
template<typename TN>
Vector2<TN>::Vector2(const TN* const vec):
	vector2{vec[0],vec[1]}
{}

template<typename TN>
inline double Vector2<TN>::norm()const{return vectorNorm(2,vector2);}
template<typename TN>
void Vector2<TN>::deg_rad(){vector2[1]=CAP::deg_rad(vector2[1]);}
template<typename TN>
inline void Vector2<TN>::normalize(){vectorNormalize(2,vector2);}
template<typename TN>
void Vector2<TN>::rad_deg(){vector2[1]=CAP::rad_deg(vector2[1]);}
template<typename TN>
void Vector2<TN>::set(TN v0,TN v1)
{
	vector2[0]=v0;
	vector2[1]=v1;
}
template<typename TN>
void Vector2<TN>::set(const TN* const vec){memcpy(vector2,vec,2*sizeof(TN));}

template<typename TN>
bool Vector2<TN>::operator==(const Vector2& vec)const{return vectorEqual(2,vector2,vec.vector2);}
template<typename TN>
TN Vector2<TN>::operator*(const Vector2& vec)const{return vectorDot(2,vector2,vec.vector2);}
template<typename TN>
TN& Vector2<TN>::operator[](int index){return vector2[index];}
template<typename TN>
const TN& Vector2<TN>::operator[](int index)const{return vector2[index];}
template<typename TN>
Vector2<TN>& Vector2<TN>::operator*=(double coefficient)
{
	vectorC(2,coefficient,vector2);
	return *this;
}
template<typename TN>
Vector2<TN>& Vector2<TN>::operator+=(const Vector2& vec)
{
	vectorAddAssign(2,1,vector2,vec.vector2);
	return *this;
}
template<typename TN>
Vector2<TN>& Vector2<TN>::operator-=(const Vector2& vec)
{
	vectorAddAssign(2,-1,vector2,vec.vector2);
	return *this;
}

//Vector3
template<typename TN>
Vector3<TN>::Vector3():
	vector3{0,0,0}
{}
template<typename TN>
Vector3<TN>::Vector3(TN v0,TN v1,TN v2):
	vector3{v0,v1,v2}
{}
template<typename TN>
Vector3<TN>::Vector3(const TN* const vec):
	vector3{vec[0],vec[1],vec[2]}
{}

template<typename TN>
inline double Vector3<TN>::norm()const{return vectorNorm(3,vector3);}
template<typename TN>
void Vector3<TN>::deg_rad()
{
	vector3[1]=CAP::deg_rad(vector3[1]);
	vector3[2]=CAP::deg_rad(vector3[2]);
}
template<typename TN>
inline void Vector3<TN>::normalize(){vectorNormalize(3,vector3);}
template<typename TN>
void Vector3<TN>::rad_deg()
{
	vector3[1]=CAP::rad_deg(vector3[1]);
	vector3[2]=CAP::rad_deg(vector3[2]);
}
template<typename TN>
void Vector3<TN>::set(TN v0,TN v1,TN v2)
{
	vector3[0]=v0;
	vector3[1]=v1;
	vector3[2]=v2;
}
template<typename TN>
void Vector3<TN>::set(const TN* const vec){memcpy(vector3,vec,3*sizeof(TN));}

template<typename TN>
bool Vector3<TN>::operator==(const Vector3& vec)const{return vectorEqual(3,vector3,vec.vector3);}
template<typename TN>
TN Vector3<TN>::operator*(const Vector3& vec)const{return vectorDot(3,vector3,vec.vector3);}
template<typename TN>
TN& Vector3<TN>::operator[](int index){return vector3[index];}
template<typename TN>
const TN& Vector3<TN>::operator[](int index)const{return vector3[index];}
template<typename TN>
Vector3<TN>& Vector3<TN>::operator*=(double coefficient)
{
	vectorC(3,coefficient,vector3);
	return *this;
}
template<typename TN>
Vector3<TN>& Vector3<TN>::operator+=(const Vector3& vec)
{
	vectorAddAssign(3,1,vector3,vec.vector3);
	return *this;
}
template<typename TN>
Vector3<TN>& Vector3<TN>::operator-=(const Vector3& vec)
{
	vectorAddAssign(3,-1,vector3,vec.vector3);
	return *this;
}

//Vector4
template<typename TN>
Vector4<TN>::Vector4():
	vector4{0,0,0,0}
{}
template<typename TN>
Vector4<TN>::Vector4(TN v0,TN v1,TN v2,TN v3):
	vector4{v0,v1,v2,v3}
{}
template<typename TN>
Vector4<TN>::Vector4(const TN* const vec):
	vector4{vec[0],vec[1],vec[2],vec[3]}
{}

template<typename TN>
inline double Vector4<TN>::norm()const{return vectorNorm(4,vector4);}
template<typename TN>
inline void Vector4<TN>::normalize(){vectorNormalize(4,vector4);}
template<typename TN>
void Vector4<TN>::set(TN v0,TN v1,TN v2,TN v3)
{
	vector4[0]=v0;
	vector4[1]=v1;
	vector4[2]=v2;
	vector4[3]=v3;
}
template<typename TN>
void Vector4<TN>::set(const TN* const vec){memcpy(vector4,vec,4*sizeof(TN));}

template<typename TN>
bool Vector4<TN>::operator==(const Vector4& vec)const{return vectorEqual(4,vector4,vec.vector4);}
template<typename TN>
TN Vector4<TN>::operator*(const Vector4& vec)const{return vectorDot(4,vector4,vec.vector4);}
template<typename TN>
TN& Vector4<TN>::operator[](int index){return vector4[index];}
template<typename TN>
const TN& Vector4<TN>::operator[](int index)const{return vector4[index];}
template<typename TN>
Vector4<TN>& Vector4<TN>::operator*=(double coefficient)
{
	vectorC(4,coefficient,vector4);
	return *this;
}
template<typename TN>
Vector4<TN>& Vector4<TN>::operator+=(const Vector4& vec)
{
	vectorAddAssign(4,1,vector4,vec.vector4);
	return *this;
}
template<typename TN>
Vector4<TN>& Vector4<TN>::operator-=(const Vector4& vec)
{
	vectorAddAssign(4,-1,vector4,vec.vector4);
	return *this;
}


//function
//please ensure the vecMin and vecMax by using vectorMM
template<typename TN>
bool vectorBetweenEqual(int dimension,const TN* const vecMin,const TN* const vecMax,const TN* const vec)
{
	for(int i=0;i< dimension;i++)
	{
		if(vec[i]< vecMin[i] || vecMax[i]< vec[i]){return false;}
	}
	return true;
}
template<typename TN>
bool vectorEqual(int dimension,const TN* const vec1,const TN* const vec2)
{
	for(int i=0;i< dimension;i++)
	{
		if(vec1[i]!=vec2[i]){return false;}
	}
	return true;
}

template<typename TN>
int inTriangle2D(const TN* const tri1,const TN* const tri2,const TN* const tri3,const TN* const point)
{
	int side=0,sign=-1;
	TN vertex[6]={0};
	
	memcpy(&vertex[0],tri1,2*sizeof(TN));
	memcpy(&vertex[2],tri2,2*sizeof(TN));
	memcpy(&vertex[4],tri3,2*sizeof(TN));
	if(!vector2_pSide(tri1,tri2,tri3)){return -1;}

	for(int i=0;i< 3;i++)
	{
		side=vector2_pSide(&vertex[i*2],&vertex[(i+1)%3*2],point);
		if(side!=0)
		{
			if(sign==-1){sign=highestBit(side);}
			else if(sign!=highestBit(side)){return 0;}
		}
	}
	
	return 1;
}
template<typename TN>
int outTriangle2D(const TN* const tri1,const TN* const tri2,const TN* const tri3,const TN* const point)
{
	bool inTriangle=true;
	int anticlockwise=-1,side=0,sign=-1,
		edgeZone[6]={0};
	TN vertex[6]={0};
	
	memcpy(&vertex[0],tri1,2*sizeof(TN));
	memcpy(&vertex[2],tri2,2*sizeof(TN));
	memcpy(&vertex[4],tri3,2*sizeof(TN));
	side=vector2_pSide(tri1,tri2,tri3);
	if(!side){return -1;}
	anticlockwise=highestBit(side);
	
	for(int i=0;i< 3;i++)
	{
		side=vector2_pSide(&vertex[i*2],&vertex[(i+1)%3*2],point);
		
		if(side!=0)
		{
			if(sign==-1){sign=highestBit(side);}
			else if(sign!=highestBit(side)){inTriangle=false;}
		}
		
		if(side==0)
		{
			edgeZone[0]=1;
			edgeZone[1]=1;
			edgeZone[2]=1;
		}
		else if(highestBit(side)==anticlockwise)
		{
			edgeZone[i]=1;
			edgeZone[(i+1)%3+3]=1;
			edgeZone[(i+2)%3+3]=1;
		}
		else
		{
			edgeZone[i+3]=1;
			edgeZone[(i+1)%3]=1;
			edgeZone[(i+2)%3]=1;
		}
	}
	
	if(inTriangle){return 0;}
	for(int i=0;i< 6;i++)
	{
		if(edgeZone[i]==0){return i+1;}
	}
	return INT_MIN;
}
template<typename TN>
inline int xorSign(TN sign1,TN sign2)
{
	if(sign1< 0 && sign2< 0 || 0<=sign1 && 0<=sign2){return 0;}
	return 1;
}

template<typename TN>
double vectorNorm(int dimension,const TN* const vec)
{
	double norm=0;
	
	for(int i=0;i< dimension;i++){norm+=pow(vec[i],2);}
	norm=pow(norm,0.5);
	
	return norm;
}

template<typename TN>
void complexMultiply(const TN* const complex1,const TN* const complex2,TN* const result)
{
	result[0]=complex1[0]*complex2[0]-complex1[1]*complex2[1];
	result[1]=complex1[0]*complex2[1]+complex1[1]*complex2[0];
}
template<typename TN>
void matrixAdd(int M,int N,double coefficient,const TN* const mat1,const TN* const mat2,TN* const result)
{
	for(int i=0;i< M;i++){vectorAdd(N,coefficient,&mat1[i*N],&mat2[i*N],&result[i*N]);}
}
template<typename TN>
void matrixAddAssign(int M,int N,double coefficient,TN* const mat1,const TN* const mat2)
{
	for(int i=0;i< M;i++){vectorAddAssign(N,coefficient,&mat1[i*N],&mat2[i*N]);}
}
template<typename TN>
void matrixC(int M,int N,double coefficient,TN* const mat)
{
	for(int i=0;i< M;i++){vectorC(N,coefficient,&mat[i*N]);}
}
template<typename TN>
void matrixMultiply(int M,int S,int N,const TN* const mat1,const TN* const mat2,TN* const result)
{
	TN element=0;
	
	for(int i=0;i< M;i++)
	{
		for(int j=0;j< N;j++)
		{
			element=0;
			for(int k=0;k< S;k++){element+=mat1[i*S+k]*mat2[k*N+j];}
			result[i*N+j]=element;
		}
	}
}
template<typename TN>
void matrixTranspose(int M,int N,const TN* const mat,TN* const result)
{
	for(int i=0;i< M;i++)
	{
		for(int j=0;j< N;j++){result[j*M+i]=mat[i*N+j];}
	}
}
template<typename TN>
void polar_rectangular(const TN* const polar,TN* const rectangular, bool isRadian)
{
	double thetaRad=isRadian?polar[1]:deg_rad(polar[1]);
	rectangular[0]=polar[0]*cos(thetaRad);
	rectangular[1]=polar[0]*sin(thetaRad);
}
template<typename TN>
void polar_rectangular_normalized(const TN* const polar,TN* const rectangular, bool isRadian)
{
	double thetaRad=isRadian?polar[1]:deg_rad(polar[1]);
	rectangular[0]=1*cos(thetaRad);
	rectangular[1]=1*sin(thetaRad);
}
template<typename TN>
void quaternionMultiply(const TN* const quaternion1,const TN* const quaternion2,TN* const result)
{
	memset(result,0,4*sizeof(TN));
	result[0]=quaternion1[0]*quaternion2[0]-vectorDot(3,&quaternion1[1],&quaternion2[1]);
	vector3Cross(&quaternion1[1],&quaternion2[1],&result[1]);
	vectorAddAssign(3,quaternion1[0],&result[1],&quaternion2[1]);
	vectorAddAssign(3,quaternion2[0],&result[1],&quaternion1[1]);
}
//(degree) 0<=theta && theta< 360
template<typename TN>
void rectangular_polar(const TN* const rectangular,TN* const polar, bool isRadian)
{
	polar[0]=vectorNorm(2,rectangular);
	if(polar[0]==0)
	{
		memset(&polar[1],0,sizeof(TN));
		return;
	}
	
	double thetaASOH=asin(rectangular[1]/static_cast<double>(polar[0]));
	if(rectangular[0]< 0){thetaASOH=PI-thetaASOH;}
	else if(0<=rectangular[0] && thetaASOH< 0){thetaASOH+=2*PI;}
	polar[1]=isRadian?thetaASOH:rad_deg(thetaASOH);
}
//(degree) 0<=theta && theta< 360 && 0<=phi && phi< 180
template<typename TN>
void rectangular_spherical(const TN* const rectangular,TN* const spherical, bool isRadian)
{
	spherical[0]=vectorNorm(3,rectangular);
	if(spherical[0]==0)
	{
		memset(&spherical[1],0,2*sizeof(TN));
		return;
	}
	
	if(rectangular[0])
	{
		double thetaATOA=atan(rectangular[1]/static_cast<double>(rectangular[0]));
		if(rectangular[0]< 0){thetaATOA+=PI;}
		else if(0< rectangular[0] && thetaATOA< 0){thetaATOA+=2*PI;}
		spherical[1]=isRadian?thetaATOA:rad_deg(thetaATOA);
	}
	else
	{
		if(rectangular[1]< 0){spherical[1]=isRadian?PI/2*3:RA*3;}
		else if(0< rectangular[1]){spherical[1]=isRadian?PI/2:RA;}
		else{spherical[1]=0;}
	}
	double phiACAH=acos(rectangular[2]/static_cast<double>(spherical[0]));
	spherical[2]=isRadian?phiACAH:rad_deg(phiACAH);
}
template<typename TN>
void spherical_rectangular(const TN* const spherical,TN* const rectangular, bool isRadian)
{
	double phiRad=isRadian?spherical[2]:deg_rad(spherical[2]),
		thetaRad=isRadian?spherical[1]:deg_rad(spherical[1]);
	TN polar0=spherical[0]*sin(phiRad);
	rectangular[0]=polar0*cos(thetaRad);
	rectangular[1]=polar0*sin(thetaRad);
	rectangular[2]=spherical[0]*cos(phiRad);
}
template<typename TN>
void spherical_rectangular_normalized(const TN* const spherical,TN* const rectangular, bool isRadian)
{
	double phiRad=isRadian?spherical[2]:deg_rad(spherical[2]),
		thetaRad=isRadian?spherical[1]:deg_rad(spherical[1]);
	TN polar0=1*sin(phiRad);
	rectangular[0]=polar0*cos(thetaRad);
	rectangular[1]=polar0*sin(thetaRad);
	rectangular[2]=1*cos(phiRad);
}
template<typename TN>
void vector2Global(double angle,const TN* const pivot,const TN* const vec2,TN* const result, bool isRadian)
{
	vector2Rotate(angle,vec2,result, isRadian);
	vectorAddAssign(2,1,result,pivot);
}
template<typename TN>
void vector2Local(double angle,const TN* const pivot,const TN* const vec2,TN* const result, bool isRadian)
{
	TN pivTemp[2];
	vector2Rotate(-angle,pivot,pivTemp, isRadian);
	vector2Rotate(-angle,vec2,result, isRadian);
	vectorAddAssign(2,-1,result,pivTemp);
}
template<typename TN>
void vector2Rotate(double angle,const TN* const vec2,TN* const result, bool isRadian)
{
	double radian=isRadian?angle:deg_rad(angle),
		cosRad=cos(radian),sinRad=sin(radian);
	result[0]=vec2[0]*cosRad-vec2[1]*sinRad;
	result[1]=vec2[0]*sinRad+vec2[1]*cosRad;
}
template<typename TN>
void vector2RotateMatrix2(double angle,TN* const result, bool isRadian)
{
	double radian=isRadian?angle:deg_rad(angle),
		cosRad=cos(radian),sinRad=sin(radian);
	result[0]=cosRad;
	result[1]=-sinRad;
	result[2]=sinRad;
	result[3]=cosRad;
}
template<typename TN>
void vector2Rotate_pivot(double angle,const TN* const pivot,const TN* const vec2,TN* const result, bool isRadian)
{
	TN vecTemp[2];
	vectorAdd(2,-1,vec2,pivot,vecTemp);
	vector2Rotate(angle,vecTemp,result, isRadian);
	vectorAddAssign(2,1,result,pivot);
}
template<typename TN>
void vector2Vertical(const TN* const vec2,TN* const result)
{
	if(vec2[0])
	{
		result[0]=-vec2[1]/vec2[0];
		result[1]=1;
	}
	else
	{
		result[1]=0;
		if(vec2[1]){result[0]=1;}
		else{result[0]=0;}
	}
}
template<typename TN>
void vector3Cross(const TN* const vec1,const TN* const vec2,TN* const result)
{
	result[0]=vec1[1]*vec2[2]-vec1[2]*vec2[1];
	result[1]=vec1[2]*vec2[0]-vec1[0]*vec2[2];
	result[2]=vec1[0]*vec2[1]-vec1[1]*vec2[0];
}
template<typename TN>
void vector3GlobalSpherical(const TN* const spherical,const TN* const pivot,const TN* const vec3,TN* const result, bool isRadian)
{
	vector3RotateSpherical(spherical,vec3,result, isRadian);
	vectorAddAssign(3,1,result,pivot);
}
template<typename TN>
void vector3LocalSpherical(const TN* const spherical,const TN* const pivot,const TN* const vec3,TN* const result, bool isRadian)
{
	TN pivTemp[3];
	vector3RotateSpherical_reverse(spherical,pivot,pivTemp, isRadian);
	vector3RotateSpherical_reverse(spherical,vec3,result, isRadian);
	vectorAddAssign(3,-1,result,pivTemp);
}
//x-axis==0, y-axis==1, z-axis==2
template<typename TN>
void vector3RotateAxis(double angle,int axis,const TN* const vec3,TN* const result, bool isRadian)
{
	if(axis< 0 || 2< axis){return;}
	else if(axis==2)
	{
		vector2Rotate(angle,vec3,result, isRadian);
		result[axis]=vec3[axis];
		return;
	}
	
	double radian=isRadian?angle:deg_rad(angle),
		cosRad=cos(radian),sinRad=sin(radian);
	if(axis)
	{
		result[2]=vec3[2]*cosRad-vec3[0]*sinRad;
		result[0]=vec3[2]*sinRad+vec3[0]*cosRad;
	}
	else
	{
		result[1]=vec3[1]*cosRad-vec3[2]*sinRad;
		result[2]=vec3[1]*sinRad+vec3[2]*cosRad;
	}
	result[axis]=vec3[axis];
}
//x-axis==0, y-axis==1, z-axis==2
template<typename TN>
void vector3RotateAxisMatrix3(double angle,int axis,TN* const result, bool isRadian)
{
	double radian=isRadian?angle:deg_rad(angle),
		cosRad=cos(radian),sinRad=sin(radian);
	memset(result,0,9*sizeof(TN));
	if(axis==0)
	{
		result[4]=cosRad;
		result[5]=-sinRad;
		result[7]=sinRad;
		result[8]=cosRad;
		result[0]=1;
	}
	else if(axis==1)
	{
		result[8]=cosRad;
		result[6]=-sinRad;
		result[2]=sinRad;
		result[0]=cosRad;
		result[4]=1;
	}
	else if(axis==2)
	{
		result[0]=cosRad;
		result[1]=-sinRad;
		result[3]=sinRad;
		result[4]=cosRad;
		result[8]=1;
	}
}
template<typename TN>
void vector3RotateAxis_pivot(double angle,int axis,const TN* const pivot,const TN* const vec3,TN* const result, bool isRadian)
{
	TN vecTemp[3];
	vectorAdd(3,-1,vec3,pivot,vecTemp);
	vector3RotateAxis(angle,axis,vecTemp,result, isRadian);
	vectorAddAssign(3,1,result,pivot);
}
template<typename TN>
void vector3RotateQuaternion(double angle,const TN* const axis,const TN* const vec,TN* const result, bool isRadian)
{
	double radian=isRadian?angle:deg_rad(angle);
	TN qtnn[4]={0},quaterTemp[4]={0},quaterVec[4]={0};
	memcpy(&qtnn[1],axis,3*sizeof(TN));
	vectorNormalize(3,&qtnn[1]);
	radian/=2;
	qtnn[0]=cos(radian);
	vectorC(3,sin(radian),&qtnn[1]);
	memcpy(&quaterVec[1],vec,3*sizeof(TN));
	quaternionMultiply(qtnn,quaterVec,quaterTemp);
	vectorC(3,-1,&qtnn[1]);
	quaternionMultiply(quaterTemp,qtnn,quaterVec);
	memcpy(result,&quaterVec[1],3*sizeof(TN));
}
template<typename TN>
void vector3RotateQuaternion_pivot(double angle,const TN* const axis,const TN* const pivot,const TN* const vec,TN* const result, bool isRadian)
{
	TN vecTemp[3]={0};
	vectorAdd(3,-1,vec,pivot,vecTemp);
	vector3RotateQuaternion(angle,axis,vecTemp,result,isRadian);
	vectorAddAssign(3,1,result,pivot);
}
template<typename TN>
void vector3RotateRectangular(double angle,const TN* const rectangular,const TN* const vec3,TN* const result, bool isRadian)
{
	TN spherical[3],vecTemp[3];
	rectangular_spherical(rectangular,spherical, true);
	vector3RotateSpherical_reverse(spherical,vec3,result, true);
	vector3RotateAxis(angle,2,result,vecTemp, isRadian);
	vector3RotateSpherical(spherical,vecTemp,result, true);
}
template<typename TN>
void vector3RotateRectangular_pivot(double angle,const TN* const rectangular,const TN* const pivot,const TN* const vec3,TN* const result, bool isRadian)
{
	TN vecTemp[3];
	vectorAdd(3,-1,vec3,pivot,vecTemp);
	vector3RotateRectangular(angle,rectangular,vecTemp,result, isRadian);
	vectorAddAssign(3,1,result,pivot);
}
template<typename TN>
void vector3RotateSpherical(const TN* const spherical,const TN* const vec3,TN* const result, bool isRadian)
{
	TN vecTemp[3];
	vector3RotateAxis(spherical[2],1,vec3,vecTemp, isRadian);
	vector3RotateAxis(spherical[1],2,vecTemp,result, isRadian);
}
template<typename TN>
void vector3RotateSpherical_pivot(const TN* const spherical,const TN* const pivot,const TN* const vec3,TN* const result, bool isRadian,bool reverse)
{
	TN vecTemp[3];
	vectorAdd(3,-1,vec3,pivot,vecTemp);
	if(reverse){vector3RotateSpherical_reverse(spherical,vecTemp,result, isRadian);}
	else{vector3RotateSpherical(spherical,vecTemp,result, isRadian);}
	vectorAddAssign(3,1,result,pivot);
}
template<typename TN>
void vector3RotateSpherical_reverse(const TN* const spherical,const TN* const vec3,TN* const result, bool isRadian)
{
	TN vecTemp[3];
	vector3RotateAxis(-spherical[1],2,vec3,vecTemp, isRadian);
	vector3RotateAxis(-spherical[2],1,vecTemp,result, isRadian);
}
template<typename TN>
void vectorAdd(int dimension,double coefficient,const TN* const vec1,const TN* const vec2,TN* const result)
{
	for(int i=0;i< dimension;i++){result[i]=vec1[i]+coefficient*vec2[i];}
}
template<typename TN>
void vectorAddAssign(int dimension,double coefficient,TN* const vec1,const TN* const vec2)
{
	for(int i=0;i< dimension;i++){vec1[i]+=coefficient*vec2[i];}
}
template<typename TN>
void vectorC(int dimension,double coefficient,TN* const vec)
{
	for(int i=0;i< dimension;i++){vec[i]*=coefficient;}
}
template<typename TN>
void vectorMM(int dimension,const TN* const vec1,const TN* const vec2,TN* const vecMin,TN* const vecMax)
{
	for(int i=0;i< dimension;i++)
	{
		if(vec1[i]< vec2[i])
		{
			vecMin[i]=vec1[i];
			vecMax[i]=vec2[i];
		}
		else
		{
			vecMin[i]=vec2[i];
			vecMax[i]=vec1[i];
		}
	}
}
template<typename TN>
void vectorNormalize(int dimension,TN* const vec)
{
	TN norm=vectorNorm(dimension,vec);
	for(int i=0;i< dimension;i++){vec[i]/=norm;}
}
template<typename TN>
void vectorScale(int dimension,double coefficient,const TN* const vec,TN* const result)
{
	memcpy(result,vec,dimension*sizeof(TN));
	vectorC(dimension,coefficient,result);
}
template<typename TN>
void vectorScale_pivot(int dimension,double coefficient,const TN* const pivot,const TN* const vec,TN* const result)
{
	vectorAdd(dimension,-1,vec,pivot,result);
	vectorC(dimension,coefficient,result);
	vectorAddAssign(dimension,1,result,pivot);
}

template<typename TN>
TN cofactor(int N,int I,int J,const TN* const det,TN* const fb)
{
	int column=0,
		i=I+1;
	
	if(i+1==N)
	{
		for(int j=0;j< N;j++)
		{
			if(fb[j]==0){return det[i*N+j];}
		}
	}
	TN vec[N-i];
	for(int j=0;j< N;j++)
	{
		if(fb[j]==0)
		{
			fb[j]=1;
			vec[column]=det[i*N+j]*minusPower(column)*cofactor(N,i,j,det,fb);
			column++;
			fb[j]=0;
		}
	}
	
	return sigmaN(N-i,&vec[0]);
}
template<typename TN>
TN determinant(int N,const TN* const det)
{
	TN fb[N],vec[N];
	
	if(N< 2){return *det;}
	
	memset(fb,0,N*sizeof(TN));
	for(int j=0;j< N;j++)
	{
		fb[j]=1;
		vec[j]=det[j]*minusPower(j)*cofactor(N,0,j,det,fb);
		fb[j]=0;
	}
	
	return sigmaN(N,vec);
}
template<typename TN>
TN sigmaN(int N,const TN* const vec)
{
	TN result=0;
	for(int i=0;i< N;i++){result+=vec[i];}
	return result;
}
//(vec0->vec1) minus==left,zero==on,plus==right
template<typename TN>
inline TN vector2_pSide(const TN* const vec0,const TN* const vec1,const TN* const p)
{return (vec1[1]-vec0[1])*p[0]+(vec0[0]-vec1[0])*p[1]+vec1[0]*vec0[1]-vec0[0]*vec1[1];}
template<typename TN>
TN vectorDot(int dimension,const TN* const vec1,const TN* const vec2)
{
	TN result=0;
	
	for(int i=0;i< dimension;i++){result+=vec1[i]*vec2[i];}
	
	return result;
}
template<typename TN>
TN vectorMax(int dimension,const TN* const vec)
{
	TN element=vec[0];
	for(int i=1;i< dimension;i++){element=(std::max)(element,vec[i]);}
	return element;
}
template<typename TN>
TN vectorMin(int dimension,const TN* const vec)
{
	TN element=vec[0];
	for(int i=1;i< dimension;i++){element=(std::min)(element,vec[i]);}
	return element;
}

}
#endif

#ifdef CAP_GLT
namespace CAP
{
//value
const double PI=4*atan(1);
const int BYTE_BIT=8,PERIGON=360,RA=90,SA=180;


//function
double plusRemainder(double dividend,double divisor)
{
	if(divisor<=0){return divisor;}
	
	while(dividend< 0){dividend+=divisor;}
	while(divisor<=dividend){dividend-=divisor;}
	return dividend;
}
unsigned long long arrangementA(int n,int m)
{
	unsigned long long argmA=1;
	
	if(m< 0 || n< 0 || n< m){return 0;}
	
	for(int i=n;n-m< i;i--){argmA*=i;}
	
	return argmA;
}
unsigned long long combinationC(int n,int m)
{
	unsigned long long cbntC=1;
	
	if(m< 0 || n< 0 || n< m){return 0;}
	else if(m==n){return cbntC;}
	
	for(int i=n;n-m< i;i--){cbntC*=i;}
	for(int i=m;1< i;i--){cbntC/=i;}
	
	return cbntC;
}

}
#endif
