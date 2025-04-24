#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Helper function to calculate expected sum in range
int calculate_expected_sum(int start, int end) {
    // Use formula: sum = n(n+1)/2 - m(m+1)/2
    // where n = end-1, m = start-1
    long n = end - 1;
    long m = start - 1;
    long sum_n = (n * (n + 1)) / 2;
    long sum_m = (m * (m + 1)) / 2;
    return sum_n - sum_m;
}

int
main()
{
    // Test different number of processes
    int test_counts[] = {1, 2, 4, 8, 16};
    int array_size = 1 << 16; // 2^16
    
    for(int t = 0; t < 5; t++) {
        int num_procs = test_counts[t];
        
        printf("Testing with %d processes:\n", num_procs);
        int pids[16];
        int result = forkn(num_procs, pids);
        
        if(result == 0) {
            int n;
            int statuses[16];
            waitall(&n, statuses);
            
            if(n != num_procs) {
                printf("  Error: Expected %d children, got %d\n", num_procs, n);
                continue;
            }
            
            int total = 0;
            for(int i = 0; i < n; i++) {
                total += statuses[i];
            }
            
            int expected = calculate_expected_sum(0, array_size);
            if(total == expected)
                printf("  Passed: Sum is correct: %d\n", total);
            else
                printf("  Failed: Expected %d, got %d\n", expected, total);
        }
        else if(result > 0 && result <= num_procs) {
            int chunk_size = array_size / num_procs;
            int start = (result - 1) * chunk_size;
            int end = (result == num_procs) ? array_size : result * chunk_size;
            
            int sum = 0;
            for(int i = start; i < end; i++) {
                sum += i;
            }
            
            exit(sum, 0);
        }
        else if(result == -1) {
            printf("  Failed: forkn failed\n");
        }
    }
    
    exit(0, 0);
}