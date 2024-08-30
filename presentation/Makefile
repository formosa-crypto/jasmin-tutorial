TARGETS = main notes
TEXSOURCES = main.tex slides.tex macros.tex notes.tex
FIGURES = *.png
BEAMERFILES = beamercolorthemeru.sty beamerfontthemeru.sty beamerinnerthemeru.sty beamerouterthemeru.sty beamerthemeru.sty

all: $(TARGETS)

$(TARGETS): $(TEXSOURCES) $(FIGURES) $(BEAMERFILES)
	pdflatex $@.tex
	pdflatex $@.tex

.PHONY: clean

clean:
	-rm -f main.aux main.bbl main.blg main.log main.nav main.out main.pdf \
		main.snm main.toc main.vrb
	-rm -f notes.aux notes.bbl notes.blg notes.log notes.nav notes.out \
		notes.pdf notes.snm notes.toc notes.vrb
	-rm -f macros.aux
	-rm -f slides.aux
