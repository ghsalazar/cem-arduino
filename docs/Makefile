SRC_DIR = ../src
TARGETS = $(notdir $(patsubst %.md, %.html, $(wildcard $(SRC_DIR)/*.md)))
HTMLFLAGS = --filter pandoc-eqnos  -s --highlight-style espresso -f markdown --webtex


all: $(TARGETS)

%.html: $(SRC_DIR)/%.md
	# ../etc/mdweb/src/mdweave $< > $@
	cat $< | \
	pandoc	$(HTMLFLAGS)	-o $@
	
#%.md: $(SRC_DIR)/%.md
#	cp $< $@

.PHONNY: clean distclean

distclean:


clean:
	rm -f $(TARGETS)