// recursive version

int collatz(int n)
{
    int collatznumber = 0;
    if (n == 1)
        return collatznumber +=0;

    else if (n % 2 == 1)
        collatznumber++;
        return collatz(n * 3 + 1);

    else (n % 2 == 0)
        collatznumber++;
        return collatz(n / 2);
}
