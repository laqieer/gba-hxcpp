#ifndef DLFCN_H
#define DLFCN_H

#ifdef __cplusplus  
extern "C" {  
#endif 

// Copied from: https://opensource.apple.com/source/dyld/dyld-519.2.2/include/dlfcn.h.auto.html

#define RTLD_LAZY	0x1
#define RTLD_NOW	0x2
#define RTLD_LOCAL	0x4
#define RTLD_GLOBAL	0x8

#define RTLD_NOLOAD	0x10
#define RTLD_NODELETE	0x80
#define RTLD_FIRST	0x100

int dlclose(void * __handle);
char * dlerror(void);
void * dlopen(const char * __path, int __mode);
void * dlsym(void * __handle, const char * __symbol);

#ifdef __cplusplus  
}  
#endif  

#endif
