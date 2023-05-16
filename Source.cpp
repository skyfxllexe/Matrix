#include <iostream>
#include <vector>
template <class Type>
class Matrix {
private:
	int n, m;
	std::vector<std::vector<Type>> v;
public:
	Matrix(int n, int m, std::vector<std::vector<Type>> v) { this->n = n; this->m = m; this->v = v; }
	bool operator==(Matrix<Type> obj);
	bool operator==(int k);
	Matrix<Type> operator*(Matrix<Type> obj);
	Matrix<Type> operator-(Matrix<Type> obj);
	Matrix<Type> operator+(Matrix<Type> obj);
	Matrix<Type> operator!(); // осталось перегрузить
	void operator=(Matrix<Type> obj);
	void showMatrix();
	void makeMatrixZero();
	int Determinant();
	static std::vector<std::vector<int>> makeZeroMatrix(int n, int m) {
		std::vector<std::vector<int>> zero(n, std::vector<int>(m, 0));
		return zero;

	}
	static std::vector<std::vector<int>> makeIdentityMatrix(int n) {
		std::vector<std::vector<int>> identity(n, std::vector<int>(n,0));
		for (int i = 0; i < n; ++i) {
			identity[i][i] = 1;
		}
		return identity;
	}
	
};
int main() {

	std::vector<std::vector<int>> v1 = { {1,2}, {1,3} };
	std::vector<std::vector<int>> v2 = { {2,2}, {1,3} };
	std::vector<std::vector<int>> v3 = { {0,0}, {0,0} };
	std::vector<std::vector<int>> v4 = { {1,0}, {0,1} };
	
	Matrix<int> A(2, 2, v1);
	Matrix<int> B(2, 2, v2);
	Matrix<int> C(2, 2, v3);
	Matrix<int> D(2, 2, v4);
	
	std::cout << A.Determinant() << std::endl;
}

template <class Type>
int Matrix<Type>::Determinant() {
	try {
		if (this->n != this->m) {
			throw n;
		}
	}
	catch (n) {
		std::cout << "Matrix should be n x n.";
		return 0;
	}

	int det = 1;
	Matrix<Type> m = *this;
	for (int i = 0; i < n; ++i) {
		if (m.v[i][i] == 0) {
			bool found = false;
			for (int j = i + 1; j < n; ++j) {
				if (m.v[j][i] != 0) {
					std::swap(m.v[i], m.v[j]);
					det = -det;
					found = true;
					break;
				}
			}
			if (!found) {
				return 0;
			}
		}
		det *= m.v[i][i];
		for (int j = i + 1; j < n; ++j) {
			Type coeff = m.v[j][i] / m.v[i][i];
			for (int k = i + 1; k < n; ++k) {
				m.v[j][k] -= coeff * m.v[i][k];
			}
		}
	}
	std::cout << det;
}


template <typename Type>
void Matrix<Type>::makeMatrixZero() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			this->v[i][j] = 0;
		}
	}
}


template <typename Type>
void Matrix<Type>::showMatrix() {
	std::cout << "Matrix: " << std::endl;
	for (int i = 0; i < this->n; ++i) {
		for (int j = 0; j < this->m; ++j) {
			std::cout << this->v[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


template <typename Type>
bool Matrix<Type>::operator==(Matrix<Type> obj) {
	if (this->n != obj.n || this->m != obj.m) { return false; }
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (obj.v[i][j] != this->v[i][j]) { return false; }
		}
	}
	return true;
}


template <typename Type>
bool Matrix<Type>::operator==(int k) {
	if (k == 1) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (i != j) {
					if (v[i][j] != 0) return false;
					if (v[i][i] != 1) return false;
				}
			}
		}
		return true;
	}
	else if (k == 0) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (v[i][j] != 0) return false;
			}
		}
		return true;
	}
}


template <typename Type>
Matrix<Type> Matrix<Type>::operator+(Matrix<Type> obj) {
	Matrix<Type> temp(n,m,v);
	if (this->n != obj.n || this->m != obj.m) { return temp; }
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			temp.v[i][j] = this->v[i][j] + obj.v[i][j];
		}
	}
	return temp;
}


template <typename Type>
Matrix<Type> Matrix<Type>::operator-(Matrix<Type> obj) {
	Matrix<Type> temp(n, m, v);
	if (this->n != obj.n || this->m != obj.m) { return temp; }
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			temp.v[i][j] = this->v[i][j] - obj.v[i][j];
		}
	}
	return temp;
}


template <typename Type>
void Matrix<Type>::operator=(Matrix<Type> obj) {
	if (this->n == obj.n || this->m == obj.m) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				this->v[i][j] = obj.v[i][j];
			}
		}
		
	}
}


template <typename Type>
Matrix<Type> Matrix<Type>::operator*(Matrix<Type> obj) {
	Matrix<Type> temp(n, obj.m, v);
	temp.makeMatrixZero();
	if (this->m != obj.n) { return temp; }
	for (int i = 0; i < this->n; ++i) {
		for (int j = 0; j < obj.m; ++j) {
			for (int k = 0; k < this->m; ++k) {
				temp.v[i][j] += this->v[i][k] * obj.v[k][j];
			}
		}
	}
	return temp;
}
