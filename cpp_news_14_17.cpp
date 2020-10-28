//Compile: g++ cpp_news_14_17.cpp -o cpp_news_14_17 -std=c++14 -Wall -Wextra
//Compile: g++ cpp_news_14_17.cpp -o cpp_news_14_17 -std=c++1z -Wall -Wextra

#include <iostream>
#include <vector>
#include <map>
#include <memory> 		//unique_ptr, make_unique 
#include <chrono>		//unit-matching library
#include <algorithm> 	//sort function

using namespace std;
using namespace std::chrono;

void section(int i){
	cout << "**********************************SECTION " << i << "**********************************"  << endl;  
}

auto autofunc(){
	vector<int> x;
	
	return x;
}

constexpr int Fibonacci(int i){
	
	if(i == 0){
		return 0;
	}else if(i == 1){
		return 1;
	} else {
		return Fibonacci(i-1) + Fibonacci(i-2);
	}
	
}

void timePrint(milliseconds time){
	
	cout << time.count() << "ms" << endl;

} 

//Variable templates
template <typename T>
constexpr T value = T(200);

template <>
constexpr double value<double> = 150;

template <>
constexpr char value<char> = 'Z';

[[deprecated("Kral bunu kullanma başını ağrırtır")]]
void dontUseFunction(){
	cout << "Bu fonksyon bu versiyonda geçersiz" << endl;
}

template <typename T>
auto print(T const& s){
	if constexpr(is_integral<T>::value){
		return s;
	}else{
		return s.length();
	}	
}

class X{
public:
	X(){
		cout << "It is constructor" << endl;
	}
	
	~X(){
		cout << "It is destructor" << endl;
	}
	
	void use(){
		cout << "It is just function" << endl;
	}
	
private:
	int x;
	double y;
	
};

