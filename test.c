// Simple test file that avoids segmentation faults

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
    int y = 5;
    
    // Function call using literals
    int z = add(10, 5);
    
    // Basic arithmetic
    int sum = x + y;
    
    return sum;
}
