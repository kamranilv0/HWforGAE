#include <vector>

/** ************************************************************************************************
 * Matrix namespace
 * This namespace contains the Matrix class and various functions to perform operations on the matrix.
 * The namespace also contains various operator overloads to perform operations on the matrix.
 * This namespace also contains functions to create identity, zero and ones matrix.
 **************************************************************************************************/
namespace matrix {
template<typename T1>

/*! \brief Matrix class
 * This class is used to create a matrix of type T1.
 * The class has various functions to perform operations on the matrix.
 * The class also has various operator overloads to perform operations on the matrix.
 */
class Matrix {
private:
    std::vector<std::vector<T1>> mat; // Matrix of type T1 to store the elements
    std::vector<std::vector<T1>> matHelper; // Helper matrix for operations
    int col=0,row=0; // col = number of rows, row = number of columns

    /*! \brief Function to resize the matrix.
     * This function is used to resize the matrix.
     * @params void
     * @return void
     */
    void resize(){
        col = mat.size();
        (col) && (row = mat[0].size());
    }
public:

    /*! \brief Default constructor
     * This constructor initializes the matrix with a single element of 0.0 with row and column size of 1.
     * @return Matrix
     */
    Matrix(){
        mat = std::vector(1,std::vector(1,0.0));
        resize();
    }

    /*! \brief Constructor with vector of vector of type T1
     * This constructor initializes the matrix with a vector of vector of type T1.
     * @param a vector of vector of type T1
     * @return Matrix
     */
    Matrix(const std::vector<std::vector<T1>> a) : mat(a) {
        resize();
    }

    /*! \brief Constructor with vector of type T1
     * This constructor initializes the matrix with a vector of type T1. The axis parameter is used to determine the orientation of the matrix.
     * @param a vector of type T1
     * @return Matrix
     */
    Matrix(int axis ,const std::vector<T1> a ){
        if (axis){
            for (auto x:a){
                std::vector<T1> temp(1,x);
                mat.push_back(temp);
            }
        }
        else{
            mat.resize(1);
            for (auto x:a){
                mat[0].push_back(x);
            }
        }
        resize();
    }

    /*! \brief Constructor with size and value of type T1
     * This constructor initializes the matrix with a single element of type T1 with row and column size of size.
     * Every element of the matrix is initialized with the value of val.
     * @param size size of the matrix
     * @param val value of type T1
     * @return Matrix
     */
    Matrix(int size , T1 val = 0) : mat(std::vector(size, std::vector<T1>(size, val))) {
        resize();
    }

    /*! \brief Constructor with pair of size and value of type T1
     * This constructor initializes the matrix with a single element of type T1 with row of dimensions.first and column of dimensions.second.
     * Every element of the matrix is initialized with the value of val.
     * @param dimensions pair of size of the matrix
     * @param val value of type T1
     * @return Matrix
     */
    Matrix(const std::pair<int,int> dimensions, T1 val = 0) : mat(std::vector(dimensions.first, std::vector<T1>(dimensions.second, val))) {
        resize();
    }

    /*! \brief Function to get the size of the matrix.
     * @params void
     * @return pair of int
     */
    std::pair<int,int> getSize(){
        return std::make_pair(col,row);
    }

    /*! \brief Function to print the matrix.
     * @params void
     * @return void
     */
    void print(){
        for (int i=0;i<col;i++){
            for (int j=0;j<row;j++)
                std::cout<<mat[i][j]<<" ";
            std::cout<<std::endl;
        }
    }

    /*! \brief Function to set the value of the matrix at a specific index.
     * @params int i, int j, T1 val
     * @return void
     */
    void setData(int c,int r,T1 val){
        mat[c][r]=val;
    }

    /*! \brief Function to get the value of the matrix at a specific index.
     * @params int i, int j
     * @return T1
     */
    const T1 getData(int c,int r)const{
        return mat[c][r];
    }

