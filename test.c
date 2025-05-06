
// Function definition
int add(int a, int b)
{
    return a + b;
}
// Test program for compiler frontend
int main()
{
    // Variable declarations
    int x = 10;
    float y = 3.14;
    bool flag = true;
    
    // Arithmetic operations
    int sum = x + 5;
    float product = y * 2.0;
    
    // Control flow
    if (x > 5)
    {
        print("x is greater than 5");
    }
    else
    {
        print("x is less than or equal to 5");
    }
    
    // While loop
    int i = 0;
    while (i < 5)
    {
        print("Loop iteration");
        i = i + 1;
    }
    
    // For loop
    for (int j = 0; j < 3; j = j + 1)
    {
        print("For loop iteration");
    }
    
    // Function call
    int result = add(x, 5);
    print("Result of add function:");
    print(result);
    
    return 0;
}
