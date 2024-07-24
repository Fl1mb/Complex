#pragma once
#include <math.h>
#include <string>
#include <iostream>

#define M_PI 3.1415 //определил Pi


//использовал двойной шаблон, для действительной части определенный тип, и для мнимой части.
template<typename Re = int, typename Im = int>
class ComplexNumber {
private:
	Re RealNumber;
	Im ImageNumber;

	//Дружественные "функции шаблонные
	template<typename Re, typename Im>
	friend ComplexNumber operator+(Re real, const ComplexNumber<Re, Im>& complex);
	template<typename Re, typename Im>
	friend ComplexNumber operator-(Re real, const ComplexNumber<Re, Im>& complex);
	template<typename Re, typename Im>
	friend ComplexNumber operator*(Re real, const ComplexNumber<Re, Im>& complex);
	template<typename Re, typename Im>
	friend ComplexNumber operator/(Re real, const ComplexNumber<Re, Im>& complex);

	template<typename Re, typename Im>
	friend std::istream& operator>>(std::istream& is, ComplexNumber<Re, Im>& complex);
	template<typename Re, typename Im>
	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber<Re, Im>& complex);
public:
	ComplexNumber(); // Конструктор по умолчанию
	ComplexNumber(const ComplexNumber& other);// Конструктор копирования
	ComplexNumber(Re Real = Re(), Im im = Im()); /*Перегруженный конструктор с параметрами. Параметры: действительная и
												мнимая части. Если аргумент 1, то меняется вещественная часть, мнимая
												обнуляется; если аргументов 2, то изменяются обе части;*/


	//Геттеры 
	Re getReal() { return RealNumber; }
	Im getImage() { return ImageNumber; }

	//возращает сопряженное число
	ComplexNumber GetConjugate();
	
	//Функции возращают модуль и аргумент ComplexNumber
	double GetModule();
	double GetArg();
	
	//Преобразоввывает в показательную форму и возращает в строчном виде
	std::string GetNumberInDemoForm();
	
	//6. Статический метод преобразования комплексного числа из показательной формы	в алгебраическую
	static ComplexNumber<Re, Im> FromExpForm(double modulus, double phase);
	
	//Перегрузка оператора присваивания
	ComplexNumber& operator=(const ComplexNumber& other);
	ComplexNumber& operator=(double number);
	
	//перегрузка оператора приведения типа
	operator double()const;

	//инкремент перегрузка
	//Префикс
	ComplexNumber& operator++();
	//Постфикс
	ComplexNumber& operator++(int);


	//Перегрузка операторов алгебраических
	ComplexNumber operator+(const ComplexNumber& other)const;
	ComplexNumber operator+(Re real)const;
	ComplexNumber operator-(const ComplexNumber& other)const;
	ComplexNumber operator-(Re real)const;
	ComplexNumber operator*(const ComplexNumber& other)const;
	ComplexNumber operator*(Re real)const;
	ComplexNumber operator/(const ComplexNumber& other)const;
	ComplexNumber operator/(Re real)const;


	ComplexNumber& operator+=(const ComplexNumber& other);
	ComplexNumber& operator+=(Re real);
	ComplexNumber& operator-=(const ComplexNumber& other);
	ComplexNumber& operator-=(Re real);
	ComplexNumber& operator*=(const ComplexNumber& other);
	ComplexNumber& operator*=(Re real);
	ComplexNumber& operator/=(const ComplexNumber& other);
	ComplexNumber& operator/=(Re real);


	//Перегрузка логических операторов
	bool operator==(const ComplexNumber& other)const;
	bool operator!=(const ComplexNumber& other)const;
	bool operator==(Re real)const;
	bool operator!=(Re real)const;

	bool operator>=(const ComplexNumber& other)const;
	bool operator<=(const ComplexNumber& other)const;
	bool operator>=(Re real)const;
	bool operator<=(Re real)const;

	bool operator>(const ComplexNumber& other)const;
	bool operator<(const ComplexNumber& other)const;
	bool operator>(Re real)const;
	bool operator<(Re real)const;

	

	
	
};

