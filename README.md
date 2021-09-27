# Data-Crunching-IPC

A C program that computes math expressions using Linux IPCs(Inter-process communication). fork() when needed and pipes for communication with children. Binary format is used for communication. Parent task reads data from the data file and pumps into appropriate pipes in parallel and the result comes back to the main task using another pipe. The equation in the first line determines the setup. Operator precedence not followed.

![image](https://user-images.githubusercontent.com/32169836/134986655-e5d0f3ee-de18-4d59-a626-7c8b0d1522f8.png)
