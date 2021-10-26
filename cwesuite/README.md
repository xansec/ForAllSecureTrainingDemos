# CWE Suite

This file is a proof-of-concept for discoverability of certain CWEs within Mayhem. Each documented CWE can be triggered using this file. To generate a binary for a particular CWE, say CWE121, you can run:

`$ make CWE121`

To make all basic CWEs:

`$ make basic`

Or to make everything:

`$ make`



### Notes

Some functions will inevitably trigger more than one CWE. This is due to the nebulous nature of CWEs - one issue can fall under the purview of multiple CWEs.

Example:
https://staging.internal.forallsecure.com/abrewer/cwesuite/913/1

