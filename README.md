# Custom Matrix Multiplication Accelerator using Vitis HLS

## Overview

This project implements a custom hardware accelerator for matrix multiplication using **AMD Vitis HLS** targeting the **Zynq UltraScale+ MPSoC (xczu3eg-sbva484-1-e)** platform.

The design extends a baseline HLS implementation by applying optimization techniques such as:

- Loop pipelining
- Loop unrolling
- Tiled computation
- Array partitioning
- Parallel AXI memory interfaces

The goal is to accelerate matrix multiplication using FPGA hardware and compare results against CPU-based implementations from previous labs.

---

## Project Objectives

- Convert C/C++ matrix multiplication code into synthesizable FPGA hardware
- Improve throughput using HLS optimization pragmas
- Compare hardware resource usage and performance against CPU versions
- Demonstrate FPGA acceleration principles

---

## Target Platform

- **Board:** AUP-ZU3
- **FPGA Family:** Zynq UltraScale+ MPSoC
- **Part:** xczu3eg-sbva484-1-e
- **Toolchain:** AMD Vitis 2025.2

---

## Files Included

```markdown
custom_matmul.cpp        -> Final HLS accelerator source code
report.pdf               -> Final project report
screenshots/             -> Synthesis and resource screenshots
README.md                -> Project documentation
Accelerator Features
Baseline Design

Standard matrix multiplication implemented in HLS.

Custom Optimized Design

Includes:

#pragma HLS PIPELINE
#pragma HLS UNROLL
#pragma HLS ARRAY_PARTITION

Additional enhancements:

Tile-based local buffers
Parallel multiply-accumulate operations
Reduced memory bottlenecks
Resource Utilization
Resource	Baseline	Custom
BRAM	2	4
DSP	7	60
FF	2,190	16,767
LUT	2,331	11,617
URAM	0	0
CPU Comparison (Lab 2)
Method	N=16 GFLOPS	N=32 GFLOPS
Naive	0.0313	0.0319
Cache-aware	0.0388	0.0398
Tiled	0.0363	0.0364

The FPGA accelerator provides a more parallel compute model than CPU execution.

How to Run in Vitis HLS
Open AMD Vitis 2025.2
Create New HLS Component
Select target part:
xczu3eg-sbva484-1-e
Add source file:
custom_matmul.cpp
Set top function:
custom_matmul_kernel
Run:
C Synthesis
Results

The custom design synthesized successfully and demonstrated increased parallelism at the cost of higher FPGA resource utilization.

This reflects the standard FPGA tradeoff:

More hardware resources = More performance potential
Future Improvements
Systolic array architecture
Floating-point support
DMA transfers
Real hardware timing benchmarks
GPU comparison
Author

Braylon Watson
