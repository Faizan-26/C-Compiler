// Simple test file for optimization techniques

// Test constant folding
int constant_fold_test() {
    int x = 3 + 5;      // Should be folded to 8
    int y = 10 * 4;     // Should be folded to 40
    return x + y;       // Should be folded to 48
}

// Test strength reduction
int strength_reduction_test(int x) {
    int a = x * 2;    // Should be converted to x << 1
    int b = x * 8;    // Should be converted to x << 3
    return a + b;     // x*2 + x*8 = x*10
}

// Simple main function - call functions defined above
int main() {
    int x = 5;
    int result1 = constant_fold_test();
    int result2 = strength_reduction_test(x);
    return result1 + result2;
} 