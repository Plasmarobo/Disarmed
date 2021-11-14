.\avrdude -v -p t85 -c usbasp-clone -B5 -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m -U 
.\avrdude -v -p t85 -c usbasp-clone -B5 -U flash:w:LEDMCUPOC.ino.tiny8.hex