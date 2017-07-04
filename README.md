# Nullibadge

Source code for a community built unofficial Defcon 25 badge.

[About](http://nu.llify.com)

[Order a Badge](https://docs.google.com/forms/d/1BT1bi9LWtsvNwGjnZjbqTZsIYf-_CRmu9A9kopbBeFg)

![](http://media.giphy.com/media/JdMtXSfw2kj60/200.gif)

## Programming

### Install MPLabX 3.65
[Win](http://ww1.microchip.com/downloads/en/DeviceDoc/MPLABX-v3.65-windows-installer.exe)
[Lin](http://ww1.microchip.com/downloads/en/DeviceDoc/MPLABX-v3.65-linux-installer.tar)
[Osx](http://ww1.microchip.com/downloads/en/DeviceDoc/MPLABX-v3.65-osx-installer.dmg)

### Install XC8 1.42
[Win](http://ww1.microchip.com/downloads/en/DeviceDoc/xc8-v1.42-full-install-windows-installer.exe)
[Lin](http://ww1.microchip.com/downloads/en/DeviceDoc/xc8-v1.42-full-install-linux-installer.run)
[OSX](http://ww1.microchip.com/downloads/en/DeviceDoc/xc8-v1.42-full-install-osx-installer.dmg)

### GIT
git clone https://github.com/nullibadge/defcon2017.git

### Pickit3
Acquire one of these: https://www.amazon.com/Funny-DIY-Expert-Programmer-Development/dp/B01NBPCLSR/ref=sr_1_1?ie=UTF8&qid=1498755321&sr=8-1&keywords=pickit3

### Step by Step
1. Plug in your pickit3 to your computer
2. Open MPLab X
3. File -> Open Project -> Select your git folder
4. Select Clean Build from the Tool Bar (Looks like a Hammer with a Brush)
5. Click Production -> Set Project Configuration -> Customize
6. Under Conf:[default] -> Configuration Pane -> Hardware Tool Pane -> Hardware Tools you should see PICkit3 with a serial # 
7. Under Conf:[default] -> Configuration Pane -> Device -> Be sure to select PIC16LF18346

Note: Early dev boards used a non L version microcontroller. These could take higher voltages. The new ones cannot and have better battery life.

Note: You don't need to power the board with battery and shouldn't when programming them. You can turn off the battery power by toggling the switch on the bottom right of the badge.

8. Under Conf:[default] -> select PICkit3 -> Under Options Categories select Power -> Check Power target circuit from PICkit3 -> change the power to 3.25V. Anything higher than 3.6V will fry the L microcontroller and destroy your badge. 
9. Under Compiler Toolchain on the right click on XC8 1.42 and click apply then ok
10. Connect the PICKit3 to your badge. The arrow indicates the left most pin.

Here is a picture of proper placement.

![](https://i.imgur.com/vfNkun4.jpg)

10. Click the Green Play button to right of "Clean Rebuild"
11. Select your PICKit3. You may get a prompt about the having the right device selected. Ensure you are using the L version if you use a new revision (>rev1) of the badge. Click OK and the badge will program.



