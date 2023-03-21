#ifndef GROSSNUM_H
#define GROSSNUM_H

#define N 251  //число не более чем из 250 цифр
#include <stdio.h>//печатаем по стандарту С, это лучше
#include <string.h>//для работы со строками (без std)
class GROSSNUM
{
protected:
    char num[N]; //массив десятичных цифр числа
    int flag; //глобальный флаг переноса
    int l; //количество цифр
    int comparison(char f1[], char f2[]);
    void reverse(); //обращает строку
    void get_l(){l=strlen(num);} //находит длину строки
    void swap(int i, int j); //меняет местами 2 цифры
    char sum_digits(char d1, char d2); //складывает d1 и d2
    char sub_digit(char x, char y);
public:
    GROSSNUM(); //конструктор по умолчанию
    GROSSNUM(const char*);//конструктор со строкой
    GROSSNUM(int); //конструктор с числом
    int operator >(GROSSNUM &x);
    int operator <(GROSSNUM &x);
    int operator >=(GROSSNUM &x);
    int operator <=(GROSSNUM &x);
    int operator ==(GROSSNUM &x);
    GROSSNUM summ(GROSSNUM &x); //симмирует 2 больших числа
    GROSSNUM subtr(GROSSNUM &x);
    void convert_num2gross(int);//простой int в большое
    void print(){reverse(); puts(num); reverse();} //печать большого
    void get_num(){ fgets(num, N, stdin); reverse();} //вводит число с клавиатуры
};
GROSSNUM::GROSSNUM()
{
    strcpy(num, "");
    flag = 0;
    l = 0;
}
GROSSNUM::GROSSNUM (const char* str)
{
    strcpy(num, str);
    reverse();
    flag = 0;
    l = strlen(str);
}
GROSSNUM::GROSSNUM(int x)
{
    convert_num2gross(x);
    flag = 0;
    l = strlen(num);
}
GROSSNUM GROSSNUM::subtr(GROSSNUM &x)
{
    int fl = 0//1 при отрицательной разности
    , n//миниимум фактических длин складываемых
    , m//длина наибольшего аргумента
    , i;
    GROSSNUM d;
    char* s[2];
    if(comparison(num, x.num) == 1)// если больше уменьшамое
    {
        s[0] = num;
        s[1] = x.num;
        n = x.l;
        m = l;
    }
    else if(comparison(num, x.num) == 0)//если больше вычитаемое
    {
        s[1] = num;
        s[0] = x.num;
        fl = 1;
        n = l;
        m = x.l;
    }
    else {
        d.num[0] = '0';
        d.num[1] = 0;
        return d;
    }
    for(i = 0; i < n; ++i) //складываю части, совпадающие по //длине
        d.num[i]=sub_digit(s[0][i], s[1][i]);
    for(;i<m;++i) //то работаем со вторым (с  //учетом флага переноса)
        d.num[i]=sub_digit(s[0][i], '0');
    for (; i > 1; --i)
        if(d.num[i-1] == '0')
        {
            d.num[i-1] = 0;
        }
        else
            break;
    if (fl) {
        d.num[i] = '-';
        d.num[i+1] = 0;
    } else
        d.num[i] = 0;
    return d;
}
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

GROSSNUM GROSSNUM::summ(GROSSNUM &x)
{
    int n //миниимум фактических длин складываемых
       ,i;
    GROSSNUM z;
    n=l>x.l?x.l:l; //нахожу более короткую строку
    for(i=0;i<n;++i) //складываю части, совпадающие по //длине
        z.num[i]=sum_digits(num[i],x.num[i]);
    if(n==l) //если короче первое слагаемое
        for(;i<x.l;++i) //то работаем со вторым (с  //учетом флага переноса)
            z.num[i]=sum_digits(x.num[i],0);
    else if(n==x.l) //если второе
            for(;i<x.l;++i) //то работаем с первым
                z.num[i]=sum_digits(num[i],0);

//отрабатываем случай возможного переполнения

    if ((i==N-1)&&(flag==1))
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

char GROSSNUM::sub_digit (char x, char y) //функция вычетания из x y
{
    if (x < '0')//корректирую если два кода цифры
        x += '0';
    if (y < '0')
        y += '0';
    char t;
    t=x-y-flag+'0';
    flag=0;
    if(t<'0')
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

int GROSSNUM::comparison(char f1[], char f2[]) //сравнивает 2 массива
{
    if (strlen(f1) > strlen(f2))
        return 1;
    else if (strlen(f2) > strlen(f1))
        return 0;
    else {
        int n = strlen(f1);
        for (int i = n - 1; i >= 0; --i) {
            if (f1[i] > f2[i])
                return 1;
            else if (f1[i] < f2[i])
                return 0;
        }
        return 2;
    }
}
/*
int GROSSNUM::comparison1(GROSSNUM f1, GROSSNUM f2) //сравнивает 2 больших числа
{
    if (strlen(f1.num) > strlen(f2.num))
        return 1;
    else if (strlen(f2.num) > strlen(f1.num))
        return 0;
    else {
        int n = strlen(f1.num);
        for (int i = n - 1; i >= 0; --i) {
            if (f1.num[i] > f2.num[i])
                return 1;
            else if (f1.num[i] < f2.num[i])
                return 0;
        }
        return 2;
    }
}
*/
//меняет местами 2 цифры
void GROSSNUM:: swap(int i, int j)
{
    char t;
    t=num[i];
    num[i]=num[j];
    num[j]=t;
}
//Метод обращает строку
void GROSSNUM:: reverse()
{
    int i;
    get_l(); // ищу длину строки
    for(i=0;i<l/2;++i)
        swap(i,l-i-1);
}

void GROSSNUM::convert_num2gross(int x)
{
    int i = 0;
    if (!x)
    {
        num[0] = '0';
        i = 1;
    }
    while(x) // получаю по одной коды цифр
    {
        num[i]=x%10+'0';
        x/=10;
        ++i;
    }
    num[i] = 0;
    l = i;//попутно их считаю
}

#endif
