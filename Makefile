CXX          ?= g++
AR           ?= ar
CPPFLAGS     += -DNDEBUG=1
CXXFLAGS     += -pthread -std=c++17 -g -O2 -Wall -Wextra -Werror -pedantic
LDFLAGS      += -pthread

MACHINE      := $(shell $(CXX) $(CPPFLAGS) $(CXXFLAGS) -dumpmachine)
ifeq ($(findstring linux,$(MACHINE)),linux)
CXXFLAGS     += -fdata-sections -ffunction-sections
LDFLAGS      += -Wl,--gc-sections
LDFLAGS      += -static-libstdc++ -static-libgcc
endif
ifeq ($(findstring x86_64,$(MACHINE)),x86_64)
CXXFLAGS     += -march=core-avx2
endif

OUT_DIR      := build
TARGETS      := snappy_benchmark

all: $(TARGETS)
.PHONY: all

clean:
	rm -rf $(TARGETS) $(OUT_DIR)
.PHONY: clean

snappy_benchmark: $(OUT_DIR)/snappy_benchmark.o \
$(OUT_DIR)/libsnappy_104.a \
$(OUT_DIR)/libsnappy_113.a \
$(OUT_DIR)/libsnappy_1110.a \
$(OUT_DIR)/libsnappy_122.a \
$(OUT_DIR)/libsnappy_121.a
	@echo Linking $@
	@mkdir -p $(@D)
	@$(CXX) $(LDFLAGS) $^ -o $@

SNAPPY_104_SRCS := $(wildcard snappy-1.0.4/*.cc)
SNAPPY_104_OBJS := $(addprefix $(OUT_DIR)/snappy_104/,$(SNAPPY_104_SRCS:.cc=.o))
SNAPPY_113_SRCS := $(wildcard snappy-1.1.3/*.cc)
SNAPPY_113_OBJS := $(addprefix $(OUT_DIR)/snappy_113/,$(SNAPPY_113_SRCS:.cc=.o))
SNAPPY_1110_SRCS := $(wildcard snappy-1.1.10/*.cc)
SNAPPY_1110_OBJS := $(addprefix $(OUT_DIR)/snappy_1110/,$(SNAPPY_1110_SRCS:.cc=.o))
SNAPPY_121_SRCS := $(wildcard snappy-1.2.1/*.cc)
SNAPPY_121_OBJS := $(addprefix $(OUT_DIR)/snappy_121/,$(SNAPPY_121_SRCS:.cc=.o))
SNAPPY_122_SRCS := $(wildcard snappy-1.2.2/*.cc)
SNAPPY_122_OBJS := $(addprefix $(OUT_DIR)/snappy_122/,$(SNAPPY_122_SRCS:.cc=.o))

$(OUT_DIR)/libsnappy_104.a: $(SNAPPY_104_OBJS)
	@echo Archiving $@
	@$(AR) rcs $@ $^
$(OUT_DIR)/libsnappy_113.a: $(SNAPPY_113_OBJS)
	@echo Archiving $@
	@$(AR) rcs $@ $^
$(OUT_DIR)/libsnappy_1110.a: $(SNAPPY_1110_OBJS)
	@echo Archiving $@
	@$(AR) rcs $@ $^
$(OUT_DIR)/libsnappy_121.a: $(SNAPPY_121_OBJS)
	@echo Archiving $@
	@$(AR) rcs $@ $^
$(OUT_DIR)/libsnappy_122.a: $(SNAPPY_122_OBJS)
	@echo Archiving $@
	@$(AR) rcs $@ $^

$(OUT_DIR)/snappy_104/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -fno-exceptions -fno-rtti -DHAVE_CONFIG_H=1 -Dsnappy=snappy_104 -c $< -o $@
$(OUT_DIR)/snappy_113/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -fno-exceptions -fno-rtti -DHAVE_CONFIG_H=1 -Dsnappy=snappy_113 -c $< -o $@
$(OUT_DIR)/snappy_1110/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -fno-exceptions -fno-rtti -DHAVE_CONFIG_H=1 -Dsnappy=snappy_1110 -c $< -o $@
$(OUT_DIR)/snappy_121/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -fno-exceptions -fno-rtti -DHAVE_CONFIG_H=1 -Dsnappy=snappy_121 -c $< -o $@
$(OUT_DIR)/snappy_122/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -w -fno-exceptions -fno-rtti -DHAVE_CONFIG_H=1 -Dsnappy=snappy_122 -c $< -o $@
$(OUT_DIR)/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
