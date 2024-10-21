#include "../main.h"

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


t_read  *read_file(char *av)
{
    char *line;
    int fd;
    t_read  *read = NULL;

    fd = open(av, O_RDONLY);
    if (fd == -1)
        ft_show_error("File not found!\n");    
    line = get_next_line(fd);
    while (line)
    {
        insert_t_read(&read, ft_strdup(line));
        free(line);
        line = get_next_line(fd);
    }
    return (read);
}



int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s1[i] == s2[i])
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

void    init_data(t_data *data)
{
    data->c1 = -1;
    data->c2 = -1;
    data->c3 = -1;
    data->f1 = -1;
    data->f2 = -1;
    data->f3 = -1;
    data->north_path = NULL;
    data->south_path = NULL;
    data->east_path = NULL;
    data->west_path = NULL;
}

int extract_len_first_word(char *s, int i)
{
    int j = 0;
    while (s[i] && s[i] != 32 && s[i] != '\n')
    {
        i++;
        j++;
    }
    return (j);
}

int skip_spaces(char *s, int i)
{
    while (s[i] == 32)
        i++;
    return (i);
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