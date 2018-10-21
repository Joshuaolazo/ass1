#!/bin/sh

#  Script.sh
#  l,m,
#
#  Created by Joshua Olazo on 10/21/18.
#  Copyright © 2018 Joshua Olazo. All rights reserved.


cat movie_metadata.csv | ./simpleCSVsorter -c movie_title > sortedmovies.csv
