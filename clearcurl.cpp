#include "clearcurl.h"

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

size_t clear_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	return size * nmemb;
}
