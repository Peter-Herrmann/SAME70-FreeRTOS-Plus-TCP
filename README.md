# SAME70-FreeRTOS-Plus-TCP Example

This repository provides a minimal example to get started with FreeRTOS+TCP on the SAME70 microcontroller. The project integrates the latest FreeRTOS 202210.01 LTS libraries and the ASF (Advanced Software Framework) libraries generated in August 2023.

## 📔 Versions

This example uses the FreeRTOS 202210.01 LTS libraries, whose versions are below.

| Component       | Version |
|-----------------|---------|
| FreeRTOS Kernel | 10.5.1  |
| FreeRTOS+TCP    | 3.1.0   |

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

