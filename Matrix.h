//
//

#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <cstring>
#include <utility>
#include <math.h> 
#include <stdexcept>


template <typename T>
class Matrix {

    static_assert(std::is_move_constructible<T>::value, "not move constructible"); // T must be move-constructible
    static_assert(std::is_move_assignable<T>:: value, "not move assignable"); // T must be move-assignable

public:
    // constructors and assignment operators
    /* TODO: Make the appropriate constructor(s) explicit */
     Matrix();
     explicit Matrix(size_t dim);
     Matrix(size_t rows, size_t cols);
     Matrix(const std::initializer_list<T> & list);
     Matrix(Matrix<T> & other);
     Matrix(Matrix<T> && other) noexcept;
     void set_element(unsigned int x, unsigned int y, T val);
     T get_element(unsigned int x, unsigned int y);
    const T get_element(unsigned int x, unsigned int y) const;

    Matrix<T> & operator=(const Matrix<T> & other);
    Matrix<T> & operator=(Matrix<T> && other) noexcept;

    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    T & operator()(size_t row, size_t col);
    const T & operator()(size_t row, size_t col) const;

    // operators
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);

    // methods
    void reset();
    void resize(unsigned int r, unsigned int c);
    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // iterators
    typedef T* iterator;

    iterator begin();
    iterator end();

private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;
    T * endPointer;
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m);

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m);

// functions
template<typename T>
 Matrix<T> identity(size_t dim);


//
// Implementations
//

template<typename T>
Matrix<T>::Matrix(): m_rows(0),m_cols(0),m_capacity(0) {
    m_vec=nullptr;

}


template<typename T>
Matrix<T>::Matrix(size_t dim):m_rows(dim), m_cols(dim), m_capacity(dim*dim) {
    m_vec=new T[m_capacity];
    for(auto i=(*this).begin(); i!=(*this).end();++i){
        *i=0;
    }
}

 template<typename T>
 Matrix<T>::Matrix(size_t rows, size_t cols): m_rows(rows), m_cols(cols), m_capacity(rows*cols) {
    m_vec=new T[m_capacity];
    for(auto i=(*this).begin(); i!=(*this).end();++i){
        *i=0;
    }
  }

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list): m_rows(sqrt(list.size())), m_cols(sqrt(list.size())), m_capacity(list.size()) {
    if(ceil((double)sqrt(list.size())) != floor((double)sqrt(list.size()))){
         throw std::out_of_range("List size is not an even square root");
     }
     m_vec=new T[m_capacity];
     auto i=(*this).begin();
     auto l=list.begin();
     while(i!=(*this).end()){
        *i=*l;
        ++i;
        ++l;
    }
}



template<typename T>
Matrix<T>::Matrix(Matrix<T> & other): m_rows(other.m_rows), m_cols(other.m_cols), m_capacity(other.m_capacity) {
    //      if(m_rows!=other.rows() || m_cols!=other.cols()){
    //      throw std::out_of_range("Matrix dimensions are not the same");
    //  }
     if(this!=&other){
     m_vec= new T[m_capacity];
       for(unsigned int r = 0; r < other.m_rows; r++) {
    for(unsigned int c = 0; c < other.m_cols; c++) {
      this->set_element(r, c, other.get_element(r, c));
    }
  }
    //  memcpy(m_vec,other.m_vec, sizeof(T)*m_capacity);
     }
}


template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept {
    if(this!=&other){
    // m_vec=other.m_vec;
    // m_capacity=other.m_capacity;
    // m_rows=other.m_rows;
    // m_cols=other.m_cols;
     m_capacity=std::move(other.m_capacity);
     m_vec=std::move(other.m_vec);
     m_rows=std::move(other.m_rows);
     m_cols=std::move(other.m_cols);
     other.m_capacity=0;
     other.m_cols=0;
     other.m_rows=0;
     other.m_vec=nullptr;
    }
}


template<typename T>
//template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
  if (this != &other) {
    if (!(this->m_rows == other.m_rows && this->m_cols == other.m_cols)) {
      this->resize(other.m_rows, other.m_cols);
    }
    for(unsigned int r = 0; r < other.m_rows; r++) {
      for(unsigned int c = 0; c < other.m_cols; c++) {
        this->set_element(r, c, other.get_element(r, c));
      }
    }
  }
  return *this;
}


template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept  {
        if(this!=&other){
            delete[] m_vec;
            m_capacity=std::move(other.m_capacity);
            m_vec=std::move(other.m_vec);
            m_rows=std::move(other.m_rows);
            m_cols=std::move(other.m_cols);
            other.m_capacity=0;
            other.m_cols=0;
            other.m_rows=0;
            other.m_vec=nullptr;            
        // T* temp=new T[other.m_capacity];
        // for(int i=0; i<other.m_rows;i++){
        //     for(int j=0; j<other.m_cols; j++){
        //         *temp=other(i,j);
        //         ++temp;
        //     }
        // }
        // delete[] m_vec;
        // m_vec=temp;
        }
        return *this;

}



