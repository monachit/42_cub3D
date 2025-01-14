#include "../main.h"

int ft_strlen_lhbal(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    return(i);
}

bool    check_player(char **ss)
{
    char *player = "NSWE";
    int i = 0;
    int count = 0;
    while (ss[i])
    {
        int j = 0;
        while (ss[i][j])
        {
            if (ft_strchr(player, ss[i][j]))
                count++;
            j++;
        }
        i++;
    }
    return (count == 1 ? true : false);
}

bool    parse_map(char **map)
{
    char *c = "0NSWE";
    int i = 0;
    while (map[i])
    {
        int j = 0;
        while (map[i][j])
        {
            if (ft_strchr(c, map[i][j]))
            {
                if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
                    return (false);
                if (map[i][j + 1] == 32 || map[i][j - 1] == 32 || map[i + 1][j] == 32
                    || map[i - 1][j] == 32 || !map[i][j + 1] || !map[i][j - 1] 
                    || !map[i + 1][j] || !map[i - 1][j])
                    return (false);
            }
            j++;
        }
        i++;
    }
    return (true);
}

char    **extract_map(t_read *file, int len)
{
    char **strs = (char **)malloc(sizeof(char *) * (len + 1));
    if (!strs)
        exit (EXIT_FAILURE);
    int i = 0;
    while (file)
    {
        if (file->type == MAP)
        {
            while (file && file->type == MAP)
            {
                char *tmp = ft_substr(file->line, 0, ft_strlen_lhbal(file->line));
                strs[i] = ft_strdup(tmp);
                file = file->next;
                free(tmp);
                i++;
            }
            strs[i] = NULL;
            break;
        }
        file = file->next;
    }
    if (!check_player(strs) || !parse_map(strs))
    {
        i = 0;
        while (strs[i])
            free(strs[i++]);
        free(strs);
        return (NULL);
    }
    return (strs);    
}
