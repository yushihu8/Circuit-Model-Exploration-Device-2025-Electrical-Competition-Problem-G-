# Circuit Model Exploration Device 2025

2025 年全国大学生电子设计竞赛 G 题“电路模型探究装置”工程仓库。

这个项目实现的是一套板上闭环系统：

- 由 STM32 控制 AD9954 产生扫频激励
- 由 FPGA 采集双路 ADC 数据并缓存
- 由 STM32 对输入输出做 FFT，计算频率响应
- 根据频率响应拟合二阶模拟模型
- 通过双线性变换生成数字 IIR 系数
- 将系数写回 FPGA，实现对被测模拟电路特性的数字复现

一句话概括：先测量，再建模，再复现。

## 仓库结构

```text
.
├── G_project+FPGA/          FPGA / Vivado 工程
├── G_Project-32H7/          STM32H743 主控工程
├── G_2025Y-32F4/            STM32F407 早期/兼容版本工程
├── G题_电路模型探究装置.pdf    赛题原文
├── 工程实现分析总结.md       项目原理与实现说明
└── README.md
```

## 核心工程说明

### 1. `G_project+FPGA`

主要负责：

- 产生 ADC 采样时钟
- 采集两路 ADC 数据
- 将采样数据写入 RAM，供 STM32 通过 SPI 读取
- 提供 SPI 从机寄存器接口
- 接收 STM32 下发的 IIR 系数
- 在 FPGA 内实时运行二阶 IIR 滤波器并输出到 DAC

关键源码位置：

- `G_project+FPGA/G_project/G_Project.srcs/sources_1/new/top.v`
- `G_project+FPGA/G_project/G_Project.srcs/sources_1/new/reg_control.v`
- `G_project+FPGA/G_project/G_Project.srcs/sources_1/new/spi_reg_control.v`
- `G_project+FPGA/G_project/G_Project.srcs/sources_1/new/iir_filter.v`

### 2. `G_Project-32H7`

主要负责：

- 控制 AD9954 输出扫频信号
- 触发 FPGA 采样并读取 RAM 数据
- 对输入/输出信号做 FFT
- 计算传递函数 `H(jw)`
- 拟合二阶模拟滤波器模型
- 双线性变换得到数字 IIR 系数
- 通过 SPI 将系数写回 FPGA

关键源码位置：

- `G_Project-32H7/G_Project-32/Src/main.c`
- `G_Project-32H7/G_Project-32/Middleware/freq_scan.c`
- `G_Project-32H7/G_Project-32/Hardware/fft.c`
- `G_Project-32H7/G_Project-32/Hardware/h_calc.c`

### 3. `G_2025Y-32F4`

这是 F407 版本的工程，保留了较完整的早期实现和 LCD 相关代码，可用于对比不同主控版本下的实现差异。

## 主要流程

1. STM32 初始化外设和 AD9954
2. AD9954 按 200 Hz 步进进行扫频
3. STM32 通过 SPI 写 FPGA 寄存器，触发一次双通道采样
4. FPGA 将 1024 组采样数据写入 RAM
5. STM32 读回数据并分别对输入、输出做 FFT
6. 计算各频点复数传递函数
7. 使用最小二乘方法拟合二阶模拟模型
8. 通过双线性变换生成数字 IIR 系数
9. 将系数写入 FPGA，进行实时数字复现

## 开发环境

本仓库包含的工具链主要有：

- STM32CubeMX / Keil MDK
- Vivado
- ARM CMSIS-DSP

## 仓库清理说明

为了让仓库更适合作为源码仓库维护，已经尽量排除了以下内容：

- `node_modules`
- Keil 构建产物
- Vivado 运行缓存
- 硬件调试快照
- 大量可再生成的仿真与 IP 派生文件

如果你需要重新生成这些文件，请在本地使用对应工具链重新构建工程。

## 参考资料

- `工程实现分析总结.md`
- `G题_电路模型探究装置.pdf`
