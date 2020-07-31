#!/usr/bin/env python2
import pyg4ometry

#--------------------------------------------------------------------------#
r = pyg4ometry.gdml.Reader("../build/apartment.gdml")
l = r.getRegistry().getWorldVolume()
v = pyg4ometry.visualisation.VtkViewer()
v.addLogicalVolume(l)
v.exportOBJScene("apartment.obj")
