# Drinko
An Arduino based drinking game

*** NOTE: This code and schematics are published for informational purposes only ***

My buddy DH wanted to create a wooden replica of Plinko from "The Price Is Right" as a drinking game for a parry.  Then we got a microcontroller, and went next level: an arcade style lighting, and a scoring system that automatically dispenses alcohol.  

The core of the lighting controller circuit are five logic level zero cross solid state relays.  The scoring switches are arcade reed switches akin to what you find in a pinball machine.  The valve for the drink dispenser is a water valve from a dishwasher.  And to keep from wasting any valuable booze, there is a proximity switch to ensure there is a cup in the drink-o-matic before the machine pours.  

Dispensing the drink at a constant flow rate is critical to party success.  You either need a food grade pump (too expensive) or a soda keg with a keg style CO2 system (what we used).   
