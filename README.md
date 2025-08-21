# UWB-AOA-with-Display-STM32F103C8T6

UWB AOA with Display STM32F103C8T6



# Feature:

• Controller:STM32F103C8T6, 72 MHz maximum frequency, 1.25 DMIPS / MHz (Dhrystone 2.1),64KB Flash memory, 20KB SRAM
• DW3000 Module(Anchor):UWB-X3-AOA
• DW3000 Module(Tag):UWB-X3-MAX
• OLED: 1.29" SSD1306
• "Zero" Dropout: On board ideal diode circuit
• Dual-USB Type C:USB-Native/USB-TTL
• USB-to-UART: CH340K
• Charger: TP4056
• Button:Reset/Btn
• Expander: 2X12 2.54mm header

* Open Source: hardware/firmware/software

# Usage:

1. Insert to USB-NATIVE port of AOA anchor.
2. Insert to USB-TTL port of AOA tag(Or Powered by Li-battery).
3. Open the AOA System Application.
4. Select Tag ID and joined.
5. Result Show



# Firmware

|Type|Default Firmware|
|-|-|-|
|Anchor|Project\_Anchor\_v1.0.hex|
|Tag|Project\_Tag\_v1.0.hex|

# How to Program?

|ST-LINK V2 |AOA Anchor/Tag Board|
|-|-|-|
|SWCLK|SWCK|
|SWDIO|SWIO|
|GND|GND|
|3.3V|+3.3V|

