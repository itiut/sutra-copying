import matplotlib.pyplot as plt

decisionNode = dict(boxstyle='sawtooth', fc='0.8')
leafNode = dict(boxstyle='round4', fc='0.8')
arrow_args = dict(arrowstyle='<-')


def plotNode(nodeTxt, centerPt, parentPt, nodeType):
    createPlot.ax1.annotate(nodeTxt, xy=parentPt, xycoords='axes fraction',
                     xytext=centerPt, textcoords='axes fraction',
                     va='center', ha='center', bbox=nodeType, arrowprops=arrow_args)


def plotMidText(centerPt, parentPt, txtString):
    xMid = (parentPt[0] + centerPt[0]) / 2.0
    yMid = (parentPt[1] + centerPt[1]) / 2.0
    createPlot.ax1.text(xMid, yMid, txtString)


def plotTree(myTree, parentPt, nodeTxt):
    numLeafs = getNumLeafs(myTree)
    # treeDepth = getTreeDepth(myTree)
    firstStr = next(iter(myTree))
    global plotTree
    centerPt = (plotTree.xOff + (1.0 + float(numLeafs)) / 2.0 / plotTree.totalW,
                plotTree.yOff)
    plotMidText(centerPt, parentPt, nodeTxt)
    plotNode(firstStr, centerPt, parentPt, decisionNode)
    secondDict = myTree[firstStr]
    plotTree.yOff -= 1.0 / plotTree.totalD
    for key in secondDict.keys():
        if isinstance(secondDict[key], dict):
            plotTree(secondDict[key], centerPt, str(key))
        else:
            plotTree.xOff += 1.0 / plotTree.totalW
            plotNode(secondDict[key], (plotTree.xOff, plotTree.yOff), centerPt, leafNode)
            plotMidText((plotTree.xOff, plotTree.yOff), centerPt, str(key))
    plotTree.yOff += 1.0 / plotTree.totalD


def createPlot(inTree):
    fig = plt.figure(1, facecolor='white')
    fig.clf()
    axprops = dict(xticks=[], yticks=[])
    global createPlot
    createPlot.ax1 = plt.subplot(111, frameon=False, **axprops)
    global plotTree
    plotTree.totalW = float(getNumLeafs(inTree))
    plotTree.totalD = float(getTreeDepth(inTree))
    plotTree.xOff = - 0.5 / plotTree.totalW
    plotTree.yOff = 1.0
    plotTree(inTree, (0.5, 1.0), '')
    plt.show()

# def createPlot():
#     fig = plt.figure(1, facecolor='white')
#     fig.clf()
#     global createPlot
#     createPlot.ax1 = plt.subplot(111, frameon=False)
#     plotNode('a decision node', (0.5, 0.1), (0.1, 0.5), decisionNode)
#     plotNode('a leaf node', (0.8, 0.1), (0.3, 0.8), leafNode)
#     plt.show()


def getNumLeafs(myTree):
    numLeafs = 0
    firstStr = next(iter(myTree))
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if isinstance(secondDict[key], dict):
            numLeafs += getNumLeafs(secondDict[key])
        else:
            numLeafs += 1
    return numLeafs


def getTreeDepth(myTree):
    maxDepth = 0
    firstStr = next(iter(myTree))
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        thisDepth = 1
        if isinstance(secondDict[key], dict):
            thisDepth += getTreeDepth(secondDict[key])
        maxDepth = max(maxDepth, thisDepth)
    return maxDepth


def retrieveTree(i):
    listOfTrees = [
        {'no surfacing': {
            0: 'no',
            1: {'flippers': {
                0: 'no',
                1: 'yes'
            }}
        }},
        {'no surfacing': {
            0: 'no',
            1: {'flippers': {
                0: {'head': {
                    0: 'no',
                    1: 'yes'
                }},
                1: 'no'
            }}
        }}
    ]
    return listOfTrees[i]
