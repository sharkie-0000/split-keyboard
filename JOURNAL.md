# S Split Keyboard Development Journal

**total time spent: 45 hours — estimated**

these dates and hours are what i remember, i did not use a timer
some screenshots have different dates from the days i remember working on this, the original files are still in each journal folder
i did not write down when i started and stopped, so i left those times out

## 8 November 2026 — Journal 01: Getting some ideas

**time spent: 3 hours — estimated**

I started off by keeping a few reference models of what I was thinking of making for a split keyboard
This one has two distinct halves, staggered key columns, and three thumb keys on each side.
I used this to base the design on and this is a reference model, not a made model

![Split keyboard reference](journal%20image/j01_01_split-keyboard-reference.png)

i also found this XIAO ESP32-S3 picture when checking out controllers
it features the tiny board and its USB-C port, but it was just a reference at this point
at some later point in the schematic, i used the XIAO RP2040, so this picture is not the controller i used in my final schematic

![Seeed Studio XIAO ESP32-S3 reference](journal%20image/j01_02_xiao-esp32-s3-reference.png)

The final reference is the mechanical switch that has a black body with a blue cross-shaped stem.
This reference came in line with my efforts to review the different components of the keyboard.
With these reference images in place, I could have something to work on in regards to the keyboard design, control board, and the switches.

![Mechanical switch reference with blue stem](journal%20image/j01_03_blue-stem-switch-reference.png)

## 8 November 2026 — Journal 02: Starting the key matrix

**time spent: 3 hours — estimated**

i started designing the schematic in KiCad with only one switch and one diode labeled SW1 and D1 respectively.
I first wired that before wiring the remaining matrix
The outer parts of the matrix were still open, hence this was the initial matrix for the circuit design

![Matrix schematic with one switch and one diode](journal%20image/j02_01_switch-and-diode.png)

I then copied and pasted the switches and diodes pairs up to 26 in total for both the switches and diodes to make one half.
The switches are labeled from SW1 to SW26 while the diodes are labeled from D1 to D26

I connected the switches and diodes in six columns and five rows labeled col1 to col6 and row1 to row5 respectively
The first four rows are connected to six keys while the last row has two keys in the first two columns
This made the matrix on one half complete and the controller connections would follow

![Matrix schematic with 26 switches and six columns and five rows](journal%20image/j02_02_26-switch-matrix.png)

## 9 November 2026 — Journal 03: Adding the controller

**time spent: 4 hours — estimated**

i placed the symbol for the XIAO RP2040 beside the key matrix
the first image below shows the controller, just as i got it without connecting any row or column labels to its pins
this was when the design switched from the previous one using the ESP32-S3 to this new RP2040 controller

![XIAO RP2040 controller symbol before wiring](journal%20image/j03_01_xiao-rp2040-symbol.png)

i connected the five rows and six columns with D0 to D10 which use up all eleven of the GPIO pins
D0 is connected to row5, D1 to col5, D2 to col6 and D3 to col4
D4 and D5 connect to col1 and col2 and D6 connects to col3
and the other four rows are connected with D10 to row1, D9 to row2, D8 to row3 and D7 to row4

i also labeled the power pins and the GND pin as can be seen in this image with no-connect symbols on the non-used pins
these pins are from the schematic, i did not make any external power connections yet

![Controller with matrix labels and power nets](journal%20image/j03_02_controller-matrix-labels.png)

once i got the labels in place, i had both the 26-key matrix and the controller designed
every key has its own diode with the cathode bar pointing toward the row side

the current plan has both parts of the keyboard connecting to the computer via their own USB cable
eventually i would need a USB hub that would be connected to the laptop from one side and the two parts of the keyboard from the other
the idea of that hub remains an idea; it would connect two USB devices but wouldn't merge their key states

after that it was time to make the same circuit for the other part and modify the labels so that two matrices do not get mixed up
it was all schematic work so far, i did not test those connections with any hardware yet