template<typename Re, typename Im>
ComplexNumber<Re, Im>::ComplexNumber()
{
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>::ComplexNumber(const ComplexNumber<Re, Im>& other)		//Просто переопределяю у объекта значения мнимой и реальной части
{
	this->RealNumber = other.RealNumber;
	this->ImageNumber = other.ImageNumber;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>::ComplexNumber(Re Real, Im im) : RealNumber(Real), ImageNumber(im)
{
}

template<typename Re, typename Im> //3. Метод, возвращающий комплексно-сопряжённое число Complex;
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::GetConjugate()
{
	return ComplexNumber(this->RealNumber, -1 * this->ImageNumber);
}

template<typename Re, typename Im>
double ComplexNumber<Re, Im>::GetModule()
{
	return sqrt(pow(this->RealNumber, 2) + pow(this->ImageNumber, 2)); //под корнем x^2 + y^2
}

template<typename Re, typename Im>
inline double ComplexNumber<Re, Im>::GetArg()
{
	return atan2(RealNumber, ImageNumber) * 180/ 3.1415; //Возращаем аргумент в виде градусов
}

template<typename Re, typename Im>
inline std::string ComplexNumber<Re, Im>::GetNumberInDemoForm()
{
	double angle = this->GetArg(); //Берем аргумент для синуса и косинуса
	std::string result = "";
	result += std::to_string(this->GetModule()); // Модуль числа
	result += "(cos(" + std::to_string(angle) + ") + isin(" + std::to_string(angle) + "))"; // Засовываем все в result
	return result;

}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im> ComplexNumber<Re, Im>::FromExpForm(double modulus, double phase)
{
	double realPart = modulus * cos(phase * M_PI / 180.0);				/*Статический метод преобразования комплексного числа из показательной формы
																		в алгебраическую. Параметры: модуль и фаза комплексного числа. Возвращаемое
																		значение типа Complex.
																		*/
	double imagPart = modulus * sin(phase * M_PI / 180.0);
	return ComplexNumber<Re, Im>(realPart, imagPart);
}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator=(const ComplexNumber<Re, Im>& other)
{
	this->RealNumber = other.RealNumber;
	this->ImageNumber = other.ImageNumber; //ну тут понятно
	return *this;
}

template<typename Re, typename Im>
inline ComplexNumber<Re,Im>& ComplexNumber<Re, Im>::operator=(double number)
{
	this->RealNumber = number;
	this->ImageNumber = 0;
	return *this; // возращаем *this, потому что this - указатель, надо разыменовать
}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im>::operator double() const
{
	return RealNumber; // Просто возращаем действительную часть
}

template<typename Re, typename Im>
inline ComplexNumber<Re,Im>& ComplexNumber<Re, Im>::operator++()
{
	this->RealNumber++; //Инкрементируем
	return *this;
}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator++(int)
{
	this->ImageNumber++; //То же самое
	return *this;
}

/*
* Перегрузку операторов сделал все похожие, просто возращал обновленный новый объект, где в конструкторе делал то что нужно, сложение, вычитание и пр.
*/
template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator+(const ComplexNumber<Re, Im>& other) const {
	return ComplexNumber<Re, Im>(RealNumber + other.RealNumber, ImageNumber + other.ImageNumber); 
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator+(Re real) const {
	return ComplexNumber<Re, Im>(RealNumber + real, ImageNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator+=(const ComplexNumber<Re, Im>& other) {
	RealNumber += other.RealNumber;
	ImageNumber += other.ImageNumber;
	return *this;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator+=(Re real) {
	RealNumber += real;
	return *this;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator-(const ComplexNumber<Re, Im>& other) const {
	return ComplexNumber<Re, Im>(RealNumber - other.RealNumber, ImageNumber - other.ImageNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator-(Re real) const {
	return ComplexNumber<Re, Im>(RealNumber - real, ImageNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator-=(const ComplexNumber<Re, Im>& other) {
	RealNumber -= other.RealNumber;
	ImageNumber -= other.ImageNumber;
	return *this;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator-=(Re real) {
	RealNumber -= real;
	return *this;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator*(const ComplexNumber<Re, Im>& other) const {
	return ComplexNumber<Re, Im>(RealNumber * other.RealNumber - ImageNumber * other.ImageNumber,
		RealNumber * other.ImageNumber + ImageNumber * other.RealNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator*(Re real) const {
	return ComplexNumber<Re, Im>(RealNumber * real, ImageNumber * real);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator*=(const ComplexNumber<Re, Im>& other) {
	*this = *this * other;
	return *this;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator*=(Re real) {
	RealNumber *= real;
	ImageNumber *= real;
	return *this;
}

template<typename Re, typename Im>
inline ComplexNumber<Re,Im>& ComplexNumber<Re, Im>::operator/=(const ComplexNumber<Re, Im>& other)
{
	RealNumber /= other.RealNumber;
	ImageNumber /= other.ImageNumber;
	return *this;
}

template<typename Re, typename Im>
inline ComplexNumber<Re,Im>& ComplexNumber<Re, Im>::operator/=(Re real)
{
	RealNumber /= real;
	ImageNumber /= real;
	return *this;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator/(const ComplexNumber<Re, Im>& other) const {
	Re denominator = other.RealNumber * other.RealNumber + other.ImageNumber * other.ImageNumber;
	return ComplexNumber<Re, Im>((RealNumber * other.RealNumber + ImageNumber * other.ImageNumber) / denominator,
		(ImageNumber * other.RealNumber - RealNumber * other.ImageNumber) / denominator);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::operator/(Re real) const {
	return ComplexNumber<Re, Im>(RealNumber / real, ImageNumber / real);
}


template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator==(const ComplexNumber<Re, Im>& other) const {
	return RealNumber == other.RealNumber && ImageNumber == other.ImageNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator!=(const ComplexNumber<Re, Im>& other) const {
	return !(*this == other);
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator==(Re real) const {
	return ImageNumber == 0 && RealNumber == real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator!=(Re real) const {
	return !(*this == ComplexNumber<Re, Im>(real, 0));
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>=(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; //если мнимая часть ноль, но возращаем 0
	}
	return RealNumber >= other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<=(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; // если мнимая часть ноль, но возращаем 0
	}
	return RealNumber <= other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>=(Re real) const {
	if (ImageNumber != 0) {
		return false; //если мнимая часть ноль, но возращаем 0
	}
	return RealNumber >= real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<=(Re real) const {
	if (ImageNumber != 0) {
		return false; //если мнимая часть ноль, но возращаем 0
	}
	return RealNumber <= real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; // если мнимая часть ноль, но возращаем 0
	}
	return RealNumber > other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; // если мнимая часть ноль, но возращаем 0
	}
	return RealNumber < other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>(Re real) const {
	if (ImageNumber != 0) {
		return false; // если мнимая часть ноль, но возращаем 0
	}
	return RealNumber > real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<(Re real) const {
	if (ImageNumber != 0) {
		return false; // если мнимая часть ноль, но возращаем 0
	}
	return RealNumber < real;
}


/// <summary>
/// Начало функций
/// Это дружественные функции
template<typename Re, typename Im>
ComplexNumber<Re, Im> operator+(Re real, const ComplexNumber<Re, Im>& complex) {
	return ComplexNumber<Re, Im>(real + complex.RealNumber, complex.ImageNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> operator-(Re real, const ComplexNumber<Re, Im>& complex) {
	return ComplexNumber<Re, Im>(real - complex.RealNumber, -complex.ImageNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> operator*(Re real, const ComplexNumber<Re, Im>& complex) {
	return ComplexNumber<Re, Im>(real * complex.RealNumber, real * complex.ImageNumber);
}

template<typename Re, typename Im>
ComplexNumber<Re, Im> operator/(Re real, const ComplexNumber<Re, Im>& complex) {
	Re denominator = complex.RealNumber * complex.RealNumber + complex.ImageNumber * complex.ImageNumber;
	return ComplexNumber<Re, Im>((real * complex.RealNumber) / denominator, (-real * complex.ImageNumber) / denominator);
}

//inline нужен чтоб все корректно работало :0
template<typename Re, typename Im>
inline std::istream& operator>>(std::istream& is, ComplexNumber<Re, Im>& complex) {
	Re real;
	Im imag;
	char separator;
	is >> real >> separator >> imag; //Считываем и записываем
	if (separator != ' ') {
		is.setstate(std::ios::failbit); /*Этот код проверяет, не равен ли символ separator пробелу (' '), и если это так, устанавливает бит ошибки (failbit) для потока ввода is, указывая на ошибку.*/
	}
	complex = ComplexNumber<Re, Im>(real, imag);
	return is;
}

template<typename Re, typename Im>
inline std::ostream& operator<<(std::ostream& os, const ComplexNumber<Re, Im>& complex) {
	os << complex.RealNumber << (complex.ImageNumber >= 0 ? " + i" : " - i") << std::abs(complex.ImageNumber); //типа cout << 
	return os;																									//Использовал тернарный оператор ? : 
																												// abs возращает модуль числа
}


/// Конец функций
