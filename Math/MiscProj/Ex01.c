#include <stdio.h>
void a() { printf("hello "); }
void b() { printf("world\n"); }
void main() {
	void (*f)(); 
	f=&a; 
        f();
  
	f=&b;
        f();
}
