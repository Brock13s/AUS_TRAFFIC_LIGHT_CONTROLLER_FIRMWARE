# AUS_TRAFFIC_LIGHT_CONTROLLER_FIRMWARE
----IN PROGRESS----
This is firmware and other junk to control a australian traffic light

Here is a schematic as to how it gets connected

---CAUTION: BE CAREFUL WITH WORKING WITH 115V TO 240V WIRING, DEATH CAN OCCUR IF YOU DO NOT KNOW WHAT THE HELL YOU ARE DOING ALWAYS ENSURE WORKING WITH THE POWER OFF AND BE MINDFUL OF CAPACITORS ALTHOUGH THE TRAFFIC LIGHT DOES NOT USE CAPACITORS NOR CONTAINS THEM.

My traffic light has 5 wires, 1 earth, 1 neutral and 3 live which goes to each lights. The earth from the traffic light goes to the earth on the plug, the neutral of the traffic light goes to the plugs neutral(Note the lights are shared to neutral so yes there is only one wire) and the live from the plug connects to the con screw terminal on each relay except for the last unused relay. Then on each relay connect each light live wire to the NO(normally open) screw terminal on the relay so ensure that each color light uses a seperate relay :)

![circuitschematiz_schem](https://github.com/Brock13s/AUS_TRAFFIC_LIGHT_CONTROLLER_FIRMWARE/assets/48967600/cdcd3144-3d1b-405e-b2b4-960b74552c65)
