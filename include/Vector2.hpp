#pragma once

namespace JD
{
	/**
	 * Class holder of 2 values x and y 
	 */
	template <typename T>
	class Vector2
	{
	public:
		/**
		 * Default constructor for vector2 with x and y of 0
		 */
		Vector2<T>();
		/**
		 * Initializes vector2 x and y
		 */
		Vector2<T>(T xValue, T yValue);
		T x;
		T y;
	};
}

