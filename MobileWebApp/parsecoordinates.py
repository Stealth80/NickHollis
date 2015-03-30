#!usr/bin/env/ python3

"""
written by: Shoba Dickinson
shobagowda@uky.edu

this script should be run using python parsecoordinates.py mapFile.kml
where mapFile.kml is the kml file that has the coordinates you need

The coordinates of all things labeled as polygons will be written, along
with the name you gave the polygon, to the screen and to a file named coord.txt
"""



import sys
import re

fp = open(sys.argv[1], 'r')
nf = open('coord.txt', 'w')

polygon = 0

for line in fp:
    result = re.search('\<name\>(.+?)\<\/name\>', line)
    if result:
        name = result.group(1)
        polygon = 0

    result = re.search('\<Polygon\>', line)
    if result:
        polygon = 1

    result = re.search('\<coordinates\>(.+?)<\/coordinates\>', line)
    if result:
        coordinates = result.group(1)
        print name
        print >> nf, name
        coordinate_list = coordinates.split(' ')
        for coord in coordinate_list:
            c = [ float(x) for x in coord.split(',') ]
            c.pop()
            c.reverse()
            print "new google.maps.LatLng(%f, %f)," % (c[0], c[1]) 
            print >> nf, "new google.maps.LatLng(%f, %f)," % (c[0], c[1]) 

nf.close()
fp.close()
