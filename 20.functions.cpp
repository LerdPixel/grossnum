void SGN:: print()
{
    reverse(); // переворот num для вывода
    if (this->sign) // если отрицательно, вывод с мунусом
        printf("-%s\n", this->num);
    else   // а при положительном вывод как обычно
        printf("%s\n", this->num);
    reverse(); // обратно
}
SGN  operator + (SGN &x, SGN& y) // складывает два больших числа со знаком
{
    SGN t;  //результат
    if(x.sign==PLUS)    //x>0
    {
        if(y.sign==PLUS) //y>0
        {
            t = x.add_modules(y); //+(|x|+|y|)
            t.sign = PLUS;
         }
        else //x>0&&y<0
        {
            if(x.compare_modules(y)) //|x|>|y|
            {
                t=x.sub_modules(y); //t=+(|x|-|y|)
                t.sign=PLUS;
            }
            else //|y|>|x|
            {
                t=y.sub_modules(x);//t=-(|y|-|x|)
                t.sign=MINUS;
            }
        }
    }
    else
    {
        if(y.sign==MINUS)    //x<0&&y<0
        {
            t=x.add_modules(y);  //t=-(|x|+|y|)
            t.sign=MINUS;
        }
        else //x<0 && y>0
        {
            if(y.compare_modules(x))//|y|>|x|
            {
                t=y.sub_modules(x); //t=+(|y|-|x|)
                t.sign=PLUS;
            }
            else //|y|<|x|
            {
                t=x.sub_modules(y);//t=-(|x|-|y|)
                t.sign=MINUS;
            }
        }
    }
    return t;
}
/* вычитает два больших числа
 * здесь сосредоточена вся логика*/
SGN  operator - (SGN &x, SGN& y)
{
    SGN t;
    if (x == y) {                            //если равны, вернуть положительный нуль
        t.num[0] = '0';
        t.num[1] = 0;
        t.l = 1;                 // c длиной 1
        t.sign = 0;
    }
    else if(x.sign==PLUS)    //x>0
    {
        if(y.sign==PLUS) //y>0
        {
            if(x.compare_modules(y)) //|x|>|y|
            {
                t=x.sub_modules(y); //t=+(|x|-|y|)
                t.sign=PLUS;
            }
            else //|y|>|x|
            {
                t=y.sub_modules(x);//t=-(|y|-|x|)
                t.sign=MINUS;
            }
         }
        else //x>0&&y<0
        {
            t=x.add_modules(y); //t=+(|x|+|y|)
            t.sign=PLUS;
        }
    }
    else
    {
        if(y.sign==MINUS)    //x<0&&y<0
        {
            if(y.compare_modules(x))//|y|>|x|
            {
                t=y.sub_modules(x); //t=+(|y|-|x|)
                t.sign=PLUS;
            }
            else //|y|<|x|
            {
                t=x.sub_modules(y);//t=-(|x|-|y|)
                t.sign=MINUS;
            }
        }
        else //x<0 && y>0
        {
            t=x.add_modules(y);  //t=-(|x|+|y|)
            t.sign=MINUS;
        }
    }
    return t;
}
SGN SGN::add_modules(SGN &x)
{
    int n //миниимум фактических длин складываемых
       ,i;
    SGN z;
    n=(this->l)>x.l?x.l:(this->l); //нахожу более короткую строку
    for(i = 0; i < n; ++i) //складываю части, совпадающие по //длине
        z.num[i] = sum_digits(this->num[i],x.num[i]);
    if(n == this->l) //если короче первое слагаемое
        for(; i < x.l; ++i) //то работаем со вторым (с  //учетом флага переноса)
            z.num[i] = sum_digits(x.num[i], '0');
    else if(n == x.l) //если второе
        for(; i < this->l;++i) //то работаем с первым
            z.num[i]=sum_digits(this->num[i], '0');
    if ((i==N-1)&&(flag==1)) //отрабатываем случай возможного переполнения
    {
        puts("number owerfull!");
//        exit(1);
    }
// когда достигнут конец более длинного числа отрабатываем установленный флаг переноса
    if(flag)
    {
        z.num[i]='1'; //учитываю флаг (если он //установлен)
        z.num[i+1]=0;
    }
    else
       z.num[i]=0; //иначе просто закрываю строку
    return z;
}
SGN SGN::sub_modules(SGN &x)
{
    SGN t;
    int i;
    for (i=0;i<x.l;++i)
        t.num[i]=sub_digit(this->num[i],x.num[i]);
    for(;i<this->l;++i)
        t.num[i]=sub_digit(this->num[i],'0');
    t.num[i]=0;
    for (; (i > 1) && (t.num[i-1] == '0'); --i) // проверка на первые нули и их удаление
            t.num[i-1] = 0;
    t.l = i;
    t.flag=0;
    return t;
}
int SGN::compare_modules(const SGN &x) const
{
    if (l > x.l)
        return 1;  // больше более длинное

    if (l == x.l) //если длины равны
        for (const char* a = num + l - 1, *b = x.num + l - 1; a >= num; --a, --b)
        {
            if (*a > *b)// сравнение по разрядам от больших к малым
                return 1;
            else if (*b > *a)
                return 0;
        }
    return 0;
}
int SGN::operator == (const SGN &x) const
{
    if(this->sign == x.sign && strcmp(this->num, x.num) == 0)
        return 1;
    return 0;
}
char GROSSNUM::sub_digit (char x, char y) //функция вычетания из x y
{
    if (x < '0')//корректирую если два кода цифры
        x += '0';
    if (y < '0')
        y += '0';
    char t; // искомая разность
    t=x-y-flag+'0';// счёт с учётом переноса
    flag=0;// обнуляем флаг
    if(t<'0') // если нужен перенос устанавливаем флаг
    {
        t+=10;
        flag=1;
    }
    return t;
}
char GROSSNUM:: sum_digits (char d1, char d2)
{
    char d; //искомая сумма
    d=d1+d2+flag-'0';
    if(d>('0'+'0')) //корректирую если два кода цифры
        d-='0';
    if (d -'0'>=10) //отрабатываю перенос разряда
    {
        d-=10;
        flag=1; //при переносе устанавливаю флаг
    }
    else
        flag=0; //если переноса не было -сбрасываю флаг
    return d;
}
