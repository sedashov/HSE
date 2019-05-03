def Dijkstra(graph, start):
    n = len(graph)
    discovered = [0] * n
    distance = [10000] * n
    distance[start] = 0
    for j in range(n):
        minDist = 10000
        index = None
        for m in range(n):
            if not discovered[m] and distance[m] < minDist:
                minDist = distance[m]
                index = m
        if minDist == 10000:
            return distance
        discovered[index] = 1
        for m in range(n):
            if distance[m] > distance[index] + graph[index][m] and\
                    not graph[index][m] < 0:
                distance[m] = distance[index] + graph[index][m]
    return distance
