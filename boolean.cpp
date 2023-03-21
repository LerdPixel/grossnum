int GROSSNUM:: operator >(GROSSNUM &x) //сравнение
{
    if(this->l>x.l)
        return 1;  // больше более длинное
    if(this->l==x.l) //если длины равны
    {
        this->reverse(); //цифры в прямом порядке
        x.reverse();
        if (strcmp(this->num,x.num)>0) //сравнили
        {
            this->reverse(); // вернули цифры
            x.reverse();
            return 1;
        }
    }
    return 0;
}
int GROSSNUM:: operator <(GROSSNUM &x) //сравнение
{
    if(this->l<x.l)
        return 1;  // больше более длинное
    if(this->l==x.l) //если длины равны
    {
        this->reverse(); //цифры в прямом порядке
        x.reverse();
        if (strcmp(this->num,x.num)<0) //сравнили
        {
            this->reverse(); // вернули цифры
            x.reverse();
            return 1;
        }
    }
    return 0;
}
int GROSSNUM:: operator >=(GROSSNUM &x) //сравнение
{
    if(this->l>x.l)
        return 1;  // больше более длинное
    if(this->l==x.l) //если длины равны
    {
        this->reverse(); //цифры в прямом порядке
        x.reverse();
        if (strcmp(this->num,x.num)>=0) //сравнили
        {
            this->reverse(); // вернули цифры
            x.reverse();
            return 1;
        }
    }
    return 0;
}
int GROSSNUM:: operator <=(GROSSNUM &x) //сравнение
{
    if(this->l<x.l)
        return 1;  // больше более длинное
    if(this->l==x.l) //если длины равны
    {
        this->reverse(); //цифры в прямом порядке
        x.reverse();
        if (strcmp(this->num,x.num)<=0) //сравнили
        {
            this->reverse(); // вернули цифры
            x.reverse();
            return 1;
        }
    }
    return 0;
}
int GROSSNUM:: operator ==(GROSSNUM &x) //сравнение
{
    if(this->l==x.l) //если длины равны
    {
        this->reverse(); //цифры в прямом порядке
        x.reverse();
        if (strcmp(this->num,x.num)==0) //сравнили
        {
            this->reverse(); // вернули цифры
            x.reverse();
            return 1;
        }
    }
    return 0;
}
