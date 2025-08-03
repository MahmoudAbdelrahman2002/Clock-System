# Clock System

A real-time clock (RTC) system built for STM32 microcontrollers using the DS1307 RTC module. This embedded system project provides accurate timekeeping with date and time management capabilities, featuring support for multiple STM32 development boards.

## Features

- **Real-Time Clock Management**: Accurate timekeeping using DS1307 RTC module
- **Dual Time Format Support**: 12-hour (AM/PM) and 24-hour time formats
- **Complete Date Tracking**: Day, date, month, and year with day-of-week support
- **I2C Communication**: Robust communication with DS1307 via I2C protocol
- **DMA Support**: Efficient data transfer using Direct Memory Access
- **LCD Display**: Visual time and date display (Blue Pill implementation)
- **Multi-Board Support**: Compatible with STM32F103C8 (Blue Pill) and STM32F446RE (Nucleo)
- **Layered Architecture**: Clean COTS (Commercial Off-The-Shelf) software structure

## Hardware Requirements

### Core Components
- **DS1307 Real-Time Clock IC** with 32.768 kHz crystal oscillator
- **Backup Battery** (CR2032) for DS1307 to maintain time during power loss
- **Pull-up Resistors** (4.7kΩ) for I2C SDA and SCL lines

### Supported Development Boards
1. **STM32F103C8T6 (Blue Pill)**
   - ARM Cortex-M3 core
   - 64KB Flash, 20KB RAM
   - Additional: 16x2 LCD display for time visualization

2. **STM32F446RE (Nucleo-64)**
   - ARM Cortex-M4 core with FPU
   - 512KB Flash, 128KB RAM
   - Built-in ST-LINK/V2-1 debugger

### Connections
| DS1307 Pin | STM32F103C8 | STM32F446RE | Description |
|------------|-------------|-------------|-------------|
| VCC        | 3.3V        | 3.3V        | Power supply |
| GND        | GND         | GND         | Ground |
| SDA        | PB7         | PB9         | I2C Data line |
| SCL        | PB6         | PB8         | I2C Clock line |

## Software Requirements

### Development Environment
- **STM32CubeIDE** (recommended) or any ARM GCC toolchain
- **ST-LINK Utility** or **OpenOCD** for programming
- **Git** for version control

### Dependencies
- STM32 HAL Libraries (included in project)
- Custom MCAL (Microcontroller Abstraction Layer) drivers
- I2C and DMA peripheral drivers

## Project Structure

```
Clock-System/
├── COTS/                          # Commercial Off-The-Shelf modules
│   ├── Bluepill F103C8/           # STM32F103C8 implementation
│   │   ├── APP/                   # Application layer
│   │   ├── HAL/                   # Hardware Abstraction Layer
│   │   │   ├── LCD/               # LCD display driver
│   │   │   └── LED/               # LED control driver
│   │   ├── MCAL/                  # Microcontroller Abstraction Layer
│   │   │   ├── RCC/               # Reset and Clock Control
│   │   │   ├── GPIO/              # General Purpose I/O
│   │   │   └── I2C/               # I2C communication
│   │   ├── LIB/                   # Library definitions
│   │   └── SERVICE/               # Service layer
│   └── Nucleo F446RE/             # STM32F446RE implementation
│       ├── Src/                   # Source files
│       │   ├── App_Abdelrahman.c  # Main application
│       │   ├── HAL/               # Hardware Abstraction Layer
│       │   │   └── RTC/           # DS1307 RTC driver
│       │   ├── MCAL/              # Microcontroller Abstraction Layer
│       │   │   ├── GPIO/          # GPIO driver
│       │   │   ├── I2C/           # I2C driver
│       │   │   ├── DMA/           # DMA driver
│       │   │   ├── RCC/           # Clock configuration
│       │   │   └── NVIC/          # Interrupt controller
│       │   └── LIB/               # Hardware definitions
│       ├── Debug/                 # Debug build files
│       └── Startup/               # Startup and linker files
├── Documents/                     # Project documentation
│   └── RTC Datasheet/
│       └── DS1307.PDF             # DS1307 RTC datasheet
├── FlowChart.jpg                  # System flow diagram
└── README.md                      # This file
```

