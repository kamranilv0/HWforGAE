#include <vector>

namespace matrix {
template<typename T1>
class Matrix {
private:
    std::vector<std::vector<T1>> mat;
    std::vector<std::vector<T1>> matHelper;
    int col=0,row=0;
    void resize(){
        col = mat.size();
        (col) && (row = mat[0].size());

    }
public:

    Matrix(){
        mat = std::vector(1,std::vector(1,0.0));
        resize();
    }

    Matrix(const std::vector<std::vector<T1>> a) : mat(a) {
        resize();
    }


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

    Matrix(int size , T1 val = 0) : mat(std::vector(size, std::vector<T1>(size, val))) {
        resize();
    }

    Matrix(const std::pair<int,int> dimensions, T1 val = 0) : mat(std::vector(dimensions.first, std::vector<T1>(dimensions.second, val))) {
        resize();
    }

    std::pair<int,int> getSize(){
        return std::make_pair(col,row);
    }

    void print(){
        for (int i=0;i<col;i++){
            for (int j=0;j<row;j++)
                std::cout<<mat[i][j]<<" ";
            std::cout<<std::endl;
        }
    }

    void setData(int c,int r,T1 val){
        mat[c][r]=val;
    }
    const T1 getData(int c,int r)const{
        return mat[c][r];
    }

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

    Matrix identity(){
        Matrix x({col, row},0);
        for (int i=0;i<((col<row)?col:row);i++){
            x.setData(i,i,1);
        }
        this->mat=x.mat;
        return *this;
    }

    T1 trace(){
        T1 tr=0;
        for(int i=0;i<((col<row)?col:row);i++){
            tr+=mat[i][i];
        }
        return tr;
    }

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

    Matrix add(T1 x){
        for (int i=0;i<col;i++) {
            for (int j=0;j<col;j++){
                mat[i][j]+=x;
            }
        }
        return *this;
    }

    Matrix subtract(T1 x){
        for (int i=0;i<col;i++) {
            for (int j=0;j<col;j++){
                mat[i][j]-=x;
            }
        }
        return *this;
    }

    Matrix neg(){
        for (int i=0;i<col;i++) {
            for (int j=0;j<row;j++){
                mat[i][j]=-mat[i][j];
            }
        }
        return *this;
    }

    Matrix magnitude(T1 x){
        for (int i=0;i<col;i++) {
            for (int j=0;j<col;j++){
                mat[i][j]*=x;
            }
        }
        return *this;
    }

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

    friend Matrix operator*(Matrix const& c1, Matrix const& c2)
    {
        if (c1.col==c2.col && c1.row==c1.row){
            Matrix x = c1,y=c2;
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




};

}