#ifndef PROPERTY_H
#define PROPERTY_H

template<typename T, bool GetterVisible = true, bool SetterVisible = true>
class Property
{
public:
	Property()
	{
	}

	operator const T& () const
	{
		static_assert(GetterVisible == true);
		return getter();
	}

	const T& operator=(const T& other)
	{
		static_assert(SetterVisible == true);
		return setter(other);
	}

	bool operator==(const T& other)
	{
		return static_cast<const T&>(*this) == other;
	}

	std::function<const T& ()> getter;
	std::function<const T& (const T&)> setter;
private:
	T value;
};

#endif // PROPERTY_H
