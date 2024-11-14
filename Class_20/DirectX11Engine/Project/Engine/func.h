#pragma once


template<typename T, int _Size>
void Safe_Del_Array(T* (&Array)[_Size])
{
	for (int i = 0; i < _Size; ++i)
	{
		if (nullptr != Array[i])
		{
			delete Array[i];
			Array[i] = nullptr;
		}
	}
}

template<typename T>
void Safe_Del_Vector(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}
