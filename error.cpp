// 参考: https://rinatz.github.io/cpp-book/ch10-01-exceptions/

#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>
#include <vector>

class MyException : public std::runtime_error{
public:
  std::string message;
  uint32_t error_code;
  MyException(const std::string &message, uint32_t error_code) : std::runtime_error(message){
    this->message = message;
    this->error_code = error_code;
  }
};

class DestructorException{
public:
  DestructorException(void){
    std::cout << "DestructorException()" << std::endl;
  }
  ~DestructorException(void) noexcept(false) {
    std::cout << "~DestructorException()" << std::endl;
    throw std::runtime_error("DestructorException");
  }
};


// ただエラーを投げるだけの関数
void make_error(void){
  throw MyException("in make_error()", 3);
}

// エラーが発生しないことを明示的示す
void no_error1(void) noexcept(true) {
  std::cout << "no_error1()" << std::endl;
}
// noexcept(no_error1())はno_error1()がnoexceptであるかどうかを返す
// noexcept(noexcept(no_error1()))とすれば、その関数がnoexceptであるかでnoexceptかどうか変化する
void no_error2(void) noexcept(noexcept(no_error1())) {
  no_error1();
  std::cout << "no_error2()" << std::endl;
}

int main(){
  // 例外処理
  std::string str = "01234ABC89";
  try{
    for(const char &c : str){
      if(isdigit(c)){
        std::cout << c << std::endl;
      }else{
        // 例外を投げる
        throw std::runtime_error("非数字が含まれています");
      }
    }
  // 例外を受け取る
  }catch(std::runtime_error &e){
    std::cout << e.what() << std::endl;
  }

  // throwは任意の型を使用できる
  try{
    throw MyException("Hello, Error?", 1);
  // catchするのはthrowで投げた型
  }catch(MyException &e){
    std::cout << e.message << std::endl;
    std::cout << e.error_code << std::endl;
  // アップキャスト可能
  // 上から順にcatchされるため、この行は実行されない
  }catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }

  // catchの型を省略できる
  try{
    throw 2;
  }catch(...){
    std::cout << "エラーが発生しました" << std::endl;
  }

  // 関数内で発生したエラーもcatchできる
  try{
    make_error();
  }catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }

  // noexceptは、エラーが発生しないことを明示的に示す
  try{
    no_error2();
  }catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }

  // 組み込みの例外クラスのスーパークラスは、すべてstd::exception
  // そのため、std::exceptionをcatchすると、その他の組み込みの例外クラスもcatchできる

  // std::invalid_argument
  // 関数の引数が不正であるときのエラー
  try{
    std::bitset<8> bits("01010x01");
    std::cout << bits << std::endl;
  }catch(std::invalid_argument &e){
    std::cout << e.what() << std::endl;
  }
  // std::out_of_range
  // 配列外参照が発生したときのエラー
  // かなり便利そう、今後も使おう
  try{
    std::vector<int> vec(10);
    vec.at(10) = 10;
  }catch(std::out_of_range &e){
    std::cout << e.what() << std::endl;
  }
  // []でアクセスした場合はエラーキャッチできないらしい
  // おい！！！！
  try{
    std::vector<int> vec(10);
    vec[10] = 10;
  }catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }
  // std::runtime_error
  // 名のとおり、実行時エラー
  // std::bad_cast
  // dynamic_castが失敗したときのエラー

  // 例外搬送中に例外が発生するとどうにもならない
  // そのため、基本的にデクストラクタで例外を発生させないようにする
  try{
    DestructorException destructor_exception;
    throw std::runtime_error("");
  }catch(std::exception &e){
    std::cout << e.what() << std::endl;
  }


  std::cout << "finished!" << std::endl;


  return 0;
}