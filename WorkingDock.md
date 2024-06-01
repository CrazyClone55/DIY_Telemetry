Tapped PT-Can from the FEM (Front Electronics Module), using this [guide](https://f87.bimmerpost.com/forums/showthread.php?t=1722189)
Also tapped 12V and GND from the FEM.
ran those into a 5 conductor cable to the back

Can H and Can L are conneted to the can controller and then to the arduino
the 12v and GND are connected to the buck converter and then to the arduino sheild

used 2 rows on the sheild as a "power bus" for the converted 5v and GND

IR sensors are wired and mounted on the dust sheild of each wheel to get rotor temp
those each go into the arduino sheild

accelerometer is mounted inside the case
HC-12 module is mounted inside the case

need to put together a list of i2c addresses

need i2c multiplexer
