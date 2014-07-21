import vigra
from vigra import graphs
from vigra import numpy
from vigra import Timer





numpy.random.seed(42)



# input
shape = [300, 200, 100]
data = numpy.random.rand(*shape).astype(numpy.float32)

with Timer("get seg"):
    seg = numpy.random.randint(5, size=shape[0]*shape[1]*shape[2])
    seg = seg.reshape(shape).astype(numpy.uint32)

with Timer("labelVolume"):
    seg = vigra.analysis.labelVolume(seg)


with Timer("findMinMax"):
    minLabel = int(seg.min())
    maxLabel = int(seg.max())

with Timer("ragOptions"):
    ragOptions = graphs.RagOptions(minLabel=minLabel, maxLabel=maxLabel, isDense=True,
                                   nThreads=1,  parallel=False)

with Timer("makeRAG"):

    adjListGraph  = graphs.listGraph()
    gridGraph = graphs.gridGraph(shape)


    affEdges = graphs._makeRag(graph=gridGraph, labels=seg, rag=adjListGraph, options=ragOptions)