![26-switch matrix beside the labeled controller](journal%20image/j03_03_matrix-and-controller-overview.png)

## 9 November 2026 — Journal 04: Second half and footprints

**time spent: 4 hours — estimated**

I copied the matrix for the second half and also another XIAO RP2040 as U2.
This side will have SW27 to SW52 and D27 to D52, therefore, there will be 52 switches and 52 diodes on both sides together.
I put a `1.` prefix for the row and column designators of this side so that it will not get joined with the first matrix in terms of names.

This controller will use a different pinout where D0 to D5 are connected to columns 1 to 6 and D6 to row1, D10, D9, D8 and D7 are connected to rows 2 to 5.
Both controllers will use their own USB connections.

![Matrix for the second half and its controller](journal%20image/j04_01_second-half-matrix-and-controller.png)

I then opened up the footprint assignment window to pick the actual pad shapes that will be used on the PCB.
In this view, I still had the diode footprint fields blank while the filter was showing the mounting hole results.

![Footprint assignment window before picking up the diode footprint](journal%20image/j04_02_footprint-assignment-before-selection.png)

i chose `Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal` for the diodes
this is a horizontal through-hole footprint with 7.62 mm spacing between the leads
the actual diode has to be this size and package, 1N4148 in the part name is not sufficient

![DO-35 horizontal diode footprint assignments](journal%20image/j04_03_diode-footprint-assignment.png)

for the switches i selected `Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB`
both controllers were selected as `Seeed_Studio_XIAO_Series:XIAO-RP2040-SMD`
the list has been updated to include SW52 and U2, so footprint selection is done for both halves

![Cherry MX switch and XIAO RP2040 footprint assignments](journal%20image/j04_04_switch-and-controller-footprints.png)

i updated the PCB from the schematic and it resulted in 106 footprints being added without warnings and errors
this updated the switches, diodes and controllers into the PCB editor
this is the result of an import, it doesn’t indicate that the schematic or the PCB has passed the rules

![PCB update showing 106 footprints added and no update warnings or errors](journal%20image/j04_05_pcb-update-results.png)



## 11 November 2026 — Journal 05: Moving the switches around

**time spent: 4 hours — estimated**

I started rearranging the imported components in the PCB editor.
Initially, the two switch groups were located in narrow columns while the diodes were positioned off to the sides.
Also, the controllers were separate from the switches and thin connection lines were stretching across the layout.

![The initial positioning of switches, diodes, and controllers](journal%20image/j05_01_initial-switch-placement.png)

Then I made a staggered layout of the right switch group adding three switches to its bottom edge for the thumb region.
I then relocated the diodes of the right group next to the switches and placed the controller on the upper side.

The left group was still in the previous narrow configuration with the diodes positioned off to the sides.
Thus, only one side of the board had achieved this arrangement at this stage.

![One half is now rearranged in staggered rows with diodes positioned nearby](journal%20image/j05_02_rearranged-half-and-diodes.png)


i checked the full board in 3D for the switch holes, pads and diode position simultaneously
preview of the board still had one large rectangular board encompassing both sets of footprints, as i had not designed the new shape of the board at that time
switches and controllers modules are not shown as the fitted components; this is only a PCB preview

![Full board 3D preview showing both groups of footprints](journal%20image/j05_03_full-board-3d-preview.png)

then i viewed the re-arranged group from an angle on the diode side
this view helped me to see how the bodies of the diodes would be distributed on the switch locations
this was just a visualization step as i still had to check the actual components' placement and spacing for the keycaps

now i moved to the other side of the board and work on its edges as the routing of copper tracks was not done

![Preview of the re-arranged group from the diode side](journal%20image/j05_04_angled-diode-side-preview.png)



## 11 November 2026 — Journal 06: Finishing the placement

**time spent: 5 hours — estimated**

then i proceeded with moving the left switch group to a wider layout, which would match the right one
both switch groups now had their respective keyboards and three switches at the bottom row
most of the components on the left side - the diodes and the controller - were located outside the layout

