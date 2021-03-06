#include <objc/runtime.h>
#include <objc/objc-runtime.h>
#include <stdio.h>
#include <dlfcn.h>

static void pyobjc_internal_init() {
	static void *foundation = NULL;
	if ( foundation == NULL ) {
		foundation = dlopen(
			"/System/Library/Frameworks/Foundation.framework/Versions/Current/Foundation", RTLD_LAZY);
		if ( foundation == NULL ) {
			printf("Got dlopen error on Foundation\n");
			return;
		}
	}
}

id allocAndInitAutoreleasePool() {
  Class NSAutoreleasePoolClass = objc_getClass("NSAutoreleasePool");
  id pool = class_createInstance(NSAutoreleasePoolClass, 0);
  return objc_msgSend(pool, sel_registerName("init"));
}

void drainAutoreleasePool(id pool) {
  (void)objc_msgSend(pool, sel_registerName("drain"));
}
