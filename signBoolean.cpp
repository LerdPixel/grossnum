int SGN::compare_modules(const SGN &x) const
{
    if (l > x.l)
        return 1;  // больше более длинное

    if (l == x.l) //если длины равны
        for (const char* a = num + l - 1, *b = x.num + l - 1; a >= num; --a, --b)
        {
            if (*a > *b)
                return 1;
            else if (*b > *a)
                return 0;
        }
    return 0;
}
int SGN::operator > (const SGN &x) const
{
    if (this->sign==0) //если первое положительно
    {
        if(x.sign==0) //и второе тоже
            return compare_modules(x); //большее, то //которое имеет больший модуль
        else //если второе отрицательно
            return 1; //то заведомо больше первое
    }       // если же первое отрицательно
    if(x.sign==1) //и второе тоже
    {
    	//больше то, что короче
        if(this->l>x.l)
            return 0;
        if(this->l<x.l)
            return 1;
    //если длины равны
        for (const char* a = num + l - 1, *b = x.num + l - 1; a >= num; --a, --b)
        {
            if (*a > *b)
                return 0;
            else if (*b > *a)
                return 1;
        }
    }
    return 0; //а если второе положительно, то оно //заведомо больше
}
int SGN::operator < (const SGN &x) const
{
    if (this->sign==1) //если первое отрицательно
    {
        if(x.sign==1) //и второе тоже
        {
            return compare_modules(x); //меньше, то //которое имеет больший модуль
        }
        else //если второе положительно
            return 1; //то заведомо меньше первое
    }       // если же первое положительно
    if(x.sign==0) //и второе тоже
    {
    	//больше то, что короче
        if(this->l>x.l)
            return 0;
        if(this->l<x.l)
            return 1;
    //если длины равны
        for (const char* a = num + l - 1, *b = x.num + l - 1; a >= num; --a, --b)
        {
            if (*a > *b)
                return 0;
            else if (*b > *a)
                return 1;
        }
    }
    return 0; //а если второе отрицательно, то оно //заведомо меньше
}
int SGN::operator <= (const SGN &x) const
{
    return !(*this > x);
}
int SGN::operator >= (const SGN &x) const
{
    return !(*this < x);
}
int SGN::operator == (const SGN &x) const
{
    if(this->sign == x.sign && strcmp(this->num, x.num) == 0)
        return 1;
    return 0;
}
int SGN::operator != (const SGN &x) const
{
    return !(*this == x)
}
