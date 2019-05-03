class BinaryTree:
    def __init__(self):
        self.root = None
        self.height = 0

    def __len__(self):
        return self.height

    def insert(self, key):
        if not self.search(key):
            counterOfHeight = 0
            newElement = Node(key)
            elementToCheck = self.root
            while elementToCheck:
                newElement.parent = elementToCheck
                if newElement.key < elementToCheck.key:
                    elementToCheck = elementToCheck.left
                else:
                    elementToCheck = elementToCheck.right
                counterOfHeight += 1
            if newElement.parent:
                if newElement.key > newElement.parent.key:
                    newElement.parent.right = newElement
                    counterOfHeight += 1
                else:
                    newElement.parent.left = newElement
                    counterOfHeight += 1
            else:
                self.root = newElement
                counterOfHeight += 1
            if counterOfHeight > self.height:
                self.height = counterOfHeight

    def search(self, key):
        currentNode = self.root
        while currentNode and key != currentNode.key:
            if currentNode.key < key:
                currentNode = currentNode.right
            else:
                currentNode = currentNode.left
        if currentNode:
            return True
        return False

    def findMax(self):
        currentMax = self.root
        while currentMax.right:
            currentMax = currentMax.right
        return currentMax.key

    def findSecondMax(self):
        currentMax = self.root
        while currentMax.right:
            currentMax = currentMax.right
        if currentMax.left:
            currentMax = currentMax.left
            while currentMax.right:
                currentMax = currentMax.right
        else:
            currentMax = currentMax.parent
        return currentMax.key

    def inOrder(self, element):
        if element.left:
            self.inOrder(element.left)
        print(element.key)
        if element.right:
            self.inOrder(element.right)

    def printLeaves(self, element):
        if element.left:
            self.printLeaves(element.left)
        if not (element.left or element.right):
            print(element.key)
        if element.right:
            self.printLeaves(element.right)

    def printForks(self, element):
        if element.left:
            self.printForks(element.left)
        if element.left and element.right:
            print(element.key)
        if element.right:
            self.printForks(element.right)

    def printHalfForks(self, element):
        if element.left:
            self.printHalfForks(element.left)
        if (element.left and not element.right) or\
                (not element.left and element.right):
            print(element.key)
        if element.right:
            self.printHalfForks(element.right)


class Node:
    def __init__(self, key, right=None, left=None, parent=None):
        self.key = key
        self.right = right
        self.left = left
        self.parent = parent


