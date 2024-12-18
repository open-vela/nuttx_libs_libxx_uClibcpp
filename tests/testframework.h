#include <exception>
#include <cstdio>
#include <typeinfo>

namespace TestFramework{
	extern unsigned long int goodcount;
	extern unsigned long int badcount;
	extern unsigned long int totalcount;

	unsigned long int getTotalTests();
	unsigned long int getBadTests();
	unsigned long int getGoodTests();

	void init();
	void results();

	// The following functions take a pointer to a function return type T and compare
	// it to the specified value.  If this is true then the goodcount is increased.
	template <typename T> void AssertReturns(T (*f)(), const T val){
		++totalcount;
		printf(".");
		T retval;
#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__
		try{
#endif
			retval = f();
			if( val == retval){
				++goodcount;
			}else{
				printf("(%lu)", totalcount);
				++badcount;
			}
#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__
		}
		catch (...) {
			printf("(e%lu)", totalcount);
			++badcount;
		}
#endif
	}

	template <typename T> void AssertThrows( void (*f)()){
#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__
		++totalcount;
		printf(".");
		try {
			f();
			//No exception thrown - something unexpected happened
			printf("N %lu", totalcount);
			++badcount;
		}
		catch (const T & e) {
			++goodcount;
		}
		catch (...) {
			printf("(e %lu)", totalcount);
			//Caught the wrong type of exception
			++badcount;
		}
#endif
	}


}



