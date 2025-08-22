DEBUG = FALSE

GCC = nspire-gcc
AS  = nspire-as
GXX = nspire-g++
LD  = nspire-ld
GENZEHN = genzehn

GCCFLAGS = -Wall -W -marm
LDFLAGS =
ZEHNFLAGS = --name "sokoban"

ifeq ($(DEBUG),FALSE)
	GCCFLAGS += -Os
else
	GCCFLAGS += -O0 -g
endif

EXE = sokoban
BUILDDIR = build
DISTDIR = bin

# Object files now go in $(BUILDDIR)
OBJS = $(patsubst %.c, $(BUILDDIR)/%.o, $(shell find . -name \*.c))
OBJS += $(patsubst %.cpp, $(BUILDDIR)/%.o, $(shell find . -name \*.cpp))
OBJS += $(patsubst %.S, $(BUILDDIR)/%.o, $(shell find . -name \*.S))

all: $(DISTDIR)/$(EXE).tns

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(GCC) $(GCCFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(GXX) $(GCCFLAGS) -c $< -o $@
	
$(BUILDDIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(AS) -c $< -o $@

$(BUILDDIR)/$(EXE).elf: $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(LD) $^ -o $@ $(LDFLAGS)

$(DISTDIR)/$(EXE).tns: $(BUILDDIR)/$(EXE).elf
	@mkdir -p $(DISTDIR)
	$(GENZEHN) --input $< --output $(BUILDDIR)/$(EXE).zehn $(ZEHNFLAGS)
	make-prg $(BUILDDIR)/$(EXE).zehn $@
	rm $(BUILDDIR)/$(EXE).zehn

clean:
	rm -rf $(BUILDDIR) $(DISTDIR)/$(EXE).tns
