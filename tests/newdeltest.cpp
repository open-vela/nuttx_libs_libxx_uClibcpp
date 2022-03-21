#include <new>
#include <memory>
#include <cstdio>

struct test{
	int a;
	float b;
};

class base {
protected:
	int a;

public:
	base() : a(0){
		printf("Executing default base class constructor. a: %i\n", a);
	}

	virtual ~base(){
		printf("Executing base class destructor\n");
	}

	virtual void print(){
		printf("Base class print function with a=%i\n", a);
	}

};

class sub : public base{
protected:
	float f;
public:
	sub() : f(0){
		printf("Executing default sub class constructor. a: %i, f: %f\n", base::a, f);
	}
	virtual ~sub(){
		printf("Executing sub class destructor\n");
	}

	virtual void print(){
		printf("Sub class print function with a=%i and f=%f\n", a, f);
	}

};


extern "C" int main(){
	test * temp = new test;
	temp->a = 5;
	delete temp;
	temp = 0;

	test *temp_1 = new test[25];
	delete [] temp_1;
	temp_1 = 0;

	base * b_0 = new base;
	b_0->print();
	delete b_0;
	b_0=0;

	base *b_1 = new base[3];
	for(int i = 0; i < 3; ++i){
		b_1[i].print();
	}
	delete [] b_1;
	b_1 = 0;

	base *b_3 = new sub;
	b_3->print();
	delete b_3;
	b_3 = 0;

	//We can only create one because we can't step through the array properly
	base *b_4 = new sub[1];
	b_4[0].print();
	delete [] b_4;
	b_4 = 0;

	printf("Testing nothrow new\n");

	base *b = new(std::nothrow) base;

	printf("Checking allocator\n");
	std::allocator<base> al;
	b = al.allocate(1);
	al.construct(b, base());
	b->print();
	al.destroy(b);
	al.deallocate(b, 1);
	b = 0;

	return 0;
}