int main(){
	section(1);
	// c++14 ile sayıların görünümünü daha anlaşılabilir yapmak
	// için normal hayatta kullandığımız "," yerine "'" kullanılabimektedir.
	long int i = 1'000'000;
	long int k = 1'00'00'00;
	cout << "i = " << i << "\nk = " << k << endl;
	
	section(2);
	// C++14 ile binary ifadeler "0b" ile başlayarak ifade edilebilmektedir.
	auto bin = 0b010110;
	cout << "bin = " << bin << endl;
	
	section(3);
	// auto return tipi ile compiler return değişkenini otomatik olarak belirleyebilmektedir.
	vector<int> y;
	y = autofunc();
	
	section(4);
	// Normalde fonksiyonlar run timeda execute edilir. Ancak fonksiyona "constexpr" konulduğu 
	// zaman fonksiyon compile timeda execute edilir. Aşağıdaki "static_assert" ile bu tarzdaki
	// fonksiyonların compile timeda kontrolleri yapılabilmektedir. "constexpr" fonksiyonu
	// olmasaydı böyle bir kontrol yapılamazdı.
	static_assert(Fibonacci(7) == 13, "Equation Error");
	int fibonacci_out;
	fibonacci_out = Fibonacci(7);
	cout << fibonacci_out << endl;
	
	section(5);
	// Generic variable tanımlamak için globalde yapılan tarzda tanımlamalar yapılabilmektedir
	cout << "int value = " << value<int> << endl;
	cout << "int value = " << value<double> << endl;
	cout << "int value = " << value<char> << endl;
	
	section(6);
	// "deprecated" ile kullanılması istenmeyen fonksiyon kullanıldığı zaman warning fırlattırılır.
	// Böyle bir ihtiyaç versiyon güncellemelerde bir fonksiyon yerine başka bir fonksiyon 
	// kullanılacağı zaman oluşur.
//	dontUseFunction();
	
	section(7);
	// Normal bir şekilde tanımlanan değişkenler stack içerisinde adreslenir. Stack içerisinde 
	// işlem yapmak hızlıdır ancak bu alan sınırlıdır. Bu yüzden yüksek boyutlarda işlem 
	// yapılamamaktadır. Bunun için heap alanının kullanılması gerekmektedir. Heapde adreslenebilir
	// alan daha fazladır ancak daha yavaştır. Heapde değişken tutmak için new syntaxı kullanılır.
	// Bununla birlikte yer ayrıltılır, sonrasında bu ayrılan alanlarda işlemler yapılır. Kullanımı
	// sona erdiği zamanda da serbest bırakılır.
	int b{5};
	int * c = new int[4];
	c[1] = 2;
	cout << "b=" << b << endl;
	cout << *(c+1) << endl;
	delete [] c;
	c = nullptr;
	
	section(8);
	// C++da pointerlarla işlem yapılacağı zaman leak oluşmaması için destructor çağırmak unutulmamalıdır.
	// C++14 ile gelen Smart Pointer özelliğiyle destructor çağırma zorunluluğu ortadan kalkmıştır.
	// Bu özellik için "memory" kütüphanesi eklenmeli. "make_unique" ilede smart pointer oluşturulur.
	X *px = new X{};
	px->use();
	delete px;
	section(9);
	//auto spx = make_unique<X>();
	unique_ptr<X> spx = make_unique<X>();
	spx->use();
	//cout << typeid(spx).name() << endl;
	
	section(10);
	// Chrone kütüphanesi ile kullanılan zaman birimlerinde oluşan karmaşıklıklar önlenmiştir. Normalde
	// integer tipinde tutulduğunda kod içerisinde unit değişimi sırasında birçok hata ile karşılaşılabilmektedir.
	// Ancak bu kütüphane sayesinde farklı zaman tiplerinde değişkenler tanımlansa bile işlemin yapılacağı
	// yerde otomatik değişken tipi güncellemesi yapılmaktadır. Bu birim eşitleme işlemi compile timeda 
	// yapıldığı için performansta sıkıntı oluşturmamaktadır.
	//seconds time0 = 12;  Bu tarzda bir kullanım yapılmamaktadır.
	seconds time0{12};
	auto time1 = 10s;
	auto time2 = 20ms;
	auto time3 = time1 +time2;
	timePrint(time0);
	timePrint(time3);
	if(time0 > time3){
		cout << "Time0 daha büyük" << endl;
	} else{
		cout << "Tİme3 daha büyük" << endl;
	}
	
	section(10);
	// Lambda fonksiyonları ile fonksiyonu dışarda tanımlamadan kullanmak istediğimiz zaman
	// işe yaramaktadır. "[]" işareti lambda fonksiyonunun başladığını ifade etmektedir. C++14 ile
	// fonksiyon parametreleri auto seçilebilmektedir. Bu türdeki fonksitonlara generic veya polymorphic 
	// lambda denilmektedir.
	vector<int> seri{1,65,123,987,12,5,2,0,342};
	
	sort(begin(seri), end(seri),
	[](auto const& a, auto const& b){
		return a < b;
	});
	int vector_size = seri.size();
	for(int i=0; i<vector_size;i++){
		cout << seri[i] << " ";
	}
	cout << endl;
	
	section(11);
	// Lambda fonksiyonunda köşeli parantez içine bodysinde kullanılacak değerler pass edilebilir. 
	// Normal değişkenler comma seperate olarak yazıldığında sadece value passing gerçekleşir. Aktarılan değişkende
	// değişiklik olması için "&" işareti ile adresi iletilebilir. Ancak unique_ptr'ların adresleri kopyalanamadığı
	// için onların adresleri ancak başka bir adrese "move" fonksiyonuyla aktarılabilir. Ancak bu noktada da eski
	// adres değişgeni kullanılamaz.
	unique_ptr<int> degisgen = make_unique<int>(4);			//??? destructionı oluşmadı
	auto lambda_function = [ptr=move(degisgen)]{
		cout << "X değeri =" << *ptr << endl;
	};
	lambda_function();
	//cout << "X değeri =" << *degisgen << endl;
	
	section(11);
	// c++17 ile birlikte if statementlarına özel variable declaration özelliği gelmiştir. Bu sayede aynı isimde farklı if
	// statementlarında aynı değişken ismiyle değişken tanımlanabilmekte ve daha temiz bir görüntü oluşturmaktadır. Tanımlanan
	// variable yapı elselerle devem ettirilirse de onların içinde de kullanılabilir.
	if(const auto it = find(begin(seri), end(seri), 123); it != end(seri)){
		*it = -1;
	}
	if(const auto it = find(begin(seri), end(seri), 342); it != end(seri)){
		*it = -2;
	}
	for(int i=0; i<vector_size;i++){
		cout << seri[i] << " ";
	}
	cout << endl;
	
	section(11);
	// c++17 ile birlikte if statementa "constexpr" eklentisi gelmiştir. Bununla birlikte if argümanı generic olduğu zaman farklı
	// tiplerde return typelı koşullar girilebilmektedir.
	int int1 = 14;
	string str1 = "Yusuf Reis";
	cout << print(int1) << endl;
	cout << print(str1) << endl;
	
	section(12);
	// c++17 ile birlikte Structured Binding özelliği gelmiştir. Bu özellik sayesinde birden fazla output dönen ifadeler "[]" ile
	// birden çok değişkene işaretlenebilir. Yine bu özellikle birlikte map'in içinde 2'li iterator dolaştırılabilir.
	map<string, string> sozluk{
		{"Yusuf", "Ozben"},
		{"Itu", "Koridor"}
	};
	auto [position, success] = sozluk.insert({"Osman", "Kostak"}); 	//std:pair dönüyor. İlk ifade iteratorın yerini ikinci ifade ekleme yapılıp yapılamadığını yazıyor.
	cout << success << endl;
	
	for(auto const& [isim, soyisim] : sozluk){  //const sayesinde compilerin for döngüsü içerisinde gereksiz kopyalamalar yapması engellenir
		cout << "name: " << isim << "  surname: " << soyisim << endl; 
	}
	
	section(13);
	//c++17 ile Nested Namespace özelliği gelmiştir. Bu özellikle birlikte iç içe yazılan namespace'ler :: olarak yan yana ifade edilebilmekte
	
	cout << "**********************************Kodun sonu**********************************" << endl;
}


