CF1			= -file-line-error 
CF3			= -s nomencl.ist -o main.nls
FILE		=	main
REM1		=	*.aux *.bbl *.blg *.bst *.glg *.glo *.gls *.ilg *.ist *.lof *.lol *.lot *.nlo *.nls *.out *.tdo *.toc *.xdy 
REM2		= *.log ${FILE}.pdf

##		COMPILING FUNCTIONS
build:  
	pdflatex ${CF1} ${FILE}.tex
small:
	pdflatex ${CF1} ${FILE}.tex
	pdflatex ${CF1} ${FILE}.tex
index: bib glossary abbreviation
full:	clean build index small postclean

##		CLEANING FUNCTIONS
clean:	preclean	postclean
preclean:	
	rm -f ${REM2} >> build.log
postclean:
	rm -f ${REM1} >> build.log

#SPECIAL BUILDS
bib:
	bibtex main
glossary: 
	makeglossaries main #compile glossary
abbreviation:
	makeindex main.nlo -s nomencl.ist -o main.nls	#Compiles abbreviations