    /*! \brief Function to calculate the determinant of the matrix.
     * @params void
     * @return T1
     */
    T1 determinant(){
        try {
            if (col!=row) throw std::runtime_error("not a square matrix");
            else if (col==0) throw std::runtime_error("not enough size");
        }catch (const std::exception& err){
            std::cout<<"Error: "<<err.what()<<std::endl;
            return 0;
        }
        if (!col) return 1;
        // 1X1
        if (col==1) return mat[0][0];
        T1 det=0;
        for (int i=0;i<row;i++){
            Matrix<T1> ms({col - 1, row - 1},0);
            for (int j=1;j<col;j++){
                int r=0;
                for (int k=0;k<row;k++){
                    if (k!=i){
                        ms.setData(j-1,r,mat[j][k]);
                        r++;}
                }
            }
            det+=(i%2==0?1:-1)*mat[0][i]*ms.determinant();
        }
        return det;
    }

    /*! \brief Function to calculate the transpose of the matrix.
     * @params void
     * @return Matrix
     */
    Matrix transpose() {
        int rows = col;
        int cols = row;
        std::vector<std::vector<T1>> result(cols, std::vector<T1>(rows));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[j][i] = mat[i][j];
            }
        }
        return Matrix(result);
    }

    /*! \brief Function to calculate the inverse of the matrix.
     * @params void
     * @return Matrix
     */
    Matrix inverse(){
        try {
            if (col!=row) throw std::runtime_error("not a square matrix");
            else if (col==0) throw std::runtime_error("not enough size");
        }catch (const std::exception& err){
            std::cout<<"Error: "<<err.what()<<std::endl;
            int x=0;
            return x;
        }
        T1 det=this->determinant();
        if (det==0) throw std::runtime_error("Non-Invertable matrix determinant equals to 0");
        double var=1.0/det;
        Matrix<double> x = this->adjoint();
        return x*var;
    }

    /*! \brief Function to calculate the trace of the matrix.
     * @params void
     * @return T1
     */
    T1 trace(){
        T1 tr=0;
        for(int i=0;i<((col<row)?col:row);i++){
            tr+=mat[i][i];
        }
        return tr;
    }

    /*! \brief Function to calculate the adjoint of the matrix.
     * @params void
     * @return Matrix
     */
    Matrix adjoint(){
        Matrix<double> x({col, row},0.0);
        for (int i=0;i<col;i++){
            for (int j=0;j<row;j++){
                Matrix m(col-1,row-1);
                int c=0,r;
                for (int a=0;a<col;a++){
                    r=0;
                    if (a!=i){
                        for (int b=0;b<row;b++){
                            if (b!=j){
                                m.setData(c,r,mat[a][b]);
                                r++;
                            }
                        }
                        a++;
                    }
                }
                x.setData(i,j,((i+j)%2==0?1:-1)*m.determinant());
            }
        }
        return x;
    }

    /*! \brief Function to add a matrix to the current matrix.
     * @params T1 x
     * @return Matrix
     */
    Matrix add(T1 x){
        for (int i=0;i<col;i++) {
            for (int j=0;j<col;j++){
                mat[i][j]+=x;
            }
        }
        return *this;
    }

    /*! \brief Function to subtract a matrix from the current matrix.
     * @params T1 x
     * @return Matrix
     */
    Matrix subtract(T1 x){
        for (int i=0;i<col;i++) {
            for (int j=0;j<col;j++){
                mat[i][j]-=x;
            }
        }
        return *this;
    }

    /*! \brief Function to convert matrix to negative of itself.
     * @params void
     * @return Matrix
     */
    Matrix neg(){
        for (int i=0;i<col;i++) {
            for (int j=0;j<row;j++){
                mat[i][j]=-mat[i][j];
            }
        }
        return *this;
    }

    /*! \brief Function to calculate magnitude of the matrix.
     * @params T1 x
     * @return Matrix
     */
    Matrix magnitude(T1 x){
        for (int i=0;i<col;i++) {
            for (int j=0;j<col;j++){
                mat[i][j]*=x;
            }
        }
        return *this;
    }

    /*! \brief Function to calculate the dot product of two matrices.
     * @params Matrix a
     * @return Matrix
     */
    T1 dot(const Matrix<T1> &a) const {
        if (col != a.col || row != a.row) {
            throw std::runtime_error("unsuitable dot product pairs");
        }

        T1 result = T1(0);
        for (int i = 0; i < col; ++i) {
            for (int j = 0; j < row; ++j) {
                result += mat[i][j] * a.getData(i, j);
            }
        }

        return result;
    }

    /*! \brief Function to calculate the cross product of two matrices.
     * @params Matrix a
     * @return Matrix
     */
    Matrix multiply(const Matrix<T1> &a) const {
        if (row != a.col) {
            throw std::runtime_error("unsuitable cross product pairs");
        }

        Matrix<T1> result({col, a.row}, T1(0));
        for (int i = 0; i < col; ++i) {
            for (int j = 0; j < a.row; ++j) {
                for (int k=0;k<row;k++){
                    result.setData(i, j, result.getData(i,j)+mat[i][k]*a.getData(k,j));
                }
            }
        }

        return result;
    }

    /*! \brief Function to calculate addition of two matrices.(pairwise addition
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * Matrix<double> matrix2({1,2,3},{4,5,6},{7,8,9});
     * (matrix+matrix2).print();
     * 2 4 6
     * 8 10 12
     * 14 16 18
     * @params Matrix c1, Matrix c2
     * @return Matrix
     */
    friend Matrix operator+(Matrix const& c1, Matrix const& c2)
    {
        if (c1.col==c2.col && c1.row==c1.row){
            Matrix x = c1,y=c2;
            for (int i=0;i<c1.col;i++){
                for (int j=0;j<c1.row;j++){
                    x.mat[i][j]+=y[i][j];
                }
            }
            return x;
        }
        throw std::runtime_error("non suitable matrix pair");
        return Matrix();
    }

    /*! \brief Function to calculate subtraction of two matrices.(pairwise subtraction)
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * Matrix<double> matrix2({1,2,3},{4,5,6},{7,8,9});
     * (matrix-matrix2).print();
     * 0 0 0
     * 0 0 0
     * 0 0 0
     * @params Matrix c1, Matrix c2
     * @return Matrix
     */
    friend Matrix operator-(Matrix const& c1, Matrix const& c2)
    {
        if (c1.col==c2.col && c1.row==c1.row){
            Matrix x = c1,y=c2;
            for (int i=0;i<c1.col;i++){
                for (int j=0;j<c1.row;j++){
                    x.mat[i][j]-=y[i][j];
                }
            }
            return x;
        }
        throw std::runtime_error("non suitable matrix pair");
        return Matrix();
    }

    /*! \brief Function to calculate multiplication of two matrices.(pairwise multiplication)
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * Matrix<double> matrix2({1,2,3},{4,5,6},{7,8,9});
     * (matrix*matrix2).print();
     * 1 4 9
     * 16 25 36
     * 49 64 81
     * @params Matrix c1, Matrix c2
     * @return Matrix
     */
    friend Matrix operator*(Matrix const& c1, Matrix const& c2)
    {
        if (c1.col==c2.col && c1.row==c1.row){
            Matrix x = c1 , y=c2 ;
            for (int i=0;i<c1.col;i++){
                for (int j=0;j<c1.row;j++){
                    x.mat[i][j]*=y.mat[i][j];
                }
            }
            return x;
        }
        throw std::runtime_error("non suitable matrix pair");
        return Matrix();
    }

    /*! \brief Function to calculate division of two matrices.(pairwise division)
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * Matrix<double> matrix2({1,2,3},{4,5,6},{7,8,9});
     * (matrix/matrix2).print();
     * 1 1 1
     * 1 1 1
     * 1 1 1
     * @params Matrix c1, Matrix c2
     * @return Matrix
     */
    friend Matrix operator/(Matrix const& c1, Matrix const& c2)
    {
        if (c1.col==c2.col && c1.row==c1.row){
            Matrix x = c1,y=c2;
            for (int i=0;i<c1.col;i++){
                for (int j=0;j<c1.row;j++){
                    x.mat[i][j]/=y[i][j];
                }
            }
            return x;
        }
        throw std::runtime_error("non suitable matrix pair");
        return Matrix();
    }

    /*! \brief Function to calculate addition of a matrix and a number.
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * (matrix+2).print();
     * 3 4 5
     * 6 7 8
     * 9 10 11
     * @params Matrix c1, T1 y
     * @return Matrix
     */
    friend Matrix operator+(Matrix const& c1, T1 y)
    {
            Matrix x = c1;
            for (int i=0;i<c1.col;i++){
                for (int j=0;j<c1.row;j++){
                    x.mat[i][j]+=y;
                }
            }
            return x;
    }

    /*! \brief Function to calculate subtraction of a matrix and a number.
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * (matrix-2).print();
     * -1 0 1
     * 2 3 4
     * 5 6 7
     * @params Matrix c1, T1 y
     * @return Matrix
     */
    friend Matrix operator-(Matrix const& c1, T1 y)
    {
            Matrix x = c1;
            for (int i=0;i<c1.col;i++){
                for (int j=0;j<c1.row;j++){
                    x.mat[i][j]-=y;
                }
            }
            return x;
    }

    /*! \brief Function to calculate multiplication of a matrix and a number.
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * (matrix*2).print();
     * 2 4 6
     * 8 10 12
     * 14 16 18
     * @params Matrix c1, T1 y
     * @return Matrix
     */
    friend Matrix operator*(Matrix const& c1, T1 y)
    {
        Matrix x = c1;
        for (int i=0;i<c1.col;i++){
            for (int j=0;j<c1.row;j++){
                x.mat[i][j]*=y;
            }
        }
        return x;
    }

    /*! \brief Function to calculate division of a matrix and a number.
     * Example:
     * Matrix<double> matrix({1,2,3},{4,5,6},{7,8,9});
     * (matrix/2).print();
     * 0.5 1 1.5
     * 2 2.5 3
     * 3.5 4 4.5
     * @params Matrix c1, T1 y
     * @return Matrix
     */
    friend Matrix operator/(Matrix const& c1, T1 y)
    {
        Matrix x = c1;
        for (int i=0;i<c1.col;i++){
            for (int j=0;j<c1.row;j++){
                x.mat[i][j]/=y;
            }
        }
        return x;
    }

    /*! \brief Operator overloading for ostream << operator.
     * Example:
     * Matrix<int> matrix({1,2,3},{4,5,6},{7,8,9});
     * std::cout<<matrix; <<--- this part
     * 1 2 3
     * 4 5 6
     * 7 8 9
     * @params ostream os, Matrix obj
     * @return ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& obj) {
        for (int i=0;i<obj.col;i++){
            for (int j = 0; j < obj.row; ++j) {
                os << obj.mat[i][j]<<" ";
            }
            os << std::endl;
        }
        return os;
    }

};

    /*! \brief Function to create an identity matrix of size.
     * Example: matrix::identity(4);
     * 1 0 0 0
     * 0 1 0 0
     * 0 0 1 0
     * 0 0 0 1
     * @params int size
     * @return Matrix
     */
    static Matrix<int> identity(int size){
        Matrix<int> x({size, size},0);
        for (int i=0;i<size;i++){
            x.setData(i,i,1);
        }
        return x;
    }

    /*! \brief Function to create a matrix of zeros of size.
     * Example: matrix::zeros(4);
     * 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * 0 0 0 0
     * @params int size
     * @return Matrix
     */
    static Matrix<int> zeros(int size){
        Matrix<int> x({size, size},0);
        return x;
    }

    /*! \brief Function to create a matrix of ones of size.
     * Example: matrix::ones(4);
     * 1 1 1 1
     * 1 1 1 1
     * 1 1 1 1
     * 1 1 1 1
     * @params int size
     * @return Matrix
     */
    static Matrix<int> ones(int size){
        Matrix<int> x({size, size},1);
        return x;
    }

}