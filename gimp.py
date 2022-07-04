#!/usr/bin/python

from gimpfu import *

def dumpGroup(g):
    for l in g.layers:
        if isinstance(l,gimp.GroupLayer):
            dumpGroup(l)
        else:
            filename = "/home/opensuse/Xelu_Free_Controller&Key_Prompts/Keyboard & Mouse/Light/"
            filename += l.name.replace("Dark", "Light")
            print l.name, l.offsets
            print l.name.replace("Dark","Light")


image=gimp.image_list()[0]
dumpGroup(image)

main()
