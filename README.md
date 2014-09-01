Light_Painters_Palette
======================
Arduino Code for the Light Painters Palette V1.0
by JD Ritchey
9-1-2014

This program incorporates a 3 wide slide switch, 2 potentiometers and an IR 
receiver for user input.  The three slide switches put the board into various 
modes.  

Program 	Switch 1	Switch 2	Switch 3	Program Description
   1	          High	          High	          High	         Nothing yet!
   2	          High         	  High      	  Low	         Remote Control
   3	          High	          Low	          High	         Nothing yet!
   4	          High	          Low	          Low	         Fade between Colors Selected with 8
   5	          Low	          High	          High	         On-All On Single Color
   6	          Low	          High	          Low	         Fade between Colors Selected with 8, 
                                                                 but fades to black between
   7	          Low	          Low	          High	         On-Off Single Color
   8	          Low	          Low	          Low	         Single Color Select

Special thanks to all the authors of the LED fading and IR Receiver code!  This wouldn't have been 
possible without you!
