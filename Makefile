DEBUG = FALSE

GCC      = nspire-gcc
AS       = nspire-as
GXX      = nspire-g++
LD       = nspire-ld
GENZEHN  = genzehn

SRC_DIR  = src
INC_DIR  = include
BUILDDIR = build
DISTDIR  = bin
EXE      = sokoban

GCCFLAGS = -Wall -W -marm -I$(INC_DIR)
LDFLAGS  =
ZEHNFLAGS = --name "sokoban"

ifeq ($(DEBUG),FALSE)
	GCCFLAGS += -Os
else
	GCCFLAGS += -O0 -g
endif

C_SRCS   = $(shell find $(SRC_DIR) -name '*.c')
CPP_SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
ASM_SRCS = $(shell find $(SRC_DIR) -name '*.S')

OBJS  = $(patsubst $(SRC_DIR)/%.c,$(BUILDDIR)/%.o,$(C_SRCS))
OBJS += $(patsubst $(SRC_DIR)/%.cpp,$(BUILDDIR)/%.o,$(CPP_SRCS))
OBJS += $(patsubst $(SRC_DIR)/%.S,$(BUILDDIR)/%.o,$(ASM_SRCS))

all: $(DISTDIR)/$(EXE).tns

# Objects
$(BUILDDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(GCC) $(GCCFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(GXX) $(GCCFLAGS) -c $< -o $@
	
$(BUILDDIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(AS) -c $< -o $@


# Linking
$(BUILDDIR)/$(EXE).elf: $(OBJS)
	@mkdir -p $(BUILDDIR)
	$(LD) $^ -o $@ $(LDFLAGS)


# Packaging
$(DISTDIR)/$(EXE).tns: $(BUILDDIR)/$(EXE).elf
	@mkdir -p $(DISTDIR)
	$(GENZEHN) --input $< --output $(BUILDDIR)/$(EXE).zehn $(ZEHNFLAGS)
	make-prg $(BUILDDIR)/$(EXE).zehn $@
	rm $(BUILDDIR)/$(EXE).zehn

clean:
	rm -rf $(BUILDDIR) $(DISTDIR)/$(EXE).tns