template<typename T>
Matrix<T>::~Matrix() {
    delete[] m_vec;
}

template<typename T>
size_t Matrix<T>::rows() const {
      return this->m_rows;

}

template<typename T>
size_t Matrix<T>::cols() const {
    return this->m_cols;
}


template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    if(row>=m_rows || col>=m_cols){
        throw std::out_of_range("Index out of bound");
    }

    return m_vec[row*m_cols + col];
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    if(row>=m_rows || col>=m_rows){
        throw std::out_of_range("index out of bound");
    }
    return m_vec[(row)*m_cols + col];

}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    if(!(m_cols==other.rows()))
        throw std::out_of_range("Matrix multiplication: dimension mismatch.");
    Matrix<T> temp(m_rows, other.m_cols);
    for (int i = 0; i < temp.m_rows; ++i) {
        for (int j = 0; j < temp.m_cols; ++j) {
            for (int k = 0; k < m_cols; ++k) {
                (temp)(i,j) += (*this)(i,k) * other(k,j);
            }
        }
    }
    return temp;

}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
    if(m_rows!=other.rows() || m_cols!=other.cols()){
        throw std::out_of_range("Matrix dimensions are not the same");
    }
     Matrix<T> temp(other.rows(),other.cols());
      for(int i=0; i<other.rows();i++){
          for(int j=0;j<other.cols();j++){
              temp(i,j)=(*this)(i,j)+other(i,j);
          }
      }
 return temp;

}


template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
    if(m_rows!=other.rows() || m_cols!=other.cols()){
        throw std::out_of_range("Matrix dimensions are not the same");
    }
     Matrix<T> temp(other.rows(),other.cols());
     for(int i=0; i<other.rows();i++){
         for(int j=0;j<other.cols();j++){
             temp(i,j)=(*this)(i,j)-other(i,j);
         }
     }
return temp;
}


template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) {
    if(!(m_cols==other.rows()))
        throw std::out_of_range("Matrix multiplication: dimension mismatch.");
    Matrix<T> temp(m_rows, other.m_cols);
    for (int i = 0; i < temp.m_rows; ++i) {
        for (int j = 0; j < temp.m_cols; ++j) {
            for (int k = 0; k < m_cols; ++k) {
                (temp)(i,j) += (*this)(i,k) * other(k,j);
            }
        }
    }
    *this=temp;
}



template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
    if(m_rows!=other.rows() || m_cols!=other.cols()){
        throw std::out_of_range("Matrix dimensions are not the same");
    }
    auto t=(*this).begin();
     for(int i=0; i<other.rows(); i++){
         for(int j=0; j<other.cols(); j++){
             *t = *t+other(i,j);
             ++t;
         }
     }
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
    if(m_rows!=other.rows() || m_cols!=other.cols()){
        throw std::out_of_range("Matrix dimensions are not the same");
    }
    auto t=(*this).begin();
     for(int i=0; i<other.rows(); i++){
         for(int j=0; j<other.cols(); j++){
             *t = *t-other(i,j);
             ++t;
         }
     }
}

template <typename T>
void Matrix<T>::resize(unsigned int r, unsigned int c) {
  T* new_vec = new T[r*c];

  this->m_rows = r;
  this->m_cols = c;

  delete[] this->m_vec;
  this->m_vec = new_vec;
}

template<typename T>
void Matrix<T>::reset() {
    for(auto i=(*this).begin(); i!=(*this).end();++i){
        *i=0;
    }
}

