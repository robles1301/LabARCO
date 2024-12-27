
# Lab description
In this lab, we will be working with the OpenMP code related to anomaly detection in hyperspectral images. In this case, our focus will be on parallelization using DPC for a single hyperspectral block. Specifically, the practice will involve parallelizing the operations performed for background extraction and anomaly detection (centroid calculation, centralization, calculation of the brightest pixel, spectral projection, and information subtraction).


DPC is a very new technology and for that reason the available documentation is not ver much. We recommend as text book reference [DPC Book](https://link.springer.com/content/pdf/10.1007%2F978-1-4842-5574-2.pdf). Before working on the code, it is very recommendable trying to visualize how the HyperLCA lossy hyperspectral compressor ([link](LbLFAD.md)).


filter works on a paper. 

As learning outcomes from the lab yo will:
1. Perform spectral transformations on hyperspectral images.
2. Parallelize code using DPC.
3. Analyze the performance improvement of the implementation.

# Important
Remember you should always compile with **icpx -fsycl**

# Task 1
[results/task1](results/task1)

# Task 2
[results/task2](results/task2)




