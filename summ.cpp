GROSSNUM GROSSNUM::summ(GROSSNUM &x)
{
    int n //миниимум фактических длин складываемых
       ,i;
    GROSSNUM z;
    n=this->l>x.l?x.l:this->l; //нахожу более короткую строку
    for(i=0;i<n;++i) //складываю части, совпадающие по //длине
        z.num[i]=sum_digits(num[i],x.num[i]);
    if(n==this->l) //если короче первое слагаемое
        for(;i<x.l;++i) //то работаем со вторым (с  //учетом флага переноса)
            z.num[i]=sum_digits(x.num[i],0);
    else if(n==x.l) //если второе
            for(;i<this->l;++i) //то работаем с первым
                z.num[i]=sum_digits(num[i],0);

//отрабатываем случай возможного переполнения

    if ((i==N-1)&&(this->flag==1))
    {
        puts("number owerfull!");
//        exit(1);
    }

/* когда достигнут конец более длинного числа отрабатываем установленный флаг переноса */
    if(this->flag)
    {
        z.num[i]='1'; //учитываю флаг (если он //установлен)
        z.num[i+1]=0;
    }
    else
       z.num[i]=0; //иначе просто закрываю строку
    return z;
}
