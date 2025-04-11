#include "header.h"

int	getLen(const char* str)
{
	int len = 0;

	for (int i = 0; str[i] != '\0'; i++)
		len++;

	return (len);
}

bool	isSame(const char* str1, const char* str2)
{
	if (getLen(str1) != getLen(str2))
		return (false);

	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return (false);
	}

	return (true);
}

void	writeStr(const char* str, const int fd)
{
	for (int i = 0; str[i] != '\0'; i++)
		write(fd, &str[i], 1);
}

time_t	getTime(void)
{
	struct timeval	time;
	time_t			value;

	gettimeofday(&time, NULL);
	value = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	return (value);
}

int		getRandomNumber(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	return (rand());
}
