
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "logging.h"

void die(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputs("\n", stderr);
	va_end(ap);
	exit(1);
}

void error(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputs("\n", stderr);
	va_end(ap);
}

void info(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputs("\n", stderr);
	va_end(ap);
}

void wlog(const char *fmt, ...)
{
	FILE *file;
	file = fopen("erlua-node.log", "a+");
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	fputs("\n", file);
	va_end(ap);
	fclose(file);
}

void dlog(const char *fmt, ...)
{
	FILE *file;
	file = fopen("erlua-node.log", "a+");
	va_list ap;
	va_start(ap, fmt);
	vfprintf(file, fmt, ap);
	fputs("\n", file);
	va_end(ap);
	fclose(file);
	exit(1);
}
