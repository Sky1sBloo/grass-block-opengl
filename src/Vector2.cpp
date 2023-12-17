#include "Vector2.hpp"

namespace JD
{
	template <typename T>
	Vector2<T>::Vector2() :
		x(0), y(0)
	{
	}

	template <typename T>
	Vector2<T>::Vector2(T xValue, T yValue) :
		x(xValue), y(yValue)
	{
	}

	
	template class Vector2<int>;
	template class Vector2<float>;
	template class Vector2<double>; 
}
