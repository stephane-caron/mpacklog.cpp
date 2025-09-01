# Makefile for mpacklog.cpp targets
#
# SPDX-License-Identifier: Apache-2.0

DOCSDIR = docs
DOCSHTML = docs/html
DOXYGEN = doxygen

# Help snippet from:
# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
.PHONY: help
help:
	@grep -P '^[a-zA-Z0-9_-]+:.*? ## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-24s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean:  ## remove all generated files
	rm -rf $(DOCSHTML)

.PHONY: docs
docs:  ## build the documentation
	$(DOXYGEN) $(DOCSDIR)/Doxyfile

.PHONY: open
docs-open:  ## open the locally built documentation in the default Web browser
	xdg-open $(DOCSHTML)/index.html
