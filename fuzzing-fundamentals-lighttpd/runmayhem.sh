#!/bin/bash

mayhem login

#vuln
mayhem run -f Mayhemfile.vuln .

#fixed
mayhem run -f Mayhemfile.fixed .
