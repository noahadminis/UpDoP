

char * utils_memcpy(char * dst_buffer, char * src_buffer, int a)
{
    char * dst = dst_buffer;
    char * src = src_buffer;

    while (a != 0)
    {
        *src++ = *dst++;
        a--;
    }
    
    return dst;
}