![Two switch groups in wider layouts](journal%20image/j06_01_both-half-switch-layouts.png)

first, i moved the left XIAO footprint to the upper inner part, near the border between the two sides
this way, both controllers were moved closer to the switch groups they controlled
the left controller was included into the layout in this manner

![Moving the left controller to the inner edge](journal%20image/j06_02_controller-moved-to-inner-edge.png)

finally, i moved the left diodes around the left switch group
these components were now located beside the keyboard instead of being stacked outside the group
there were still connection lines spanning over both halves, which means that it is just placement of components without routing


![Diodes distributed around the switches in both keyboard halves](journal%20image/j06_03_diodes-distributed-around-switches.png)

I adjusted the positions of the three bottom switches on the left side and brought the thumb cluster closer to the center gap.
As compared to the previous image, the thumb clusters are closer to the inner part of the keyboard
I still had to make sure that the spacing of the real switches and the keycaps was right.

![Left thumb key cluster moved toward the center](journal%20image/j06_04_left-thumb-cluster-repositioned.png)

I proceeded with drawing the board boundaries around the key clusters,
which were characterized by the sloping bottom edges and the notched middle part, rather than just one large rectangular one, shown in the previous image.

It was a draft, I had to see whether the boundaries made a valid board and left enough space for the components and USB connectors.
The routing was my next task.

![Contours of the board around the keyboard halves](journal%20image/j06_05_keyboard-board-contours.png)


## 11 November 2026 — Journal 07: Routing the board

**time spent: 5 hours — estimated**

i began this process with the switches, diodes and controllers placed within the board outline
the figure below shows the rectangle-shaped outer board outline and multiple pointed cutouts in the middle of the layout
there were also some connection lines to be seen prior to routing

![Layout before routing with the middle openings shown](journal%20image/j07_01_layout-and-central-cutouts.png)

the second figure below shows the tracks being drawn between the switch pads, diodes and controllers pads on both sides
the red and blue tracks represent the copper layers
the layout has thus been taken from connection lines to routed tracks

![Routed tracks on the front and back copper layers](journal%20image/j07_02_routed-front-and-back-tracks.png)

after importing the routing session into the design, the program indicated that it was imported and merged successfully
the status indicated 404 pads, 22 vias, 633 track segments and 88 nets, with zero unrouted connections

this indicated that there were no unrouted connections for this design, but it did not mean passing the design rule check
some checks such as track spacing and distance from the board edges have to be done yet


![Routing statistics with zero unrouted connections from imported design](journal%20image/j07_03_imported-routing-statistics.png)

i added GND zones on F.Cu and B.Cu
with 0.5mm clearance, 0.25mm min width, thermal connections with 0.5mm spacing and spoke width 0.5mm
corner smoothing is set to none, while island removal is always

![GND zone parameters on both copper layers](journal%20image/j07_04_ground-zone-settings.png)

i filled the zones and could see the copper in the vicinity of tracks and pads on both sides of the middle openings
there are spaces between the pads and tracks visible within the fill
need to check the GND connection after fill and perform board checks

![Filling GND zones with copper around the routed keyboard layout](journal%20image/j07_05_filled-ground-zones.png)

i opened the routed board in 3D to inspect the holes, diode models and center openings altogether
it still shows there are parts of the board connecting the two key areas, meaning it is not yet separated into two movable boards

I have to figure out that mechanical aspect of the split design before proceeding with the circuit board.
This was just a routed PCB preview; there was no physical board at all yet.

![3D preview of the routed board and central openings](journal%20image/j07_06_routed-board-3d-preview.png)

## 11 November 2026 — Journal 08: Adding mounting holes

**time spent: 5 hours — estimated**

i modified the top centre area to create a wider rectangular cut-out around the controller footprints
the point-shaped holes lower down in the middle remained intact
the tracks and the copper fills were already created before i modified this area

![Board with the modified top-centre recess](journal%20image/j08_01_revised-top-centre-recess.png)

