#include "../main.h"

void    ft_show_error(char *str)
{
    write(2, "Error\n", 6);
    write(2, str, ft_strlen(str));
    exit (1);
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s1[i] == s2[i])
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

int	ft_atoi_lhbal(char *str)
{
	int	i;
	int	res;
	int	prev;

	i = 0;
	res = 0;
	prev = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = res;
		res = res * 10 + str[i] - 48;
		if (prev != res / 10)
			return (-1);
		i++;
	}
	return (res);
}

int check_name(char *name)
{
    int i;

    i = 0;
    while (name[i])
    {
        if (name[i] == '.')
        {
            if (name[i + 1] == 'c' && name[i + 2] == 'u' && name[i + 3] == 'b' && name[i + 4] == '\0')
                return (0);
            else
                return (1);
        }
        i++;
    }
    return (1);
}