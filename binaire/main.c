#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_memalloc(size_t size)
{
	void *ptr;

	if (!(ptr = malloc(size)))
	{
		write(2, "Malloc error.\n", 14);
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

char	*concatstr(uint32_t *h)
{
	return (NULL);
}

static int		rotate(uint32_t a, uint32_t b)
{
	return ((a << b) | (a >> (32-b)));
}

static void	hash3(uint32_t *str, unsigned int *a, uint32_t *k, int *s)
{
	int i;
	uint32_t f;
	uint32_t g;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			f = (a[1] & a[2]) | ((~a[1]) & a[3]);
			g = i;
		}
		else if (i < 32)
		{
			f = (a[3] & a[1]) | ((~a[3]) & a[2]);
			g = (5*i + 1) % 16;
		}
		else if (i < 48)
		{
			f = a[1] ^ a[2] ^ a[3];
			g = (3*i + 5) % 16;
		}
		else
		{
			f = a[2] ^ (a[1] | (~a[3]));
			g = (7*i) % 16;
		}
		f = f + a[0] + k[i] + str[g];
		a[0] = a[3];
		a[3] = a[2];
		a[2] = a[1];
		a[1] = a[1] + rotate(f, s[i]);
		i++;
	}
	return ;
}

char *hash2(int s[64], uint32_t k[64], char *str, int size)
{
	uint32_t a[4];
	uint32_t h[4];
	int i;

	i = 0;
	h[0] = 1732584193;
	h[1] = 4023233417;
	h[2] = 2562383102;
	h[3] = 271733878;
	while (i < size)
	{
		a[0] = h[0];
		a[1] = h[1];
		a[2] = h[2];
		a[3] = h[3];
		hash3((uint32_t*)(&(str[i*64])), a, k, s);
		h[0] += a[0];
		h[1] += a[1];
		h[2] += a[2];
		h[3] += a[3];
		i++;
	}
	printf("%u %u %u %u\n", h[0], h[1], h[2], h[3]);
	return (concatstr(h));
}

char	*hash1(char *str, int size)
{
	int s[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 
		22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 
		4, 11, 16, 23, 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 6, 10, 
		15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	uint32_t k[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 
		0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 
		0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 
		0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 
		0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 
		0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 
		0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 
		0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 
		0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 
		0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 
		0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
	
	return (hash2(s, k , str, size / 64));
}

char	*prepare(char *str, int *size)
{
	int len;
	uint64_t index;
	char *str2;

	index = strlen(str);
	len = strlen(str);
	str[len++] = -128;
	while (len % 64 != 56)
		len++;
	str2 = ft_memalloc(len + 8);
	strncpy(str2, str, index + 1);
	index = index * 8;
	memcpy(&(str2[len]), &index, 8);
	*size = len + 8;
	return (str2);
}

int		main(int ac, char **av)
{
	ac = 1;
	int size;
	char *str;

	str = av[1];
	size = 0;
	
	str = prepare(str, &size);
	printf("%s\n", str);
	str = hash1(str, size);
	return (0);
}
