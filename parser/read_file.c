#include "../main.h"

void    insert_t_read(t_read **file, char *str)
{
    t_read *new = malloc(sizeof(t_read));
    if (!new)
        exit (EXIT_FAILURE);
    new->line = str;
    new->type = INIT;
    new->next = NULL;
    if (!(*file))
    {
        *file = new;
        return ;
    }
    t_read *curr = *file;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
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
