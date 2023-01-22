#pragma once
#include <map>
#include <list>
#include <forward_list>
#include <set>

template<typename T>
class Traits;

//unsigned char ->int
template<>
class Traits<unsigned char>
{
public:	typedef int Trait;
};

//int -> long
template<>
class Traits<int>
{
public: typedef long Trait;

};

//double -> double
template<>
class Traits<double>
{
public: typedef long double Trait;
};

//short -> int
template<>
class Traits<short>
{
public: typedef int Trait;
};

//long -> long long
template<>
class Traits<long>
{
public: typedef long long Trait;
};

//float -> double
template<>
class Traits<float>
{
public: typedef double Trait;
};

//long double -> long double
template<>
class Traits<long double>
{
public: typedef long double Trait;
};

//unsigned

//unsigned int -> unsigned long
template<>
class Traits<unsigned int>
{
public: typedef unsigned long Trait;

};


//unsigned short -> unsigned int
template<>
class Traits<unsigned short>
{
public: typedef unsigned int Trait;
};

//unsigned long -> unsigned long long
template<>
class Traits<unsigned long>
{
public: typedef unsigned long long Trait;
};