# ESP-IDF Peripheral Examples Repository

This repository contains a collection of ESP-IDF (Espressif IoT Development Framework) examples that showcase various peripherals and functionality commonly used in ESP32 microcontroller-based projects. Each example provides detailed explanations, code samples to help you understand and utilize these features effectively.

## Table of Contents

- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Examples](#examples)
  - [ADC (Analog-to-Digital Converter)](#adc-example)
  - [PWM (Pulse Width Modulation)](#pwm-example)
  - [Timer](#timer-example)
  - [I2C (Inter-Integrated Circuit)](#i2c-example)
  - [SPI (Serial Peripheral Interface)](#spi-example)
  - [Display Control for ST7789](#display-control-for-st7789)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The ESP-IDF is a powerful framework for developing IoT applications with Espressif's ESP32 and  microcontrollers. This repository aims to provide you with clear and practical examples of working with different peripherals and components commonly used in embedded systems projects.

## Getting Started

Before you can run the examples in this repository, you need to set up your development environment and configure the ESP-IDF. Follow these steps to get started:

1. Install ESP-IDF: Follow the [official ESP-IDF installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) to set up the framework on your development machine.

2. Clone this Repository: Clone this repository to your local machine using the following command:

   ```bash
   git clone https://github.com/your-username/esp-idf-examples.git
   ```

3. Configure ESP-IDF: Navigate to the repository's root directory and configure the ESP-IDF environment:

   ```bash
   cd esp-idf-examples
   idf.py set-target <your_target>
   ```

   Replace `<your_target>` with the appropriate target for your board.

4. Build and Flash an Example: Choose an example from the list below, navigate to its directory, and build and flash the code to your ESP32/ board using the following commands:

   ```bash
   cd <example_directory>
   idf.py build
   idf.py -p /dev/ttyUSB0 flash  # Replace /dev/ttyUSB0 with your serial port
   ```

Now you're ready to explore and run the examples!

## Examples

### ADC Example

The ADC example demonstrates how to use the Analog-to-Digital Converter on the ESP32/ to read analog voltage values from external sensors. It includes wiring diagrams and code samples to get you started quickly.

- Directory: `adc/`
- Detailed README: [Link to ADC Example README](./adc/README.md)

### PWM Example

The PWM example illustrates how to generate PWM signals to control devices like motors, LEDs, and servos. It provides code snippets and wiring instructions for different use cases.

- Directory: `pwm/`
- Detailed README: [Link to PWM Example README](./pwm/README.md)

### Timer Example

The Timer example demonstrates how to set up and use timers for precise timing and scheduling tasks. It covers various timer configurations and their applications.

- Directory: `timer/`
- Detailed README: [Link to Timer Example README](./timer/README.md)

### I2C Example

The I2C example shows how to communicate with I2C devices using ESP32. It includes code samples and connection diagrams for working with I2C peripherals.

- Directory: `i2c/`
- Detailed README: [Link to I2C Example README](./i2c/README.md)

### I2C Bus Example

The I2C Bus example shows how to communicate with I2C devices using i2c_bus library. It includes code samples and connection diagrams for working with ip5306 BMS.

- Directory: `ip5306_i2c/`
- Detailed README: [Link to I2C Example README](./ip5306_i2c/README.md)

### SPI Example

This code demonstrates how to use the SPI master half duplex mode to read/write a AT93C46D.

- Directory: `spi/`
- Detailed README: [Link to SPI Example README](./spi/README.md)

### Display Control for ST7789

This example focuses on controlling an ST7789-based display module using SPI communication. It covers graphics rendering on the screen.

- Directory: `st7789/`
- Detailed README: [Link to ST7789 Display Example README](./st7789/README.md)

## Usage

Each example directory contains a README file with detailed instructions on how to use and modify the code for your specific needs. Feel free to explore, experiment, and adapt these examples for your own projects.

## Contributing

We welcome contributions to this repository. If you have additional peripheral examples or improvements to existing ones, please open a pull request. Refer to our [Contribution Guidelines](CONTRIBUTING.md) for details on how to contribute.

## License

This repository is licensed under the [MIT License](LICENSE), which means you are free to use, modify, and distribute the code for both personal and commercial purposes. Please refer to the license file for more details.

---

Thank you for using our ESP-IDF Peripheral Examples Repository. We hope these examples help you in your ESP32/ projects. If you have any questions or encounter issues, please feel free to open an issue in this repository or reach out to our community for assistance. Happy coding!