template<typename T>
void Matrix<T>::insert_row(size_t row) {
    if(row>=m_rows){
        throw std::out_of_range("index out of bounds");
    }
     Matrix<T> cur(*this);
     delete[] m_vec;
     m_rows=m_rows+1;
     m_vec=new T[m_cols*m_rows];
     for( int i=0; i<m_rows; i++){
         for(int j=0; j<m_cols; j++){
             if(i<row){
                (*this)(i,j)=cur(i,j);

             }
             else if(i==row){
                 (*this)(i,j)=0;
             }
             else if(i>row){
                 break;
             }

         }
     }
        for(int i=row+1; i<m_rows;i++){
            for(int j=0; j<m_cols;j++){
                (*this)(i,j)=cur(i-1,j);
         }
     }
    cur.~Matrix();

}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    if(row>=m_rows){
        throw std::out_of_range("index out of bounds");
    }
     Matrix<T> cur(*this);
     delete[] m_vec;
     m_rows=m_rows+1;
     m_vec=new T[m_cols*m_rows];
     for( int i=0; i<m_rows; i++){
         for(int j=0; j<m_cols; j++){
             if(i<row+1){
                (*this)(i,j)=cur(i,j);

             }
             else if(i==row+1){
                 (*this)(i,j)=0;
             }
             else if(i>row+1){
                 break;
             }

         }
     }
        for(int i=row+2; i<m_rows;i++){
            for(int j=0; j<m_cols;j++){
                (*this)(i,j)=cur(i-1,j);
         }
     }
    //cur.~Matrix();

}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    if(row>=m_rows){
        throw std::out_of_range("index out of bounds");
    }
     Matrix<T> cur(*this);
     delete[] m_vec;
     m_rows=m_rows-1;
     m_vec=new T[m_cols*m_rows];
     for( int i=0; i<m_rows+1; i++){
         for(int j=0; j<m_cols; j++){
             if(i<row){
                (*this)(i,j)=cur(i,j);

             }
             else if(i>row){
                (*this)(i-1,j)=cur(i,j);

            }

         }
     }
     cur.~Matrix();

}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    if(col>=m_cols){
        throw std::out_of_range("index out of bounds");
    }
     Matrix<T> cur(*this);
     delete[] m_vec;
     m_cols=m_cols+1;
     m_vec=new T[m_cols*m_rows];
     for(int i=0; i<m_rows; i++){
         for( int j=0; j<m_cols; j++){
             if(j<col){
                (*this)(i,j)=cur(i,j);

             }
             else if(j==col){
                 (*this)(i,j)=0;
             }
             else if(j>col){
                 break;
             }

         }
     }
     for(int i=0; i<m_rows;i++){
         for(int j=col+1; j<m_cols;j++){
                (*this)(i,j)=cur(i,j-1);
         }
     }
    cur.~Matrix();


}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    if(col>=m_cols){
        throw std::out_of_range("index out of bounds");
    }
     Matrix<T> cur(*this);
     delete[] m_vec;
     m_cols=m_cols+1;
     m_vec=new T[m_cols*m_rows];
     for(int i=0; i<m_rows; i++){
         for( int j=0; j<m_cols; j++){
             if(j<col+1){
                (*this)(i,j)=cur(i,j);

             }
             else if(j==col+1){
                 (*this)(i,j)=0;
             }
             else if(j>col+1){
                 break;
             }

         }
     }
     for(int i=0; i<m_rows;i++){
         for(int j=col+2; j<m_cols;j++){
                (*this)(i,j)=cur(i,j-1);
         }
     }
    cur.~Matrix();

}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    if(col>=m_cols){
        throw std::out_of_range("index out of bounds");
    }
    Matrix<T> cur(*this);
     delete[] m_vec;
     m_cols=m_cols-1;
     m_vec=new T[m_cols*m_rows];
     for(int i=0; i<m_rows; i++){
         for( int j=0; j<m_cols+1; j++){
             if(i<col){
                (*this)(i,j)=cur(i,j);

             }
             else if(i>col){
                (*this)(i,j-1)=cur(i,j);

            }

         }
     }
    cur.~Matrix();

}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return m_vec;

}


template<typename T>
typename Matrix<T>::iterator Matrix<T>::end(){
    return m_vec+m_capacity;
}



template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
   for(int i=0; i<m.rows(); i++){
        for(int j=0; j<m.cols(); j++){
            is>>m(i,j);
        }

    }
return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    os<<"[";
    for(int i=0; i<m.rows(); i++){
        for(int j=0; j<m.cols(); j++){
            os<<m(i,j)<<" ";
        }
        if(i==m.rows()-1){
            os<<"]";
        }
        os << std::endl;
    }
    os<< "\n";
    return os;
}

template<typename T>
Matrix<T> identity(size_t dim) {
    Matrix<T> m(dim);
    for(int i=0; i<m.m_rows; i++){
        for(int j=0; j<m.m_cols; j++){
            if(j==i){
                m(i,j)=1;
            }
        }
}
    return m;

}

template <class T>
void Matrix<T>::set_element(unsigned int x, unsigned int y, T val) {
  if (x >= this->m_rows || y >= this->m_cols) {
    throw std::out_of_range("Index is out of range");
  }

  this->m_vec[x * this->m_cols + y] = val;
}

template <class T>
T Matrix<T>::get_element(unsigned int x, unsigned int y) {
  if (x >= this->m_rows || y >= this->m_cols) {
    throw std::out_of_range("index is out of range");
  }
  return this->m_vec[x * this->m_cols + y];
}
template <class T>
const T Matrix<T>::get_element(unsigned int x, unsigned int y) const{
  if (x >= this->m_rows || y >= this->m_cols) {
    throw std::out_of_range("index is out of range");
  }
  return this->m_vec[x * this->m_cols + y];
}


#endif //MATRIX_H