the following illustration is showing the rounded corners of this upper cut-out and the copper fills around both key groups
that way i got another opportunity to see how the modified board edges relate to the layout
this was only a visual check, but not the final step to declare the board as ready for manufacturing

![Modified outline and copper fills around both keyboard groups](journal%20image/j08_02_outline-and-copper-fill-overview.png)

four mounting holes were added to the schematic and labeled H1 to H4
these would be my next target to move to the PCB layout

![Four mounting hole symbols in the schematic](journal%20image/j08_03_four-mounting-hole-symbols.png)

i chose `MountingHole:MountingHole_3.2mm_M3` for all four holes
this is a 3.2 mm clearance hole for M3 screws without any copper pads surrounding it
this determines the hole size, although sufficient space is required around the screw heads and spacers as well

![M3 mounting hole footprints assigned to H1 through H4](journal%20image/j08_04_m3-mounting-hole-footprints.png)

after updating the PCB, the new hole footprints became visible collectively outside of the board on the left
the holes were imported but not yet placed correctly, meaning i had to place each individual hole on the board

![New mounting hole footprints outside the board prior to placing](journal%20image/j08_05_mounting-holes-imported-to-pcb.png)

i placed one hole close to each of the four corners of the board, avoiding the central holes
the overview now includes all four holes, switches, controllers, track paths and copper fill
these locations must still be in alignment with the mounting posts in the case


![Four mounting holes positioned close to the outer corners](journal%20image/j08_06_mounting-holes-at-outer-corners.png)

i viewed the top side on the 3D viewer and saw the four corner holes and modified top cutout
the switch holes and controller pads are visible also
the material connecting the two parts remains at the center holes

![Preview of the top side on the 3D viewer with four corner holes](journal%20image/j08_07_top-side-3d-preview.png)

from the angled view on the diode side, i saw the holes close to the diode and routed circuit boards
even before i build it, i have to ensure the screw head clearance, copper and board edges, etc.
this is just preview of my design since i haven't yet assembled and tested it

![Angled preview of the diode side of the board with mounting holes](journal%20image/j08_08_angled-diode-side-preview.png)

## 12 November 2026 — Journal 09: Making the case model

**time spent: 4 hours — estimated**

i began the case CAD by inserting the PCB as a reference
the chosen model depicts both groups of switches, diode bodies located underneath the board and the mounting holes in the corners
thus i had to build a board-shaped form in order to create the tray

![Selected PCB model showing both switch groups and the underneath components](journal%20image/j09_01_pcb-reference-in-cad.png)

i created a tray with a raised border in the form of a rectangle
this was the first design of the case without the further openings and centre rib

![First CAD tray with the raised perimeter rim](journal%20image/j09_02_initial-case-tray.png)

i inserted the PCB inside the tray in order to compare the board edges and the case walls
in such way i could see how the two models look together; however, the CAD view is not an indicator that the board itself will fit
the reference also should be compared to the final PCB outline

![PCB reference inserted inside the tray](journal%20image/j09_03_pcb-aligned-with-tray.png)

i took one of the corner mounting holes as the centre point for a circle sketch
this became the reference for creating a mounting post underneath the board
taking into account the hole location allowed me to align

![Circular sketch centred on a PCB mounting hole](journal%20image/j09_04_mounting-circle-sketch.png)

the close-up reveals a small round post in the mounting area
it appears aligned in the model, but i had not verified the actual screw/spacer in the part yet
the post diameter and its clearance still needs to be confirmed before printing

![Detail of the mounting post at a corner location](journal%20image/j09_05_corner-mounting-post-detail.png)

i modified the case design by creating a wide aperture along the top edge and a narrow rib from the bottom area separating the two regions
and i viewed it in an orientation with the PCB visible to understand the new design around the PCB

![Modified Case with PCB Visible](journal%20image/j09_06_revised-case-with-pcb.png)

