CC = avr-gcc
CXX = avr-g++

CHIP = atmega328p
CPUFREQ = 16000000
LIBS += -lm

C_SRCS   := $(shell find . -name "*.c")
CXX_SRCS := $(shell find . -name "*.cpp")
OBJS = $(CXX_SRCS:.cpp=.o) $(C_SRCS:.c=.o)
TARGET =midi
OPTIMIZATION = s -fpack-struct -fshort-enums -flto -ggdb3
WARNINGS = -Wall -Wextra -Wno-main
DEFINES = -DF_CPU=$(CPUFREQ)UL
INCDIRS = -Iarduino

LINKFLAGS += $(LIBDIRS) $(LIBS) -mrelax -mmcu=$(CHIP)
CFLAGS += -O$(OPTIMIZATION) $(WARNINGS) $(USERADD) -std=c99
CXXFLAGS += -O$(OPTIMIZATION) $(WARNINGS) $(USERADD)
CPPFLAGS += $(INCDIRS) -mmcu=$(CHIP) $(DEFINES) $(USERADDDEF)

DOWNLOADPATH = COM6
AVRDUDECHIP = atmega2560
PROGRAMMER = arduino
RATE = 115200

$(TARGET).hex : $(TARGET).elf Makefile
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf : $(OBJS) Makefile
	$(CXX) $(OBJS) -o $(TARGET).elf $(LINKFLAGS) $(CFLAGS)

$(OBJS) : Makefile

.PHONY : download

download : $(TARGET).hex Makefile
	avrdude -c $(PROGRAMMER) -p $(AVRDUDECHIP) -P $(DOWNLOADPATH) -b$(RATE) -U flash:w:$(TARGET).hex

.PHONY : upload

upload : Makefile
	avrdude -c $(PROGRAMMER) -p $(AVRDUDECHIP) -P $(DOWNLOADPATH) -b$(RATE) -U flash:r:device.hex:i

.PHONY : verify

verify : $(TARGET).hex Makefile
	avrdude -c $(PROGRAMMER) -p $(AVRDUDECHIP) -P $(DOWNLOADPATH) -b$(RATE) -U flash:v:$(TARGET).hex

.PHONY : size

size : $(TARGET).elf Makefile
	avr-size $(TARGET).elf

%.o : %.d Makefile

$(C_SRCS:.c=.d) : %.d : %.c Makefile
	@rm -f $@
	$(CC) $(CPPFLAGS) $< -M -o .$@~
	@sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < .$@~ > $@
	@rm -f .$@~

$(CXX_SRCS:.cpp=.d) : %.d : %.cpp Makefile
	@rm -f $@
	$(CXX) $(CPPFLAGS) $< -M -o .$@~
	@sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < .$@~ > $@
	@rm -f .$@~

include $(OBJS:.o=.d)

.PHONY : clean

clean : Makefile
	rm *.o *.elf *.hex *.d -f
