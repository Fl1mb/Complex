#pragma once
#include <math.h>
#include <string>
#include <iostream>

#define M_PI 3.1415 //��������� Pi


//����������� ������� ������, ��� �������������� ����� ������������ ���, � ��� ������ �����.
template<typename Re = int, typename Im = int>
class ComplexNumber {
private:
	Re RealNumber;
	Im ImageNumber;

	//������������� "������� ���������
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
	ComplexNumber(); // ����������� �� ���������
	ComplexNumber(const ComplexNumber& other);// ����������� �����������
	ComplexNumber(Re Real = Re(), Im im = Im()); /*������������� ����������� � �����������. ���������: �������������� �
												������ �����. ���� �������� 1, �� �������� ������������ �����, ������
												����������; ���� ���������� 2, �� ���������� ��� �����;*/


	//������� 
	Re getReal() { return RealNumber; }
	Im getImage() { return ImageNumber; }

	//��������� ����������� �����
	ComplexNumber GetConjugate();
	
	//������� ��������� ������ � �������� ComplexNumber
	double GetModule();
	double GetArg();
	
	//���������������� � ������������� ����� � ��������� � �������� ����
	std::string GetNumberInDemoForm();
	
	//6. ����������� ����� �������������� ������������ ����� �� ������������� �����	� ��������������
	static ComplexNumber<Re, Im> FromExpForm(double modulus, double phase);
	
	//���������� ��������� ������������
	ComplexNumber& operator=(const ComplexNumber& other);
	ComplexNumber& operator=(double number);
	
	//���������� ��������� ���������� ����
	operator double()const;

	//��������� ����������
	//�������
	ComplexNumber& operator++();
	//��������
	ComplexNumber& operator++(int);


	//���������� ���������� ��������������
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


	//���������� ���������� ����������
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
ComplexNumber<Re, Im>::ComplexNumber(const ComplexNumber<Re, Im>& other)		//������ ������������� � ������� �������� ������ � �������� �����
{
	this->RealNumber = other.RealNumber;
	this->ImageNumber = other.ImageNumber;
}

template<typename Re, typename Im>
ComplexNumber<Re, Im>::ComplexNumber(Re Real, Im im) : RealNumber(Real), ImageNumber(im)
{
}

template<typename Re, typename Im> //3. �����, ������������ ����������-���������� ����� Complex;
ComplexNumber<Re, Im> ComplexNumber<Re, Im>::GetConjugate()
{
	return ComplexNumber(this->RealNumber, -1 * this->ImageNumber);
}

template<typename Re, typename Im>
double ComplexNumber<Re, Im>::GetModule()
{
	return sqrt(pow(this->RealNumber, 2) + pow(this->ImageNumber, 2)); //��� ������ x^2 + y^2
}

template<typename Re, typename Im>
inline double ComplexNumber<Re, Im>::GetArg()
{
	return atan2(RealNumber, ImageNumber) * 180/ 3.1415; //��������� �������� � ���� ��������
}

template<typename Re, typename Im>
inline std::string ComplexNumber<Re, Im>::GetNumberInDemoForm()
{
	double angle = this->GetArg(); //����� �������� ��� ������ � ��������
	std::string result = "";
	result += std::to_string(this->GetModule()); // ������ �����
	result += "(cos(" + std::to_string(angle) + ") + isin(" + std::to_string(angle) + "))"; // ���������� ��� � result
	return result;

}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im> ComplexNumber<Re, Im>::FromExpForm(double modulus, double phase)
{
	double realPart = modulus * cos(phase * M_PI / 180.0);				/*����������� ����� �������������� ������������ ����� �� ������������� �����
																		� ��������������. ���������: ������ � ���� ������������ �����. ������������
																		�������� ���� Complex.
																		*/
	double imagPart = modulus * sin(phase * M_PI / 180.0);
	return ComplexNumber<Re, Im>(realPart, imagPart);
}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator=(const ComplexNumber<Re, Im>& other)
{
	this->RealNumber = other.RealNumber;
	this->ImageNumber = other.ImageNumber; //�� ��� �������
	return *this;
}

template<typename Re, typename Im>
inline ComplexNumber<Re,Im>& ComplexNumber<Re, Im>::operator=(double number)
{
	this->RealNumber = number;
	this->ImageNumber = 0;
	return *this; // ��������� *this, ������ ��� this - ���������, ���� ������������
}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im>::operator double() const
{
	return RealNumber; // ������ ��������� �������������� �����
}

template<typename Re, typename Im>
inline ComplexNumber<Re,Im>& ComplexNumber<Re, Im>::operator++()
{
	this->RealNumber++; //��������������
	return *this;
}

template<typename Re, typename Im>
inline ComplexNumber<Re, Im>& ComplexNumber<Re, Im>::operator++(int)
{
	this->ImageNumber++; //�� �� �����
	return *this;
}

/*
* ���������� ���������� ������ ��� �������, ������ �������� ����������� ����� ������, ��� � ������������ ����� �� ��� �����, ��������, ��������� � ��.
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
		return false; //���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber >= other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<=(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; // ���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber <= other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>=(Re real) const {
	if (ImageNumber != 0) {
		return false; //���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber >= real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<=(Re real) const {
	if (ImageNumber != 0) {
		return false; //���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber <= real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; // ���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber > other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<(const ComplexNumber<Re, Im>& other) const {
	if (ImageNumber != 0 || other.ImageNumber != 0) {
		return false; // ���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber < other.RealNumber;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator>(Re real) const {
	if (ImageNumber != 0) {
		return false; // ���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber > real;
}

template<typename Re, typename Im>
bool ComplexNumber<Re, Im>::operator<(Re real) const {
	if (ImageNumber != 0) {
		return false; // ���� ������ ����� ����, �� ��������� 0
	}
	return RealNumber < real;
}


/// <summary>
/// ������ �������
/// ��� ������������� �������
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

//inline ����� ���� ��� ��������� �������� :0
template<typename Re, typename Im>
inline std::istream& operator>>(std::istream& is, ComplexNumber<Re, Im>& complex) {
	Re real;
	Im imag;
	char separator;
	is >> real >> separator >> imag; //��������� � ����������
	if (separator != ' ') {
		is.setstate(std::ios::failbit); /*���� ��� ���������, �� ����� �� ������ separator ������� (' '), � ���� ��� ���, ������������� ��� ������ (failbit) ��� ������ ����� is, �������� �� ������.*/
	}
	complex = ComplexNumber<Re, Im>(real, imag);
	return is;
}

template<typename Re, typename Im>
inline std::ostream& operator<<(std::ostream& os, const ComplexNumber<Re, Im>& complex) {
	os << complex.RealNumber << (complex.ImageNumber >= 0 ? " + i" : " - i") << std::abs(complex.ImageNumber); //���� cout << 
	return os;																									//����������� ��������� �������� ? : 
																												// abs ��������� ������ �����
}


/// ����� �������
