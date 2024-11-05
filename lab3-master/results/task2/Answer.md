# Task 2: Ansewers
## Questions
1. Generate a roofline and analyze the information depicted. Copy a screenshot of the roofline in your response to support your analysis. Finally, create a snapshot with the name "task2" and add it to this same folder.

- **Current Performance:** The loop achieves 17.22 GFLOPS with an arithmetic intensity of 1 FLOP/Byte, indicating it’s limited by memory access rather than compute capacity.
- **Position near DRAM Bandwidth Line:** This suggests that data transfer from memory is the main bottleneck, and the loop isn’t utilizing the full computational power of the CPU.

2. Why is the algorithm limited? What techniques could we apply to improve performance?

- The performance is limited because the loop is memory-bound,we can improve it by **optimizing memory access** and **reducing memory traffic**