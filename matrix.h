#ifndef MATRIX_H_88CB33BC6CDF
#define MATRIX_H_88CB33BC6CDF

#include <vector>
#include <string>
#include <sstream>
#include <cassert>


template<typename T>
class Matrix
{
public:
	Matrix(uint32_t rows, uint32_t cols): data(rows, std::vector<T>(cols)) {}
	Matrix(uint32_t size): data(size, std::vector<T>(size)) {}
	Matrix(const std::vector<std::vector<T>>& elements);
	Matrix(const std::vector<T>& elements, bool is_col = false);
	~Matrix() = default;

	inline uint32_t rows() const { return this->data.size(); }
	inline uint32_t cols() const { return this->data.front().size(); }

	inline bool is_column() const { return this->cols() == 1; }
	inline bool is_row() const { return this->rows() == 1; }

	Matrix<T>& operator=(const Matrix<T>& other) { this->data = other.data; return *this; }

	inline std::vector<T>& operator[](size_t index) { return data[index]; }
	inline const std::vector<T>& operator[](size_t index) const { return data[index]; }

	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator+(const T& addend) const;
	Matrix<T>& operator+=(const Matrix<T>& other) { return *this = *this + other; }
	Matrix<T>& operator+=(const T& addend) { return *this = *this + addend; }

	Matrix<T> operator-(const Matrix<T>& other) const;
	Matrix<T> operator-(const T& subtrahend) const;
	Matrix<T>& operator-=(const Matrix<T>& other) { return *this = *this - other; }
	Matrix<T>& operator-=(const T& subtrahend) { return *this = *this - subtrahend; }

	Matrix<T> operator*(const T& factor) const;
	Matrix<T>& operator*=(const T& factor) { return *this = *this * factor; }

	Matrix<T> operator/(const T& divisor) const;
	Matrix<T>& operator/=(const T& divisor) { return *this = *this / divisor; }

	Matrix<T> transpose() const;
	Matrix<T> operator~() const { return this->transpose(); }
	Matrix<T> operator-() const { return *this * -1; }

	Matrix<T> operator*(const Matrix<T>& other) const;

	std::string to_string() const;

private:
	std::vector<std::vector<T>> data;
};


template<typename T>
Matrix<T>::Matrix (const std::vector<std::vector<T>>& elements)
{
	this->data = std::vector(elements.size(), std::vector<T>(elements.front().size()));

	for (uint32_t i = 0; i < elements.size(); ++i)
	{
		assert(this->data[i].size() == elements[i].size());
		this->data[i] = elements[i];
	}
}

template<typename T>
Matrix<T>::Matrix (const std::vector<T>& elements, bool is_col)
{
	this->data = std::vector(1, elements);
	if (is_col) *this = ~*this;
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	assert(this->rows() == other.rows());
	assert(this->cols() == other.cols());

	Matrix sum(this->rows(), this->cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < this->cols(); ++j)
			sum[i][j] = this->data[i][j] + other[i][j];

	return sum;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T& addend) const
{	
	Matrix sum(this->rows(), this->cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < this->cols(); ++j)
			sum[i][j] = this->data[i][j] + addend; 

	return sum;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
	assert(this->rows() == other.rows());
	assert(this->cols() == other.cols());

	Matrix diff(this->rows(), this->cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < this->cols(); ++j)
			diff[i][j] = this->data[i][j] - other[i][j];

	return diff;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T& subtrahend) const
{
	Matrix diff(this->rows(), this->cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < this->cols(); ++j)
			diff[i][j] = this->data[i][j] - subtrahend;

	return diff;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const T& factor) const
{
	Matrix prod(this->rows(), this->cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < this->cols(); ++j)
			prod[i][j] = this->data[i][j] * factor;

	return prod;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T& divisor) const
{
	Matrix quot(this->rows(), this->cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < this->cols(); ++j)
			quot[i][j] = this->data[i][j] / divisor;

	return quot;
}


template<typename T>
Matrix<T> Matrix<T>::transpose() const
{
	Matrix transposed(cols(), rows());

	for (uint32_t i = 0; i < rows(); ++i)
		for (uint32_t j = 0; j < cols(); ++j)
			transposed[j][i] = data[i][j];

	return transposed;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	assert(this->cols() == other.rows());
	Matrix prod(this->rows(), other.cols());

	for (uint32_t i = 0; i < this->rows(); ++i)
		for (uint32_t j = 0; j < other.cols(); ++j)
			for (uint32_t k = 0; k < this->cols(); ++k)
				prod[i][j] += this->data[i][k] * other[k][j];

	return prod;
}


template<typename T>
std::string Matrix<T>::to_string() const
{
	std::ostringstream ss;
	for (const std::vector<T>& row: data)
	{
		for (const T& elem: row)
			ss << elem << ' ';
		ss << '\n';
	}
	return ss.str();
}


#endif // MATRIX_H_88CB33BC6CDF
