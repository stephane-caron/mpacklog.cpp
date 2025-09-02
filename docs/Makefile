# Makefile for mpacklog.cpp targets
#
# SPDX-License-Identifier: Apache-2.0

DOXYGEN = doxygen
OUTPUTDIR = html

.PHONY: html
html:  ## build the documentation
	(cd .. && $(DOXYGEN) $(CURDIR)/Doxyfile)

.PHONY: clean
clean:  ## remove all generated files
	rm -rf $(OUTPUTDIR)

.PHONY: open
open:  ## open the locally built documentation in Firefox
	xdg-open $(OUTPUTDIR)/index.html