i removed the PCB to get a better view of the inner surfaces of the case
this image reveals the two recessed areas, the middle rib and mounting posts without the obstruction of the PCB

i have not done any testing or printing on this case yet
i will have to verify the shape of the PCB, the mounting holes, space available below the diodes, and room for USB connections

![Inside of the case with the PCB not visible](journal%20image/j09_07_case-interior-without-pcb.png)


## 12 November 2026 — Journal 10: Checking the cost

**time spent: 6 hours — estimated**

I have obtained the quotation for five FR-4 boards with two layers from JLCPCB.
From the website, the board size was 256.5 x 159 mm. The cost for the boards was $19.70 while the cost for engineering was $4.
The cost of the board would be $23.70 while that of two-day build would be zero.

The cost of shipping was estimated at $31.69. This means that the total cost of the boards and shipping will be $55.39.
This was the quotation before checkout when I have not yet made any order.

![JLCPCB quotation for five boards and shipping cost](journal%20image/j10_01_jlcpcb-fabrication-and-shipping-quote.png)

I have entered the components on `bom.csv`. Then adjusted the costs of the components to US dollar.
This is the old screenshot with $50.84 cost for the components, switches are not priced yet. This has the $23 set aside for the PCB.

![USD bill of materials before switch pricing](journal%20image/j10_02_bom-before-switch-pricing.png)

i found a 150-pc pack of LHGJFKO three-pin switches priced at ₹1,699
i took the listed price without using the coupon discount at the same rate of ₹93.8075 per US dollar for the remaining BOM entries
this comes out to $18.11 for the pack and makes the CSV total $68.95

for the keyboard i will use 52 switches; the above price is for the entire pack of 150 switches
the CSV cost will remain the same as $23 PCB cost and excludes the quoted shipping charges, case printing, mounting hardware, cable and the required hub

![Amazon listing of the 150-switch pack with ₹1,699 cost](journal%20image/j10_03_amazon-switch-pack-price.png)

i also looked up the price of Robu listing of the XIAO RP2040
as per the screenshot, one such controller would be ₹529 including GST, but it is currently out of stock
two controllers are needed, hence i have to find them before purchasing

The other issue I must take care of is selecting diodes; the one specified in the BOM has a different package than the DO-35 through-hole part that I used on the PCB
I need either to get a matching diode or make changes to the footprint before ordering them

![Robu listing showing the XIAO RP2040 price and availability](journal%20image/j10_04_robu-controller-price-and-stock.png)

## 12 November 2026 — Journal 11: Basic firmware demo

**Time spent: 2 hours — estimated**

I've written a basic Arduino sketch into `firmware/firmware.ino` before working on the keyboard.
`KEYBOARD_HALF` variable selects the pin map for U1 or U2 since both controllers have different row/column pin mapping.
Both versions have 5 rows, 6 columns, and 26 keys (empty cells are not used).

Pin arrays use RP2040 GPIOs numbers, not D numbers as marked on the board.
Columns use input pull-ups and keyboard USB output is configured in the code.
This version assumes the separate USB connections for both halves.


![Firmware Setup with the two controller pin maps and debounce configuration](journal%20image/j11_01_firmware-pin-maps-and-setup.png)

the loop sets one row low at a time and checks its columns, then proceeds to the next row
it detects changes and waits 10 ms before accepting the reading to ensure that the press is stable
each new press is recognized and transmits one lowercase letter through USB

the letters are sent from a to z in matrix order, which allows me to see which keypress position triggers
at the moment both halves use the same demo letters, this is not the final keyboard layout and does not include layers or held keys

both pin configurations passed a C++ syntax test with Arduino and keyboard stubs, which is just a basic validation on the computer side
now I have to compile the code for the real XIAO RP2040 and test each half on hardware
one way of testing will be to connect the row1 and col1 on a blank controller and see if it types a letter a in a text editor, which I have not done yet

![Matrix scan loop, debounce routine, and USB keyboard sending routine](journal%20image/j11_02_matrix-scanning-and-usb-output.png)