## Getting Started

### 1. Hardware Setup
1. Connect the DS1307 RTC module to your STM32 board as per the connection table above
2. Install a CR2032 battery in the DS1307 module
3. Connect pull-up resistors (4.7kΩ) between VCC and SDA/SCL lines
4. For Blue Pill: Connect the LCD display according to the LCD driver configuration

### 2. Software Setup
1. Clone this repository:
   ```bash
   git clone https://github.com/MahmoudAbdelrahman2002/Clock-System.git
   cd Clock-System
   ```

2. Open the project in STM32CubeIDE:
   - Choose the appropriate board folder (`Bluepill F103C8` or `Nucleo F446RE`)
   - Import the project into your workspace

3. Build the project:
   - Select your target configuration
   - Build the project using Ctrl+B or the build button

4. Flash the firmware:
   - Connect your STM32 board via ST-LINK
   - Flash the compiled binary to the microcontroller

### 3. Usage
1. **Initial Setup**: On first boot, the system initializes the DS1307 RTC
2. **Time Setting**: Use the provided API functions to set initial time and date
3. **Time Reading**: The system continuously reads and displays current time
4. **Power Backup**: Time is maintained even during power loss thanks to the backup battery

## API Reference

### Core Functions

#### RTC Initialization
```c
uint8_t ds1307_RTC_init(void);
```
Initializes the DS1307 RTC module and I2C communication.
- **Returns**: Error status (0 = success, 1 = failure)

#### Set Date and Time
```c
void ds1307_RTC_set_DateANDTime(DS1307_RTC_date_t* rtc_date, DS1307_RTC_time_t* rtc_time);
```
Sets the current date and time in the RTC.
- **Parameters**:
  - `rtc_date`: Pointer to date structure (day, date, month, year)
  - `rtc_time`: Pointer to time structure (hour, minute, second, format)

#### Get Date and Time
```c
void ds1307_RTC_get_DateANDTime(DS1307_RTC_date_t* rtc_date, DS1307_RTC_time_t* rtc_time);
```
Retrieves the current date and time from the RTC.

### Data Structures

#### Time Structure
```c
typedef struct {
    uint8_t SEC;                    // Seconds (0-59)
    uint8_t MIN;                    // Minutes (0-59)
    uint8_t HOUR;                   // Hours (1-12 or 0-23)
    time_format_t time_format;      // 12/24 hour format
} DS1307_RTC_time_t;
```

#### Date Structure
```c
typedef struct {
    uint8_t DAY;                    // Day of week (1-7)
    uint8_t DATE;                   // Date (1-31)
    uint8_t MONTH;                  // Month (1-12)
    uint8_t YEAR;                   // Year (0-99, represents 2000-2099)
} DS1307_RTC_date_t;
```

## Configuration

### Time Format Options
- `_24_Hour_Mode`: 24-hour format (00:00 - 23:59)
- `_12_Hour_Mode_AM`: 12-hour AM format
- `_12_Hour_Mode_PM`: 12-hour PM format

### Days of Week
```c
typedef enum {
    SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
} days;
```

## Troubleshooting

### Common Issues

1. **RTC Not Responding**
   - Check I2C connections (SDA, SCL)
   - Verify pull-up resistors are connected
   - Ensure DS1307 has proper power supply (3.3V)

2. **Time Not Retained**
   - Replace backup battery (CR2032)
   - Check battery holder connections

3. **Build Errors**
   - Ensure correct STM32CubeIDE version
   - Verify all include paths are correct
   - Check that the target microcontroller is properly selected

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Mahmoud Abdelrahman**
- GitHub: [@MahmoudAbdelrahman2002](https://github.com/MahmoudAbdelrahman2002)
- Project: [Clock-System](https://github.com/MahmoudAbdelrahman2002/Clock-System)

## Acknowledgments

- STMicroelectronics for STM32 development tools and documentation
- Maxim Integrated for DS1307 RTC datasheet and specifications
- ARM Cortex-M community for embedded development resources
