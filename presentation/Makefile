TEXSOURCES = jasmin101.tex slides.tex macros.tex
BIBFILES = bib/*.bib
FIGURES = *.png
BEAMERFILES = beamercolorthemeru.sty beamerfontthemeru.sty beamerinnerthemeru.sty beamerouterthemeru.sty beamerthemeru.sty

jasmin101.pdf: $(TEXSOURCES) $(BIBFILES) $(FIGURES) $(BEAMERFILES)
	pdflatex jasmin101.tex
# bibtex jasmin101
	pdflatex jasmin101.tex
	pdflatex jasmin101.tex

.PHONY: clean

clean:
	-rm -f jasmin101.aux
	-rm -f jasmin101.bbl
	-rm -f jasmin101.blg
	-rm -f jasmin101.log
	-rm -f jasmin101.nav
	-rm -f jasmin101.out
	-rm -f jasmin101.pdf
	-rm -f jasmin101.snm
	-rm -f jasmin101.toc
	-rm -f macros.aux
	-rm -f slides.aux
