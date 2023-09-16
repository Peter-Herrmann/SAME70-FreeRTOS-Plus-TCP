# SAME70-FreeRTOS-Plus-TCP Example

[![GitHub license](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP/blob/main/LICENSE)
[![GitHub issues](https://img.shields.io/github/issues/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP)](https://github.com/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP/issues)
[![Run Clang-Format](https://github.com/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP/actions/workflows/format.yml/badge.svg)](https://github.com/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP/actions/workflows/format.yml)

This repository provides a minimal example to get started with FreeRTOS+TCP on the SAME70 microcontroller. The project integrates the ASF (Advanced Software Framework) libraries generated in August 2023, and either the latest release version or the latest LTS version of the FreeRTOS kernel and FreeRTOS+TCP.

## 📔 Versions

There are two release versions of this example. The latest available versions are one release, and the latest Long Term Support (LTS) version is another.

| Component       | [LTS Release](https://github.com/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP/tree/release/lts) | [Latest Release](https://github.com/Peter-Herrmann/SAME70-FreeRTOS-Plus-TCP/tree/release/latest) |
|-----------------|:-----------:|:--------------:|
| FreeRTOS Kernel | 10.5.1      | 10.6.1         |
| FreeRTOS+TCP    | 3.1.0       | 4.0.0          |

## 🛠 Building the Project

### Prerequisites

- [Microchip Studio](https://www.microchip.com/mplab/microchip-studio) (Tested with Microchip Studio 7.0.2594)
- A SAME70-XPLD board or a compatible board.

### Setup for Different SAME70 Versions

The project is pre-configured for the SAME70Q21 version. For other SAME70 variants:

1. Open Microchip Studio.
2. Navigate to `Project > "Your Project Name" Properties`.
3. Access the `Device` section.
4. Click on `Change Device` and pick your specific SAME70 version from the list.
5. Save and rebuild the project.

## 📖 Documentation
- [FreeRTOS Kernel Official Documentation](https://www.freertos.org/RTOS.html)
- [FreeRTOS+TCP Official Documentation](https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/index.html)
- [SAME70 Datasheet and Manuals](https://www.microchip.com/wwwproducts/en/ATSAME70)

## 🤝 Contributing

Discovered a bug or have enhancement suggestions? Open an issue! Contributions via pull requests are always welcome.

## 📜 License

This project is open source and available under the [Apache License 2.0](LICENSE).

