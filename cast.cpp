#include <iostream>

class SuperClass {
public:
  int a = 10;
  // デストラクタは仮想関数にしておく
  virtual ~SuperClass() = default;
};
class SubClass: public SuperClass {
public:
  int b = 20;
};

int main(){
  /* アップキャスト(スーパークラスからサブクラスへのキャスト) */
  SubClass* sub1 = new SubClass();
  SuperClass* super1 = sub1;
  std::cout << "up cast: " << super1->a << std::endl;
  /* ダウンキャスト(サブクラスからスーパークラスへのキャスト) */
  /* あまり好ましくない( https://qiita.com/RYO-4947123/items/eaeb48b6fcf97c02710f ) */
  // サブクラスのインスタンス代入ではキャスト成功
  // スーパークラスのインスタンス代入ではキャスト失敗
  SuperClass* super2 = new SubClass();
  SubClass* sub2 = dynamic_cast<SubClass*>(super2); // 実行時キャスト
  if(sub2 != nullptr){
    std::cout << "down cast: " << sub2->b << std::endl;
  }else{
    std::cout << "down cast failed" << std::endl;
  }

  // const_castは、const属性を除去できる
  // 当然のごとく、まず使わないし、そうするべき
  const int c(30);
  std::cout << "c: " << c << std::endl;
  int& c_ptr = const_cast<int&>(c);
  c_ptr = 31;
  std::cout << "c_ptr: " << c_ptr << std::endl;

  // static_castは、型を変換できる
  // いわゆる通常のキャスト
  int d = 40;
  char d_char = static_cast<char>(d);
  std::cout << "d: " << d << std::endl;
  std::cout << "d_char: " << d_char << std::endl;

  return 0;
}


