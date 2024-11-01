#include "../main.h"

int skip_spaces(char *str, int i)
{
    while (str[i] == 32)
        i++;
    return (i);
    
}

int calcul_words(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] != 32)
        {
            count++;
            while (str[i] && str[i] != 32 && str[i] != '\n')
                i++;
        }
        while (str[i] == 32)
            i++;
    }
    return (count);
}

int extract_len(char *str, int i)
{
    int len = 0;
    while (str[i] && str[i] != '\n' && str[i] != 32)
    {
        len++;
        i++;
    }
    return (len);
}

bool    check_characters(char *str)
{
    int i = 0;
    char *s = "10NSEW ";
    while (str[i] && str[i] != '\n')
    {
        if (!ft_strchr(s, str[i]))
            return (false);
        i++;
    }
    return (true);
    
}

bool    check_empty_line(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] != 32)
            return (false);
        i++;
    }
    return (true);
    
}

void    process_line(t_read *line_file)
{
    int i = 0;
    if (calcul_words(line_file->line) == 2)
    {
        i = skip_spaces(line_file->line, 0);
        if (!ft_strcmp("F", ft_substr(line_file->line, i, extract_len(line_file->line, i))))
            line_file->type = F;
        else if (!ft_strcmp("C", ft_substr(line_file->line, i, extract_len(line_file->line, i))))
            line_file->type = C;
        else if (!ft_strcmp("NO", ft_substr(line_file->line, i, extract_len(line_file->line, i))))
            line_file->type = NO;
        else if (!ft_strcmp("SO", ft_substr(line_file->line, i, extract_len(line_file->line, i))))
            line_file->type = SO;
        else if (!ft_strcmp("WE", ft_substr(line_file->line, i, extract_len(line_file->line, i))))
            line_file->type = WE;
        else if (!ft_strcmp("EA", ft_substr(line_file->line, i, extract_len(line_file->line, i))))
            line_file->type = EA;
    }
    if (check_empty_line(line_file->line))
        line_file->type = EMPTY;
    else if (check_characters(line_file->line))
        line_file->type = MAP;
}

void    token_data(t_read **file)
{
    t_read *curr = *file;
    while (curr)
    {
        process_line(curr);
        curr = curr->next;
    }
}