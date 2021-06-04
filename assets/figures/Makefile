SRCDIR = ../../src
TARGETS = $(patsubst %.dot, %.png, $(notdir $(wildcard $(SRCDIR)/*.dot)))

all: $(TARGETS)

%.png: $(SRCDIR)/%.dot
	dot	$<	-Tpng	-o $@