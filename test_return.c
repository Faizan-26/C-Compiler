int main()
{
    int x = 10;

    if (x > 5)
    {
        print(x);
    }

    return false; // This should generate a return type error (bool instead of int)
}

bool test_function()
{
    int y = 20;
    return y; // This should generate a return type error (int instead of bool)
}