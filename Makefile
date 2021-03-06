# output binary
BIN := rt

SRCDIR_RT := src
SRCDIR_GUI := gui
PERFDIR := perf

VPATH := $(SRCDIR_RT):$(SRCDIR_GUI)

# intermediate directory for generated object files
OBJDIR := .o
# intermediate directory for generated dependency files
DEPDIR := .d


# source files
SRCS_RT := $(wildcard $(SRCDIR_RT)/*.cpp)
SRCS_GUI := $(wildcard $(SRCDIR_GUI)/*.cpp)
SRCS := $(SRCS_RT) $(SRCS_GUI)
# object files, auto generated from source files

OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SRCS)))
# dependency files, auto generated from source files
DEPS := $(patsubst %.cpp,$(DEPDIR)/%.d,$(notdir $(SRCS)))

# compilers (at least gcc and clang) don't create the subdirectories automatically
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS)) >/dev/null)

# C++ compiler
CXX := g++
# linker
LD := ld

# C++ flags
CXXFLAGS := #-std=c++11
# C/C++ flags
OPTFLAGS :=  -O3
CPPFLAGS := -g $(OPTFLAGS) -Wall -Wextra `wx-config --cxxflags` -I$(SRCDIR_RT) #-pedantic 
# linker flags
#LDFLAGS := -L/usr/lib/x86_64-linux-gnu -lpthread -lwx_gtk2u_xrc-3.0 -lwx_gtk2u_html-3.0 -lwx_gtk2u_qa-3.0 -lwx_gtk2u_adv-3.0 -lwx_gtk2u_core-3.0 -lwx_baseu_xml-3.0 -lwx_baseu_net-3.0 -lwx_baseu-3.0 -lc
LDFLAGS := `wx-config --libs` -ljsoncpp
# flags required for dependency generation; passed to compilers
DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td

# compile C source files
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS)  -c -o $@ 
# compile C++ source files
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ 
# link object files to binary
LINK.o = $(CXX) -o $@ $(LDFLAGS) $(LDLIBS)
# precompile step
PRECOMPILE =
# postcompile step
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all: $(BIN)

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)
	$(RM) $(BIN)
	$(RM) $(PERFDIR)/perf $(PERFDIR)/gmon.out  $(PERFDIR)/perflog
	

.PHONY: perf
perf: $(PERFDIR)/perf
	cd $(PERFDIR); ./perf ../rt.json; gprof ./perf gmon.out > perflog

$(PERFDIR)/perf: $(PERFDIR)/rt_perf.cpp $(SRCS_RT)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -pg -o $@  $^ -ljsoncpp

$(BIN): $(OBJS)
	$(CXX) -o $@  $^ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

.PRECIOUS = $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(DEPS)
