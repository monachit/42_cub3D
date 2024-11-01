#include "../main.h"

int calcul_token(t_read *file, t_type type)
{
    int count = 0;
    while (file)
    {
        if (file->type == type)
            count++;        
        file = file->next;
    }
    return (count);
}

bool    check_all(t_read *file)
{
    while (file)
    {
        if (file->type == INIT)
            return (false);
        file = file->next;
    }
    return (true);
}

bool    check_map_last(t_read *file)
{
    while (file)
    {
        if (file->type == MAP)
        {
            while (file && file->type == MAP)
                file = file->next;
            while (file && file->type == EMPTY)
                file = file->next;
            break;
        }
        file = file->next;
    }
    return (file ? false : true);
    
}

bool    check_order(t_read *file)
{
    if (!check_all(file) || calcul_token(file, NO) != 1 || calcul_token(file, SO) != 1
        || calcul_token(file, WE) != 1 || calcul_token(file, EA) != 1 
        || calcul_token(file, F) != 1 || calcul_token(file, C) != 1 
        || calcul_token(file, MAP) < 3 || !check_map_last(file))
        return (false);
    else
        return (true);
}