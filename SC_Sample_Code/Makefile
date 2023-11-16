# make でコンパイル
# make clean で生成ファイルの削除

PROGNAME := Feedback
SRCDIR := src
OUTDIR := build
TARGET := $(OUTDIR)/$(PROGNAME)
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OUTDIR)/,$(patsubst %.cpp,%.o,$(SRCS)))
#$(warning $(OBJS))

CC = g++
CFLAGS = -Wall -O2

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o:%.cpp
	@if [ ! -e $(@D) ]; then mkdir -p $(@D); fi
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OUTDIR)