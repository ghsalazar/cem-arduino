SRC_DIR = ../src
TARGETS = $(notdir $(patsubst %.md, %.html, $(wildcard $(SRC_DIR)/*.md)))
HTMLFLAGS = --filter pandoc-eqnos --highlight-style espresso -f markdown --webtex
DOCXFLAGS = --filter pandoc-eqnos --highlight-style espresso -f markdown


all: $(TARGETS)

%.html: $(SRC_DIR)/%.md
	sh ../etc/mdweb/src/mdweave $< |	pandoc	$(HTMLFLAGS)	-o $@

%.docx: $(SRC_DIR)/%.md
	sh ../etc/mdweb/src/mdweave $< |	pandoc	$(DOCXFLAGS)	-o $@

.PHONNY: clean distclean

distclean:


clean:
	rm -f $(TARGETS)