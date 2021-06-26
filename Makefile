TARGET = K
SRCS = main.cpp snake.cpp

CPPSRCS = $(filter %.cpp,$(SRCS))
OBJS += $(CPPSRCS:%.cpp=%.o)
Q := @

COMMAND  = $(if $(v),$1,$(if $(2), @echo $2 && $(1), @$1))
CXXFLAGS := -Wall -Wno-format-security -Wno-pointer-arith -g -O2 --std=c++11
LIBS := -lncurses

.PHONY: build
build: $(TARGET)
	$(Q)echo "Build complete."

.PHONY: clean
clean:
	$(call COMMAND, rm -f $(TARGET) $(OBJS) test, "Cleaning" )
	$(Q)echo "Clean complete."


$(TARGET): $(OBJS)
	$(call COMMAND, g++ $(CXXFLAGS) -o $@ $^ $(LIBS), "Linking\t$@")

%.o: %.cpp
	$(call COMMAND, g++ $(CXXFLAGS) -o $@ -c $<, "Compiling\t$@")