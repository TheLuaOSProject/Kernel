#include "lj-libc/limits.h"
#include "common.h"
#include "luck/io/log.h"
#include "luck/memory/manager.h"
#include "memory.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

double acos(double x) { panic("todo: acos"); }
double asin(double x) { panic("todo: asin"); }
double atan(double x) { panic("todo: atan"); }
double atan2(double y, double x) { panic("todo: atan2"); }
double cos(double x) { panic("todo: cos"); }
double cosh(double x) { panic("todo: cosh"); }
double exp(double x) { panic("todo: exp"); }
double log(double x) { panic("todo: log10"); }
double log10(double x) { panic("todo: log10"); }
double log2(double x) { panic("todo: log2"); }
double sin(double x) { panic("todo: sin"); }
double sinh(double x) { panic("todo: sinh"); }
double tan(double x) { panic("todo: tan"); }
double tanh(double x) { panic("todo: tanh"); }
double frexp(double value, int *exp) { panic("todo: frexp"); }

double fmod(double x, double y) { panic("todo: fmod"); }
double ldexp(double x, int y) { panic("todo: ldexp"); }
double modf(double x, double* y) { panic("todo: modf"); }
double pow(double x, double y) { panic("todo: pow"); }

void fclose() {panic("todo:fclose");}
void feof() {panic("todo:feof");}
void ferror() {panic("todo:ferror");}
void fopen() {panic("todo:fopen");}
void fputs() {panic("todo:fputs");}
void fputc() {panic("todo:fputc");}
void fread() {panic("todo:fread");}
void fflush() {panic("todo:fflush");}
void fgets() {panic("todo:fgets");}
// void strncpy() {panic("todo:strncpy");}
void strerror() {panic("todo:strerror");}
void strtoul() {panic("todo:strtoul");}

PCB* _get_pcb() { static PCB pcb; return &pcb; }

void realloc() {panic("todo:realloc");}
void free() {panic("todo:free");}

[[noreturn]] void exit(int code){panic("exit");}

size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream) {
	if (!stream) panic("null stream pointer?");
	if (!stream->write) panic("write to nonwriteable file");
	stream->write(ptr, (int)(size * nitems));
	return (int)(size * nitems);
}
void putchar(char c) {
	fwrite(&c, 1, 1, stdout);
}

void *ljsup_alloc(void *ud, void *ptr, size_t osize, size_t nsize) {
	void* nptr = kalloc(nsize);
	if (osize < nsize) memory_copy(nptr, ptr, osize);
	else memory_copy(nptr, ptr, nsize);
	if (ptr) kfree(ptr, osize);
	return nptr;
}

void *memchr(const void *s, byte c, size_t n)
{
    const byte *bytes = (const byte*)s;
    for (size_t i = 0; i < n; i++) {
        if (*(bytes + i) == c)
            return (void*)(bytes + i);
    }
    return NULL;
}

void *memrchr(const void *s, byte c, size_t n)
{
    const byte *bytes = (const byte*)s;
    for (size_t i = n - 1; i < n; i--) {
        if (*(bytes + i) == c)
            return (void*)(bytes + i);
    }
    return NULL;
}
