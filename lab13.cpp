#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;


template<typename T>
class myMatrix {
    public:
    myMatrix(string fromFileName) {
        ifstream f;
        f.open(fromFileName);
        f >> NN;
        f >> MM;
        vector<T> v;
        T a;
        for (int i = 0; i < NN; i++) {
            v.clear();
            for (int j = 0; j < MM; j++) {
                f >> a;
                v.push_back(a);
            }
            values.push_back(v);
        }

    }
    
    myMatrix(int n, int m) {
        NN = n;
        MM = m;
        vector<T> v;
        T a;
        for (int i = 0; i < NN; i++) {
            v.clear();
            for (int j = 0; j < MM; j++) {
                v.push_back(0);
            }
            values.push_back(v);
        }

    }
    int rNum() {
        return NN;
    }

    int cNum() {
        return MM;
    }
    
    bool operator ==(myMatrix m) {
        if ((m.rNum() != NN) || (m.cNum() != MM)) {
            return false;
        }
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < MM; j++) {
                if (values[i][j] != m[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator ==(int x) {
        if ((x != 0) && (x != 1)) {
            return false;
        }
        if (x == 0) {
            for (int i = 0; i < NN; i++) {
                for (int j = 0; j < MM; j++) {
                    if (values[i][j] != 0) {
                        return false;
                    }
                }
            }
            return true;
        }
        if (x == 1) {
            if (NN != MM) {return false;}
            for (int i = 0; i < NN; i++) {
                for (int j = 0; j < MM; j++) {
                    if (values[i][j] != 0) {
                        if ((i==j) && (values[i][j] == 1)) {continue;}
                        return false;
                    }
                }
            }
            return true;
        }

    }

    myMatrix operator*(myMatrix m) {
        myMatrix res(NN, m.cNum());
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < m.cNum(); j++) {
                T sum = 0;
                for (int k = 0; k < MM; k++) {
                    sum += values[i][k] * m[k][j];
                }
                res.setValue(i, j, sum);
            }
        }
        return res;
    }

    myMatrix operator+(myMatrix m) {
        myMatrix res(NN, MM);
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < MM; j++) {
                res.setValue(i, j, m[i][j] + values[i][j]);
            }
        }
        return res;

    }

    myMatrix operator-(myMatrix m) {
        myMatrix res(NN, MM);
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < MM; j++) {
                res.setValue(i, j, m[i][j] - values[i][j]);
            }
        }
        return res;

    }
    myMatrix operator*(T x) {
        myMatrix res(NN, MM);
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < MM; j++) {
                res.setValue(i, j, x * values[i][j]);
            }
        }
        return res;

    }

    
    void print() {
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < MM; j++) {
                cout << values[i][j] << ' ';
            }
            cout << endl;
        }
    }

    vector<T> operator[](int i) {
        return values[i];
    }

    void setValue(int i, int j, T a) {
        values[i][j] = a;
    }

    myMatrix minor(int y, int x) { // x - номер вычеркиваемого столбца, y - вычеркиваемая строка
        myMatrix m(NN-1, NN-1);
        int c = 0;
        int r = 0;
        for (int i = 0; i < NN; i++) {
            if (i == y) {
                continue;
            }
            
            c = 0;
            for (int j = 0; j < MM; j++) {
                if (j == x) {
                    continue;
                }
                
                m.setValue(r, c, values[i][j]);
                c++;
            }
            r++;
        }
        return m;
    }
    
    myMatrix operator!() {
        if (NN != MM) {
            throw invalid_argument("Matrix is not square matrix");
        }
        T d = determinant();
        if (d == 0) {
            throw invalid_argument("Determinant of matrix is zero");
        }

        if (1 / d * d != 1) {
            throw invalid_argument("Invertible matrix doesn't exist");
        }
        myMatrix m(NN, NN);
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < NN; j++) {
                int k = ((i + j) % 2 == 1)? -1 : 1;
                T mnr = k * minor(i, j).determinant();
                m.setValue(j, i, mnr / d);
            }
        }
        return m;
    } 

    T determinant() {
        if (NN != MM) {

            throw invalid_argument("Matrix is not square matrix");
        }
        if (NN == 1) {
            return values[0][0];
        }
        int t = 1;
        int s = 0;
        for (int i = 0; i < NN; i++) {
            s += t * values[0][i] * minor(0, i).determinant();
            t = -t;
        }
        return s;
    }
    void save2File(string fileName) {
        ofstream f;
        f.open(fileName);
        f << NN << ' ' << MM << endl;
        for (int i = 0; i < NN; i++) {
            for (int j = 0; j < MM; j++) {
                f << values[i][j] << ' ';
            }
        }
        f.close();
    }
    static myMatrix Zero(int x, int y) {
        myMatrix m(x, y);
        return m;
    }
    static myMatrix One(int n) {
        myMatrix m (n,n);
        for (int i = 0; i < n; i++) {
            m.setValue(i, i, 1);
        }
        return m;

    }
    private:
    int NN;
    int MM;
    vector<vector<T>> values;

};

template<typename T>
myMatrix<T> operator*(T x, myMatrix<T> m) {
    return m * x;
}


int main() {
    myMatrix<int> m("input1");
    cout << "Matrix m loaded from file input1" << endl;
    m.print();

    myMatrix<int> m1(2,3);
    cout << endl << "Matrix m1 created with 2 rows and 3 columns\n";
    m1.print();

    string seq1 = (m == m1)? "" : "not ";
    string seq2 = (m == m)? "" : "not ";

    cout << endl << "Matrix m is " << seq1 << "equal to matrix m1" << endl;
    cout << endl << "Matrix m is " << seq2 << "equal to matrix m" << endl;

    cout << endl << "Matrix m multiplied by scalar 2 from the right:\n";
    (m * 2).print();

    cout << endl << "Matrix m multiplied by scalar 2 from the left:\n";
    (2 * m).print();

    cout << endl << "Sum of the matrix m with itself 3 times:\n";
    (m + m + m).print();

    myMatrix<int> m2("input2");
    cout << endl << "Matrix m2 from file input2:\n";
    m2.print();

    myMatrix<int> m3 = m*m2;
    cout << endl << "Matrix m3 is a product m*m2:\n";
    m3.print();

    cout << endl << "Matrix m5 from file 3:\n";
    myMatrix<int> m5("input3");
    m5.print();

    cout << endl << "Determinant of the matrix m5:\n";
    cout << m5.determinant() << endl;
    myMatrix<int> m6 = !m5;
    cout << endl << "Inverse matrix of m5 is:\n";
    m6.print();
    cout << endl << "Check the product of m5 and !m5:\n";
    (m5*m6).print();

    myMatrix<double> m7("input4");
    cout << endl << "Matrix m7 is a matrix of double from file 4:\n";
    m7.print();
    cout << endl << "Inverse matrix of m7:\n";
    (!m7).print();

    (!m7).save2File("output1");
    cout << endl << "Matrix m7 has been writen to file ouptut1\n";
    cout << endl << "Loading matrix from file 4 as matrix of long and trying to get inverse:\n";
    myMatrix<long> m8("input4");
    try
    {
        (!m8).print();
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }

    cout << endl << "Zero matrix of size 4x4:\n";
    myMatrix<int>::Zero(4, 4).print();
    cout << endl << "Identity matrix of size 4x4:\n";
    myMatrix<int>::One(4).print();
}
