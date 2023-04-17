# Course work for parallel computing

## The task

The task is to implement a parallel version of quicksort algorithm using and compare it with the sequential version.

## The algorithm

The algorithm is based on the following steps:
1. Divide the array into two parts: the first one contains elements less than the pivot, the second one contains elements greater than the pivot.
2. Sort the first part in parallel usgin std::async.
3. Sort the second part in parallel usgin std::async.
4. As the array passes into function as reference, no merge needed
5. Wait for std::future objects to complete.

## The results

The results are presented in the following table:


| Sync size | Array Size | Sync qsort (ms) | Async qsort (ms) | Boost rate |
|-----------|------------|-----------------|------------------|------------|
| 100       | 100000     | 21.069          | 11.281           | 1.86765    |
| 100       | 1000000    | 220.609         | 52.029           | 4.24012    |
| 100       | 10000000   | 2464.36         | 533.981          | 4.61507    |
| 100       | 100000000  | 27449.8         | 5222.53          | 5.25604    |
| **Avg**   |			 |                 |                  | **3.986**  |
| 1000      | 100000     | 24.832          | 13.002           | 1.90986    |
| 1000      | 1000000    | 225.885         | 64.124           | 3.52263    |
| 1000      | 10000000   | 2431.43         | 481.184          | 5.05302    |
| 1000      | 100000000  | 27491.2         | 5284.94          | 5.2018     |
| **Avg**   |            |                 |                  | **3.942**  |
| 10000     | 100000     | 24.966          | 8.901            | 2.80485    |
| 10000     | 1000000    | 234.728         | 70.017           | 3.35244    |
| 10000     | 10000000   | 2463.56         | 516.379          | 4.77084    |
| 10000     | 100000000  | 27521.6         | 5363.95          | 5.13084    |
| **Avg**   |            |                 |                  | **4.015**  |
| 100000    | 100000     | 24.579          | 12               | 2.04825    |
| 100000    | 1000000    | 228.041         | 73.927           | 3.08468    |
| 100000    | 10000000   | 2434.07         | 495.656          | 4.91082    |
| 100000    | 100000000  | 27536.5         | 5377.14          | 5.12103    |
| **Avg**   |            |                 |                  | **3.791**  |

Looks like the best value of sync size is 10'000 because it is average 4.015 faster than the sequential version.
