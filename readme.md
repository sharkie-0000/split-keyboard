# S Split Keyboard

my 52-key split keyboard design based on two Seeed Studio XIAO RP2040 boards, Cherry MX style mechanical switches and my custom KiCad PCB layout 
each half of keyboard contains 26 keys and its own USB connection, with an additional USB hub to be added in the future

the current repository contains the layout of the PCB, a model of the case, files for production of the board and a demo Arduino firmware
this is just a work-in-progress design and demo, no physical realization or testing has been done yet

[Development journal — 45 estimated hours](JOURNAL.md) · [Parts list](bom.csv)

## how it works

Each controller scans a 5 rows by 6 columns matrix with 26 key points being used and one diode per key
The sample program lowers each row one by one and after detecting stable change sends corresponding character through USB port

```text
26 keys + diodes --> XIAO RP2040 U1 --> USB --> Computer
26 keys + diodes --> XIAO RP2040 U2 --> USB --> Computer
```

Both parts communicate by themselves, there is no connection cable between the controllers that transfers information
Later I plan to use a USB hub to connect both USB cables to my laptop, I have neither designed nor manufactured such hub myself
PCB previews contain a certain amount of board material connecting both key parts, and I still need to resolve this issue in order to allow separate movement of both parts

## main features

- 52 keys with 26 keys on each side and 3 thumb keys in each layout
- 2 XIAO RP2040 microcontrollers with USB separately
- One diode for each switch with Cherry MX 1u PCB mounts
- Wiring on two layers of copper and ground zones
- Four 3.2 mm holes for M3 screws
- Case model in STEP format and STL printing export
- Arduino matrix example with pinout for each controller

## images

these are screenshots of the design and CAD model, i have not built the keyboard yet

![Second-half schematic](journal%20image/j04_01_second-half-matrix-and-controller.png)

![Routed PCB](journal%20image/j07_05_filled-ground-zones.png)

![PCB top view](journal%20image/j08_07_top-side-3d-preview.png)

![PCB diode side](journal%20image/j08_08_angled-diode-side-preview.png)

![Case interior](journal%20image/j09_07_case-interior-without-pcb.png)

## how i plan to build it

this is my strategy for the creation of the circuit; this is only hypothetical since I haven't tested it on the physical board yet

1. sort the diode packaging and the edges of the board, which joins the two halves together and perform schematic and PCB rule checks then export the board files
2. preview the board at the PCB site including the drill holes and the edges of the board before placing your order
3. preview the case and make sure it matches up with the final PCB design and include screw locations, diode locations, and room for USB ports and then perform a test print
4. place the corresponding through-hole diodes in the correct orientation according to the schematic and PCB designs
5. inspect the footprints and clearance around the controllers and switches before placement and ensure there is no unintentional solder connection between pads
6. test each controller and matrix via USB port before assembling the board and installing the keycaps

## firmware demo

open [firmware/firmware.ino](firmware/firmware.ino) in Arduino IDE with a board package that supports XIAO RP2040 and USB Keyboard
set `KEYBOARD_HALF` to `1` if you are working on U1 or `2` if on U2, choose the appropriate board and port, and upload the firmware to each keyboard individually

each half will type the letters `a-z` in the order of the matrix with 10 ms debounce delay
in the demo it will send one character for each press; it doesn't have a typical typing keyboard layout or the ability to hold keys and modifiers yet
the pin configurations in the code have RP2040 GPIO numbers that are not the same as the D pins written on the board

both pin setups passed the C++ syntax validation on the PC using stubbed board libraries, now I need to compile and test them on the actual board

## what is in the repo

```text
.
├── 3d/              Case STEP model and STL export
├── firmware/        Basic Arduino matrix demo
├── gerber/          PCB fabrication exports
├── gerber.zip       Fabrication archive
├── image/           Existing project screenshots
├── journal/         Individual entries and original screenshots
├── journal image/   Copies used by the combined journal
├── kicad/           KiCad design and PCB STEP export
├── bom.csv          Parts, USD prices and purchase links
├── JOURNAL.md       Combined development journal
└── readme.md        Project overview
```

## parts and BOM

i used the parts and USD prices from [bom.csv](bom.csv) for this table
the switches are listed as one pack of 150, the keyboard only needs 52 of them

| Qty | Component | Unit price (USD) | Total (USD) | Link |
|---:|---|---:|---:|---|
| 2 | Seeed Studio XIAO RP2040 v1.0 | $5.64 | $11.28 | [Buy](https://robu.in/product/seeed-studio-xiao-rp2040-v1-0/) |
| 1 | Blank Pudding Keycap Set | $15.99 | $15.99 | [Buy](https://meckeys.com/shop/accessories/keyboard-accessories/keycaps/blank-pudding-keycap-set/) |
| 52 | DIODE-1N4148-SOD-80 (SKU 1415737) | $0.0109 | $0.57 | [Buy](https://robu.in/product/diode-1n4148/) |
| 1 | PCB fabrication (JLCPCB order) | $23.00 | $23.00 | [Buy](https://jlcpcb.com/) |
| 1 | LHGJFKO 3-pin mechanical keyboard switches (150-piece pack) | $18.11 | $18.11 | [Buy](https://www.amazon.in/dp/B0GFDG9GB7) |
| | **Total** | | **$68.95** | |


## PCB and case files

the [Gerber archive](gerber.zip) and [Gerber directory](gerber/) contain the board files i have exported
the picture of the rout indicates no unrouted traces, but i do not have the result which proves that the design rule check is done
check the borders of the final board and export the files once again after making any changes to the design, before sending it for production

the case files are [STEP](3d/s-split-keyboard.step) and [STL](3d/printable-s-split-keyboard.stl)
the [PCB STEP file export](kicad/s-split-keyboard.step) is also provided for comparison of the board and the case
now i have to check how it fits and mount and if there is enough space for cables