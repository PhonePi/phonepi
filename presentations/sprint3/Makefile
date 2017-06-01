%.tex: %.md preamble.yml preamble.tex guillemots.hs
	pandoc $*.md preamble.yml --include-in-header=preamble.tex -s -S -t beamer -o $*.tex

%.pdf: %.tex
	xelatex $*.tex
	xelatex $*.tex

all: presentation.pdf 

.PHONY: all

clean: 
	rm *.pdf *.vrb *.toc *.nav *.log *.aux *.fdb_latexmk *.snm *.out
