#!/usr/bin/python

from gimpfu import *
import os

f1 = open('layer-map.txt', 'w')

def getLayers(g):
    for l in g.layers:
        if isinstance(l,gimp.GroupLayer):
            getLayers(l)
        else:
            print l.name, l.offsets
            print >> f1, l.name, l.offsets
def start():
    image=gimp.image_list()[0]
    getLayers(image)
    message = "Successfully printed the coordinates to: " + os.path.realpath(f1.name)
    pdb.gimp_message(message)
    f1.close()

register(
  "LayerCoordinates",
  "Grabs all layers in the image and prints their coordinates",
  "Grabs all layers in the image and prints their coordinates",
  "Shroomerian",
  "GNU General Pulbic License",
  "2022",
  "LayerCoordinates",
  "*",
  [],
  [],
  start,
  menu="<Image>/Filters/LayerCoordinates"
)

main()
